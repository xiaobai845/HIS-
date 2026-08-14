#pragma once

#ifndef _MED_MEDICATION_REQUEST_DO_H_
#define _MED_MEDICATION_REQUEST_DO_H_

#include "../DoInclude.h"

class MedMedicationRequestDO : public BaseDO
{
    // ===== »ù´¡×Ö¶Î =====
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenant_id, Tenant_id);
    MYSQL_SYNTHESIZE(string, created_at, Created_at);
    MYSQL_SYNTHESIZE(string, updated_at, Updated_at);
    MYSQL_SYNTHESIZE(string, created_by, Created_by);
    MYSQL_SYNTHESIZE(string, updated_by, Updated_by);
    MYSQL_SYNTHESIZE(bool, is_deleted, Is_deleted);
    MYSQL_SYNTHESIZE(string, deleted_at, Deleted_at);
    MYSQL_SYNTHESIZE(string, deleted_by, Deleted_by);
    MYSQL_SYNTHESIZE(int, version, Version);

    // ===== ÒµÎñ×Ö¶Î =====
    MYSQL_SYNTHESIZE(string, bus_no, Bus_no);
    MYSQL_SYNTHESIZE(string, prescription_no, Prescription_no);
    MYSQL_SYNTHESIZE(string, group_id, Group_id);
    MYSQL_SYNTHESIZE(string, package_id, Package_id);
    MYSQL_SYNTHESIZE(string, status_enum, Status_enum);
    MYSQL_SYNTHESIZE(int, status_reason, Status_reason);
    MYSQL_SYNTHESIZE(string, status_changed_time, Status_changed_time);
    MYSQL_SYNTHESIZE(string, intent_enum, Intent_enum);
    MYSQL_SYNTHESIZE(string, category_enum, Category_enum);
    MYSQL_SYNTHESIZE(string, priority_enum, Priority_enum);
    MYSQL_SYNTHESIZE(bool, perform_flag, Perform_flag);
    MYSQL_SYNTHESIZE(string, medication_id, Medication_id);
    MYSQL_SYNTHESIZE(string, patient_id, Patient_id);
    MYSQL_SYNTHESIZE(string, encounter_id, Encounter_id);
    MYSQL_SYNTHESIZE(string, requester_id, Requester_id);
    MYSQL_SYNTHESIZE(string, location_id, Location_id);
    MYSQL_SYNTHESIZE(string, org_id, Org_id);
    MYSQL_SYNTHESIZE(string, perform_location, Perform_location);
    MYSQL_SYNTHESIZE(string, perform_org, Perform_org);
    MYSQL_SYNTHESIZE(string, performer_enum, Performer_enum);
    MYSQL_SYNTHESIZE(string, performer_id, Performer_id);
    MYSQL_SYNTHESIZE(string, device_def_id, Device_def_id);
    MYSQL_SYNTHESIZE(string, recorder_id, Recorder_id);
    MYSQL_SYNTHESIZE(string, req_authored_time, Req_authored_time);
    MYSQL_SYNTHESIZE(bool, report_flag, Report_flag);
    MYSQL_SYNTHESIZE(string, support_info, Support_info);
    MYSQL_SYNTHESIZE(string, reason_json, Reason_json);
    MYSQL_SYNTHESIZE(string, therapy_enum, Therapy_enum);
    MYSQL_SYNTHESIZE(string, effective_dose_start, Effective_dose_start);
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    MYSQL_SYNTHESIZE(int, execute_num, Execute_num);
    MYSQL_SYNTHESIZE(string, unit_code, Unit_code);
    MYSQL_SYNTHESIZE(string, method_code, Method_code);
    MYSQL_SYNTHESIZE(string, rate_code, Rate_code);
    MYSQL_SYNTHESIZE(double, dose, Dose);
    MYSQL_SYNTHESIZE(string, dose_unit_code, Dose_unit_code);
    MYSQL_SYNTHESIZE(double, max_dose, Max_dose);
    MYSQL_SYNTHESIZE(double, first_dose, First_dose);
    MYSQL_SYNTHESIZE(string, first_dose_unit_code, First_dose_unit_code);
    MYSQL_SYNTHESIZE(string, first_duration, First_duration);
    MYSQL_SYNTHESIZE(string, dispense_interval, Dispense_interval);
    MYSQL_SYNTHESIZE(int, dispense_per_quantity, Dispense_per_quantity);
    MYSQL_SYNTHESIZE(int, dispense_per_duration, Dispense_per_duration);
    MYSQL_SYNTHESIZE(string, lot_number, Lot_number);
    MYSQL_SYNTHESIZE(string, trace_no, Trace_no);
    MYSQL_SYNTHESIZE(bool, skin_test_flag, Skin_test_flag);
    MYSQL_SYNTHESIZE(bool, infusion_flag, Infusion_flag);
    MYSQL_SYNTHESIZE(string, speed_code, Speed_code);
    MYSQL_SYNTHESIZE(string, contract_id, Contract_id);
    MYSQL_SYNTHESIZE(string, condition_definition_id, Condition_definition_id);
    MYSQL_SYNTHESIZE(string, encounter_diagnosis_id, Encounter_diagnosis_id);
    MYSQL_SYNTHESIZE(string, performer_check_id, Performer_check_id);
    MYSQL_SYNTHESIZE(string, check_time, Check_time);
    MYSQL_SYNTHESIZE(string, effective_dose_end, Effective_dose_end);
    MYSQL_SYNTHESIZE(string, refund_medicine_id, Refund_medicine_id);
    MYSQL_SYNTHESIZE(string, rx_type_code, Rx_type_code);
    MYSQL_SYNTHESIZE(string, yb_class_enum, Yb_class_enum);
    MYSQL_SYNTHESIZE(string, dosage_instruction, Dosage_instruction);
    MYSQL_SYNTHESIZE(string, based_on_table, Based_on_table);
    MYSQL_SYNTHESIZE(string, based_on_id, Based_on_id);
    MYSQL_SYNTHESIZE(bool, tcm_flag, Tcm_flag);
    MYSQL_SYNTHESIZE(string, content_json, Content_json);
    MYSQL_SYNTHESIZE(double, chinese_herbs_dose_quantity, Chinese_herbs_dose_quantity);
    MYSQL_SYNTHESIZE(bool, suffering_flag, Suffering_flag);
    MYSQL_SYNTHESIZE(int, sort_number, Sort_number);
    MYSQL_SYNTHESIZE(string, generate_source_enum, Generate_source_enum);
    MYSQL_SYNTHESIZE(string, remark, Remark);

public:
    MedMedicationRequestDO() : BaseDO("med_medication_request")
    {
        // ===== »ù´¡×Ö¶Î =====
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenant_id);
        MYSQL_ADD_FIELD("created_at", "s", created_at);
        MYSQL_ADD_FIELD("updated_at", "s", updated_at);
        MYSQL_ADD_FIELD("created_by", "s", created_by);
        MYSQL_ADD_FIELD("updated_by", "s", updated_by);
        MYSQL_ADD_FIELD("is_deleted", "b", is_deleted);
        MYSQL_ADD_FIELD("deleted_at", "s", deleted_at);
        MYSQL_ADD_FIELD("deleted_by", "s", deleted_by);
        MYSQL_ADD_FIELD("version", "i", version);

        // ===== ÒµÎñ×Ö¶Î =====
        MYSQL_ADD_FIELD("bus_no", "s", bus_no);
        MYSQL_ADD_FIELD("prescription_no", "s", prescription_no);
        MYSQL_ADD_FIELD("group_id", "s", group_id);
        MYSQL_ADD_FIELD("package_id", "s", package_id);
        MYSQL_ADD_FIELD("status_enum", "s", status_enum);
        MYSQL_ADD_FIELD("status_reason", "i", status_reason);
        MYSQL_ADD_FIELD("status_changed_time", "s", status_changed_time);
        MYSQL_ADD_FIELD("intent_enum", "s", intent_enum);
        MYSQL_ADD_FIELD("category_enum", "s", category_enum);
        MYSQL_ADD_FIELD("priority_enum", "s", priority_enum);
        MYSQL_ADD_FIELD("perform_flag", "b", perform_flag);
        MYSQL_ADD_FIELD("medication_id", "s", medication_id);
        MYSQL_ADD_FIELD("patient_id", "s", patient_id);
        MYSQL_ADD_FIELD("encounter_id", "s", encounter_id);
        MYSQL_ADD_FIELD("requester_id", "s", requester_id);
        MYSQL_ADD_FIELD("location_id", "s", location_id);
        MYSQL_ADD_FIELD("org_id", "s", org_id);
        MYSQL_ADD_FIELD("perform_location", "s", perform_location);
        MYSQL_ADD_FIELD("perform_org", "s", perform_org);
        MYSQL_ADD_FIELD("performer_enum", "s", performer_enum);
        MYSQL_ADD_FIELD("performer_id", "s", performer_id);
        MYSQL_ADD_FIELD("device_def_id", "s", device_def_id);
        MYSQL_ADD_FIELD("recorder_id", "s", recorder_id);
        MYSQL_ADD_FIELD("req_authored_time", "s", req_authored_time);
        MYSQL_ADD_FIELD("report_flag", "b", report_flag);
        MYSQL_ADD_FIELD("support_info", "s", support_info);
        MYSQL_ADD_FIELD("reason_json", "s", reason_json);
        MYSQL_ADD_FIELD("therapy_enum", "s", therapy_enum);
        MYSQL_ADD_FIELD("effective_dose_start", "s", effective_dose_start);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("execute_num", "i", execute_num);
        MYSQL_ADD_FIELD("unit_code", "s", unit_code);
        MYSQL_ADD_FIELD("method_code", "s", method_code);
        MYSQL_ADD_FIELD("rate_code", "s", rate_code);
        MYSQL_ADD_FIELD("dose", "d", dose);
        MYSQL_ADD_FIELD("dose_unit_code", "s", dose_unit_code);
        MYSQL_ADD_FIELD("max_dose", "d", max_dose);
        MYSQL_ADD_FIELD("first_dose", "d", first_dose);
        MYSQL_ADD_FIELD("first_dose_unit_code", "s", first_dose_unit_code);
        MYSQL_ADD_FIELD("first_duration", "s", first_duration);
        MYSQL_ADD_FIELD("dispense_interval", "s", dispense_interval);
        MYSQL_ADD_FIELD("dispense_per_quantity", "i", dispense_per_quantity);
        MYSQL_ADD_FIELD("dispense_per_duration", "i", dispense_per_duration);
        MYSQL_ADD_FIELD("lot_number", "s", lot_number);
        MYSQL_ADD_FIELD("trace_no", "s", trace_no);
        MYSQL_ADD_FIELD("skin_test_flag", "b", skin_test_flag);
        MYSQL_ADD_FIELD("infusion_flag", "b", infusion_flag);
        MYSQL_ADD_FIELD("speed_code", "s", speed_code);
        MYSQL_ADD_FIELD("contract_id", "s", contract_id);
        MYSQL_ADD_FIELD("condition_definition_id", "s", condition_definition_id);
        MYSQL_ADD_FIELD("encounter_diagnosis_id", "s", encounter_diagnosis_id);
        MYSQL_ADD_FIELD("performer_check_id", "s", performer_check_id);
        MYSQL_ADD_FIELD("check_time", "s", check_time);
        MYSQL_ADD_FIELD("effective_dose_end", "s", effective_dose_end);
        MYSQL_ADD_FIELD("refund_medicine_id", "s", refund_medicine_id);
        MYSQL_ADD_FIELD("rx_type_code", "s", rx_type_code);
        MYSQL_ADD_FIELD("yb_class_enum", "s", yb_class_enum);
        MYSQL_ADD_FIELD("dosage_instruction", "s", dosage_instruction);
        MYSQL_ADD_FIELD("based_on_table", "s", based_on_table);
        MYSQL_ADD_FIELD("based_on_id", "s", based_on_id);
        MYSQL_ADD_FIELD("tcm_flag", "b", tcm_flag);
        MYSQL_ADD_FIELD("content_json", "s", content_json);
        MYSQL_ADD_FIELD("chinese_herbs_dose_quantity", "d", chinese_herbs_dose_quantity);
        MYSQL_ADD_FIELD("suffering_flag", "b", suffering_flag);
        MYSQL_ADD_FIELD("sort_number", "i", sort_number);
        MYSQL_ADD_FIELD("generate_source_enum", "s", generate_source_enum);
        MYSQL_ADD_FIELD("remark", "s", remark);
    }
};

typedef std::shared_ptr<MedMedicationRequestDO> MedMedicationRequestDOPtr;

#endif