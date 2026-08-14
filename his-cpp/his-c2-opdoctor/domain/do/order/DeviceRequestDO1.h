#pragma once
#ifndef _DEVICE_REQUEST_DO_1_H_
#define _DEVICE_REQUEST_DO_1_H_

#include "../DoInclude.h"

/**
 * 耗材请求实体类
 * 对应表: wkf_device_request
 */
class DeviceRequestDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);

    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, prescriptionNo, PrescriptionNo);
    MYSQL_SYNTHESIZE(string, activityId, ActivityId);
    MYSQL_SYNTHESIZE(string, packageId, PackageId);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(string, intentCode, IntentCode);
    MYSQL_SYNTHESIZE(string, categoryEnum, CategoryEnum);
    MYSQL_SYNTHESIZE(string, priorityEnum, PriorityEnum);
    MYSQL_SYNTHESIZE(int, performFlag, PerformFlag);
    MYSQL_SYNTHESIZE(string, groupNo, GroupNo);
    MYSQL_SYNTHESIZE(string, deviceTypeCode, DeviceTypeCode);
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
    MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);
    MYSQL_SYNTHESIZE(string, deviceDefId, DeviceDefId);
    MYSQL_SYNTHESIZE(string, deviceSpecifications, DeviceSpecifications);
    MYSQL_SYNTHESIZE(string, requesterId, RequesterId);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(string, locationId, LocationId);
    MYSQL_SYNTHESIZE(string, performLocation, PerformLocation);
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
    MYSQL_SYNTHESIZE(string, patientId, PatientId);
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);
    MYSQL_SYNTHESIZE(string, useTime, UseTime);
    MYSQL_SYNTHESIZE(string, useStartTime, UseStartTime);
    MYSQL_SYNTHESIZE(string, useEndTime, UseEndTime);
    MYSQL_SYNTHESIZE(string, useTiming, UseTiming);
    MYSQL_SYNTHESIZE(string, reqAuthoredTime, ReqAuthoredTime);
    MYSQL_SYNTHESIZE(string, performerEnum, PerformerEnum);
    MYSQL_SYNTHESIZE(string, performerId, PerformerId);
    MYSQL_SYNTHESIZE(string, performOrgId, PerformOrgId);
    MYSQL_SYNTHESIZE(int, asNeedFlag, AsNeedFlag);
    MYSQL_SYNTHESIZE(string, asNeedReason, AsNeedReason);
    MYSQL_SYNTHESIZE(string, contractCode, ContractCode);
    MYSQL_SYNTHESIZE(string, refundDeviceId, RefundDeviceId);
    MYSQL_SYNTHESIZE(string, ybClassEnum, YbClassEnum);
    MYSQL_SYNTHESIZE(string, traceNo, TraceNo);
    MYSQL_SYNTHESIZE(string, conditionDefinitionId, ConditionDefinitionId);
    MYSQL_SYNTHESIZE(string, encounterDiagnosisId, EncounterDiagnosisId);
    MYSQL_SYNTHESIZE(string, observationIdJson, ObservationIdJson);
    MYSQL_SYNTHESIZE(string, supportInfo, SupportInfo);
    MYSQL_SYNTHESIZE(string, basedOnTable, BasedOnTable);
    MYSQL_SYNTHESIZE(string, basedOnId, BasedOnId);
    MYSQL_SYNTHESIZE(string, generateSourceEnum, GenerateSourceEnum);
    MYSQL_SYNTHESIZE(string, remark, Remark);
    MYSQL_SYNTHESIZE(int, sortNumber, SortNumber);

public:
    DeviceRequestDO1() : BaseDO("wkf_device_request")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("prescription_no", "s", prescriptionNo);
        MYSQL_ADD_FIELD("activity_id", "s", activityId);
        MYSQL_ADD_FIELD("package_id", "s", packageId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("intent_code", "s", intentCode);
        MYSQL_ADD_FIELD("category_enum", "s", categoryEnum);
        MYSQL_ADD_FIELD("priority_enum", "s", priorityEnum);
        MYSQL_ADD_FIELD("perform_flag", "i", performFlag);
        MYSQL_ADD_FIELD("group_no", "s", groupNo);
        MYSQL_ADD_FIELD("device_type_code", "s", deviceTypeCode);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
        MYSQL_ADD_FIELD("lot_number", "s", lotNumber);
        MYSQL_ADD_FIELD("device_def_id", "s", deviceDefId);
        MYSQL_ADD_FIELD("device_specifications", "s", deviceSpecifications);
        MYSQL_ADD_FIELD("requester_id", "s", requesterId);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
        MYSQL_ADD_FIELD("perform_location", "s", performLocation);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("rate_code", "s", rateCode);
        MYSQL_ADD_FIELD("use_time", "s", useTime);
        MYSQL_ADD_FIELD("use_start_time", "s", useStartTime);
        MYSQL_ADD_FIELD("use_end_time", "s", useEndTime);
        MYSQL_ADD_FIELD("use_timing", "s", useTiming);
        MYSQL_ADD_FIELD("req_authored_time", "s", reqAuthoredTime);
        MYSQL_ADD_FIELD("performer_enum", "s", performerEnum);
        MYSQL_ADD_FIELD("performer_id", "s", performerId);
        MYSQL_ADD_FIELD("perform_org_id", "s", performOrgId);
        MYSQL_ADD_FIELD("as_need_flag", "i", asNeedFlag);
        MYSQL_ADD_FIELD("as_need_reason", "s", asNeedReason);
        MYSQL_ADD_FIELD("contract_code", "s", contractCode);
        MYSQL_ADD_FIELD("refund_device_id", "s", refundDeviceId);
        MYSQL_ADD_FIELD("yb_class_enum", "s", ybClassEnum);
        MYSQL_ADD_FIELD("trace_no", "s", traceNo);
        MYSQL_ADD_FIELD("condition_definition_id", "s", conditionDefinitionId);
        MYSQL_ADD_FIELD("encounter_diagnosis_id", "s", encounterDiagnosisId);
        MYSQL_ADD_FIELD("observation_id_json", "s", observationIdJson);
        MYSQL_ADD_FIELD("support_info", "s", supportInfo);
        MYSQL_ADD_FIELD("based_on_table", "s", basedOnTable);
        MYSQL_ADD_FIELD("based_on_id", "s", basedOnId);
        MYSQL_ADD_FIELD("generate_source_enum", "s", generateSourceEnum);
        MYSQL_ADD_FIELD("remark", "s", remark);
        MYSQL_ADD_FIELD("sort_number", "i", sortNumber);
    }
};

typedef std::shared_ptr<DeviceRequestDO1> PtrDeviceRequestDO1;

#endif // !_DEVICE_REQUEST_DO_1_H_