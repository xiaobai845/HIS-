#pragma once
#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 处方签署目标子DTO
 * 单次请求内单条待签署处方的数据封装
 */
class chinapres3SignTargetDTO : public oatpp::DTO
{
    DTO_INIT(chinapres3SignTargetDTO, DTO);

    // 处方主记录ID，对应数据库 med_medication_request 表主键id
    API_DTO_FIELD_REQUIRE(String, medicationRequestId, ZH_WORDS_GETTER("chinapres3.field.medicationRequestId"), true);

    // 处方分组标识（当前注释停用）
    // API_DTO_FIELD_REQUIRE(String, prescriptionGroupKey, ZH_WORDS_GETTER("chinapres3.field.prescriptionGroupKey"), true);
};

#include OATPP_CODEGEN_END(DTO)