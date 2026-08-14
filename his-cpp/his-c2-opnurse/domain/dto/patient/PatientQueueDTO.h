#ifndef _PATIENTQUEUEDTO_H_
#define _PATIENTQUEUEDTO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientQueueDTO : public oatpp::DTO
{
	DTO_INIT(PatientQueueDTO, DTO);
	// Encounter ID (used to link act and consumable queries)
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("patient1.field.encounterId"), true);
	// Patient name
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("patient1.field.name"), true);
	// Gender
	API_DTO_FIELD_REQUIRE(String, gender, ZH_WORDS_GETTER("patientqueue.field.gender"), true);
	// Age
	API_DTO_FIELD_REQUIRE(Int32, age, ZH_WORDS_GETTER("patientqueue.field.age"), true);
	// Visit time
	API_DTO_FIELD_REQUIRE(String, visitTime, ZH_WORDS_GETTER("patientqueue.field.visitTime"), true);
	// Queue number (business number)
	API_DTO_FIELD_REQUIRE(String, queueNumber, ZH_WORDS_GETTER("patientqueue.field.queueNumber"), true);
	// Payment type
	API_DTO_FIELD_REQUIRE(String, paymentType, ZH_WORDS_GETTER("patientqueue.field.paymentType"), true);
};

/**
 * 患者候诊队列分页DTO。
 */
class PatientQueuePageDTO : public PageDTO<PatientQueueDTO::Wrapper>
{
	DTO_INIT(PatientQueuePageDTO, PageDTO<PatientQueueDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTQUEUEDTO_H_
