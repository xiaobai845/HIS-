#ifndef _MEDICALRECORDCONTROLLER_
#define _MEDICALRECORDCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/outpatientrecord/MedicalRecordQuery.h"
#include "domain/vo/outpatientrecord/MedicalRecordPageJsonVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) 
#define API_TAG ZH_WORDS_GETTER("medicalrecord.tags.tag")

class MedicalRecordController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(MedicalRecordController);
public:

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("medicalrecord.query.summary"), queryMedicalRecord, MedicalRecordQuery, MedicalRecordPageJsonVO::Wrapper , API_TAG);

	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/medicalrecord", queryMedicalRecord, MedicalRecordQuery, executeQueryMedicalRecord(query));

private:
	MedicalRecordPageJsonVO::Wrapper executeQueryMedicalRecord(const MedicalRecordQuery::Wrapper& query);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 

#endif // _MEDICALRECORDCONTROLLER_