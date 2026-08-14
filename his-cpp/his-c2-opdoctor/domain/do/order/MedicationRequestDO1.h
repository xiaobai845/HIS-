#pragma once
#ifndef _MEDICATION_REQUEST_DO_1_H_
#define _MEDICATION_REQUEST_DO_1_H_
#include "../DoInclude.h"

/**
 * 药品医嘱实体类
 * 对应表: med_medication_request
 */
class MedicationRequestDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);

    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, prescriptionNo, PrescriptionNo);
    MYSQL_SYNTHESIZE(string, groupId, GroupId);
    MYSQL_SYNTHESIZE(string, packageId, PackageId);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(int, statusReason, StatusReason);
    MYSQL_SYNTHESIZE(string, statusChangedTime, StatusChangedTime);
    MYSQL_SYNTHESIZE(string, intentEnum, IntentEnum);
    MYSQL_SYNTHESIZE(string, categoryEnum, CategoryEnum);
    MYSQL_SYNTHESIZE(string, priorityEnum, PriorityEnum);
    MYSQL_SYNTHESIZE(int, performFlag, PerformFlag);
    MYSQL_SYNTHESIZE(string, medicationId, MedicationId);
    MYSQL_SYNTHESIZE(string, patientId, PatientId);
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
    MYSQL_SYNTHESIZE(string, requesterId, RequesterId);
    MYSQL_SYNTHESIZE(string, locationId, LocationId);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(string, performLocation, PerformLocation);
    MYSQL_SYNTHESIZE(string, performOrg, PerformOrg);
    MYSQL_SYNTHESIZE(string, performerEnum, PerformerEnum);
    MYSQL_SYNTHESIZE(string, performerId, PerformerId);
    MYSQL_SYNTHESIZE(string, deviceDefId, DeviceDefId);
    MYSQL_SYNTHESIZE(string, recorderId, RecorderId);
    MYSQL_SYNTHESIZE(string, reqAuthoredTime, ReqAuthoredTime);
    MYSQL_SYNTHESIZE(int, reportFlag, ReportFlag);
    MYSQL_SYNTHESIZE(string, supportInfo, SupportInfo);
    MYSQL_SYNTHESIZE(string, reasonJson, ReasonJson);
    MYSQL_SYNTHESIZE(string, therapyEnum, TherapyEnum);
    MYSQL_SYNTHESIZE(string, effectiveDoseStart, EffectiveDoseStart);
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    MYSQL_SYNTHESIZE(int, executeNum, ExecuteNum);
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
    MYSQL_SYNTHESIZE(string, methodCode, MethodCode);
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);
    MYSQL_SYNTHESIZE(double, dose, Dose);
    MYSQL_SYNTHESIZE(string, doseUnitCode, DoseUnitCode);
    MYSQL_SYNTHESIZE(double, maxDose, MaxDose);
    MYSQL_SYNTHESIZE(double, firstDose, FirstDose);
    MYSQL_SYNTHESIZE(string, firstDoseUnitCode, FirstDoseUnitCode);
    MYSQL_SYNTHESIZE(string, firstDuration, FirstDuration);
    MYSQL_SYNTHESIZE(string, dispenseInterval, DispenseInterval);
    MYSQL_SYNTHESIZE(int, dispensePerQuantity, DispensePerQuantity);
    MYSQL_SYNTHESIZE(int, dispensePerDuration, DispensePerDuration);
    MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);
    MYSQL_SYNTHESIZE(string, traceNo, TraceNo);
    MYSQL_SYNTHESIZE(int, skinTestFlag, SkinTestFlag);
    MYSQL_SYNTHESIZE(int, infusionFlag, InfusionFlag);
    MYSQL_SYNTHESIZE(string, speedCode, SpeedCode);
    MYSQL_SYNTHESIZE(string, contractId, ContractId);
    MYSQL_SYNTHESIZE(string, conditionDefinitionId, ConditionDefinitionId);
    MYSQL_SYNTHESIZE(string, encounterDiagnosisId, EncounterDiagnosisId);
    MYSQL_SYNTHESIZE(string, performerCheckId, PerformerCheckId);
    MYSQL_SYNTHESIZE(string, checkTime, CheckTime);
    MYSQL_SYNTHESIZE(string, effectiveDoseEnd, EffectiveDoseEnd);
    MYSQL_SYNTHESIZE(string, refundMedicineId, RefundMedicineId);
    MYSQL_SYNTHESIZE(string, rxTypeCode, RxTypeCode);
    MYSQL_SYNTHESIZE(string, ybClassEnum, YbClassEnum);
    MYSQL_SYNTHESIZE(string, dosageInstruction, DosageInstruction);
    MYSQL_SYNTHESIZE(string, basedOnTable, BasedOnTable);
    MYSQL_SYNTHESIZE(string, basedOnId, BasedOnId);
    MYSQL_SYNTHESIZE(int, tcmFlag, TcmFlag);
    MYSQL_SYNTHESIZE(string, contentJson, ContentJson);
    MYSQL_SYNTHESIZE(double, chineseHerbsDoseQuantity, ChineseHerbsDoseQuantity);
    MYSQL_SYNTHESIZE(int, sufferingFlag, SufferingFlag);
    MYSQL_SYNTHESIZE(int, sortNumber, SortNumber);
    MYSQL_SYNTHESIZE(string, generateSourceEnum, GenerateSourceEnum);
    MYSQL_SYNTHESIZE(string, remark, Remark);

public:
    MedicationRequestDO1() : BaseDO("med_medication_request")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("prescription_no", "s", prescriptionNo);
        MYSQL_ADD_FIELD("group_id", "s", groupId);
        MYSQL_ADD_FIELD("package_id", "s", packageId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("status_reason", "i", statusReason);
        MYSQL_ADD_FIELD("status_changed_time", "s", statusChangedTime);
        MYSQL_ADD_FIELD("intent_enum", "s", intentEnum);
        MYSQL_ADD_FIELD("category_enum", "s", categoryEnum);
        MYSQL_ADD_FIELD("priority_enum", "s", priorityEnum);
        MYSQL_ADD_FIELD("perform_flag", "i", performFlag);
        MYSQL_ADD_FIELD("medication_id", "s", medicationId);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("requester_id", "s", requesterId);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("perform_location", "s", performLocation);
        MYSQL_ADD_FIELD("perform_org", "s", performOrg);
        MYSQL_ADD_FIELD("performer_enum", "s", performerEnum);
        MYSQL_ADD_FIELD("performer_id", "s", performerId);
        MYSQL_ADD_FIELD("device_def_id", "s", deviceDefId);
        MYSQL_ADD_FIELD("recorder_id", "s", recorderId);
        MYSQL_ADD_FIELD("req_authored_time", "s", reqAuthoredTime);
        MYSQL_ADD_FIELD("report_flag", "i", reportFlag);
        MYSQL_ADD_FIELD("support_info", "s", supportInfo);
        MYSQL_ADD_FIELD("reason_json", "s", reasonJson);
        MYSQL_ADD_FIELD("therapy_enum", "s", therapyEnum);
        MYSQL_ADD_FIELD("effective_dose_start", "s", effectiveDoseStart);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("execute_num", "i", executeNum);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
        MYSQL_ADD_FIELD("method_code", "s", methodCode);
        MYSQL_ADD_FIELD("rate_code", "s", rateCode);
        MYSQL_ADD_FIELD("dose", "d", dose);
        MYSQL_ADD_FIELD("dose_unit_code", "s", doseUnitCode);
        MYSQL_ADD_FIELD("max_dose", "d", maxDose);
        MYSQL_ADD_FIELD("first_dose", "d", firstDose);
        MYSQL_ADD_FIELD("first_dose_unit_code", "s", firstDoseUnitCode);
        MYSQL_ADD_FIELD("first_duration", "s", firstDuration);
        MYSQL_ADD_FIELD("dispense_interval", "s", dispenseInterval);
        MYSQL_ADD_FIELD("dispense_per_quantity", "i", dispensePerQuantity);
        MYSQL_ADD_FIELD("dispense_per_duration", "i", dispensePerDuration);
        MYSQL_ADD_FIELD("lot_number", "s", lotNumber);
        MYSQL_ADD_FIELD("trace_no", "s", traceNo);
        MYSQL_ADD_FIELD("skin_test_flag", "i", skinTestFlag);
        MYSQL_ADD_FIELD("infusion_flag", "i", infusionFlag);
        MYSQL_ADD_FIELD("speed_code", "s", speedCode);
        MYSQL_ADD_FIELD("contract_id", "s", contractId);
        MYSQL_ADD_FIELD("condition_definition_id", "s", conditionDefinitionId);
        MYSQL_ADD_FIELD("encounter_diagnosis_id", "s", encounterDiagnosisId);
        MYSQL_ADD_FIELD("performer_check_id", "s", performerCheckId);
        MYSQL_ADD_FIELD("check_time", "s", checkTime);
        MYSQL_ADD_FIELD("effective_dose_end", "s", effectiveDoseEnd);
        MYSQL_ADD_FIELD("refund_medicine_id", "s", refundMedicineId);
        MYSQL_ADD_FIELD("rx_type_code", "s", rxTypeCode);
        MYSQL_ADD_FIELD("yb_class_enum", "s", ybClassEnum);
        MYSQL_ADD_FIELD("dosage_instruction", "s", dosageInstruction);
        MYSQL_ADD_FIELD("based_on_table", "s", basedOnTable);
        MYSQL_ADD_FIELD("based_on_id", "s", basedOnId);
        MYSQL_ADD_FIELD("tcm_flag", "i", tcmFlag);
        MYSQL_ADD_FIELD("content_json", "s", contentJson);
        MYSQL_ADD_FIELD("chinese_herbs_dose_quantity", "d", chineseHerbsDoseQuantity);
        MYSQL_ADD_FIELD("suffering_flag", "i", sufferingFlag);
        MYSQL_ADD_FIELD("sort_number", "i", sortNumber);
        MYSQL_ADD_FIELD("generate_source_enum", "s", generateSourceEnum);
        MYSQL_ADD_FIELD("remark", "s", remark);
    }
};

typedef std::shared_ptr<MedicationRequestDO1> PtrMedicationRequestDO1;
#endif // !_MEDICATION_REQUEST_DO_1_H_