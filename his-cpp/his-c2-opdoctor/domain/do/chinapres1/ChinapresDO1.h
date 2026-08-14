#pragma once
#ifndef _CHINAPRESDO1_H
#define _CHINAPRESDO1_H

#include"../DoInclude.h"


class ChinapresDO1 : public BaseDO
{
    // ========== 1. 通用字段 ==========
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(bool, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(string, deletedAt, DeletedAt);
    MYSQL_SYNTHESIZE(string, deletedBy, DeletedBy);
    MYSQL_SYNTHESIZE(int, version, Version);
    // ========== 2. 处方业务标识 ==========
    MYSQL_SYNTHESIZE(string, busNo, BusNo);                     // 业务编号（NOT NULL）
    MYSQL_SYNTHESIZE(string, prescriptionNo, PrescriptionNo);   // 处方编号
    MYSQL_SYNTHESIZE(string, groupId, GroupId);                 // 分组标识
    MYSQL_SYNTHESIZE(string, packageId, PackageId);             // 组套/套餐标识
    // ========== 3. 状态与意图 ==========
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);           // 状态枚举（NOT NULL）
    MYSQL_SYNTHESIZE(int, statusReason, StatusReason);          // 状态原因
    MYSQL_SYNTHESIZE(string, statusChangedTime, StatusChangedTime); // 状态变更时间
    MYSQL_SYNTHESIZE(string, intentEnum, IntentEnum);           // 意图枚举
    MYSQL_SYNTHESIZE(string, categoryEnum, CategoryEnum);       // 类别枚举
    MYSQL_SYNTHESIZE(string, priorityEnum, PriorityEnum);         // 优先级枚举
    MYSQL_SYNTHESIZE(bool, performFlag, PerformFlag);           // 执行标志
    // ========== 4. 关联对象（患者、就诊、药品） ==========
    MYSQL_SYNTHESIZE(string, medicationId, MedicationId);       // 药品标识（NOT NULL）-> 关联药品定义表
    MYSQL_SYNTHESIZE(string, patientId, PatientId);             // 患者标识（NOT NULL）
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);       // 就诊标识（NOT NULL）
    // ========== 5. 开方与执行位置 ==========
    MYSQL_SYNTHESIZE(string, requesterId, RequesterId);         // 开方人标识
    MYSQL_SYNTHESIZE(string, locationId, LocationId);           // 位置/科室标识
    MYSQL_SYNTHESIZE(string, orgId, OrgId);                     // 开立机构标识
    MYSQL_SYNTHESIZE(long long, performLocation, PerformLocation); // 发放药房库位主键（BIGINT）
    MYSQL_SYNTHESIZE(long long, performOrg, PerformOrg);           // 执行机构（BIGINT）
    // ========== 6. 执行人与记录人 ==========
    MYSQL_SYNTHESIZE(string, performerEnum, PerformerEnum);     // 执行人枚举
    MYSQL_SYNTHESIZE(string, performerId, PerformerId);           // 执行人标识
    MYSQL_SYNTHESIZE(string, deviceDefId, DeviceDefId);         // 设备定义标识
    MYSQL_SYNTHESIZE(string, recorderId, RecorderId);           // 记录人标识
    // ========== 7. 时间与标志 ==========
    MYSQL_SYNTHESIZE(string, reqAuthoredTime, ReqAuthoredTime); // 医嘱开立时间
    MYSQL_SYNTHESIZE(bool, reportFlag, ReportFlag);             // 报表标志
    MYSQL_SYNTHESIZE(string, supportInfo, SupportInfo);         // 辅助信息
    MYSQL_SYNTHESIZE(string, reasonJson, ReasonJson);           // 原因JSON
    // ========== 8. 治疗类型与有效剂量期 ==========
    MYSQL_SYNTHESIZE(string, therapyEnum, TherapyEnum);           // 治疗类型枚举（NOT NULL）
    MYSQL_SYNTHESIZE(string, effectiveDoseStart, EffectiveDoseStart); // 有效剂量开始
    // ========== 9. 数量与单位 ==========
    MYSQL_SYNTHESIZE(double, quantity, Quantity);               // 数量（
    MYSQL_SYNTHESIZE(int, executeNum, ExecuteNum);              // 执行次数
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);                 // 单元编码（NOT NULL）
    // ========== 10. 用法、频次、剂量 ==========
    MYSQL_SYNTHESIZE(string, methodCode, MethodCode);           // 用法编码（NOT NULL）-> 页面"水煎服"
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);               // 频次编码（NOT NULL）-> 页面"每日两次"
    MYSQL_SYNTHESIZE(double, dose, Dose);                       // 单次剂量 -> 页面药材卡片"10g"
    MYSQL_SYNTHESIZE(string, doseUnitCode, DoseUnitCode);         // 剂量单位 -> "g"
    MYSQL_SYNTHESIZE(double, maxDose, MaxDose);                 // 最大剂量（西药安全限制）
    MYSQL_SYNTHESIZE(double, firstDose, FirstDose);               // 首剂量
    MYSQL_SYNTHESIZE(string, firstDoseUnitCode, FirstDoseUnitCode); // 首剂单位
    MYSQL_SYNTHESIZE(string, firstDuration, FirstDuration);     // 首剂耗时
    // ========== 11. 发药相关（西药/注射剂为主，中药暂不用但也注册） ==========
    MYSQL_SYNTHESIZE(string, dispenseInterval, DispenseInterval); // 发药间隔
    MYSQL_SYNTHESIZE(int, dispensePerQuantity, DispensePerQuantity); // 发药per数量
    MYSQL_SYNTHESIZE(int, dispensePerDuration, DispensePerDuration); // 发药per耗时
    // ========== 12. 批号与追溯 ==========
    MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);             // 批号
    MYSQL_SYNTHESIZE(string, traceNo, TraceNo);                 // 追踪编号（TEXT转string）
    // ========== 13. 特殊标志（皮试、输液等） ==========
    MYSQL_SYNTHESIZE(bool, skinTestFlag, SkinTestFlag);         // 皮试标志
    MYSQL_SYNTHESIZE(bool, infusionFlag, InfusionFlag);         // 输液标志
    MYSQL_SYNTHESIZE(string, speedCode, SpeedCode);             // 滴速编码
    // ========== 14. 合同与诊断 ==========
    MYSQL_SYNTHESIZE(string, contractId, ContractId);           // 合同标识
    MYSQL_SYNTHESIZE(string, conditionDefinitionId, ConditionDefinitionId); // 诊断定义主键 -> 页面"眩晕(气血两虚证)"
    MYSQL_SYNTHESIZE(string, encounterDiagnosisId, EncounterDiagnosisId);   // 就诊诊断标识
    // ========== 15. 核对与退费 ==========
    MYSQL_SYNTHESIZE(string, performerCheckId, PerformerCheckId); // 核对人标识
    MYSQL_SYNTHESIZE(string, checkTime, CheckTime);             // 核对时间
    MYSQL_SYNTHESIZE(string, effectiveDoseEnd, EffectiveDoseEnd); // 有效剂量结束
    MYSQL_SYNTHESIZE(string, refundMedicineId, RefundMedicineId); // 退费药品标识
    // ========== 16. 处方类型与医保 ==========
    MYSQL_SYNTHESIZE(string, rxTypeCode, RxTypeCode);           // 处方类型编码
    MYSQL_SYNTHESIZE(string, ybClassEnum, YbClassEnum);         // 医保class枚举
    MYSQL_SYNTHESIZE(string, dosageInstruction, DosageInstruction); // 用法说明
    // ========== 17. 来源与中医标志 ==========
    MYSQL_SYNTHESIZE(string, basedOnTable, BasedOnTable);       // 依据表名
    MYSQL_SYNTHESIZE(string, basedOnId, BasedOnId);             // 依据标识
    MYSQL_SYNTHESIZE(bool, tcmFlag, TcmFlag);                   // 中医标志（查历史处方必带条件）
    MYSQL_SYNTHESIZE(string, contentJson, ContentJson);           // 内容JSON
    // ========== 18. 中药特有字段 ==========
    MYSQL_SYNTHESIZE(double, chineseHerbsDoseQuantity, ChineseHerbsDoseQuantity); // 中药付数 -> 页面"付数：10"
    MYSQL_SYNTHESIZE(bool, sufferingFlag, SufferingFlag);       // 代煎标志 -> 页面"代煎"开关
    MYSQL_SYNTHESIZE(int, sortNumber, SortNumber);                // 排序号 -> 药材显示顺序
    MYSQL_SYNTHESIZE(string, generateSourceEnum, GenerateSourceEnum); // 生成来源
    MYSQL_SYNTHESIZE(string, remark, Remark);                   // 备注 -> 页面"备注"框

public:
    ChinapresDO1() : BaseDO("med_medication_request")
    {
        // 通用字段
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, false);
        MYSQL_ADD_FIELD("created_at", "dt", createdAt);
        MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updatedAt, false);
        MYSQL_ADD_FIELD_NULLABLE("created_by", "s", createdBy, false);
        MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updatedBy, false);
        MYSQL_ADD_FIELD("is_deleted", "b", isDeleted);
        MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", deletedAt, false);
        MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deletedBy, false);
        MYSQL_ADD_FIELD("version", "i", version);
        // 处方业务标识
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD_NULLABLE("prescription_no", "s", prescriptionNo, false);
        MYSQL_ADD_FIELD_NULLABLE("group_id", "s", groupId, false);
        MYSQL_ADD_FIELD_NULLABLE("package_id", "s", packageId, false);
        // 状态与意图
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD_NULLABLE("status_reason", "i", statusReason, false);
        MYSQL_ADD_FIELD_NULLABLE("status_changed_time", "dt", statusChangedTime, false);
        MYSQL_ADD_FIELD_NULLABLE("intent_enum", "s", intentEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("category_enum", "s", categoryEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("priority_enum", "s", priorityEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("perform_flag", "b", performFlag, false);
        // 关联对象
        MYSQL_ADD_FIELD("medication_id", "s", medicationId);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        // 开方与执行位置
        MYSQL_ADD_FIELD_NULLABLE("requester_id", "s", requesterId, false);
        MYSQL_ADD_FIELD_NULLABLE("location_id", "s", locationId, false);
        MYSQL_ADD_FIELD_NULLABLE("org_id", "s", orgId, false);
        MYSQL_ADD_FIELD_NULLABLE("perform_location", "bi", performLocation, false); 
        MYSQL_ADD_FIELD_NULLABLE("perform_org", "bi", performOrg, false);
        // 执行人与记录人
        MYSQL_ADD_FIELD_NULLABLE("performer_enum", "s", performerEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("performer_id", "s", performerId, false);
        MYSQL_ADD_FIELD_NULLABLE("device_def_id", "s", deviceDefId, false);
        MYSQL_ADD_FIELD_NULLABLE("recorder_id", "s", recorderId, false);
        // 时间与标志
        MYSQL_ADD_FIELD_NULLABLE("req_authored_time", "dt", reqAuthoredTime, false);
        MYSQL_ADD_FIELD_NULLABLE("report_flag", "b", reportFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("support_info", "s", supportInfo, false);
        MYSQL_ADD_FIELD_NULLABLE("reason_json", "s", reasonJson, false);
        // 治疗类型
        MYSQL_ADD_FIELD("therapy_enum", "s", therapyEnum);
        MYSQL_ADD_FIELD_NULLABLE("effective_dose_start", "dt", effectiveDoseStart, false);
        // 数量与单位
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD_NULLABLE("execute_num", "i", executeNum, false);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
        // 用法、频次、剂量
        MYSQL_ADD_FIELD("method_code", "s", methodCode);
        MYSQL_ADD_FIELD("rate_code", "s", rateCode);
        MYSQL_ADD_FIELD_NULLABLE("dose", "d", dose, false);
        MYSQL_ADD_FIELD_NULLABLE("dose_unit_code", "s", doseUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("max_dose", "d", maxDose, false);
        MYSQL_ADD_FIELD_NULLABLE("first_dose", "d", firstDose, false);
        MYSQL_ADD_FIELD_NULLABLE("first_dose_unit_code", "s", firstDoseUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("first_duration", "s", firstDuration, false);
        // 发药相关
        MYSQL_ADD_FIELD_NULLABLE("dispense_interval", "s", dispenseInterval, false);
        MYSQL_ADD_FIELD_NULLABLE("dispense_per_quantity", "i", dispensePerQuantity, false);
        MYSQL_ADD_FIELD_NULLABLE("dispense_per_duration", "i", dispensePerDuration, false);
        // 批号与追溯
        MYSQL_ADD_FIELD_NULLABLE("lot_number", "s", lotNumber, false);
        MYSQL_ADD_FIELD_NULLABLE("trace_no", "s", traceNo, false);
        // 特殊标志
        MYSQL_ADD_FIELD_NULLABLE("skin_test_flag", "b", skinTestFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("infusion_flag", "b", infusionFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("speed_code", "s", speedCode, false);
        // 合同与诊断
        MYSQL_ADD_FIELD_NULLABLE("contract_id", "s", contractId, false);
        MYSQL_ADD_FIELD_NULLABLE("condition_definition_id", "s", conditionDefinitionId, false);
        MYSQL_ADD_FIELD_NULLABLE("encounter_diagnosis_id", "s", encounterDiagnosisId, false);
        // 核对与退费
        MYSQL_ADD_FIELD_NULLABLE("performer_check_id", "s", performerCheckId, false);
        MYSQL_ADD_FIELD_NULLABLE("check_time", "dt", checkTime, false);
        MYSQL_ADD_FIELD_NULLABLE("effective_dose_end", "dt", effectiveDoseEnd, false);
        MYSQL_ADD_FIELD_NULLABLE("refund_medicine_id", "s", refundMedicineId, false);
        // 处方类型与医保
        MYSQL_ADD_FIELD_NULLABLE("rx_type_code", "s", rxTypeCode, false);
        MYSQL_ADD_FIELD_NULLABLE("yb_class_enum", "s", ybClassEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("dosage_instruction", "s", dosageInstruction, false);
        // 来源与中医
        MYSQL_ADD_FIELD_NULLABLE("based_on_table", "s", basedOnTable, false);
        MYSQL_ADD_FIELD_NULLABLE("based_on_id", "s", basedOnId, false);
        MYSQL_ADD_FIELD_NULLABLE("tcm_flag", "b", tcmFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("content_json", "s", contentJson, false);
        // 中药特有
        MYSQL_ADD_FIELD_NULLABLE("chinese_herbs_dose_quantity", "d", chineseHerbsDoseQuantity, false);
        MYSQL_ADD_FIELD_NULLABLE("suffering_flag", "b", sufferingFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("sort_number", "i", sortNumber, false);
        MYSQL_ADD_FIELD_NULLABLE("generate_source_enum", "s", generateSourceEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark, false);
    }
};

typedef std::shared_ptr<ChinapresDO1> PtrChinapresDO;

#endif // !_CHINAPRESDO1_H_
