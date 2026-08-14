#pragma once
#ifndef _SERVICE_REQUEST_DO_1_H_
#define _SERVICE_REQUEST_DO_1_H_
#include "../DoInclude.h"

/**
 * 诊疗/检查医嘱实体类
 * 对应表: wkf_service_request
 */
class ServiceRequestDO1 : public BaseDO
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
    MYSQL_SYNTHESIZE(string, basedOnTable, BasedOnTable);
    MYSQL_SYNTHESIZE(string, basedOnId, BasedOnId);
    MYSQL_SYNTHESIZE(string, requisitionId, RequisitionId);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(string, intentEnum, IntentEnum);
    MYSQL_SYNTHESIZE(string, categoryEnum, CategoryEnum);
    MYSQL_SYNTHESIZE(string, groupId, GroupId);
    MYSQL_SYNTHESIZE(string, priorityEnum, PriorityEnum);
    MYSQL_SYNTHESIZE(int, performFlag, PerformFlag);
    MYSQL_SYNTHESIZE(string, activityId, ActivityId);
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
    MYSQL_SYNTHESIZE(string, patientId, PatientId);
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
    MYSQL_SYNTHESIZE(string, authoredTime, AuthoredTime);
    MYSQL_SYNTHESIZE(string, requesterId, RequesterId);
    MYSQL_SYNTHESIZE(string, performerTypeCode, PerformerTypeCode);
    MYSQL_SYNTHESIZE(string, performerId, PerformerId);
    MYSQL_SYNTHESIZE(string, performerCheckId, PerformerCheckId);
    MYSQL_SYNTHESIZE(string, checkTime, CheckTime);
    MYSQL_SYNTHESIZE(string, locationId, LocationId);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(string, reasonText, ReasonText);
    MYSQL_SYNTHESIZE(string, contractId, ContractId);
    MYSQL_SYNTHESIZE(string, occurrenceStartTime, OccurrenceStartTime);
    MYSQL_SYNTHESIZE(string, occurrenceEndTime, OccurrenceEndTime);
    MYSQL_SYNTHESIZE(string, relevantHistoryId, RelevantHistoryId);
    MYSQL_SYNTHESIZE(string, refundServiceId, RefundServiceId);
    MYSQL_SYNTHESIZE(string, contentJson, ContentJson);
    MYSQL_SYNTHESIZE(string, ybClassEnum, YbClassEnum);
    MYSQL_SYNTHESIZE(int, printCount, PrintCount);
    MYSQL_SYNTHESIZE(string, conditionDefinitionId, ConditionDefinitionId);
    MYSQL_SYNTHESIZE(string, encounterDiagnosisId, EncounterDiagnosisId);
    MYSQL_SYNTHESIZE(string, therapyEnum, TherapyEnum);
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);
    MYSQL_SYNTHESIZE(string, parentId, ParentId);
    MYSQL_SYNTHESIZE(string, generateSourceEnum, GenerateSourceEnum);
    MYSQL_SYNTHESIZE(string, remark, Remark);
    MYSQL_SYNTHESIZE(string, entrustContent, EntrustContent);
    MYSQL_SYNTHESIZE(int, sortNumber, SortNumber);
    MYSQL_SYNTHESIZE(int, executionCount, ExecutionCount);

public:
    ServiceRequestDO1() : BaseDO("wkf_service_request")
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
        MYSQL_ADD_FIELD("based_on_table", "s", basedOnTable);
        MYSQL_ADD_FIELD("based_on_id", "s", basedOnId);
        MYSQL_ADD_FIELD("requisition_id", "s", requisitionId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("intent_enum", "s", intentEnum);
        MYSQL_ADD_FIELD("category_enum", "s", categoryEnum);
        MYSQL_ADD_FIELD("group_id", "s", groupId);
        MYSQL_ADD_FIELD("priority_enum", "s", priorityEnum);
        MYSQL_ADD_FIELD("perform_flag", "i", performFlag);
        MYSQL_ADD_FIELD("activity_id", "s", activityId);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("authored_time", "s", authoredTime);
        MYSQL_ADD_FIELD("requester_id", "s", requesterId);
        MYSQL_ADD_FIELD("performer_type_code", "s", performerTypeCode);
        MYSQL_ADD_FIELD("performer_id", "s", performerId);
        MYSQL_ADD_FIELD("performer_check_id", "s", performerCheckId);
        MYSQL_ADD_FIELD("check_time", "s", checkTime);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("reason_text", "s", reasonText);
        MYSQL_ADD_FIELD("contract_id", "s", contractId);
        MYSQL_ADD_FIELD("occurrence_start_time", "s", occurrenceStartTime);
        MYSQL_ADD_FIELD("occurrence_end_time", "s", occurrenceEndTime);
        MYSQL_ADD_FIELD("relevant_history_id", "s", relevantHistoryId);
        MYSQL_ADD_FIELD("refund_service_id", "s", refundServiceId);
        MYSQL_ADD_FIELD("content_json", "s", contentJson);
        MYSQL_ADD_FIELD("yb_class_enum", "s", ybClassEnum);
        MYSQL_ADD_FIELD("print_count", "i", printCount);
        MYSQL_ADD_FIELD("condition_definition_id", "s", conditionDefinitionId);
        MYSQL_ADD_FIELD("encounter_diagnosis_id", "s", encounterDiagnosisId);
        MYSQL_ADD_FIELD("therapy_enum", "s", therapyEnum);
        MYSQL_ADD_FIELD("rate_code", "s", rateCode);
        MYSQL_ADD_FIELD("parent_id", "s", parentId);
        MYSQL_ADD_FIELD("generate_source_enum", "s", generateSourceEnum);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("entrust_content", "s", entrustContent);
        MYSQL_ADD_FIELD("sort_number", "i", sortNumber);
        MYSQL_ADD_FIELD("execution_count", "i", executionCount);
    }
};

typedef std::shared_ptr<ServiceRequestDO1> PtrServiceRequestDO1;
#endif // !_SERVICE_REQUEST_DO_1_H_