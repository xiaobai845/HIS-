#include "ChinapresDAO1.h"
#include "ChinapresMapper1.h"

std::list<PtrChinapresDO> ChinapresDAO1::selectAll(const ChinapresQuery1::Wrapper& query)
{
	string sql = "SELECT id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, deleted_at, deleted_by, version, bus_no, prescription_no, group_id, package_id, status_enum, status_reason, status_changed_time, intent_enum, category_enum, priority_enum, perform_flag, medication_id, patient_id, encounter_id, requester_id, location_id, org_id, perform_location, perform_org, performer_enum, performer_id, device_def_id, recorder_id, req_authored_time, report_flag, support_info, reason_json, therapy_enum, effective_dose_start, quantity, execute_num, unit_code, method_code, rate_code, dose, dose_unit_code, max_dose, first_dose, first_dose_unit_code, first_duration, dispense_interval, dispense_per_quantity, dispense_per_duration, lot_number, trace_no, skin_test_flag, infusion_flag, speed_code, contract_id, condition_definition_id, encounter_diagnosis_id, performer_check_id, check_time, effective_dose_end, refund_medicine_id, rx_type_code, yb_class_enum, dosage_instruction, based_on_table, based_on_id, tcm_flag, content_json, chinese_herbs_dose_quantity, suffering_flag, sort_number, generate_source_enum, remark FROM med_medication_request WHERE patient_id = ? AND tcm_flag = 1";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, query->patientId.getValue(""));

	if (query->encounterId && !query->encounterId->empty()) {
		sql += " AND encounter_id = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->encounterId.getValue(""));
	}
	if (query->presId) {
		sql += " AND prescription_no = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->presId.getValue(""));
	}
	if (query->keyword) {
		sql += " AND (prescription_no LIKE CONCAT('%',?,'%') OR bus_no LIKE CONCAT('%',?,'%'))";
		SQLPARAMS_PUSH(params, "s", std::string, query->keyword.getValue(""));
		SQLPARAMS_PUSH(params, "s", std::string, query->keyword.getValue(""));
	}
	sql += " ORDER BY prescription_no, sort_number";
	return sqlSession->executeQuery<PtrChinapresDO>(sql, ChinapresMapper1(), params);
}

std::list<PtrChinapresDO> ChinapresDAO1::selectDetail(const ChinapresDetailQuery1::Wrapper& query)
{
	string sql = "SELECT id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, deleted_at, deleted_by, version, bus_no, prescription_no, group_id, package_id, status_enum, status_reason, status_changed_time, intent_enum, category_enum, priority_enum, perform_flag, medication_id, patient_id, encounter_id, requester_id, location_id, org_id, perform_location, perform_org, performer_enum, performer_id, device_def_id, recorder_id, req_authored_time, report_flag, support_info, reason_json, therapy_enum, effective_dose_start, quantity, execute_num, unit_code, method_code, rate_code, dose, dose_unit_code, max_dose, first_dose, first_dose_unit_code, first_duration, dispense_interval, dispense_per_quantity, dispense_per_duration, lot_number, trace_no, skin_test_flag, infusion_flag, speed_code, contract_id, condition_definition_id, encounter_diagnosis_id, performer_check_id, check_time, effective_dose_end, refund_medicine_id, rx_type_code, yb_class_enum, dosage_instruction, based_on_table, based_on_id, tcm_flag, content_json, chinese_herbs_dose_quantity, suffering_flag, sort_number, generate_source_enum, remark FROM med_medication_request WHERE patient_id = ? AND tcm_flag = 1";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, query->patientId.getValue(""));

	if (query->encounterId && !query->encounterId->empty()) {
		sql += " AND encounter_id = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->encounterId.getValue(""));
	}
	if (query->presId) {
		sql += " AND prescription_no = ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->presId.getValue(""));
	}
	sql += " ORDER BY sort_number";
	return sqlSession->executeQuery<PtrChinapresDO>(sql, ChinapresMapper1(), params);
}