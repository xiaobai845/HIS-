#pragma once
#ifndef _PATIENTFINISHQUERY_H_
#define _PATIENTFINISHQUERY_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientFinishQuery : public oatpp::DTO
{
	DTO_INIT(PatientFinishQuery, DTO);

    //前端传入 encounterId唯一标识
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("finish.query.encounterId"), true);



};



#include OATPP_CODEGEN_END(DTO)

#endif // !_PATIENTFINISHQUERY_H_
