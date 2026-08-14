#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 处方收费明细分页查询条件Query
 *
 * 封装处方收费明细列表查询所需筛选条件，继承分页查询基类
 * 继承PageQuery自动携带分页参数：页码pageIndex、每页条数pageSize
 *
 * 关联业务数据：通过 serviceTable + serviceId 关联匹配对应的药品处方记录
 */
class chinapres3ChargeItemQuery : public PageQuery
{
    DTO_INIT(chinapres3ChargeItemQuery, PageQuery);

    // 业务来源表名，固定值 "med_medication_request" 代表药品处方业务
    DTO_FIELD(String, serviceTable);
    DTO_FIELD_INFO(serviceTable) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.serviceTable");
    }

    // 业务主键ID，对应 serviceTable 指定表内的处方明细主键ID
    DTO_FIELD(String, serviceId);
    DTO_FIELD_INFO(serviceId) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.serviceId");
    }

    // 处方单据流水号
    DTO_FIELD(String, prescriptionNo);
    DTO_FIELD_INFO(prescriptionNo) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.prescriptionNo");
    }

    // 患者唯一标识ID
    DTO_FIELD(String, patientId);
    DTO_FIELD_INFO(patientId) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.patientId");
    }

    // 就诊记录唯一标识ID
    DTO_FIELD(String, encounterId);
    DTO_FIELD_INFO(encounterId) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.encounterId");
    }

    // ---- 处方撤回相关筛选条件 ----
    // 逻辑删除标识，撤回业务流程专用，用于过滤已做逻辑删除的收费记录
    DTO_FIELD(String, isDeleted);
    DTO_FIELD_INFO(isDeleted) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.isDeleted");
    }
};

#include OATPP_CODEGEN_END(DTO)