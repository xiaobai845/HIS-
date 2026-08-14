#pragma once
#ifndef _SERVICE_REQUEST_MAPPER_1_H_
#define _SERVICE_REQUEST_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/ServiceRequestDO1.h"

/**
 * ’Ô¡∆/ºÏ≤È“Ω÷ˆ±Ì◊÷∂Œ∆•≈‰”≥…‰
 */
class ServiceRequestMapper1 : public Mapper<ServiceRequestDO1>
{
public:
    ServiceRequestDO1 mapper(ResultSet* resultSet) const override
    {
        ServiceRequestDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setPrescriptionNo(resultSet->getString("prescription_no"));
        data.setBasedOnTable(resultSet->getString("based_on_table"));
        data.setBasedOnId(resultSet->getString("based_on_id"));
        data.setRequisitionId(resultSet->getString("requisition_id"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setIntentEnum(resultSet->getString("intent_enum"));
        data.setCategoryEnum(resultSet->getString("category_enum"));
        data.setGroupId(resultSet->getString("group_id"));
        data.setPriorityEnum(resultSet->getString("priority_enum"));
        data.setPerformFlag(resultSet->getInt("perform_flag"));
        data.setActivityId(resultSet->getString("activity_id"));
        data.setQuantity(resultSet->getDouble("quantity"));
        data.setUnitCode(resultSet->getString("unit_code"));
        data.setPatientId(resultSet->getString("patient_id"));
        data.setEncounterId(resultSet->getString("encounter_id"));
        data.setAuthoredTime(resultSet->getString("authored_time"));
        data.setRequesterId(resultSet->getString("requester_id"));
        data.setPerformerTypeCode(resultSet->getString("performer_type_code"));
        data.setPerformerId(resultSet->getString("performer_id"));
        data.setPerformerCheckId(resultSet->getString("performer_check_id"));
        data.setCheckTime(resultSet->getString("check_time"));
        data.setLocationId(resultSet->getString("location_id"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setReasonText(resultSet->getString("reason_text"));
        data.setContractId(resultSet->getString("contract_id"));
        data.setOccurrenceStartTime(resultSet->getString("occurrence_start_time"));
        data.setOccurrenceEndTime(resultSet->getString("occurrence_end_time"));
        data.setRelevantHistoryId(resultSet->getString("relevant_history_id"));
        data.setRefundServiceId(resultSet->getString("refund_service_id"));
        data.setContentJson(resultSet->getString("content_json"));
        data.setYbClassEnum(resultSet->getString("yb_class_enum"));
        data.setPrintCount(resultSet->getInt("print_count"));
        data.setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data.setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data.setTherapyEnum(resultSet->getString("therapy_enum"));
        data.setRateCode(resultSet->getString("rate_code"));
        data.setParentId(resultSet->getString("parent_id"));
        data.setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
        data.setRemark(resultSet->getString("remark"));
        data.setEntrustContent(resultSet->getString("entrust_content"));
        data.setSortNumber(resultSet->getInt("sort_number"));
        data.setExecutionCount(resultSet->getInt("execution_count"));
        return data;
    }
};

/**
 * ’Ô¡∆/ºÏ≤È“Ω÷ˆ±Ì◊÷∂Œ∆•≈‰”≥…‰-÷«ƒ‹÷∏’Î∞Ê±æ
 */
class PtrServiceRequestMapper1 : public Mapper<PtrServiceRequestDO1>
{
public:
    PtrServiceRequestDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<ServiceRequestDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setCreatedBy(resultSet->getString("created_by"));
        data->setUpdatedBy(resultSet->getString("updated_by"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setUpdatedAt(resultSet->getString("updated_at"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setVersion(resultSet->getInt("version"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setPrescriptionNo(resultSet->getString("prescription_no"));
        data->setBasedOnTable(resultSet->getString("based_on_table"));
        data->setBasedOnId(resultSet->getString("based_on_id"));
        data->setRequisitionId(resultSet->getString("requisition_id"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setIntentEnum(resultSet->getString("intent_enum"));
        data->setCategoryEnum(resultSet->getString("category_enum"));
        data->setGroupId(resultSet->getString("group_id"));
        data->setPriorityEnum(resultSet->getString("priority_enum"));
        data->setPerformFlag(resultSet->getInt("perform_flag"));
        data->setActivityId(resultSet->getString("activity_id"));
        data->setQuantity(resultSet->getDouble("quantity"));
        data->setUnitCode(resultSet->getString("unit_code"));
        data->setPatientId(resultSet->getString("patient_id"));
        data->setEncounterId(resultSet->getString("encounter_id"));
        data->setAuthoredTime(resultSet->getString("authored_time"));
        data->setRequesterId(resultSet->getString("requester_id"));
        data->setPerformerTypeCode(resultSet->getString("performer_type_code"));
        data->setPerformerId(resultSet->getString("performer_id"));
        data->setPerformerCheckId(resultSet->getString("performer_check_id"));
        data->setCheckTime(resultSet->getString("check_time"));
        data->setLocationId(resultSet->getString("location_id"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setReasonText(resultSet->getString("reason_text"));
        data->setContractId(resultSet->getString("contract_id"));
        data->setOccurrenceStartTime(resultSet->getString("occurrence_start_time"));
        data->setOccurrenceEndTime(resultSet->getString("occurrence_end_time"));
        data->setRelevantHistoryId(resultSet->getString("relevant_history_id"));
        data->setRefundServiceId(resultSet->getString("refund_service_id"));
        data->setContentJson(resultSet->getString("content_json"));
        data->setYbClassEnum(resultSet->getString("yb_class_enum"));
        data->setPrintCount(resultSet->getInt("print_count"));
        data->setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data->setTherapyEnum(resultSet->getString("therapy_enum"));
        data->setRateCode(resultSet->getString("rate_code"));
        data->setParentId(resultSet->getString("parent_id"));
        data->setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
        data->setRemark(resultSet->getString("remark"));
        data->setEntrustContent(resultSet->getString("entrust_content"));
        data->setSortNumber(resultSet->getInt("sort_number"));
        data->setExecutionCount(resultSet->getInt("execution_count"));
        return data;
    }
};

#endif // !_SERVICE_REQUEST_MAPPER_1_H_