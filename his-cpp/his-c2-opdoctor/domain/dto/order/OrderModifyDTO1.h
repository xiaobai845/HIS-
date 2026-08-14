#pragma once
#ifndef _ORDER_MODIFY_DTO_1_H_
#define _ORDER_MODIFY_DTO_1_H_

#include "domain/dto/order/OrderAddDTO1.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 修改医嘱请求
 *
 * 设计说明：
 * - 仅允许修改 DRAFT 状态的医嘱
 * - 仅允许修改自己开的医嘱（requester_id 校验）
 * - 支持乐观锁版本控制（version 必传）
 * - 目录字段（catalogId、itemName、spec、unitPrice 等）不可修改
 * - orderNo 允许修改，用于前端拖拽排序
 *
 * 兼容字段：
 * - visitId 自动映射到 encounterId
 * - dosage 自动映射到 dose
 * - quantityInt 自动映射到 quantity
 */
class OrderModifyDTO1 : public oatpp::DTO {
    DTO_INIT(OrderModifyDTO1, DTO);

    // 定位字段
    API_DTO_FIELD_REQUIRE(String, orderId, ZH_WORDS_GETTER("createOrder.order.field.orderId"), true);
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("createOrder.order.field.encounterId"), true);
    API_DTO_FIELD_REQUIRE(Int32, version, ZH_WORDS_GETTER("createOrder.order.field.version"), true);

    // 允许修改的字段
    API_DTO_FIELD_REQUIRE(Float64, dose, ZH_WORDS_GETTER("createOrder.order.field.dose"), false);
    API_DTO_FIELD_REQUIRE(String, doseUnit, ZH_WORDS_GETTER("createOrder.order.field.doseUnit"), false);
    API_DTO_FIELD_REQUIRE(String, frequency, ZH_WORDS_GETTER("createOrder.order.field.frequency"), false);
    API_DTO_FIELD_REQUIRE(String, routeCode, ZH_WORDS_GETTER("createOrder.order.field.routeCode"), false);
    API_DTO_FIELD_REQUIRE(Int32, useDays, ZH_WORDS_GETTER("createOrder.order.field.useDays"), false);
    API_DTO_FIELD_REQUIRE(Float64, quantity, ZH_WORDS_GETTER("createOrder.order.field.quantity"), false);
    API_DTO_FIELD_REQUIRE(String, quantityUnit, ZH_WORDS_GETTER("createOrder.order.field.quantityUnit"), false);
    API_DTO_FIELD_REQUIRE(Boolean, isSkinTest, ZH_WORDS_GETTER("createOrder.order.field.isSkinTest"), false);
    API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("createOrder.order.field.remark"), false);

    // 分组与排序
    API_DTO_FIELD_REQUIRE(String, groupId, ZH_WORDS_GETTER("createOrder.order.field.groupId"), false);
    API_DTO_FIELD_REQUIRE(Int32, orderNo, ZH_WORDS_GETTER("createOrder.order.field.orderNo"), false);

    // === 关联 PayloadDTO ===
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

#include OATPP_CODEGEN_END(DTO)
#endif