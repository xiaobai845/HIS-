#pragma once
#ifndef _PrescriptionQuery_H_
#define _PrescriptionQuery_H_

#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Prescription2Query :public oatpp::DTO
{
	DTO_INIT(Prescription2Query, DTO);
	//患者病例号
	API_DTO_FIELD_DEFAULT(String, num, ZH_WORDS_GETTER("cyclectrl2.patient.patientNo"));
	//本次/历史处方
	API_DTO_FIELD_DEFAULT(String, type, ZH_WORDS_GETTER("cyclectrl2.patient.timetype"));
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_QUERY_H_
