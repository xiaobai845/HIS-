#pragma once

#ifndef _WITHDRAWMEDICALADVICEDTO_H_
#define _WITHDRAWMEDICALADVICEDTO_H_

#include "../../GlobalInclude.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(DTO)

class WithdrawMedicalAdviceDTO : public oatpp::DTO
{
    DTO_INIT(WithdrawMedicalAdviceDTO, DTO);

    // 包含医嘱记录的就诊标识
    API_DTO_FIELD_REQUIRE(String, encounterId,
        ZH_WORDS_GETTER("medical-advice.field.encounter-id"), true);
    // 期望的乐观锁版本号
    API_DTO_FIELD_REQUIRE(Int32, version,
        ZH_WORDS_GETTER("medical-advice.field.version"), true);
    // 待撤回的医嘱标识列表
    API_DTO_FIELD_REQUIRE(List<String>, adviceIds,
        ZH_WORDS_GETTER("medical-advice.field.advice-ids"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_WITHDRAWMEDICALADVICEDTO_H_
