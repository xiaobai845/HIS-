#pragma once

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiagnoseAddVO : oatpp::DTO
{
    DTO_INIT(DiagnoseAddVO, DTO)

    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("diagnose.add.id"), true);
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("diagnose.add.encounterId"), true);
    API_DTO_FIELD_REQUIRE(String, description, ZH_WORDS_GETTER("diagnose.add.description"), true);
    API_DTO_FIELD_REQUIRE(Int8, primaryFlag, ZH_WORDS_GETTER("diagnose.add.primaryFlag"), true);
    API_DTO_FIELD_REQUIRE(String, createdAt, ZH_WORDS_GETTER("diagnose.add.createdAt"), true);
};

class DiagnoseAddJsonVO : public JsonVO<DiagnoseAddVO::Wrapper>
{
	DTO_INIT(DiagnoseAddJsonVO, JsonVO<DiagnoseAddVO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)