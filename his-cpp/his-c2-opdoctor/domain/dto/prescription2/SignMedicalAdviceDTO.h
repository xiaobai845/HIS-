#pragma once

#ifndef _SIGNMEDICALADVICEDTO_H_
#define _SIGNMEDICALADVICEDTO_H_

#include "../../GlobalInclude.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(DTO)

class SignMedicalAdviceDTO : public oatpp::DTO
{
    DTO_INIT(SignMedicalAdviceDTO, DTO);

    // 包含医嘱记录的就诊标识
    API_DTO_FIELD_REQUIRE(String, encounterId,
        ZH_WORDS_GETTER("medical-advice.field.encounter-id"), true);
    // 期望的乐观锁版本号
    API_DTO_FIELD_REQUIRE(Int32, version,
        ZH_WORDS_GETTER("medical-advice.field.version"), true);
    // 待签发的医嘱标识列表
    API_DTO_FIELD_REQUIRE(List<String>, adviceIds,
        ZH_WORDS_GETTER("medical-advice.field.advice-ids"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_SIGNMEDICALADVICEDTO_H_
