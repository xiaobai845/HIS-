#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/25
*/
#ifndef _CHINAPRES2_MAPPER_
#define _CHINAPRES2_MAPPER_

#include "Mapper.h"
#include "../../domain/do/chinapres2/Chinapres2MainDO.h"
#include "../../domain/do/chinapres2/Chinapres2ViewDO.h"

/**
 * 处方主表 Mapper（单表查询，不包含关联字段）
 */
class Chinapres2Mapper : public Mapper<Chinapres2MainDO>
{
public:
    Chinapres2MainDO mapper(ResultSet* resultSet) const override
    {
        Chinapres2MainDO data;
        data.setId(resultSet->getString("id"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setPrescriptionNo(resultSet->getString("prescription_no"));
        data.setGroupId(resultSet->getString("group_id"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setPatientId(resultSet->getString("patient_id"));
        data.setEncounterId(resultSet->getString("encounter_id"));
        data.setRequesterId(resultSet->getString("requester_id"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setMethodCode(resultSet->getString("method_code"));
        data.setRateCode(resultSet->getString("rate_code"));
        data.setExecuteNum(resultSet->getInt("execute_num"));
        data.setChineseHerbsDoseQuantity(resultSet->getDouble("chinese_herbs_dose_quantity"));
        data.setSufferingFlag(resultSet->getInt("suffering_flag"));
        data.setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data.setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data.setDosageInstruction(resultSet->getString("dosage_instruction"));
        data.setRemark(resultSet->getString("remark"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setStatusReason(resultSet->getString("status_reason"));
        return data;
    }
};

/**
 * 处方主表智能指针 Mapper
 */
class PtrChinapres2Mapper : public Mapper<PtrChinapres2MainDO>
{
public:
    PtrChinapres2MainDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<Chinapres2MainDO>();
        data->setId(resultSet->getString("id"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setPrescriptionNo(resultSet->getString("prescription_no"));
        data->setGroupId(resultSet->getString("group_id"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setPatientId(resultSet->getString("patient_id"));
        data->setEncounterId(resultSet->getString("encounter_id"));
        data->setRequesterId(resultSet->getString("requester_id"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setMethodCode(resultSet->getString("method_code"));
        data->setRateCode(resultSet->getString("rate_code"));
        data->setExecuteNum(resultSet->getInt("execute_num"));
        data->setChineseHerbsDoseQuantity(resultSet->getDouble("chinese_herbs_dose_quantity"));
        data->setSufferingFlag(resultSet->getInt("suffering_flag"));
        data->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
        data->setConditionDefinitionId(resultSet->getString("condition_definition_id"));
        data->setDosageInstruction(resultSet->getString("dosage_instruction"));
        data->setRemark(resultSet->getString("remark"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setStatusReason(resultSet->getString("status_reason"));
        return data;
    }
};

/**
 * 处方视图 Mapper（联查：主表 + 诊断名 + 医生名 + 药材汇总）
 * 用于分页列表展示
 */
 /*
 class Chinapres2ViewMapper : public Mapper<PtrChinapres2ViewDO>
 {
 public:
     PtrChinapres2ViewDO mapper(ResultSet* resultSet) const override
     {
         auto data = std::make_shared<Chinapres2ViewDO>();
         // 继承自主表的字段
         data->setId(resultSet->getString("id"));
         data->setBusNo(resultSet->getString("bus_no"));
         data->setPrescriptionNo(resultSet->getString("prescription_no"));
         data->setGroupId(resultSet->getString("group_id"));
         data->setStatusEnum(resultSet->getString("status_enum"));
         data->setIsDeleted(resultSet->getInt("is_deleted"));
         data->setPatientId(resultSet->getString("patient_id"));
         data->setEncounterId(resultSet->getString("encounter_id"));
         data->setRequesterId(resultSet->getString("requester_id"));
         data->setOrgId(resultSet->getString("org_id"));
         data->setMethodCode(resultSet->getString("method_code"));
         data->setRateCode(resultSet->getString("rate_code"));
         data->setExecuteNum(resultSet->getInt("execute_num"));
         data->setChineseHerbsDoseQuantity(resultSet->getDouble("chinese_herbs_dose_quantity"));
         data->setSufferingFlag(resultSet->getInt("suffering_flag"));
         data->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
         data->setConditionDefinitionId(resultSet->getString("condition_definition_id"));
         data->setDosageInstruction(resultSet->getString("dosage_instruction"));
         data->setRemark(resultSet->getString("remark"));
         data->setCreatedAt(resultSet->getString("created_at"));
         data->setStatusReason(resultSet->getString("status_reason"));

         // 视图扩展字段（来自联查）
         data->setDiagnosisName(resultSet->getString("diagnosis_name"));
         data->setRequesterName(resultSet->getString("requester_name"));
         data->setMedicationNames(resultSet->getString("medication_names"));
         data->setTotalPrice(resultSet->getDouble("total_price"));

         return data;
     }
 };
 */
#endif // !_CHINAPRES2_MAPPER_