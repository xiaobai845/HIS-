#ifndef _PATIENTACTDTO_H_
#define _PATIENTACTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientActDTO : public oatpp::DTO
{
	DTO_INIT(PatientActDTO, DTO);
	// Status
	API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("patient1.field.status"), true);
	// Order content
	API_DTO_FIELD_REQUIRE(String, orderContent, ZH_WORDS_GETTER("patient1.field.orderContent"), true);
	// Amount (formatted price)
	API_DTO_FIELD_REQUIRE(String, amount, ZH_WORDS_GETTER("patientact.field.amount"), true);
	// Whether executed
	API_DTO_FIELD_REQUIRE(Int32, isAct, ZH_WORDS_GETTER("patient1.field.act"), false);
};

/**
 * Wrapper DTO combining patient queue info and act item list.
 * Patient info is shown once at the top of the UI,
 * items are rendered as the data table below.
 */
class PatientActWrapperDTO : public oatpp::DTO
{
	DTO_INIT(PatientActWrapperDTO, DTO);
	// Patient name from queue
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("patientqueue.field.name"));
	// Patient gender from queue
	API_DTO_FIELD_DEFAULT(String, gender, ZH_WORDS_GETTER("patientqueue.field.gender"));
	// Patient age from queue
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("patientqueue.field.age"));
	// Act item list
	API_DTO_FIELD_DEFAULT(Vector<Object<PatientActDTO>>, items, ZH_WORDS_GETTER("patient1.field.act"));
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTACTDTO_H_
