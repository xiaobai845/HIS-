#pragma once
#ifndef _MEDICATION_REQUEST_MAPPER_1_H_
#define _MEDICATION_REQUEST_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/MedicationRequestDO1.h"

/**
 * 药品医嘱表字段匹配映射
 */
class MedicationRequestMapper1 : public Mapper<MedicationRequestDO1>
{
public:
    MedicationRequestDO1 mapper(ResultSet* resultSet) const override
    {
        MedicationRequestDO1 data;
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
        data.setGroupId(resultSet->getString("group_id"));
        data.setPackageId(resultSet->getString("package_id"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setStatusReason(resultSet->getInt("status_reason"));
        data.setStatusChangedTime(resultSet->getString("status_changed_time"));
        data.setIntentEnum(resultSet->getString("intent_enum"));
        data.setCategoryEnum(resultSet->getString("category_enum"));
        data.setPriorityEnum(resultSet->getString("priority_enum"));
        data.setPerformFlag(resultSet->getInt("perform_flag"));
        data.setMedicationId(resultSet->getString("medication_id"));
        data.setPatientId(resultSet->getString("patient_id"));
        data.setEncounterId(resultSet->getString("encounter_id"));
        data.setRequesterId(resultSet->getString("requester_id"));
        data.setLocationId(resultSet->getString("location_id"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setPerformLocation(resultSet->getString("perform_location"));
        data.setPerformOrg(resultSet->getString("perform_org"));
        data.setPerformerEnum(resultSet->getString("performer_enum"));
        data.setPerformerId(resultSet->getString("performer_id"));
        data.setDeviceDefId(resultSet->getString("device_def_id"));
        data.setRecorderId(resultSet->getString("recorder_id"));
        data.setReqAuthoredTime(resultSet->getString("req_authored_time"));
        data.setReportFlag(resultSet->getInt("report_flag"));
        data.setSupportInfo(resultSet->getString("support_info"));
        data.setReasonJson(resultSet->getString("reason_json"));
        data.setTherapyEnum(resultSet->getString("therapy_enum"));
        data.setEffectiveDoseStart(resultSet->getString("effective_dose_start"));
        data.setQuantity(resultSet->getDouble("quantity"));
        data.setExecuteNum(resultSet->getInt("execute_num"));
        data.setUnitCode(resultSet->getString("unit_code"));
        data.setMethodCode(resultSet->getString("method_code"));
        data.setRateCode(resultSet->getString("rate_code"));
        data.setDose(resultSet->getDouble("dose"));
        data.setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data.setMaxDose(resultSet->getDouble("max_dose"));
        data.setFirstDose(resultSet->getDouble("first_dose"));
        data.setFirstDoseUnitCode(resultSet->getString("first_dose_unit_code"));
        data.setFirstDuration(resultSet->getString("first_duration"));
        data.setDispenseInterval(resultSet->getString("dispense_interval"));
        data.setDispensePerQuantity(resultSet->getInt("dispense_per_quantity"));
        data.setDispensePerDuration(resultSet->getInt("dispense_per_duration"));
        data.setLotNumber(resultSet->getString("lot_number"));
        data.setTraceNo(resultSet->getString("trace_no"));
        data.setSkinTestFlag(resultSet->getInt("skin_test_flag"));
        data.setInfusionFlag(resultSet->getInt("infusion_flag"));
        data.setSpeedCode(resultSet->getString("speed_code"));
        data.setContractId(resultSet->getString("contract_id"));
        data.setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data.setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data.setPerformerCheckId(resultSet->getString("performer_check_id"));
        data.setCheckTime(resultSet->getString("check_time"));
        data.setEffectiveDoseEnd(resultSet->getString("effective_dose_end"));
        data.setRefundMedicineId(resultSet->getString("refund_medicine_id"));
        data.setRxTypeCode(resultSet->getString("rx_type_code"));
        data.setYbClassEnum(resultSet->getString("yb_class_enum"));
        data.setDosageInstruction(resultSet->getString("dosage_instruction"));
        data.setBasedOnTable(resultSet->getString("based_on_table"));
        data.setBasedOnId(resultSet->getString("based_on_id"));
        data.setTcmFlag(resultSet->getInt("tcm_flag"));
        data.setContentJson(resultSet->getString("content_json"));
        data.setChineseHerbsDoseQuantity(resultSet->getDouble("chinese_herbs_dose_quantity"));
        data.setSufferingFlag(resultSet->getInt("suffering_flag"));
        data.setSortNumber(resultSet->getInt("sort_number"));
        data.setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
        data.setRemark(resultSet->getString("remark"));
        return data;
    }
};

/**
 * 药品医嘱表字段匹配映射-智能指针版本
 */
class PtrMedicationRequestMapper1 : public Mapper<PtrMedicationRequestDO1>
{
public:
    PtrMedicationRequestDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<MedicationRequestDO1>();
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
        data->setGroupId(resultSet->getString("group_id"));
        data->setPackageId(resultSet->getString("package_id"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setStatusReason(resultSet->getInt("status_reason"));
        data->setStatusChangedTime(resultSet->getString("status_changed_time"));
        data->setIntentEnum(resultSet->getString("intent_enum"));
        data->setCategoryEnum(resultSet->getString("category_enum"));
        data->setPriorityEnum(resultSet->getString("priority_enum"));
        data->setPerformFlag(resultSet->getInt("perform_flag"));
        data->setMedicationId(resultSet->getString("medication_id"));
        data->setPatientId(resultSet->getString("patient_id"));
        data->setEncounterId(resultSet->getString("encounter_id"));
        data->setRequesterId(resultSet->getString("requester_id"));
        data->setLocationId(resultSet->getString("location_id"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setPerformLocation(resultSet->getString("perform_location"));
        data->setPerformOrg(resultSet->getString("perform_org"));
        data->setPerformerEnum(resultSet->getString("performer_enum"));
        data->setPerformerId(resultSet->getString("performer_id"));
        data->setDeviceDefId(resultSet->getString("device_def_id"));
        data->setRecorderId(resultSet->getString("recorder_id"));
        data->setReqAuthoredTime(resultSet->getString("req_authored_time"));
        data->setReportFlag(resultSet->getInt("report_flag"));
        data->setSupportInfo(resultSet->getString("support_info"));
        data->setReasonJson(resultSet->getString("reason_json"));
        data->setTherapyEnum(resultSet->getString("therapy_enum"));
        data->setEffectiveDoseStart(resultSet->getString("effective_dose_start"));
        data->setQuantity(resultSet->getDouble("quantity"));
        data->setExecuteNum(resultSet->getInt("execute_num"));
        data->setUnitCode(resultSet->getString("unit_code"));
        data->setMethodCode(resultSet->getString("method_code"));
        data->setRateCode(resultSet->getString("rate_code"));
        data->setDose(resultSet->getDouble("dose"));
        data->setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data->setMaxDose(resultSet->getDouble("max_dose"));
        data->setFirstDose(resultSet->getDouble("first_dose"));
        data->setFirstDoseUnitCode(resultSet->getString("first_dose_unit_code"));
        data->setFirstDuration(resultSet->getString("first_duration"));
        data->setDispenseInterval(resultSet->getString("dispense_interval"));
        data->setDispensePerQuantity(resultSet->getInt("dispense_per_quantity"));
        data->setDispensePerDuration(resultSet->getInt("dispense_per_duration"));
        data->setLotNumber(resultSet->getString("lot_number"));
        data->setTraceNo(resultSet->getString("trace_no"));
        data->setSkinTestFlag(resultSet->getInt("skin_test_flag"));
        data->setInfusionFlag(resultSet->getInt("infusion_flag"));
        data->setSpeedCode(resultSet->getString("speed_code"));
        data->setContractId(resultSet->getString("contract_id"));
        data->setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data->setPerformerCheckId(resultSet->getString("performer_check_id"));
        data->setCheckTime(resultSet->getString("check_time"));
        data->setEffectiveDoseEnd(resultSet->getString("effective_dose_end"));
        data->setRefundMedicineId(resultSet->getString("refund_medicine_id"));
        data->setRxTypeCode(resultSet->getString("rx_type_code"));
        data->setYbClassEnum(resultSet->getString("yb_class_enum"));
        data->setDosageInstruction(resultSet->getString("dosage_instruction"));
        data->setBasedOnTable(resultSet->getString("based_on_table"));
        data->setBasedOnId(resultSet->getString("based_on_id"));
        data->setTcmFlag(resultSet->getInt("tcm_flag"));
        data->setContentJson(resultSet->getString("content_json"));
        data->setChineseHerbsDoseQuantity(resultSet->getDouble("chinese_herbs_dose_quantity"));
        data->setSufferingFlag(resultSet->getInt("suffering_flag"));
        data->setSortNumber(resultSet->getInt("sort_number"));
        data->setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
        data->setRemark(resultSet->getString("remark"));
        return data;
    }
};

#endif // !_MEDICATION_REQUEST_MAPPER_1_H_