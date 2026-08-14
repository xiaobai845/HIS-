#include "stdafx.h"
#include "Prescription3Controller.h"

namespace
{
Prescription3AffectedOrderDTO::Wrapper affectedOrder(
    const std::string& id,
    const std::string& type,
    const std::string& groupId)
{
    auto item = Prescription3AffectedOrderDTO::createShared();
    item->adviceId = id;
    item->type = type;
    item->groupId = groupId;
    return item;
}

std::string orderTypeName(Prescription3OrderType type)
{
    switch (type)
    {
    case Prescription3OrderType::Medication:
        return "MEDICATION";
    case Prescription3OrderType::Service:
        return "SERVICE";
    case Prescription3OrderType::Device:
        return "DEVICE";
    }
    return "UNKNOWN";
}

oatpp::List<oatpp::Object<Prescription3AffectedOrderDTO>>
toAffectedOrders(const std::vector<Prescription3OrderDO>& orders)
{
    auto result = oatpp::List<
        oatpp::Object<Prescription3AffectedOrderDTO>>::createShared();
    for (const auto& order : orders)
    {
        result->push_back(affectedOrder(
            order.id, orderTypeName(order.type), order.groupId));
    }
    return result;
}

Prescription3DeleteJsonVO::Wrapper makeDeleteResponse(
    bool success,
    int affectedCount,
    const std::string& message,
    int code = 10000,
    int version = 0,
    const std::string& updatedAt = "")
{
    auto vo = Prescription3DeleteJsonVO::createShared();
    vo->data = Prescription3DeleteResultDTO::createShared();
    vo->data->success = success;
    vo->data->affectedCount = affectedCount;
    vo->data->version = version;
    vo->data->updatedAt = updatedAt;
    vo->data->message = message;
    vo->setStatus(ResultStatus(message, code));
    return vo;
}

Prescription3MergeJsonVO::Wrapper makeMergeResponse(
    bool success,
    int affectedCount,
    const std::string& groupId,
    const std::string& message,
    int code = 10000,
    int version = 0,
    const std::string& updatedAt = "")
{
    auto vo = Prescription3MergeJsonVO::createShared();
    vo->data = Prescription3MergeResultDTO::createShared();
    vo->data->success = success;
    vo->data->affectedCount = affectedCount;
    vo->data->groupId = groupId;
    vo->data->version = version;
    vo->data->updatedAt = updatedAt;
    vo->data->message = message;
    vo->setStatus(ResultStatus(message, code));
    return vo;
}

Prescription3SplitJsonVO::Wrapper makeSplitResponse(
    bool success,
    int affectedCount,
    const std::string& message,
    int code = 10000,
    int version = 0,
    const std::string& updatedAt = "")
{
    auto vo = Prescription3SplitJsonVO::createShared();
    vo->data = Prescription3SplitResultDTO::createShared();
    vo->data->success = success;
    vo->data->affectedCount = affectedCount;
    vo->data->version = version;
    vo->data->updatedAt = updatedAt;
    vo->data->message = message;
    vo->setStatus(ResultStatus(message, code));
    return vo;
}
}

void Prescription3Controller::addBatchDeleteSwaggerExamples(
    const std::shared_ptr<EndpointInfo>& info)
{
    auto request = Prescription3BatchDeleteDTO::createShared();
    request->encounterId = "330900000000000001";
    request->version = 2;
    request->adviceIds = {
        "331100000000000001",
        "331100000000000002"
    };
    info->body.description =
        ZH_WORDS_GETTER("prescription3.batchDelete.description");
    info->body.addExample("default", request);
    auto success = makeDeleteResponse(
        true, 3, "Orders deleted successfully", 10000, 3,
        "2026-07-18 10:30:00.123456");
    success->data->affectedOrders = {
        affectedOrder("331100000000000001", "MEDICATION", ""),
        affectedOrder("331100000000000002", "SERVICE", "")
    };
    info->responses[Status::CODE_200].addExample("success", success);
    info->responses[Status::CODE_200].addExample(
        "invalidStatus",
        makeDeleteResponse(
            false,
            0,
            "Only DRAFT orders can be changed",
            PRESCRIPTION3_INVALID_STATUS));
    info->responses[Status::CODE_200].addExample(
        "versionConflict",
        makeDeleteResponse(
            false,
            0,
            "The order list version is stale; refresh and retry",
            PRESCRIPTION3_CONCURRENT_CHANGE));
}

void Prescription3Controller::addMergeSwaggerExamples(
    const std::shared_ptr<EndpointInfo>& info)
{
    auto request = Prescription3MergeGroupDTO::createShared();
    request->encounterId = "330900000000000001";
    request->version = 2;
    request->adviceIds = {
        "331100000000000001",
        "331100000000000002"
    };
    info->body.description =
        ZH_WORDS_GETTER("prescription3.mergeGroup.description");
    info->body.addExample("default", request);
    auto success = makeMergeResponse(
        true,
        3,
        "331234567890123456",
        "Orders merged successfully",
        10000,
        3,
        "2026-07-18 10:30:00.123456");
    success->data->affectedOrders = {
        affectedOrder("331100000000000001", "MEDICATION",
            "331234567890123456"),
        affectedOrder("331100000000000002", "DEVICE",
            "331234567890123456")
    };
    info->responses[Status::CODE_200].addExample("success", success);
    info->responses[Status::CODE_200].addExample(
        "scopeMismatch",
        makeMergeResponse(
            false,
            0,
            "",
            "Orders must have the same business scope",
            PRESCRIPTION3_SCOPE_MISMATCH));
    info->responses[Status::CODE_200].addExample(
        "encounterNotEditable",
        makeMergeResponse(
            false,
            0,
            "",
            "Only an IN_PROGRESS encounter can change orders",
            PRESCRIPTION3_INVALID_STATUS));
}

void Prescription3Controller::addSplitSwaggerExamples(
    const std::shared_ptr<EndpointInfo>& info)
{
    auto request = Prescription3SplitGroupDTO::createShared();
    request->encounterId = "330900000000000001";
    request->version = 2;
    request->adviceIds = {
        "331100000000000001"
    };
    info->body.description =
        ZH_WORDS_GETTER("prescription3.splitGroup.description");
    info->body.addExample("default", request);
    auto success = makeSplitResponse(
        true, 3, "Order group split successfully", 10000, 3,
        "2026-07-18 10:30:00.123456");
    success->data->affectedOrders = {
        affectedOrder("331100000000000001", "MEDICATION", ""),
        affectedOrder("331100000000000002", "SERVICE", "")
    };
    info->responses[Status::CODE_200].addExample("success", success);
    info->responses[Status::CODE_200].addExample(
        "invalidGroup",
        makeSplitResponse(
            false,
            0,
            "Only grouped orders can be split",
            PRESCRIPTION3_INVALID_GROUP));
    info->responses[Status::CODE_200].addExample(
        "versionConflict",
        makeSplitResponse(
            false,
            0,
            "The order list version is stale; refresh and retry",
            PRESCRIPTION3_CONCURRENT_CHANGE));
}

Prescription3DeleteJsonVO::Wrapper
Prescription3Controller::execBatchDeletePrescription3(
    const Prescription3BatchDeleteDTO::Wrapper& dto,
    const PayloadDTO& payload)
{
    try
    {
        Prescription3Service service;
        const auto result = service.batchDelete(dto, payload.getId());
        auto response = makeDeleteResponse(
            true,
            result.affectedRows,
            "Orders deleted successfully",
            10000,
            result.version,
            result.updatedAt);
        response->data->affectedOrders =
            toAffectedOrders(result.affectedOrders);
        return response;
    }
    catch (const Prescription3BusinessException& exception)
    {
        return makeDeleteResponse(
            false, 0, exception.what(), exception.code());
    }
    catch (const sql::SQLException&)
    {
        return makeDeleteResponse(
            false,
            0,
            "Database operation failed",
            PRESCRIPTION3_DATABASE_ERROR);
    }
    catch (const std::exception&)
    {
        return makeDeleteResponse(
            false, 0, "Server operation failed", 9994);
    }
}

Prescription3MergeJsonVO::Wrapper
Prescription3Controller::execMergePrescription3Group(
    const Prescription3MergeGroupDTO::Wrapper& dto,
    const PayloadDTO& payload)
{
    try
    {
        Prescription3Service service;
        const auto result = service.mergeGroup(dto, payload.getId());
        auto response = makeMergeResponse(
            true,
            result.affectedRows,
            result.groupId,
            "Orders merged successfully",
            10000,
            result.version,
            result.updatedAt);
        response->data->affectedOrders =
            toAffectedOrders(result.affectedOrders);
        return response;
    }
    catch (const Prescription3BusinessException& exception)
    {
        return makeMergeResponse(
            false, 0, "", exception.what(), exception.code());
    }
    catch (const sql::SQLException&)
    {
        return makeMergeResponse(
            false,
            0,
            "",
            "Database operation failed",
            PRESCRIPTION3_DATABASE_ERROR);
    }
    catch (const std::exception&)
    {
        return makeMergeResponse(
            false, 0, "", "Server operation failed", 9994);
    }
}

Prescription3SplitJsonVO::Wrapper
Prescription3Controller::execSplitPrescription3Group(
    const Prescription3SplitGroupDTO::Wrapper& dto,
    const PayloadDTO& payload)
{
    try
    {
        Prescription3Service service;
        const auto result = service.splitGroup(dto, payload.getId());
        auto response = makeSplitResponse(
            true,
            result.affectedRows,
            "Order group split successfully",
            10000,
            result.version,
            result.updatedAt);
        response->data->affectedOrders =
            toAffectedOrders(result.affectedOrders);
        return response;
    }
    catch (const Prescription3BusinessException& exception)
    {
        return makeSplitResponse(
            false, 0, exception.what(), exception.code());
    }
    catch (const sql::SQLException&)
    {
        return makeSplitResponse(
            false,
            0,
            "Database operation failed",
            PRESCRIPTION3_DATABASE_ERROR);
    }
    catch (const std::exception&)
    {
        return makeSplitResponse(
            false, 0, "Server operation failed", 9994);
    }
}
