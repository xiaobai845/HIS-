#pragma once

#ifndef _PRESCRIPTION3_SPLIT_GROUP_DTO_H_
#define _PRESCRIPTION3_SPLIT_GROUP_DTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Splits complete draft groups. Passing any group member selects its complete
 * group.
 */
class Prescription3SplitGroupDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3SplitGroupDTO, DTO);

    API_DTO_FIELD_REQUIRE(
        String,
        encounterId,
        ZH_WORDS_GETTER("prescription3.field.encounterId"),
        true
    );

    API_DTO_FIELD_REQUIRE(
        Int32,
        version,
        ZH_WORDS_GETTER("prescription3.field.version"),
        true
    );

    API_DTO_FIELD_REQUIRE(
        List<String>,
        adviceIds,
        ZH_WORDS_GETTER("prescription3.field.splitAdviceIds"),
        true
    );
};

#include OATPP_CODEGEN_END(DTO)

#endif
