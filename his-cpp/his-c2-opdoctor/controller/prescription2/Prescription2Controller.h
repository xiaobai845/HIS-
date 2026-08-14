#pragma once

#ifndef _PRESCRIPTION2CONTROLLER_H_
#define _PRESCRIPTION2CONTROLLER_H_

#include "domain/dto/prescription2/PrintApplicationFormDTO.h"
#include "domain/dto/prescription2/SignMedicalAdviceDTO.h"
#include "domain/dto/prescription2/WithdrawMedicalAdviceDTO.h"
#include "domain/vo/prescription2/MedicalAdviceVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("medical-advice.tags.tag")

// 医嘱业务操作控制器
class Prescription2Controller : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(Prescription2Controller);

public:
    // 签发选中的草稿状态医嘱记录
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("medical-advice.sign.summary"),
        signMedicalAdvice, SignMedicalAdviceJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/medical-advice/sign", signMedicalAdvice,
        BODY_DTO(SignMedicalAdviceDTO::Wrapper, dto),
        execSignMedicalAdvice(dto, authObject->getPayload()));

    // 撤回选中的已签发医嘱记录
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("medical-advice.withdraw.summary"),
        withdrawMedicalAdvice, WithdrawMedicalAdviceJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/medical-advice/withdraw", withdrawMedicalAdvice,
        BODY_DTO(WithdrawMedicalAdviceDTO::Wrapper, dto),
        execWithdrawMedicalAdvice(dto, authObject->getPayload()));

    // 增加服务申请单的打印次数
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("medical-advice.print-application-form.summary"),
        printApplicationForm, PrintApplicationFormJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/medical-advice/print-application-form", printApplicationForm,
        BODY_DTO(PrintApplicationFormDTO::Wrapper, dto),
        execPrintApplicationForm(dto, authObject->getPayload()));

private:
    // 校验并执行医嘱签发请求
    SignMedicalAdviceJsonVO::Wrapper execSignMedicalAdvice(
        const SignMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload);
    // 校验并执行医嘱撤回请求
    WithdrawMedicalAdviceJsonVO::Wrapper execWithdrawMedicalAdvice(
        const WithdrawMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload);
    // 校验并执行服务申请单打印操作
    PrintApplicationFormJsonVO::Wrapper execPrintApplicationForm(
        const PrintApplicationFormDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_PRESCRIPTION2CONTROLLER_H_
