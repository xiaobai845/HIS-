#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/24 18:00:00
*/
#ifndef _CHINAPRES2_DETAIL_DO_
#define _CHINAPRES2_DETAIL_DO_
#include "../DoInclude.h"

/**
 * 中医处方明细表 DO (对应表 med_medication_request_detail)
 * 存储每味药材的规格、数量、单价等
 */
class Chinapres2DetailDO : public BaseDO
{
    // 明细主键
    MYSQL_SYNTHESIZE(string, id, Id);
    // 关联主表ID (外键)
    MYSQL_SYNTHESIZE(string, requestId, RequestId);
    // 药品ID (关联字典表)
    MYSQL_SYNTHESIZE(string, medicationId, MedicationId);
    // 药材数量 (如 10)
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    // 数量单位 (如 g)
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
    // 单次剂量 (通常与quantity一致)
    MYSQL_SYNTHESIZE(double, dose, Dose);
    // 剂量单位
    MYSQL_SYNTHESIZE(string, doseUnitCode, DoseUnitCode);
    // 排序号 (用于前端显示顺序)
    MYSQL_SYNTHESIZE(int, sortNo, SortNo);

    // 通用审计字段（如果你的BaseDO不提供，就自己加上）
    MYSQL_SYNTHESIZE(string, createBy, CreateBy);
    MYSQL_SYNTHESIZE(string, createTime, CreateTime);
    MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
    MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);

public:
    Chinapres2DetailDO() : BaseDO("med_medication_request_detail")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("request_id", "s", requestId);          // 外键关联主表
        MYSQL_ADD_FIELD("medication_id", "s", medicationId);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("dose", "d", dose, false);
        MYSQL_ADD_FIELD_NULLABLE("dose_unit_code", "s", doseUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("sort_no", "i", sortNo, false);

        // 审计字段
        MYSQL_ADD_FIELD_NULLABLE("create_by", "s", createBy, false);
        MYSQL_ADD_FIELD_NULLABLE("create_time", "s", createTime, false);
        MYSQL_ADD_FIELD_NULLABLE("update_by", "s", updateBy, false);
        MYSQL_ADD_FIELD_NULLABLE("update_time", "s", updateTime, false);
    }
};

typedef std::shared_ptr<Chinapres2DetailDO> PtrChinapres2DetailDO;

#endif // !_CHINAPRES2_DETAIL_DO_