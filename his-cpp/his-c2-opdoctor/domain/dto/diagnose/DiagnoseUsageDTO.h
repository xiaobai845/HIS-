#pragma once

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiagnoseUsageDTO : public oatpp::DTO
{
	DTO_INIT(DiagnoseUsageDTO, DTO)

	API_DTO_FIELD_DEFAULT(String, id, ZH_WORDS_GETTER("diagnose.usage.id"));
	API_DTO_FIELD_DEFAULT(String, encounterId, ZH_WORDS_GETTER("diagnose.usage.encounterId"));
	API_DTO_FIELD_DEFAULT(String, conditionId, ZH_WORDS_GETTER("diagnose.usage.conditionId"));
	API_DTO_FIELD_DEFAULT(String, description, ZH_WORDS_GETTER("diagnose.usage.description"));
	API_DTO_FIELD_DEFAULT(String, diagTypeCode, ZH_WORDS_GETTER("diagnose.usage.diagTypeCode"));
	API_DTO_FIELD_DEFAULT(Int32, diagCode, ZH_WORDS_GETTER("diagnose.usage.diagCode"));
	API_DTO_FIELD_DEFAULT(Int32, rank, ZH_WORDS_GETTER("diagnose.usage.rank"));
	API_DTO_FIELD_DEFAULT(Int8, primaryFlag, ZH_WORDS_GETTER("diagnose.usage.primaryFlag"));
	API_DTO_FIELD_DEFAULT(Int8, highestDiagFlag, ZH_WORDS_GETTER("diagnose.usage.highestDiagFlag"));
	API_DTO_FIELD_DEFAULT(Int8, tcmFlag, ZH_WORDS_GETTER("diagnose.usage.tcmFlag"));
	API_DTO_FIELD_DEFAULT(String, tcmSyndromeGroup, ZH_WORDS_GETTER("diagnose.usage.tcmSyndromeGroup"));
	API_DTO_FIELD_DEFAULT(String, medType, ZH_WORDS_GETTER("diagnose.usage.medType"));
	API_DTO_FIELD_DEFAULT(Int32, conditionCode, ZH_WORDS_GETTER("diagnose.usage.conditionCode"));
	API_DTO_FIELD_DEFAULT(String, createdAt, ZH_WORDS_GETTER("diagnose.usage.createdAt"));
};

#include OATPP_CODEGEN_END(DTO)
