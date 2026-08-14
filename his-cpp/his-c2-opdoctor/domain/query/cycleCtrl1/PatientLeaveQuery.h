#pragma once
#ifndef _PATIENTLEAVEQUERY_H_
#define _PATIENTLEAVEQUERY_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientLeaveQuery : public oatpp::DTO
{
	DTO_INIT(PatientLeaveQuery, DTO);

	//╬ем╗▒Ж╩Х
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("leave.query.encounterId"), true);
};




#include OATPP_CODEGEN_END(DTO)



#endif // !_PATIENTLEAVEQUERY_H_
