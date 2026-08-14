#pragma once
#ifndef _DEVICE_REQUEST_MAPPER_1_H_
#define _DEVICE_REQUEST_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/DeviceRequestDO1.h"

/**
 * ºÄ²ÄÇëÇó±í×Ö¶ÎÆ¥ÅäÓ³Éä
 */
class DeviceRequestMapper1 : public Mapper<DeviceRequestDO1>
{
public:
    DeviceRequestDO1 mapper(ResultSet* resultSet) const override
    {
        DeviceRequestDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setPrescriptionNo(resultSet->getString("prescription_no"));
        data.setActivityId(resultSet->getString("activity_id"));
        data.setPackageId(resultSet->getString("package_id"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setIntentCode(resultSet->getString("intent_code"));
        data.setCategoryEnum(resultSet->getString("category_enum"));
        data.setPriorityEnum(resultSet->getString("priority_enum"));
        data.setPerformFlag(resultSet->getInt("perform_flag"));
        data.setGroupNo(resultSet->getString("group_no"));
        data.setDeviceTypeCode(resultSet->getString("device_type_code"));
        data.setQuantity(resultSet->getDouble("quantity"));
        data.setUnitCode(resultSet->getString("unit_code"));
        data.setLotNumber(resultSet->getString("lot_number"));
        data.setDeviceDefId(resultSet->getString("device_def_id"));
        data.setDeviceSpecifications(resultSet->getString("device_specifications"));
        data.setRequesterId(resultSet->getString("requester_id"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setLocationId(resultSet->getString("location_id"));
        data.setPerformLocation(resultSet->getString("perform_location"));
        data.setEncounterId(resultSet->getString("encounter_id"));
        data.setPatientId(resultSet->getString("patient_id"));
        data.setRateCode(resultSet->getString("rate_code"));
        data.setUseTime(resultSet->getString("use_time"));
        data.setUseStartTime(resultSet->getString("use_start_time"));
        data.setUseEndTime(resultSet->getString("use_end_time"));
        data.setUseTiming(resultSet->getString("use_timing"));
        data.setReqAuthoredTime(resultSet->getString("req_authored_time"));
        data.setPerformerEnum(resultSet->getString("performer_enum"));
        data.setPerformerId(resultSet->getString("performer_id"));
        data.setPerformOrgId(resultSet->getString("perform_org_id"));
        data.setAsNeedFlag(resultSet->getInt("as_need_flag"));
        data.setAsNeedReason(resultSet->getString("as_need_reason"));
        data.setContractCode(resultSet->getString("contract_code"));
        data.setRefundDeviceId(resultSet->getString("refund_device_id"));
        data.setYbClassEnum(resultSet->getString("yb_class_enum"));
        data.setTraceNo(resultSet->getString("trace_no"));
        data.setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data.setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data.setObservationIdJson(resultSet->getString("observation_id_json"));
        data.setSupportInfo(resultSet->getString("support_info"));
        data.setBasedOnTable(resultSet->getString("based_on_table"));
        data.setBasedOnId(resultSet->getString("based_on_id"));
        data.setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
        data.setRemark(resultSet->getString("remark"));
        data.setSortNumber(resultSet->getInt("sort_number"));
        return data;
    }
};

/**
 * ºÄ²ÄÇëÇó±í×Ö¶ÎÆ¥ÅäÓ³Éä-ÖÇÄÜÖ¸Õë°æ±¾
 */
class PtrDeviceRequestMapper1 : public Mapper<PtrDeviceRequestDO1>
{
public:
    PtrDeviceRequestDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<DeviceRequestDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setUpdatedAt(resultSet->getString("updated_at"));
        data->setCreatedBy(resultSet->getString("created_by"));
        data->setUpdatedBy(resultSet->getString("updated_by"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setVersion(resultSet->getInt("version"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setPrescriptionNo(resultSet->getString("prescription_no"));
        data->setActivityId(resultSet->getString("activity_id"));
        data->setPackageId(resultSet->getString("package_id"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setIntentCode(resultSet->getString("intent_code"));
        data->setCategoryEnum(resultSet->getString("category_enum"));
        data->setPriorityEnum(resultSet->getString("priority_enum"));
        data->setPerformFlag(resultSet->getInt("perform_flag"));
        data->setGroupNo(resultSet->getString("group_no"));
        data->setDeviceTypeCode(resultSet->getString("device_type_code"));
        data->setQuantity(resultSet->getDouble("quantity"));
        data->setUnitCode(resultSet->getString("unit_code"));
        data->setLotNumber(resultSet->getString("lot_number"));
        data->setDeviceDefId(resultSet->getString("device_def_id"));
        data->setDeviceSpecifications(resultSet->getString("device_specifications"));
        data->setRequesterId(resultSet->getString("requester_id"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setLocationId(resultSet->getString("location_id"));
        data->setPerformLocation(resultSet->getString("perform_location"));
        data->setEncounterId(resultSet->getString("encounter_id"));
        data->setPatientId(resultSet->getString("patient_id"));
        data->setRateCode(resultSet->getString("rate_code"));
        data->setUseTime(resultSet->getString("use_time"));
        data->setUseStartTime(resultSet->getString("use_start_time"));
        data->setUseEndTime(resultSet->getString("use_end_time"));
        data->setUseTiming(resultSet->getString("use_timing"));
        data->setReqAuthoredTime(resultSet->getString("req_authored_time"));
        data->setPerformerEnum(resultSet->getString("performer_enum"));
        data->setPerformerId(resultSet->getString("performer_id"));
        data->setPerformOrgId(resultSet->getString("perform_org_id"));
        data->setAsNeedFlag(resultSet->getInt("as_need_flag"));
        data->setAsNeedReason(resultSet->getString("as_need_reason"));
        data->setContractCode(resultSet->getString("contract_code"));
        data->setRefundDeviceId(resultSet->getString("refund_device_id"));
        data->setYbClassEnum(resultSet->getString("yb_class_enum"));
        data->setTraceNo(resultSet->getString("trace_no"));
        data->setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data->setObservationIdJson(resultSet->getString("observation_id_json"));
        data->setSupportInfo(resultSet->getString("support_info"));
        data->setBasedOnTable(resultSet->getString("based_on_table"));
        data->setBasedOnId(resultSet->getString("based_on_id"));
        data->setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
        data->setRemark(resultSet->getString("remark"));
        data->setSortNumber(resultSet->getInt("sort_number"));
        return data;
    }
};

#endif // !_DEVICE_REQUEST_MAPPER_1_H_