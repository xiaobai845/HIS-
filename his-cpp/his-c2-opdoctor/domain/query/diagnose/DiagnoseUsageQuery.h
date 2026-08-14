#pragma once

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiagnoseUsageQuery : public PageQuery
{
	DTO_INIT(DiagnoseUsageQuery, PageQuery);

	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("diagnose.usage.keyword"));
	API_DTO_FIELD_DEFAULT(String, diagTypeCode, ZH_WORDS_GETTER("diagnose.usage.diagTypeCode"));
	API_DTO_FIELD_DEFAULT(String, startDate, ZH_WORDS_GETTER("diagnose.usage.startDate"));
	API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("diagnose.usage.endDate"));
};

#include OATPP_CODEGEN_END(DTO)