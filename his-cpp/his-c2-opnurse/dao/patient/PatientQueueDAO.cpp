/*
 Copyright Zero One Star. All rights reserved.

 @Author: AI Assistant
 @Date: 2026/07/24 18:30:00

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
#include "PatientQueueDAO.h"
#include <sstream>

PatientQueueResult PatientQueueMapper::mapper(ResultSet* rs) const
{
	PatientQueueResult result;
	// Map AppointmentQueueDO fields
	result.queue.setId(rs->getString("id"));
	if (!rs->isNull("tenant_id"))
		result.queue.setTenantId(rs->getString("tenant_id"));
	if (!rs->isNull("patient_id"))
		result.queue.setPatientId(rs->getString("patient_id"));
	if (!rs->isNull("encounter_id"))
		result.queue.setEncounterId(rs->getString("encounter_id"));
	if (!rs->isNull("bus_no"))
		result.queue.setBusNo(rs->getString("bus_no"));
	result.queue.setDisplayOrder(rs->getInt("display_order"));
	if (!rs->isNull("start_instant"))
		result.queue.setStartInstant(rs->getString("start_instant"));
	if (!rs->isNull("booking_date"))
		result.queue.setBookingDate(rs->getString("booking_date"));
	if (!rs->isNull("triage_level"))
		result.queue.setTriageLevel(rs->getString("triage_level"));

	// Map PatientDO fields
	if (!rs->isNull("name"))
		result.patient.setName(rs->getString("name"));
	if (!rs->isNull("gender_enum"))
		result.patient.setGenderEnum(rs->getString("gender_enum"));
	if (!rs->isNull("birth_date"))
		result.patient.setBirthDate(rs->getString("birth_date"));

	// Map extended joined fields
	if (!rs->isNull("encounter_id"))
		result.encounterId = rs->getString("encounter_id");
	if (!rs->isNull("p_id"))
		result.patient.setId(rs->getString("p_id"));
	if (!rs->isNull("medical_record_no"))
		result.medicalRecordNo = rs->getString("medical_record_no");
	if (!rs->isNull("visit_no"))
		result.visitNo = rs->getString("visit_no");
	if (!rs->isNull("registered_at"))
		result.registeredAt = rs->getString("registered_at");
	if (!rs->isNull("department_name"))
		result.departmentName = rs->getString("department_name");
	if (!rs->isNull("visit_type_name"))
		result.visitTypeName = rs->getString("visit_type_name");
	if (!rs->isNull("encounter_status"))
		result.statusEnum = rs->getString("encounter_status");
	if (!rs->isNull("status_name"))
		result.statusName = rs->getString("status_name");
	if (!rs->isNull("payment_type_name")) {
		result.paymentType = rs->getString("payment_type_name");
		result.paymentTypeName = rs->getString("payment_type_name");
	}
	if (!rs->isNull("priority_name"))
		result.priorityName = rs->getString("priority_name");
	if (!rs->isNull("risk_hint"))
		result.riskHint = rs->getString("risk_hint");
	if (!rs->isNull("pending_count"))
		result.pendingCount = rs->getInt("pending_count");
	return result;
}

std::list<PatientQueueResult> PatientQueueDAO::queryPatientQueue(
	const std::string& keyword, const std::string& startDate, const std::string& endDate,
	const std::string& tenantId,
	int pageIndex, int pageSize)
{
	std::ostringstream sql;
	sql << "SELECT q.id, q.tenant_id, q.patient_id, q.encounter_id, q.bus_no, q.display_order, "
		<< "q.start_instant, q.booking_date, q.triage_level, "
		<< "p.id AS p_id, p.name, p.gender_enum, p.birth_date, "
		<< "e.medical_record_no, e.visit_no, "
		<< "e.created_at AS registered_at, "
		<< "DATEDIFF(CURDATE(), p.birth_date) / 365 AS age, "
		<< "dep.name AS department_name, "
		<< "e.visit_type_name, "
		<< "e.status_enum AS encounter_status, "
		<< "st.display_name AS status_name, "
		<< "e.yb_class_text AS payment_type_name, "
		<< "tl.display_name AS priority_name, "
		<< "COALESCE(e.risk_hint, '') AS risk_hint, "
		<< "(SELECT COUNT(*) FROM wkf_appointment_queue q2 "
		<< " WHERE q2.is_deleted = 0 AND q2.tenant_id = q.tenant_id "
		<< "   AND q2.booking_date = q.booking_date "
		<< "   AND q2.display_order < q.display_order) AS pending_count "
		<< "FROM wkf_appointment_queue q "
		<< "JOIN adm_patient p ON q.patient_id = p.id "
		<< "JOIN adm_encounter e ON q.encounter_id = e.id "
		<< "LEFT JOIN adm_department dep ON e.department_id = dep.id "
		<< "LEFT JOIN adm_code_dict st ON st.code = e.status_enum AND st.category = 'encounter_status' "
		<< "LEFT JOIN adm_code_dict tl ON tl.code = q.triage_level AND tl.category = 'triage_level' "
		<< "WHERE q.is_deleted = 0 "
		<< "AND q.tenant_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, tenantId);
	if (!keyword.empty()) {
		sql << "AND (p.name LIKE ? OR q.bus_no = ?) ";
		SQLPARAMS_PUSH(params, "s", std::string, "%" + keyword + "%");
		SQLPARAMS_PUSH(params, "s", std::string, keyword);
	}
	if (!startDate.empty()) {
		sql << "AND q.booking_date >= ? ";
		SQLPARAMS_PUSH(params, "s", std::string, startDate);
	}
	if (!endDate.empty()) {
		sql << "AND q.booking_date <= ? ";
		SQLPARAMS_PUSH(params, "s", std::string, endDate);
	}

	sql << "ORDER BY q.display_order ASC ";
	sql << "LIMIT ?, ? ";
	SQLPARAMS_PUSH(params, "i", int, (pageIndex - 1) * pageSize);
	SQLPARAMS_PUSH(params, "i", int, pageSize);

	PatientQueueMapper mapper;
	return sqlSession->executeQuery<PatientQueueResult>(sql.str(), mapper, params);
}

uint64_t PatientQueueDAO::countPatientQueue(
	const std::string& keyword, const std::string& startDate, const std::string& endDate,
	const std::string& tenantId)
{
	std::ostringstream sql;
	sql << "SELECT COUNT(*) FROM wkf_appointment_queue q "
		<< "JOIN adm_patient p ON q.patient_id = p.id "
		<< "JOIN adm_encounter e ON q.encounter_id = e.id "
		<< "WHERE q.is_deleted = 0 "
		<< "AND q.tenant_id = ? ";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, tenantId);
	if (!keyword.empty()) {
		sql << "AND (p.name LIKE ? OR q.bus_no = ?) ";
		SQLPARAMS_PUSH(params, "s", std::string, "%" + keyword + "%");
		SQLPARAMS_PUSH(params, "s", std::string, keyword);
	}
	if (!startDate.empty()) {
		sql << "AND q.booking_date >= ? ";
		SQLPARAMS_PUSH(params, "s", std::string, startDate);
	}
	if (!endDate.empty()) {
		sql << "AND q.booking_date <= ? ";
		SQLPARAMS_PUSH(params, "s", std::string, endDate);
	}

	return sqlSession->executeQueryNumerical(sql.str(), params);
}

PatientInfoResult PatientInfoMapper::mapper(ResultSet* rs) const
{
	PatientInfoResult result;
	result.name = rs->getString("name");
	result.gender = rs->getString("gender_enum");
	result.birthDate = rs->getString("birth_date");
	return result;
}

PatientInfoResult PatientQueueDAO::queryByEncounterId(const std::string& encounterId)
{
	std::ostringstream sql;
	sql << "SELECT p.name, p.gender_enum, p.birth_date "
		<< "FROM wkf_appointment_queue q "
		<< "JOIN adm_patient p ON q.patient_id = p.id "
		<< "WHERE q.is_deleted = 0 "
		<< "AND q.encounter_id = ? "
		<< "LIMIT 1";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, encounterId);

	PatientInfoMapper mapper;
	auto results = sqlSession->executeQuery<PatientInfoResult>(sql.str(), mapper, params);
	if (results.empty()) {
		return PatientInfoResult();
	}
	return results.front();
}
