// controller/order/OrderController1.cpp
#include "stdafx.h"
#include "OrderController1.h"
#include "../../service/order/OrderService1.h"
#include "../../service/ClientManager.h"
#include "domain/vo/BaseJsonVO.h"
#include <list>

// ========== 1. 分页查询医嘱 ==========
OrderDetailPageJsonVO1::Wrapper OrderController1::execQueryOrder(
    const OrderQuery1::Wrapper& query,
    const PayloadDTO& payload)
{
    auto service = OrderService1(
        ClientManager::getRedisClient(),
        ClientManager::getMongoClient()
    );

    auto pageDto = service.queryOrderList(query, &payload);

    auto jvo = OrderDetailPageJsonVO1::createShared();
    jvo->success(pageDto);
    return jvo;
}

// ========== 2. 新增单条医嘱 ==========
OrderDetailJsonVO1::Wrapper OrderController1::execAddOrder(
    const OrderAddDTO1::Wrapper& dto,
    const PayloadDTO& payload)
{
    auto service = OrderService1(
        ClientManager::getRedisClient(),
        ClientManager::getMongoClient()
    );

    std::string errorMsg;
    auto result = service.addOrder(dto, &payload, errorMsg);

    auto jvo = OrderDetailJsonVO1::createShared();

    if (!errorMsg.empty()) {
        jvo->setStatus(RS_FAIL);
        jvo->message = oatpp::String(errorMsg);
        return jvo;
    }

    if (!result) {
        jvo->setStatus(RS_FAIL);
        jvo->message = oatpp::String("Failed to add order: unknown error");
        return jvo;
    }

    jvo->success(result);
    return jvo;
}

// ========== 3. 修改医嘱 ==========
OrderDetailJsonVO1::Wrapper OrderController1::execModifyOrder(
    const OrderModifyDTO1::Wrapper& dto,
    const PayloadDTO& payload)
{
    auto service = OrderService1(
        ClientManager::getRedisClient(),
        ClientManager::getMongoClient()
    );

    std::string errorMsg;
    auto result = service.modifyOrder(dto, &payload, errorMsg);

    auto jvo = OrderDetailJsonVO1::createShared();

    if (!errorMsg.empty()) {
        jvo->setStatus(RS_FAIL);
        jvo->message = oatpp::String(errorMsg);
        return jvo;
    }

    if (!result) {
        jvo->setStatus(RS_FAIL);
        jvo->message = oatpp::String("Failed to modify order: unknown error");
        return jvo;
    }

    jvo->success(result);
    return jvo;
}

// ========== 4. 批量新增医嘱 ==========
OrderBatchJsonVO::Wrapper OrderController1::execBatchAddOrder(
    const OrderBatchAddDTO1::Wrapper& dto,
    const PayloadDTO& payload)
{
    auto jvo = OrderBatchJsonVO::createShared();

    if (!dto->orders || dto->orders->empty()) {
        jvo->setStatus(RS_PARAMS_INVALID);
        jvo->message = oatpp::String("Order list is empty");
        return jvo;
    }

    auto service = OrderService1(
        ClientManager::getRedisClient(),
        ClientManager::getMongoClient()
    );

    std::list<std::string> errors;
    auto results = service.batchAddOrder(dto->orders, &payload, errors);

    if (!errors.empty()) {
        std::string errorMsg = "Batch add failed: ";
        bool first = true;
        for (const auto& err : errors) {
            if (!first) errorMsg += "; ";
            first = false;
            errorMsg += err;
        }
        jvo->setStatus(RS_FAIL);
        jvo->message = oatpp::String(errorMsg);
        return jvo;
    }

    auto resultList = oatpp::List<OrderDetailDTO1::Wrapper>::createShared();
    for (auto& item : results) {
        resultList->push_back(item);
    }

    jvo->success(resultList);
    return jvo;
}