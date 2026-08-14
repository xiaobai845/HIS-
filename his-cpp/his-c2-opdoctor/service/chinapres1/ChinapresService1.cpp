#include "stdafx.h"
#include "ChinapresService1.h"
#include "dao/chinapres1/ChinapresDAO1.h"
#include "dao/chinapres1/MedicationDefinitionDAO1.h"
#include "dao/chinapres1/ChargeItemDefinitionDAO1.h"
#include "dao/mongo/MongoDictDAO.h"
#include <map>

ChinapresListDTO1::Wrapper ChinapresService1::queryList(const ChinapresQuery1::Wrapper& query)
{
	ChinapresDAO1 dao;
	auto preList = dao.selectAll(query);

	std::map<std::string, std::list<PtrChinapresDO>> groupMap;
	for (auto& one : preList) {
		groupMap[one->getPrescriptionNo()].push_back(one);
	}

	MedicationDefinitionDAO1 medDao;
	auto result = ChinapresListDTO1::createShared();
	result->records = oatpp::List<oatpp::Object<ChinapresDTO1>>::createShared();

	for (auto& pair : groupMap) {
		auto& records = pair.second;
		auto dto = ChinapresDTO1::createShared();
		dto->id = pair.first;
		dto->count = std::to_string(records.size());

		std::string herbsStr;
		for (auto& record : records) {
			auto medDef = medDao.selectById(record->getMedicationId());
			if (medDef && !medDef->getName().empty()) {
				if (!herbsStr.empty()) herbsStr += ",";
				herbsStr += medDef->getName();
			}
		}
		dto->herbs = herbsStr;
		result->records->push_back(dto);
	}
	return result;
}

ChinapresDetailDTO1::Wrapper ChinapresService1::queryDetail(const ChinapresDetailQuery1::Wrapper& query)
{
	ChinapresDAO1 dao;
	auto detailList = dao.selectDetail(query);
	if (detailList.empty()) {
		return nullptr;
	}
	auto first = detailList.front();
	auto dto = ChinapresDetailDTO1::createShared();
	dto->prescriptionId = first->getPrescriptionNo();
	dto->encounterId = first->getEncounterId();
	dto->patientId = first->getPatientId();

	MongoDictDAO mongoDao;
	dto->status = first->getStatusEnum();
	dto->statusName = mongoDao.getDictName("medication_status", first->getStatusEnum());
	dto->usage = first->getMethodCode();
	dto->frequency = first->getRateCode();
	dto->days = (oatpp::Int32)first->getExecuteNum();
	dto->copies = (oatpp::Int32)(int)first->getChineseHerbsDoseQuantity();
	dto->decoction = first->getSufferingFlag();
	dto->diagnosis = first->getConditionDefinitionId();
	dto->remark = first->getRemark();

	dto->version = (oatpp::Int32)first->getVersion();
	dto->createdAt = first->getCreatedAt();
	dto->statusChangedAt = first->getStatusChangedTime();
	dto->totalCount = (oatpp::Int32)(int)detailList.size();

	MedicationDefinitionDAO1 medDao;
	ChargeItemDefinitionDAO1 chargeDao;
	auto herbList = oatpp::List<oatpp::Object<ChinapresHerbDTO>>::createShared();
	double totalDoseAmount = 0.0;
	for (auto record : detailList) {
		auto herb = ChinapresHerbDTO::createShared();
		auto medDef = medDao.selectById(record->getMedicationId());
		herb->medicineId = record->getMedicationId();
		herb->medicineCode = medDef ? medDef->getBusNo() : "";
		herb->name = medDef ? medDef->getName() : "Î´ÖªÒ©²Ä";
		herb->quantity = record->getQuantity();
		herb->unit = record->getUnitCode();
		herb->dose = record->getDose();
		herb->doseUnit = record->getDoseUnitCode();
		herb->sortNumber = (oatpp::Int32)record->getSortNumber();
		auto chargeDef = chargeDao.selectByInstanceId(record->getMedicationId());
		double unitPrice = chargeDef ? chargeDef->getPriceValue() : 0.0;
		herb->unitPrice = unitPrice;
		double subtotal = unitPrice * record->getDose() * first->getChineseHerbsDoseQuantity();
		herb->subtotal = subtotal;
		totalDoseAmount += unitPrice * record->getDose();
		herbList->push_back(herb);
	}
	dto->details = herbList;
	dto->doseAmount = std::round(totalDoseAmount * 100) / 100;
	dto->totalAmount = std::round(totalDoseAmount * first->getChineseHerbsDoseQuantity() * 100) / 100;

	return dto;
}