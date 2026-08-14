#pragma once

#include "domain/GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientDiagnoseQuery : public PageQuery
{
	DTO_INIT(PatientDiagnoseQuery, PageQuery);

	API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("diagnose.patient.patientId"), true);
	API_DTO_FIELD_DEFAULT(String, keyword, ZH_WORDS_GETTER("diagnose.patient.keyword"));
	API_DTO_FIELD_DEFAULT(String, diagTypeCode, ZH_WORDS_GETTER("diagnose.patient.diagTypeCode"));
	API_DTO_FIELD_DEFAULT(String, startDate, ZH_WORDS_GETTER("diagnose.patient.startDate"));
	API_DTO_FIELD_DEFAULT(String, endDate, ZH_WORDS_GETTER("diagnose.patient.endDate"));
};

#include OATPP_CODEGEN_END(DTO)