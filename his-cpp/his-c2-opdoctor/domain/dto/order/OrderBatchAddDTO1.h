#pragma once
#ifndef _ORDER_BATCH_ADD_DTO_1_H_
#define _ORDER_BATCH_ADD_DTO_1_H_

#include "../../GlobalInclude.h"
#include "domain/dto/order/OrderAddDTO1.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 批量新增医嘱请求
 *
 * 设计说明：
 * - 前端一次性传入多条医嘱数据
 * - 后端使用事务保证全部成功或全部失败（原子性）
 * - 每条医嘱独立校验，任一失败则整体回滚
 */
class OrderBatchAddDTO1 : public oatpp::DTO {
    DTO_INIT(OrderBatchAddDTO1, DTO);

    // 批量新增列表（必传，至少一条）
    API_DTO_FIELD_REQUIRE(List<OrderAddDTO1::Wrapper>, orders, ZH_WORDS_GETTER("createOrder.order.field.orderList"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif