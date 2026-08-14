#if 0
#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/24 18:00:00
*/
#ifndef _CHINAPRES2_VIEW_DO_
#define _CHINAPRES2_VIEW_DO_
#include "Chinapres2MainDO.h"

/**
 * 处方视图 DO (用于复杂联表查询，不直接对应物理表)
 * 分页列表展示时使用，扩展了主表没有的关联字段
 */
class Chinapres2ViewDO : public Chinapres2MainDO
{
    // ---------- 关联查询扩展字段 ----------
    // 诊断名称 (来自 encounter_diagnosis 表)
    MYSQL_SYNTHESIZE(string, diagnosisName, DiagnosisName);
    // 开方医生姓名 (来自 user 表)
    MYSQL_SYNTHESIZE(string, requesterName, RequesterName);
    // 处方总金额 (由明细表 sum(quantity * unit_price) 计算得出)
    MYSQL_SYNTHESIZE(double, totalPrice, TotalPrice);
    // 药材名称拼接字符串 (如 "黄芪, 当归, 甘草")，由明细表 + 药品字典表 group_concat 得到
    MYSQL_SYNTHESIZE(string, medicationNames, MedicationNames);

public:
    // 视图 DO 不需要构造时映射字段，因为它的数据由 SQL 填充，不走 BaseDO 的 insert/update
    // 但为了统一，可以保留空构造，或者不继承 BaseDO 的构造逻辑
    Chinapres2ViewDO() : Chinapres2MainDO()
    {
        // 注意：这里不添加 MYSQL_ADD_FIELD，因为视图字段不参与持久化
        // 这些字段只在 Service 层执行 select 联查时由 DB 结果集映射填充
    }
};

typedef std::shared_ptr<Chinapres2ViewDO> PtrChinapres2ViewDO;

#endif // !_CHINAPRES2_VIEW_DO_

#endif