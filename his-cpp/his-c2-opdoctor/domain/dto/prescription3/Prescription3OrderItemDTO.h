#pragma once

#ifndef _PRESCRIPTION3_ORDER_ITEM_DTO_H_
#define _PRESCRIPTION3_ORDER_ITEM_DTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Identifies one outpatient order in one of the supported order tables.
 */
class Prescription3OrderItemDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3OrderItemDTO, DTO);

    API_DTO_FIELD_REQUIRE(
        String,
        id,
        ZH_WORDS_GETTER("prescription3.field.orderId"),
        true
    );

    API_DTO_FIELD_REQUIRE(
        String,
        type,
        ZH_WORDS_GETTER("prescription3.field.orderType"),
        true
    );
};

#include OATPP_CODEGEN_END(DTO)

#endif
