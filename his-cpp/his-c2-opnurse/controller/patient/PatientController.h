#ifndef _PATIENTCONTROLLER_H_
#define _PATIENTCONTROLLER_H_

#include"domain/vo/BaseJsonVO.h"
#include"domain/query/patient/PatientQuery.h"
#include"domain/vo/patient/PatientVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("patient1.tags.tag")

class PatientController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(PatientController);
public:
	// Endpoint info definition
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("patient1.query.summary"),
		queryPatient, PatientQuery, PatientQueuePageJsonVO::Wrapper, API_TAG);
	// Endpoint binding
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/patient/query",
		queryPatient, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, PatientQuery, queryParams);
		std::string userId = authObject->getPayload().getId();
		API_HANDLER_RESP_VO(execQueryPatient(query, userId));
	)

private:
	// Execute paginated patient queue query
	PatientQueuePageJsonVO::Wrapper execQueryPatient(const PatientQuery::Wrapper& query, const std::string& userId);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_PATIENTCONTROLLER_H_