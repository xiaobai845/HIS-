#pragma once

#ifndef _PRESCRIPTION3_MEDICATION_REQUEST_DO_H_
#define _PRESCRIPTION3_MEDICATION_REQUEST_DO_H_

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * med_medication_request 领域模型。
 *
 * DATETIME(6) 字段暂以 String 承载，便于兼容项目当前 Oat++ DTO；
 * 如果公共库已有 DateTime 类型，可以统一替换。
 */
class Prescription3MedicationRequestDO : public oatpp::DTO
{
    DTO_INIT(Prescription3MedicationRequestDO, DTO);

    DTO_FIELD(String, id, "id");
    DTO_FIELD(String, tenantId, "tenant_id");
    DTO_FIELD(String, createdAt, "created_at");
    DTO_FIELD(String, updatedAt, "updated_at");
    DTO_FIELD(String, createdBy, "created_by");
    DTO_FIELD(String, updatedBy, "updated_by");
    DTO_FIELD(Int32, isDeleted, "is_deleted");
    DTO_FIELD(String, deletedAt, "deleted_at");
    DTO_FIELD(String, deletedBy, "deleted_by");
    DTO_FIELD(Int32, version, "version");
    DTO_FIELD(String, busNo, "bus_no");
    DTO_FIELD(String, prescriptionNo, "prescription_no");
    DTO_FIELD(String, groupId, "group_id");
    DTO_FIELD(String, packageId, "package_id");
    DTO_FIELD(String, statusEnum, "status_enum");
    DTO_FIELD(Int32, statusReason, "status_reason");
    DTO_FIELD(String, statusChangedTime, "status_changed_time");
    DTO_FIELD(String, intentEnum, "intent_enum");
    DTO_FIELD(String, categoryEnum, "category_enum");
    DTO_FIELD(String, priorityEnum, "priority_enum");
    DTO_FIELD(Int32, performFlag, "perform_flag");
    DTO_FIELD(String, medicationId, "medication_id");
    DTO_FIELD(String, patientId, "patient_id");
    DTO_FIELD(String, encounterId, "encounter_id");
    DTO_FIELD(String, requesterId, "requester_id");
    DTO_FIELD(String, locationId, "location_id");
    DTO_FIELD(String, orgId, "org_id");
    DTO_FIELD(Int64, performLocation, "perform_location");
    DTO_FIELD(Int64, performOrg, "perform_org");
    DTO_FIELD(String, performerEnum, "performer_enum");
    DTO_FIELD(String, performerId, "performer_id");
    DTO_FIELD(String, deviceDefId, "device_def_id");
    DTO_FIELD(String, recorderId, "recorder_id");
    DTO_FIELD(String, reqAuthoredTime, "req_authored_time");
    DTO_FIELD(Int32, reportFlag, "report_flag");
    DTO_FIELD(String, supportInfo, "support_info");
    DTO_FIELD(String, reasonJson, "reason_json");
    DTO_FIELD(String, therapyEnum, "therapy_enum");
    DTO_FIELD(String, effectiveDoseStart, "effective_dose_start");
    DTO_FIELD(Float64, quantity, "quantity");
    DTO_FIELD(Int32, executeNum, "execute_num");
    DTO_FIELD(String, unitCode, "unit_code");
    DTO_FIELD(String, methodCode, "method_code");
    DTO_FIELD(String, rateCode, "rate_code");
    DTO_FIELD(Float64, dose, "dose");
    DTO_FIELD(String, doseUnitCode, "dose_unit_code");
    DTO_FIELD(Float64, maxDose, "max_dose");
    DTO_FIELD(Float64, firstDose, "first_dose");
    DTO_FIELD(String, firstDoseUnitCode, "first_dose_unit_code");
    DTO_FIELD(String, firstDuration, "first_duration");
    DTO_FIELD(String, dispenseInterval, "dispense_interval");
    DTO_FIELD(Int32, dispensePerQuantity, "dispense_per_quantity");
    DTO_FIELD(Int32, dispensePerDuration, "dispense_per_duration");
    DTO_FIELD(String, lotNumber, "lot_number");
    DTO_FIELD(String, traceNo, "trace_no");
    DTO_FIELD(Int32, skinTestFlag, "skin_test_flag");
    DTO_FIELD(Int32, infusionFlag, "infusion_flag");
    DTO_FIELD(String, speedCode, "speed_code");
    DTO_FIELD(String, contractId, "contract_id");
    DTO_FIELD(String, conditionDefinitionId, "condition_definition_id");
    DTO_FIELD(String, encounterDiagnosisId, "encounter_diagnosis_id");
    DTO_FIELD(String, performerCheckId, "performer_check_id");
    DTO_FIELD(String, checkTime, "check_time");
    DTO_FIELD(String, effectiveDoseEnd, "effective_dose_end");
    DTO_FIELD(String, refundMedicineId, "refund_medicine_id");
    DTO_FIELD(String, rxTypeCode, "rx_type_code");
    DTO_FIELD(String, ybClassEnum, "yb_class_enum");
    DTO_FIELD(String, dosageInstruction, "dosage_instruction");
    DTO_FIELD(String, basedOnTable, "based_on_table");
    DTO_FIELD(String, basedOnId, "based_on_id");
    DTO_FIELD(Int32, tcmFlag, "tcm_flag");
    DTO_FIELD(String, contentJson, "content_json");
    DTO_FIELD(Float64, chineseHerbsDoseQuantity, "chinese_herbs_dose_quantity");
    DTO_FIELD(Int32, sufferingFlag, "suffering_flag");
    DTO_FIELD(Int32, sortNumber, "sort_number");
    DTO_FIELD(String, generateSourceEnum, "generate_source_enum");
    DTO_FIELD(String, remark, "remark");
};

#include OATPP_CODEGEN_END(DTO)

#endif
