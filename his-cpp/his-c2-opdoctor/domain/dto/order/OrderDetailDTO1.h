#pragma once
#ifndef _ORDER_DETAIL_DTO_1_H_
#define _ORDER_DETAIL_DTO_1_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 医嘱详情 DTO（数据对象，用于业务层传递）
 */
class OrderDetailDTO1 : public oatpp::DTO {
    DTO_INIT(OrderDetailDTO1, DTO);

    // 基础信息
    API_DTO_FIELD_REQUIRE(String, orderId, ZH_WORDS_GETTER("createOrder.order.field.orderId"), true);
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("createOrder.order.field.encounterId"), true);
    API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("createOrder.order.field.patientId"), true);
    API_DTO_FIELD_REQUIRE(String, doctorId, ZH_WORDS_GETTER("createOrder.order.field.doctorId"), true);
    API_DTO_FIELD_REQUIRE(String, doctorName, ZH_WORDS_GETTER("createOrder.order.field.doctorName"), true);

    // 目录信息
    API_DTO_FIELD_REQUIRE(String, catalogId, ZH_WORDS_GETTER("createOrder.order.field.catalogId"), true);
    API_DTO_FIELD_REQUIRE(String, itemCode, ZH_WORDS_GETTER("createOrder.order.field.itemCode"), true);
    API_DTO_FIELD_REQUIRE(String, itemName, ZH_WORDS_GETTER("createOrder.order.field.itemName"), true);
    API_DTO_FIELD_REQUIRE(String, spec, ZH_WORDS_GETTER("createOrder.order.field.spec"), true);
    API_DTO_FIELD_REQUIRE(Float64, unitPrice, ZH_WORDS_GETTER("createOrder.order.field.unitPrice"), true);
    API_DTO_FIELD_REQUIRE(String, orderType, ZH_WORDS_GETTER("createOrder.order.field.orderType"), true);

    // 分类信息
    API_DTO_FIELD_REQUIRE(String, categoryCode, ZH_WORDS_GETTER("createOrder.order.field.categoryCode"), false);
    API_DTO_FIELD_REQUIRE(String, categoryName, ZH_WORDS_GETTER("createOrder.order.field.categoryName"), false);

    // 临床决策
    API_DTO_FIELD_REQUIRE(Float64, dose, ZH_WORDS_GETTER("createOrder.order.field.dose"), false);
    API_DTO_FIELD_REQUIRE(String, doseUnit, ZH_WORDS_GETTER("createOrder.order.field.doseUnit"), false);
    API_DTO_FIELD_REQUIRE(String, frequency, ZH_WORDS_GETTER("createOrder.order.field.frequency"), false);
    API_DTO_FIELD_REQUIRE(String, routeCode, ZH_WORDS_GETTER("createOrder.order.field.routeCode"), false);
    API_DTO_FIELD_REQUIRE(Int32, useDays, ZH_WORDS_GETTER("createOrder.order.field.useDays"), false);
    API_DTO_FIELD_REQUIRE(Float64, quantity, ZH_WORDS_GETTER("createOrder.order.field.quantity"), true);
    API_DTO_FIELD_REQUIRE(String, quantityUnit, ZH_WORDS_GETTER("createOrder.order.field.quantityUnit"), false);
    API_DTO_FIELD_REQUIRE(String, contentPerUnit, ZH_WORDS_GETTER("createOrder.order.field.contentPerUnit"), false);
    API_DTO_FIELD_REQUIRE(Boolean, isSkinTest, ZH_WORDS_GETTER("createOrder.order.field.isSkinTest"), false);
    API_DTO_FIELD_REQUIRE(Float64, totalPrice, ZH_WORDS_GETTER("createOrder.order.field.totalPrice"), true);

    // 状态
    API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("createOrder.order.field.status"), true);
    API_DTO_FIELD_REQUIRE(String, statusDisplay, ZH_WORDS_GETTER("createOrder.order.field.statusDisplay"), false);

    // 分组与排序
    API_DTO_FIELD_REQUIRE(String, groupId, ZH_WORDS_GETTER("createOrder.order.field.groupId"), false);
    API_DTO_FIELD_REQUIRE(Int32, orderNo, ZH_WORDS_GETTER("createOrder.order.field.orderNo"), false);

    // 时间与版本
    API_DTO_FIELD_REQUIRE(String, createTime, ZH_WORDS_GETTER("createOrder.order.field.createTime"), true);
    API_DTO_FIELD_REQUIRE(String, updatedAt, ZH_WORDS_GETTER("createOrder.order.field.updatedAt"), false);
    API_DTO_FIELD_REQUIRE(Int32, version, ZH_WORDS_GETTER("createOrder.order.field.version"), false);

    // 其他
    API_DTO_FIELD_REQUIRE(String, prescriptionNo, ZH_WORDS_GETTER("createOrder.order.field.prescriptionNo"), false);
    API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("createOrder.order.field.remark"), false);

    // 显示名
    API_DTO_FIELD_REQUIRE(String, orderTypeDisplay, ZH_WORDS_GETTER("createOrder.order.field.orderTypeDisplay"), false);
    API_DTO_FIELD_REQUIRE(String, frequencyDisplay, ZH_WORDS_GETTER("createOrder.order.field.frequencyDisplay"), false);
    API_DTO_FIELD_REQUIRE(String, routeDisplay, ZH_WORDS_GETTER("createOrder.order.field.routeDisplay"), false);
};

/**
 * 分页容器 DTO
 */
class OrderDetailPageDTO1 : public PageDTO<OrderDetailDTO1::Wrapper> {
    DTO_INIT(OrderDetailPageDTO1, PageDTO<OrderDetailDTO1::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _ORDER_DETAIL_DTO_1_H_