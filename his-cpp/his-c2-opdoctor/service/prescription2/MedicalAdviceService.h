#pragma once

#ifndef _MEDICAL_ADVICESERVICE_H_
#define _MEDICAL_ADVICESERVICE_H_

#include "domain/dto/prescription2/PrintApplicationFormDTO.h"
#include "domain/dto/prescription2/SignMedicalAdviceDTO.h"
#include "domain/dto/prescription2/WithdrawMedicalAdviceDTO.h"
#include <list>

// 医嘱业务服务
class MedicalAdviceService
{
public:
    // 将草稿状态医嘱记录变更为已签发状态
    std::list<std::string> signMedicalAdvice(
        const SignMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload);
    // 将已签发医嘱记录变更为撤回状态
    std::list<std::string> withdrawMedicalAdvice(
        const WithdrawMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload);
    // 记录一次服务申请单打印操作
    std::string printApplicationForm(
        const PrintApplicationFormDTO::Wrapper& dto, const PayloadDTO& payload);

private:
    // 移除空标识和重复标识，同时保留请求顺序
    std::list<std::string> normalizeAdviceIds(
        const oatpp::List<oatpp::String>& adviceIds) const;
};

#endif // !_MEDICAL_ADVICESERVICE_H_
