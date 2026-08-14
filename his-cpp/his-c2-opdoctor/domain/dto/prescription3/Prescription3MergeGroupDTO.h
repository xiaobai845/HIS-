#pragma once

#ifndef _PRESCRIPTION3_MERGE_GROUP_DTO_H_
#define _PRESCRIPTION3_MERGE_GROUP_DTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Merges two or more draft order units. Existing groups are expanded and
 * replaced by one server-generated group identifier.
 */
class Prescription3MergeGroupDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3MergeGroupDTO, DTO);

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
        ZH_WORDS_GETTER("prescription3.field.mergeAdviceIds"),
        true
    );
};

#include OATPP_CODEGEN_END(DTO)

#endif
