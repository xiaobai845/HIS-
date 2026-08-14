#ifndef _PATIENTACTCONTROLLER_H_
#define _PATIENTACTCONTROLLER_H_

#include"domain/vo/patient/PatientVO.h"
#include"domain/query/patient/PatientAct.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("patient1.tags.tag")

class PatientActController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(PatientActController);
public:
	// Endpoint info definition
	// encounterId is a PATH parameter that identifies the visit.
	// No query filters — backend returns all acts for the encounter.
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("patient1.query.act"),
		actPatient, PatientActListJsonVO::Wrapper, API_TAG);
	// Endpoint binding
	// Path:    /patient/query-act/{encounterId}
	// Header:  Authorization
	ENDPOINT(API_M_GET, "/patient/query-act/{encounterId}", actPatient,
		PATH(String, encounterId),
		API_HANDLER_AUTH_PARAME) {
		std::string eid = encounterId ? encounterId.getValue("") : std::string("");
		API_HANDLER_RESP_VO(execActPatient(eid));
	}

private:
	// Execute patient act query
	PatientActListJsonVO::Wrapper execActPatient(const std::string& encounterId);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_PATIENTACTCONTROLLER_H_
