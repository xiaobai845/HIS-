/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2022/12/03 11:01:02
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
      https://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "stdafx.h"
#include "PrescriptionService.h"
#include "BaseDAO.h"
#include "Mapper.h"
#include "domain/do/MedMedicationRequestDO.h"
#include "domain/do/AdmChargeItemDO.h"
#include <ctime>

namespace {
	struct ScalarStr { std::string val; };
	class ScalarStrMapper : public Mapper<ScalarStr>
	{
	public:
		ScalarStr mapper(ResultSet* rs) const override
		{
			ScalarStr s; s.val = rs->getString(1); return s;
		}
	};

	class RxMapper : public Mapper<MedMedicationRequestDO>
	{
	public:
		MedMedicationRequestDO mapper(ResultSet* rs) const override
		{
			MedMedicationRequestDO d;
			d.setId(rs->getString(1));
			d.setPrescription_no(rs->getString(2));
			d.setPatient_id(rs->getString(3));
			d.setEncounter_id(rs->getString(4));
			d.setStatus_enum(rs->getString(5));
			d.setCategory_enum(rs->getString(6));
			d.setCreated_at(rs->getString(7));
			d.setRequester_id(rs->getString(8));
			d.setContent_json(rs->getString(9));
			d.setRemark(rs->getString(10));
			return d;
		}
	};

	class ChargeItemMapper : public Mapper<AdmChargeItemDO>
	{
	public:
		AdmChargeItemDO mapper(ResultSet* rs) const override
		{
			AdmChargeItemDO d;
			d.setId(rs->getString(1));
			d.setBus_no(rs->getString(2));
			d.setDefinition_id(rs->getString(3));
			d.setQuantity_value(rs->getDouble(4));
			d.setTotal_price(rs->getDouble(5));
			d.setStatus_enum(rs->getString(6));
			d.setRefund_id(rs->getString(7));
			return d;
		}
	};
}

static int calcAge(const std::string& birthDate)
{
	if (birthDate.empty()) return 0;
	int year = std::stoi(birthDate.substr(0, 4));
	time_t now = time(nullptr);
	struct tm* tm_now = gmtime(&now);
	return (tm_now->tm_year + 1900) - year;
}

oatpp::List<oatpp::Object<Prescription2DetailDTO>> PrescriptionService::queryPrescriptions(const Prescription2Query::Wrapper& query)
{
	auto resultList = oatpp::List<oatpp::Object<Prescription2DetailDTO>>::createShared();
	std::string patientNo = query->num.getValue("");
	if (patientNo.empty()) return resultList;
	bool today = (query->type.getValue("today") == "today");

	BaseDAO dao;
	auto* ss = dao.getSqlSession();

	// 1. 病历号 → 患者ID + 基本信息
	std::string pid = ss->executeQueryOne<ScalarStr>(
		"SELECT id FROM adm_patient WHERE bus_no = ? AND is_deleted = 0 LIMIT 1",
		ScalarStrMapper(), "%s", patientNo).val;
	if (pid.empty()) return resultList;

	std::string patientName = ss->executeQueryOne<ScalarStr>(
		"SELECT name FROM adm_patient WHERE id = ?", ScalarStrMapper(), "%s", pid).val;
	std::string gender = ss->executeQueryOne<ScalarStr>(
		"SELECT gender_enum FROM adm_patient WHERE id = ?", ScalarStrMapper(), "%s", pid).val;
	std::string birthDate = ss->executeQueryOne<ScalarStr>(
		"SELECT birth_date FROM adm_patient WHERE id = ?", ScalarStrMapper(), "%s", pid).val;

	// 2. 处方列表
	std::string timeCond = today
		? "AND DATE(created_at) = CURDATE() "
		: "AND DATE(created_at) < CURDATE() ";
	std::string sql =
		"SELECT id, prescription_no, patient_id, encounter_id, "
		"status_enum, category_enum, created_at, requester_id, "
		"content_json, remark "
		"FROM med_medication_request "
		"WHERE patient_id = ? AND is_deleted = 0 ";
	sql += timeCond + "ORDER BY created_at DESC";
	auto prescriptions = ss->executeQuery<MedMedicationRequestDO>(sql, RxMapper(), "%s", pid);

	// 3. 组装 DTO
	for (auto& rx : prescriptions)
	{
		auto dto = Prescription2DetailDTO::createShared();

		dto->patientName = patientName;
		dto->gender = gender;
		dto->age = calcAge(birthDate);
		dto->patientId = rx.getPatient_id();

		dto->prescriptionNo = rx.getPrescription_no();
		dto->costType = rx.getCategory_enum();
		dto->date = rx.getCreated_at();
		dto->doctor = rx.getRequester_id();
		dto->items = rx.getContent_json();

		// 科室 — 查 adm_encounter
		dto->department = ss->executeQueryOne<ScalarStr>(
			"SELECT organization_id FROM adm_encounter "
			"WHERE id = ? AND is_deleted = 0",
			ScalarStrMapper(), "%s", rx.getEncounter_id()).val;

		// 诊断 — encounter_diagnosis
		dto->diagnosis = ss->executeQueryOne<ScalarStr>(
			"SELECT description FROM adm_encounter_diagnosis "
			"WHERE encounter_id = ? AND is_deleted = 0 "
			"ORDER BY created_at DESC LIMIT 1",
			ScalarStrMapper(), "%s", rx.getEncounter_id()).val;

		// 收费项 & 合计
		auto chargeItems = ss->executeQuery<AdmChargeItemDO>(
			"SELECT id, bus_no, definition_id, quantity_value, total_price, status_enum, refund_id "
			"FROM adm_charge_item "
			"WHERE prescription_no = ? AND is_deleted = 0",
			ChargeItemMapper(), "%s", rx.getPrescription_no());
		double tp = 0.0;
		for (auto& ci : chargeItems) tp += ci.getTotal_price();
		dto->totalPrice = tp;

		resultList->push_back(dto);
	}
	return resultList;
}
