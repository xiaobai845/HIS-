#pragma once

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiagnoseDeleteVO : public oatpp::DTO
{
	DTO_INIT(DiagnoseDeleteVO, DTO);

	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("diagnose.delete.id"), true);
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("diagnose.delete.encounterId"), true);
	API_DTO_FIELD_REQUIRE(String, conditionId, ZH_WORDS_GETTER("diagnose.delete.conditionId"), true);
	API_DTO_FIELD_REQUIRE(String, deletedAt, ZH_WORDS_GETTER("diagnose.delete.deletedAt"), true);
	API_DTO_FIELD_REQUIRE(String, deletedBy, ZH_WORDS_GETTER("diagnose.delete.deletedBy"), true);
};

class DiagnoseDeleteJsonVO : public JsonVO<DiagnoseDeleteVO::Wrapper>
{
	DTO_INIT(DiagnoseDeleteJsonVO, JsonVO<DiagnoseDeleteVO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)