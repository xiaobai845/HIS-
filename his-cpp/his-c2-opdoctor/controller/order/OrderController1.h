// controller/order/OrderController1.h
#pragma once
#ifndef _ORDER_CONTROLLER_1_H_
#define _ORDER_CONTROLLER_1_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/order/OrderQuery1.h"
#include "domain/vo/order/OrderVO1.h"
#include "domain/dto/order/OrderAddDTO1.h"
#include "domain/dto/order/OrderDetailDTO1.h"
#include "domain/dto/order/OrderModifyDTO1.h"
#include "domain/dto/order/OrderBatchAddDTO1.h"
#include "domain/dto/PayloadDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("createOrder.order.tags.tag")

class OrderController1 : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(OrderController1);

public:
    // ========== 1. 分页查询医嘱 ==========
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("createOrder.order.query.summary"),
        queryOrder,
        OrderQuery1,
        OrderDetailPageJsonVO1::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/createOrder/query",
        queryOrder,
        OrderQuery1,
        execQueryOrder(query, authObject->getPayload())
    );

    // ========== 2. 新增单条医嘱 ==========
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("createOrder.order.add.summary"),
        addOrder,
        OrderDetailJsonVO1::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/createOrder/add",
        addOrder,
        BODY_DTO(OrderAddDTO1::Wrapper, dto),
        execAddOrder(dto, authObject->getPayload())
    );

    // ========== 3. 修改医嘱 ==========
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("createOrder.order.modify.summary"),
        modifyOrder,
        OrderDetailJsonVO1::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_AUTH(
        API_M_PUT,
        "/createOrder/modify",
        modifyOrder,
        BODY_DTO(OrderModifyDTO1::Wrapper, dto),
        execModifyOrder(dto, authObject->getPayload())
    );

    // ========== 4. 批量新增医嘱 ==========
    // 使用 OrderBatchJsonVO::Wrapper 替代复杂的模板类型
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("createOrder.order.batchAdd.summary"),
        batchAddOrder,
        OrderBatchJsonVO::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST,
        "/createOrder/batchAdd",
        batchAddOrder,
        BODY_DTO(OrderBatchAddDTO1::Wrapper, dto),
        execBatchAddOrder(dto, authObject->getPayload())
    );

private:
    OrderDetailPageJsonVO1::Wrapper execQueryOrder(
        const OrderQuery1::Wrapper& query,
        const PayloadDTO& payload
    );

    OrderDetailJsonVO1::Wrapper execAddOrder(
        const OrderAddDTO1::Wrapper& dto,
        const PayloadDTO& payload
    );

    OrderDetailJsonVO1::Wrapper execModifyOrder(
        const OrderModifyDTO1::Wrapper& dto,
        const PayloadDTO& payload
    );

    OrderBatchJsonVO::Wrapper execBatchAddOrder(
        const OrderBatchAddDTO1::Wrapper& dto,
        const PayloadDTO& payload
    );
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif