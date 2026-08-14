#pragma once
#ifndef _AdmissionQuery_H_
#define _AdmissionQuery_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Admission2Query : public oatpp::DTO
{
	DTO_INIT(Admission2Query, DTO);

	API_DTO_FIELD_DEFAULT(String, num, ZH_WORDS_GETTER("cyclectrl2.patient.patientNo"));
	API_DTO_FIELD_REQUIRE(String, admissionDepartment, ZH_WORDS_GETTER("cyclectrl2.admission.admissionDepartment"), true);
	API_DTO_FIELD_REQUIRE(String, admissionWard, ZH_WORDS_GETTER("cyclectrl2.admission.admissionWard"), true);
	API_DTO_FIELD_REQUIRE(String, diagnosisType, ZH_WORDS_GETTER("cyclectrl2.admission.diagnosisType"), true);
	API_DTO_FIELD_REQUIRE(String, admissionDiagnosis, ZH_WORDS_GETTER("cyclectrl2.admission.admissionDiagnosis"), true);
	API_DTO_FIELD_DEFAULT(String, diagnosisSyndrome, ZH_WORDS_GETTER("cyclectrl2.admission.diagnosisSyndrome"));
	API_DTO_FIELD_DEFAULT(String, diagnosisDesc, ZH_WORDS_GETTER("cyclectrl2.admission.diagnosisDesc"));
	API_DTO_FIELD_REQUIRE(String, admissionType, ZH_WORDS_GETTER("cyclectrl2.admission.admissionType"), true);
	API_DTO_FIELD_REQUIRE(String, admissionMethod, ZH_WORDS_GETTER("cyclectrl2.admission.admissionMethod"), true);
	API_DTO_FIELD_REQUIRE(String, priority, ZH_WORDS_GETTER("cyclectrl2.admission.priority"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif
