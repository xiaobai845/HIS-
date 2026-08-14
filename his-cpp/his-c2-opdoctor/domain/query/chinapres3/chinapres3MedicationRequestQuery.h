#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 中药处方单据分页查询条件传输对象
 *
 * 封装中药处方主表列表查询所需过滤条件
 * 继承 PageQuery 自动携带分页参数：页码 pageIndex、每页条数 pageSize
 */
class chinapres3MedicationRequestQuery : public PageQuery
{
    DTO_INIT(chinapres3MedicationRequestQuery, PageQuery);

    // 处方流水号，支持模糊匹配查询
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

    // 处方状态枚举：DRAFT草稿、ACTIVE已开立、CANCELLED已作废
    DTO_FIELD(String, statusEnum);
    DTO_FIELD_INFO(statusEnum) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.statusEnum");
    }
};

#include OATPP_CODEGEN_END(DTO)