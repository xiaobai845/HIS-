#include "stdafx.h"
#include "Prescription2Controller.h"
#include "service/prescription2/MedicalAdviceService.h"

SignMedicalAdviceJsonVO::Wrapper Prescription2Controller::execSignMedicalAdvice(
    const SignMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload)
{
    auto response = SignMedicalAdviceJsonVO::createShared();
    // 开始签发前校验请求字段
    if (!dto || !dto->encounterId || dto->encounterId->empty() ||
        !dto->version || dto->version < 0 || !dto->adviceIds || dto->adviceIds->empty())
    {
        response->init(nullptr, RS_PARAMS_INVALID);
        return response;
    }

    // 将状态流转委托给服务层
    const auto signedIds = MedicalAdviceService().signMedicalAdvice(dto, payload);
    if (signedIds.empty())
    {
        response->fail(nullptr);
        return response;
    }

    // 将已签发标识转换为响应数据
    auto data = oatpp::List<oatpp::String>::createShared();
    for (const auto& id : signedIds)
    {
        data->push_back(id.c_str());
    }
    response->success(data);
    return response;
}

WithdrawMedicalAdviceJsonVO::Wrapper Prescription2Controller::execWithdrawMedicalAdvice(
    const WithdrawMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload)
{
    auto response = WithdrawMedicalAdviceJsonVO::createShared();
    // 开始撤回前校验请求字段
    if (!dto || !dto->encounterId || dto->encounterId->empty() ||
        !dto->version || dto->version < 0 || !dto->adviceIds || dto->adviceIds->empty())
    {
        response->init(nullptr, RS_PARAMS_INVALID);
        return response;
    }

    // 将状态流转委托给服务层
    const auto withdrawnIds = MedicalAdviceService().withdrawMedicalAdvice(dto, payload);
    if (withdrawnIds.empty())
    {
        response->fail(nullptr);
        return response;
    }

    // 将已撤回标识转换为响应数据
    auto data = oatpp::List<oatpp::String>::createShared();
    for (const auto& id : withdrawnIds)
    {
        data->push_back(id.c_str());
    }
    response->success(data);
    return response;
}

PrintApplicationFormJsonVO::Wrapper Prescription2Controller::execPrintApplicationForm(
    const PrintApplicationFormDTO::Wrapper& dto, const PayloadDTO& payload)
{
    auto response = PrintApplicationFormJsonVO::createShared();
    // 打印操作必须指定一个服务申请单
    if (!dto || !dto->serviceRequestId || dto->serviceRequestId->empty())
    {
        response->init(nullptr, RS_PARAMS_INVALID);
        return response;
    }

    // 将打印次数更新委托给服务层
    const std::string serviceRequestId = MedicalAdviceService().printApplicationForm(dto, payload);
    if (serviceRequestId.empty())
    {
        response->fail(nullptr);
        return response;
    }

    response->success(serviceRequestId.c_str());
    return response;
}
