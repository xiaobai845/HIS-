#pragma once

#ifndef _MEDICAL_ADVICE_VO_
#define _MEDICAL_ADVICE_VO_

#include "../../GlobalInclude.h"
#include "../../dto/prescription2/PrintApplicationFormDTO.h"
#include "../../dto/prescription2/SignMedicalAdviceDTO.h"
#include "../../dto/prescription2/WithdrawMedicalAdviceDTO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(DTO)

// 医嘱签发成功时返回的 JSON 响应
class SignMedicalAdviceJsonVO : public JsonVO<List<String>>
{
    DTO_INIT(SignMedicalAdviceJsonVO, JsonVO<List<String>>);
};

// 医嘱撤回成功时返回的 JSON 响应
class WithdrawMedicalAdviceJsonVO : public JsonVO<List<String>>
{
    DTO_INIT(WithdrawMedicalAdviceJsonVO, JsonVO<List<String>>);
};

// 服务申请单打印成功时返回的 JSON 响应
class PrintApplicationFormJsonVO : public JsonVO<String>
{
    DTO_INIT(PrintApplicationFormJsonVO, JsonVO<String>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_MEDICAL_ADVICE_VO_
