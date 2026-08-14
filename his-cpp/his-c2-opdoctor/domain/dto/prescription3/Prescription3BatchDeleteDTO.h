#pragma once

#ifndef _PRESCRIPTION3_BATCH_DELETE_DTO_H_
#define _PRESCRIPTION3_BATCH_DELETE_DTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Deletes draft outpatient orders. A selected group member expands to its
 * complete group. Order types are resolved by the backend.
 */
class Prescription3BatchDeleteDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3BatchDeleteDTO, DTO);

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
        ZH_WORDS_GETTER("prescription3.field.deleteAdviceIds"),
        true
    );
};

#include OATPP_CODEGEN_END(DTO)

#endif
