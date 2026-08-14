#pragma once
#ifndef _ORDER_AUDIT_DTO_1_H_
#define _ORDER_AUDIT_DTO_1_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 医嘱操作审计日志 DTO
 * 写入 MongoDB order_audit_logs 集合
 */
class OrderAuditDTO1 : public oatpp::DTO {
    DTO_INIT(OrderAuditDTO1, DTO);

    API_DTO_FIELD_REQUIRE(String, orderId, ZH_WORDS_GETTER("createOrder.order.audit.orderId"), true);
    API_DTO_FIELD_REQUIRE(String, orderType, ZH_WORDS_GETTER("createOrder.order.audit.orderType"), true);
    API_DTO_FIELD_REQUIRE(String, operationType, ZH_WORDS_GETTER("createOrder.order.audit.operationType"), true);
    API_DTO_FIELD_REQUIRE(String, operatorId, ZH_WORDS_GETTER("createOrder.order.audit.operatorId"), true);
    API_DTO_FIELD_REQUIRE(String, operatorName, ZH_WORDS_GETTER("createOrder.order.audit.operatorName"), true);
    API_DTO_FIELD_REQUIRE(String, operatorOrgId, ZH_WORDS_GETTER("createOrder.order.audit.operatorOrgId"), true);
    API_DTO_FIELD_REQUIRE(String, operationTime, ZH_WORDS_GETTER("createOrder.order.audit.operationTime"), true);
    API_DTO_FIELD_REQUIRE(String, beforeData, ZH_WORDS_GETTER("createOrder.order.audit.beforeData"), false);
    API_DTO_FIELD_REQUIRE(String, afterData, ZH_WORDS_GETTER("createOrder.order.audit.afterData"), false);
    API_DTO_FIELD_REQUIRE(List<String>, changedFields, ZH_WORDS_GETTER("createOrder.order.audit.changedFields"), false);
    API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("createOrder.order.audit.remark"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif // _ORDER_AUDIT_DTO_1_H_