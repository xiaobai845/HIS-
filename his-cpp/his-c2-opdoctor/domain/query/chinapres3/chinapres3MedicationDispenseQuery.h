#pragma once
#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 处方发药记录分页查询条件Query
 *
 * 封装处方发药列表筛选条件，可通过处方ID、患者ID、就诊ID等条件过滤数据
 * 继承PageQuery自动携带分页参数：页码pageIndex、每页条数pageSize
 */
class chinapres3MedicationDispenseQuery : public PageQuery
{
    DTO_INIT(chinapres3MedicationDispenseQuery, PageQuery);

    // 药品申请单ID，关联药品处方表 med_medication_request.id
    DTO_FIELD(String, medReqId);
    DTO_FIELD_INFO(medReqId) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.medReqId");
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

    // 发药业务全局唯一流水号
    DTO_FIELD(String, busNo);
    DTO_FIELD_INFO(busNo) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.busNo");
    }

    // 发药状态编码：PREPARATION 待发药 / DISPENSED 已发药
    DTO_FIELD(String, statusEnum);
    DTO_FIELD_INFO(statusEnum) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.statusEnum");
    }

    // ---- 处方撤回相关筛选条件 ----
    // 逻辑删除标识，撤回业务流程使用，用于过滤掉已逻辑删除的数据
    DTO_FIELD(String, isDeleted);
    DTO_FIELD_INFO(isDeleted) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.isDeleted");
    }
};

#include OATPP_CODEGEN_END(DTO)