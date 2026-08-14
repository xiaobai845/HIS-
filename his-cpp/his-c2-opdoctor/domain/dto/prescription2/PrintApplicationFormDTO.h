#pragma once

#ifndef _PRINTAPPLICATIONFORMDTO_H_
#define _PRINTAPPLICATIONFORMDTO_H_

#include "../../GlobalInclude.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(DTO)

class PrintApplicationFormDTO : public oatpp::DTO
{
    DTO_INIT(PrintApplicationFormDTO, DTO);

    // 待打印服务申请单标识
    API_DTO_FIELD_REQUIRE(String, serviceRequestId,
        ZH_WORDS_GETTER("medical-advice.field.service-request-id"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PRINTAPPLICATIONFORMDTO_H_
