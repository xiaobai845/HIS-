#ifndef _PATIENTQUEUE_H_
#define _PATIENTQUEUE_H_
#include"../../GlobalInclude.h"
#include"domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientQuery :public PageQuery
{
	DTO_INIT(PatientQuery, PageQuery);
	// Keyword (patient name or queue number)
	API_DTO_FIELD_REQUIRE(String, keyword, ZH_WORDS_GETTER("patient1.field.name"), false);
	// Start date
	API_DTO_FIELD_REQUIRE(String, startDate, ZH_WORDS_GETTER("patient1.field.date"), false);
	// End date
	API_DTO_FIELD_REQUIRE(String, endDate, ZH_WORDS_GETTER("patient1.field.date"), false);

};
#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTQUEUE_H_
