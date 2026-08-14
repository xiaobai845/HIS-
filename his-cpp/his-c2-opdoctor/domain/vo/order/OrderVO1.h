#pragma once
#ifndef _ORDER_VO_1_H_
#define _ORDER_VO_1_H_

#include "../../dto/order/OrderDetailDTO1.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 医嘱详情分页 JSON 响应 VO
 */
class OrderDetailPageJsonVO1 : public JsonVO<OrderDetailPageDTO1::Wrapper> {
    DTO_INIT(OrderDetailPageJsonVO1, JsonVO<OrderDetailPageDTO1::Wrapper>);
};

/**
 * 单条医嘱详情 JSON 响应 VO
 */
class OrderDetailJsonVO1 : public JsonVO<OrderDetailDTO1::Wrapper> {
    DTO_INIT(OrderDetailJsonVO1, JsonVO<OrderDetailDTO1::Wrapper>);
};

/**
 * 批量新增医嘱 JSON 响应 VO
 * 专门用于返回 List<OrderDetailDTO1>
 */
class OrderBatchJsonVO : public JsonVO<oatpp::List<OrderDetailDTO1::Wrapper>> {
    DTO_INIT(OrderBatchJsonVO, JsonVO<oatpp::List<OrderDetailDTO1::Wrapper>>);
};

#include OATPP_CODEGEN_END(DTO)
#endif