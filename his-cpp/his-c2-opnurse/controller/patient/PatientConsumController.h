#ifndef _PATIENTCONSUMCONTROLLER_H_
#define _PATIENTCONSUMCONTROLLER_H_

#include"domain/vo/patient/PatientVO.h"
#include"domain/query/patient/PatientConsumable.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("patient1.tags.tag")

class PatientConsumController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(PatientConsumController);
public:
	// Endpoint info definition
	// Design contract:
	//   - encounterId is a PATH parameter (implicit filter, identifies the visit)
	//   - consumableRoom is a QUERY parameter (user-entered filter)
	//   - patientId is NOT passed explicitly: the backend derives the patient
	//     from the encounter via adm_encounter.patient_id, so the caller
	//     only needs to know which encounter to query.
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("patient1.queryconsum.consum"),
		consumPatient, PatientConsumQuery, PatientConsumListJsonVO::Wrapper, API_TAG);
	// Endpoint binding
	// Path:    /patient/query-consum/{encounterId}
	// Query:   consumableRoom
	// Header:  Authorization
	ENDPOINT(API_M_GET, "/patient/query-consum/{encounterId}", consumPatient,
		PATH(String, encounterId),
		QUERIES(QueryParams, queryParams),
		API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, PatientConsumQuery, queryParams);
		std::string eid = encounterId ? encounterId.getValue("") : std::string("");
		API_HANDLER_RESP_VO(execConsumPatient(query, eid));
	}

private:
	// Execute patient consumable query
	PatientConsumListJsonVO::Wrapper execConsumPatient(
		const PatientConsumQuery::Wrapper& query,
		const std::string& encounterId);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_PATIENTCONSUMCONTROLLER_H_
