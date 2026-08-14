#include "stdafx.h"
#include "chinapres3Service.h"
#include "TransactionManager.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"
#include <sstream>
#include <set>
#include <map>

// ===================================================================
//                         //////// Revoke
// ===================================================================

chinapres3RevokeResultVO::Wrapper chinapres3Service::revoke(
	const chinapres3RevokeDTO::Wrapper& dto,
	const PayloadDTO& payload)
{
	auto resultVo = chinapres3RevokeResultVO::createShared();

	// ---- 1. ////////// ----
	auto medReqIds = dto->medicationRequestIds;
	if (!medReqIds || medReqIds->size() == 0) {
		resultVo->code = 400;
		resultVo->message = "Parameter cannot be empty, please pass medication request IDs";
		return resultVo;
	}

	auto now = SimpleDateTimeFormat::format();
	auto currentUser = payload.getUsername();

	// ---- 2. ////////////////////////////////////// ----
	// // prescription_no /////////////////// all-or-nothing ///
	std::map<std::string, std::vector<Ptrchinapres3MedicationRequestDO>> presGroups;

	for (auto& mid : *medReqIds) {
		auto midStr = std::string(mid.getValue(""));
		if (midStr.empty()) continue;

		auto req = medReqDAO.selectById(midStr);
		if (!req) {
			resultVo->code = 404;
			resultVo->message = "Medication request not found, ID=" + midStr;
			return resultVo;
		}
		if (req->getStatusEnum() != "ACTIVE") {
			resultVo->code = 404;
			resultVo->message = "Medication request not in issued status, current status="
				+ req->getStatusEnum() + ", ID=" + midStr;
			return resultVo;
		}

		auto presNo = req->getPrescriptionNo();
		presGroups[presNo].push_back(req);
	}

	// ---- 3. All-or-nothing ////////////////////// ----
	for (auto& entry : presGroups) {
		uint64_t dbCount = medReqDAO.countByPrescriptionNo(entry.first, "ACTIVE");
		if (entry.second.size() != dbCount) {
			resultVo->code = 400;
			std::ostringstream errMsg;
			errMsg << "Incomplete prescription: " << entry.first
				<< " has " << dbCount << " issued drug line(s) but only "
				<< entry.second.size() << " selected. Please revoke all or none.";
			resultVo->message = errMsg.str();
			return resultVo;
		}
	}

	// ---- 4. ////////////////////////////////////// ----
	// //////////////////// PREPARATION /////////////////////
	std::vector<Ptrchinapres3MedicationDispenseDO> allDispenses;

	for (auto& entry : presGroups) {
		for (auto& req : entry.second) {
			auto dispQuery = chinapres3MedicationDispenseQuery::createShared();
			dispQuery->medReqId = req->getId();
			dispQuery->statusEnum = "PREPARATION";
			dispQuery->isDeleted = "0";
			dispQuery->pageIndex = 1;
			dispQuery->pageSize = 1000;
			auto dispList = medDispDAO.selectWithPage(dispQuery);

			if (dispList.empty()) {
				resultVo->code = 409;
				resultVo->message = "Some medication has been dispensed or already revoked, cannot revoke. "
					"Medication request ID=" + req->getId();
				return resultVo;
			}

			for (auto& d : dispList) {
				allDispenses.push_back(d);
			}
		}
	}

	// ---- 5. ///////// ////////////////// ----
	try {
		TransactionManager tm(&medReqDAO, &medDispDAO, &chargeDAO);

		// 5a. ///////////////////// DRAFT
		for (auto& entry : presGroups) {
			for (auto& req : entry.second) {
				req->setStatusEnum("DRAFT");
				req->setUpdatedBy(currentUser);
				req->setUpdatedAt(now);
				medReqDAO.update(*req);
			}
		}

		// 5b. //////////////////// is_deleted = 1
		for (auto& d : allDispenses) {
			d->setIsDeleted("1");
			d->setUpdatedBy(currentUser);
			d->setUpdatedAt(now);
			medDispDAO.update(*d);
		}

		// 5c. ////////////////////// is_deleted = 1
		std::set<std::string> uniquePresNos;
		for (auto& entry : presGroups) {
			uniquePresNos.insert(entry.first);
		}
		for (auto& presNo : uniquePresNos) {
			auto chargeQuery = chinapres3ChargeItemQuery::createShared();
			chargeQuery->prescriptionNo = presNo;
			chargeQuery->isDeleted = "0";
			chargeQuery->pageIndex = 1;
			chargeQuery->pageSize = 1000;
			auto charges = chargeDAO.selectWithPage(chargeQuery);

			for (auto& c : charges) {
				c->setIsDeleted("1");
				c->setUpdatedBy(currentUser);
				c->setUpdatedAt(now);
				chargeDAO.update(*c);
			}
		}

		tm.commit();

		// ---- 6. ////////// ----
		v_int32 revokedMedCount = 0;
		for (auto& entry : presGroups) {
			revokedMedCount += static_cast<v_int32>(entry.second.size());
		}

		auto resultData = chinapres3RevokeResultDTO::createShared();
		resultData->revokedPrescriptionCount = static_cast<oatpp::Int32>(presGroups.size());
		resultData->revokedMedicationCount = revokedMedCount;

		auto presNoList = oatpp::Vector<oatpp::String>::createShared();
		for (auto& presNo : uniquePresNos) {
			presNoList->push_back(oatpp::String(presNo.c_str()));
		}
		resultData->revokedPrescriptionNos = presNoList;
		resultData->revokedAt = now.c_str();

		resultVo->success(resultData);
		resultVo->message = "Revoke completed successfully";
		return resultVo;

	} catch (const std::exception& e) {
		resultVo->code = 500;
		std::ostringstream errMsg;
		errMsg << "Transaction failed: " << e.what();
		resultVo->message = errMsg.str();
		return resultVo;
	}
}

// ===================================================================
//                         //////// Issue
// ===================================================================

chinapres3IssueResultVO::Wrapper chinapres3Service::issue(
	const chinapres3IssueDTO::Wrapper& dto,
	const PayloadDTO& payload)
{
	auto resultVo = chinapres3IssueResultVO::createShared();

	// ==================== 1. ////////// ====================
	auto encounterId = dto->encounterId;
	if (!encounterId || encounterId.getValue("") == "") {
		resultVo->code = 400;
		resultVo->message = "Parameter cannot be empty, please pass encounter ID";
		return resultVo;
	}
	// patientId removed from DTO: already present in med_medication_request, used directly
	auto signTargets = dto->signTargets;
	if (!signTargets || signTargets->size() == 0) {
		resultVo->code = 400;
		resultVo->message = "Parameter cannot be empty, please pass prescription list to sign";
		return resultVo;
	}

	// ==================== 2. ////////////////////////////////////// ====================
	std::vector<Ptrchinapres3MedicationRequestDO> validRequests;
	std::stringstream errStream;

	for (auto& target : *signTargets) {
		auto medReqId = target->medicationRequestId;
		if (!medReqId || medReqId.getValue("") == "") {
			resultVo->code = 400;
			resultVo->message = "Parameter cannot be empty, please pass prescription ID";
			return resultVo;
		}
		auto req = medReqDAO.selectById(medReqId.getValue(""));
		if (!req) {
			errStream << "Prescription record not found, prescription ID=" << medReqId.getValue("");
			resultVo->code = 404;
			resultVo->message = errStream.str();
			return resultVo;
		}
		auto status = req->getStatusEnum();
		if (status != "DRAFT") {
			errStream << "Prescription status disallows dispensing, current status=" << status
				<< ", prescription ID=" << medReqId.getValue("");
			resultVo->code = 400;
			resultVo->message = errStream.str();
			return resultVo;
		}
		// /////////ID//////
		auto reqEncounterId = req->getEncounterId();
		if (!reqEncounterId.empty() && reqEncounterId != encounterId.getValue("")) {
			resultVo->code = 400;
			resultVo->message = "Encounter ID mismatches prescription, prescription ID="
				+ medReqId.getValue("");
			return resultVo;
		}
		// patientId consistency no longer checked here:
		// patientId is derived from the medication request record,
		// and all sign targets must belong to the same encounter
		validRequests.push_back(req);
	}

	// ==================== 2b. All-or-nothing completeness check ====================
	// Group valid requests by prescription_no and verify every DRAFT drug line
	// under the same prescription is included in signTargets
	{
		std::map<std::string, v_int32> presCounts;
		for (auto& req : validRequests) {
			auto presNo = req->getPrescriptionNo();
			if (!presNo.empty()) {
				presCounts[presNo]++;
			}
		}
		for (auto& entry : presCounts) {
			uint64_t dbCount = medReqDAO.countByPrescriptionNo(entry.first, "DRAFT");
			if (static_cast<uint64_t>(entry.second) != dbCount) {
				std::ostringstream errMsg;
				errMsg << "Incomplete prescription: " << entry.first
					<< " has " << dbCount << " drug line(s) but only "
					<< entry.second << " selected. Please sign all or none.";
				resultVo->code = 400;
				resultVo->message = errMsg.str();
				return resultVo;
			}
		}
	}

	// ==================== 3. /////////////////////////////////////////////////////// ====================
	try
	{
		TransactionManager tm(&medReqDAO, &medDispDAO, &chargeDAO);
		auto now = SimpleDateTimeFormat::format();
		auto snowFlake = SnowFlake::getInstance();
		auto currentUser = payload.getUsername();
		auto orgId = payload.getId();

		std::vector<std::string> busNos;               // //////////////////////
		std::set<std::string> processedPrescriptions;  // ////////////////////////////////

		// ----- 3a. ////////////////////////ACTIVE -----
		for (auto& req : validRequests) {
			req->setStatusEnum("ACTIVE");
			req->setRxTypeCode("TCM");
			req->setUpdatedBy(currentUser);
			req->setUpdatedAt(now);
			medReqDAO.update(*req);
		}

		// ----- 3b. ////////////////////////////// medication_dispense -----
		// key://///// value:////////////////ID///////////////
		std::map<std::string, std::string> presNoToReqId;
		for (auto& req : validRequests) {
			chinapres3MedicationDispenseDO dispDO;
			dispDO.setId(std::to_string(snowFlake->nextId()));
			auto busNo = "BUS" + std::to_string(snowFlake->nextId());
			dispDO.setBusNo(busNo);
			busNos.push_back(busNo);
			dispDO.setStatusEnum("PREPARATION");        // ////////
			dispDO.setDispenseEnum("OUTPATIENT");       // //////////
			dispDO.setMedReqId(req->getId());
			dispDO.setPatientId(req->getPatientId());
			dispDO.setEncounterId(encounterId.getValue(""));
			// ////////////////////////////////////////
			dispDO.setMedicationId(req->getMedicationId());
			dispDO.setQuantity(req->getQuantity());
			dispDO.setUnitCode(req->getUnitCode());
			dispDO.setLocationId(req->getLocationId());
			dispDO.setCreatedBy(currentUser);
			dispDO.setCreatedAt(now);
			medDispDAO.insert(dispDO);

			auto presNo = req->getPrescriptionNo();
			if (!presNo.empty()) {
				processedPrescriptions.insert(presNo);
				// ///////////////////////////////////////
				if (presNoToReqId.find(presNo) == presNoToReqId.end()) {
					presNoToReqId[presNo] = req->getId();
				}
			}
		}

		// ----- 3c. ////////////////////// adm_charge_item -----
		for (auto& presNo : processedPrescriptions) {
			chinapres3ChargeItemDO newCharge;
			newCharge.setId(std::to_string(snowFlake->nextId()));
			newCharge.setServiceTable("med_medication_request");
			newCharge.setServiceId(presNoToReqId[presNo]);
			newCharge.setPrescriptionNo(presNo);
			newCharge.setPatientId(validRequests.front()->getPatientId());
			newCharge.setEncounterId(encounterId.getValue(""));
			newCharge.setGenerateSourceEnum("TCM_ISSUE");
			newCharge.setContextEnum("OUTPATIENT");
			newCharge.setTotalPrice(0.0);
			newCharge.setQuantityValue(1.0);
			newCharge.setUnitPrice(0.0);
			newCharge.setOrgId(orgId);
			newCharge.setCreatedBy(currentUser);
			newCharge.setCreatedAt(now);
			chargeDAO.insert(newCharge);
		}

		// ----- 3d. ///////////////////// -----
		tm.commit();

		// ==================== 4. Assemble result ====================
	auto resultData = chinapres3IssueResultDTO::createShared();
	resultData->processedCount = static_cast<oatpp::Int32>(validRequests.size());
	resultData->prescriptionCount = static_cast<oatpp::Int32>(processedPrescriptions.size());

	// Collect prescription numbers
	auto presNoList = oatpp::Vector<oatpp::String>::createShared();
	for (auto& presNo : processedPrescriptions) {
		presNoList->push_back(oatpp::String(presNo.c_str()));
	}
	resultData->prescriptionNos = presNoList;
	resultData->statusEnum = "ACTIVE";
	resultData->issuedAt = now.c_str();

	// Dispense business serial numbers (bus_no for pharmacy lookup)
	auto busNoList = oatpp::Vector<oatpp::String>::createShared();
	for (auto& bno : busNos) {
		busNoList->push_back(oatpp::String(bno.c_str()));
	}
	resultData->busNos = busNoList;

	resultVo->success(resultData);
	resultVo->message = "Prescription issued successfully";
	}
	catch (const std::exception& e)
	{
		resultVo->code = 500;
		std::stringstream errMsg;
		errMsg << "Exception occurred during prescription issue transaction: " << e.what();
		resultVo->message = errMsg.str();
	}

	return resultVo;
}
