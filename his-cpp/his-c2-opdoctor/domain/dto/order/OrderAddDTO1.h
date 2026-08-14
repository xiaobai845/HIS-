#pragma once
#ifndef _ORDER_ADD_DTO_1_H_
#define _ORDER_ADD_DTO_1_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 新增医嘱请求
 *
 * 设计说明：
 * - 前端传入 encounterId、catalogId、orderType，后端自动推导 patientId 和项目信息
 * - 剂量使用数值类型 + 独立单位字段
 * - 数量使用数值类型 + 独立单位字段
 * - orderNo（sortNumber）由前端维护，强制必填
 * - groupId 用于组套关联
 *
 * 兼容字段：
 * - visitId 自动映射到 encounterId
 * - itemCode 自动映射到 catalogId
 * - dosage 自动映射到 dose
 * - quantityInt 自动映射到 quantity
 */
class OrderAddDTO1 : public oatpp::DTO {
    DTO_INIT(OrderAddDTO1, DTO);

   // 上下文
API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("createOrder.order.field.encounterId"), true);
API_DTO_FIELD_REQUIRE(String, catalogId, ZH_WORDS_GETTER("createOrder.order.field.catalogId"), true);
API_DTO_FIELD_REQUIRE(String, orderType, ZH_WORDS_GETTER("createOrder.order.field.orderType"), true);
API_DTO_FIELD_REQUIRE(String, expenseType, ZH_WORDS_GETTER("createOrder.order.field.expenseType"), true);

// 临床决策
API_DTO_FIELD_REQUIRE(Float64, dose, ZH_WORDS_GETTER("createOrder.order.field.dose"), false);
API_DTO_FIELD_REQUIRE(String, doseUnit, ZH_WORDS_GETTER("createOrder.order.field.doseUnit"), false);
API_DTO_FIELD_REQUIRE(String, frequency, ZH_WORDS_GETTER("createOrder.order.field.frequency"), false);
API_DTO_FIELD_REQUIRE(String, routeCode, ZH_WORDS_GETTER("createOrder.order.field.routeCode"), false);
API_DTO_FIELD_REQUIRE(Int32, useDays, ZH_WORDS_GETTER("createOrder.order.field.useDays"), false);
API_DTO_FIELD_REQUIRE(Float64, quantity, ZH_WORDS_GETTER("createOrder.order.field.quantity"), true);
API_DTO_FIELD_REQUIRE(String, quantityUnit, ZH_WORDS_GETTER("createOrder.order.field.quantityUnit"), true);
API_DTO_FIELD_REQUIRE(Boolean, isSkinTest, ZH_WORDS_GETTER("createOrder.order.field.isSkinTest"), false);
API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("createOrder.order.field.remark"), false);

// 分组与排序
API_DTO_FIELD_REQUIRE(String, groupId, ZH_WORDS_GETTER("createOrder.order.field.groupId"), false);
API_DTO_FIELD_REQUIRE(Int32, orderNo, ZH_WORDS_GETTER("createOrder.order.field.orderNo"), true);

// 兼容旧字段
API_DTO_FIELD_REQUIRE(String, itemCode, ZH_WORDS_GETTER("createOrder.order.field.itemCode"), false);
    // === 关联 PayloadDTO ===
protected:
    const PayloadDTO* _payload;
public:
    const PayloadDTO* getPayload(void) const { return _payload; }
    void setPayload(const PayloadDTO* var) { _payload = var; }
};

#include OATPP_CODEGEN_END(DTO)
#endif