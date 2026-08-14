#pragma once

#ifndef _PRESCRIPTION3_CONTROLLER_H_
#define _PRESCRIPTION3_CONTROLLER_H_

#include "../../domain/GlobalInclude.h"
#include "../../domain/dto/prescription3/Prescription3BatchDeleteDTO.h"
#include "../../domain/dto/prescription3/Prescription3MergeGroupDTO.h"
#include "../../domain/dto/prescription3/Prescription3SplitGroupDTO.h"
#include "../../domain/vo/prescription3/Prescription3OperationVO.h"
#include "../../service/prescription3/Prescription3Service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("prescription3.tags.tag")

class Prescription3Controller
    : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(Prescription3Controller);

public:
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("prescription3.batchDelete.summary"),
        batchDeletePrescription3,
        Prescription3DeleteJsonVO::Wrapper,
        API_TAG,
        addBatchDeleteSwaggerExamples(info);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_DEL,
        "/prescription3/batch",
        batchDeletePrescription3,
        BODY_DTO(Prescription3BatchDeleteDTO::Wrapper, dto),
        execBatchDeletePrescription3(dto, authObject->getPayload())
    );

    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("prescription3.mergeGroup.summary"),
        mergePrescription3Group,
        Prescription3MergeJsonVO::Wrapper,
        API_TAG,
        addMergeSwaggerExamples(info);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_PUT,
        "/prescription3/group/merge",
        mergePrescription3Group,
        BODY_DTO(Prescription3MergeGroupDTO::Wrapper, dto),
        execMergePrescription3Group(dto, authObject->getPayload())
    );

    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("prescription3.splitGroup.summary"),
        splitPrescription3Group,
        Prescription3SplitJsonVO::Wrapper,
        API_TAG,
        addSplitSwaggerExamples(info);
    );

    API_HANDLER_ENDPOINT_AUTH(
        API_M_PUT,
        "/prescription3/group/split",
        splitPrescription3Group,
        BODY_DTO(Prescription3SplitGroupDTO::Wrapper, dto),
        execSplitPrescription3Group(dto, authObject->getPayload())
    );

private:
    using EndpointInfo =
        oatpp::web::server::api::Endpoint::Info;

    static void addBatchDeleteSwaggerExamples(
        const std::shared_ptr<EndpointInfo>& info);
    static void addMergeSwaggerExamples(
        const std::shared_ptr<EndpointInfo>& info);
    static void addSplitSwaggerExamples(
        const std::shared_ptr<EndpointInfo>& info);

    Prescription3DeleteJsonVO::Wrapper execBatchDeletePrescription3(
        const Prescription3BatchDeleteDTO::Wrapper& dto,
        const PayloadDTO& payload);

    Prescription3MergeJsonVO::Wrapper execMergePrescription3Group(
        const Prescription3MergeGroupDTO::Wrapper& dto,
        const PayloadDTO& payload);

    Prescription3SplitJsonVO::Wrapper execSplitPrescription3Group(
        const Prescription3SplitGroupDTO::Wrapper& dto,
        const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif
