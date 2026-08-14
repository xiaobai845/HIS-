#pragma once
#ifndef _ORDER_QUERY_1_H_
#define _ORDER_QUERY_1_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 医嘱分页查询请求
 * 支持关键词搜索、类型筛选、状态筛选
 */
class OrderQuery1 : public PageQuery
{
    DTO_INIT(OrderQuery1, PageQuery);

    // 就诊ID（必填）
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("createOrder.order.field.encounterId"), true);

    // 关键词搜索（可选，支持编码/名称/拼音码/商品名模糊匹配）
    API_DTO_FIELD_REQUIRE(String, keyword, ZH_WORDS_GETTER("createOrder.common.keyword"), false);

    // 医嘱类型筛选（可选，medication / service / device）
    API_DTO_FIELD_REQUIRE(String, orderType, ZH_WORDS_GETTER("createOrder.order.field.orderType"), false);

    // 状态筛选（可选，支持多状态，如 ["DRAFT","SIGNED"]，不传返回全部）
    API_DTO_FIELD_REQUIRE(List<String>, statusList, ZH_WORDS_GETTER("createOrder.order.field.status"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif