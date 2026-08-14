#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/24 18:00:00
*/
#ifndef _CHINAPRES2_MAIN_DO_
#define _CHINAPRES2_MAIN_DO_
#include "../DoInclude.h"

/**
 * 中医处方主表 DO (对应表 med_medication_request)
 * 存储处方头部信息，不包含药材明细
 */
class Chinapres2MainDO : public BaseDO
{
    // ---------- 基础标识与流转号 ----------
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, prescriptionNo, PrescriptionNo);
    MYSQL_SYNTHESIZE(string, groupId, GroupId);          // 处方分组聚合键
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);    // 签发/撤回等
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);         // 软删除标记

    // ---------- 关联标识 ----------
    MYSQL_SYNTHESIZE(string, patientId, PatientId);
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
    MYSQL_SYNTHESIZE(string, requesterId, RequesterId);  // 开方医生ID
    MYSQL_SYNTHESIZE(string, orgId, OrgId);

    // ---------- 处方全局信息 ----------
    MYSQL_SYNTHESIZE(string, methodCode, MethodCode);            // 用法：水煎服
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);                // 频次：每日一次
    MYSQL_SYNTHESIZE(int, executeNum, ExecuteNum);               // 天数
    MYSQL_SYNTHESIZE(double, chineseHerbsDoseQuantity, ChineseHerbsDoseQuantity); // 付数
    MYSQL_SYNTHESIZE(int, sufferingFlag, SufferingFlag);         // 代煎开关
    MYSQL_SYNTHESIZE(string, encounterDiagnosisId, EncounterDiagnosisId);
    MYSQL_SYNTHESIZE(string, conditionDefinitionId, ConditionDefinitionId);
    MYSQL_SYNTHESIZE(string, dosageInstruction, DosageInstruction);
    MYSQL_SYNTHESIZE(string, remark, Remark);

    // ---------- 时间与状态 ----------
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, statusReason, StatusReason);        // 撤回原因等

public:
    Chinapres2MainDO() : BaseDO("med_medication_request")
    {
        // 主键
        MYSQL_ADD_FIELD_PK("id", "s", id);
        // 基础字段
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD_NULLABLE("prescription_no", "s", prescriptionNo, false);
        MYSQL_ADD_FIELD_NULLABLE("group_id", "s", groupId, false);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);

        // 关联ID
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD_NULLABLE("requester_id", "s", requesterId, false);
        MYSQL_ADD_FIELD_NULLABLE("org_id", "s", orgId, false);

        // 全局信息
        MYSQL_ADD_FIELD_NULLABLE("method_code", "s", methodCode, false);
        MYSQL_ADD_FIELD_NULLABLE("rate_code", "s", rateCode, false);
        MYSQL_ADD_FIELD_NULLABLE("execute_num", "i", executeNum, false);
        MYSQL_ADD_FIELD_NULLABLE("chinese_herbs_dose_quantity", "d", chineseHerbsDoseQuantity, false);
        MYSQL_ADD_FIELD_NULLABLE("suffering_flag", "i", sufferingFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("encounter_diagnosis_id", "s", encounterDiagnosisId, false);
        MYSQL_ADD_FIELD_NULLABLE("condition_definition_id", "s", conditionDefinitionId, false);
        MYSQL_ADD_FIELD_NULLABLE("dosage_instruction", "s", dosageInstruction, false);
        MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, false);

        // 时间
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD_NULLABLE("status_reason", "s", statusReason, false);
    }
};

typedef std::shared_ptr<Chinapres2MainDO> PtrChinapres2MainDO;

#endif // !_CHINAPRES_MAIN_DO_