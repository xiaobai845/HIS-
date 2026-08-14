#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_CONTROLLER_
#define _PRINT_LOG_CONTROLLER_

#include "ApiHelper.h"
#include "domain/vo/opnurse/PrintLogVO.h"
#include "domain/query/opnurse/PrintLogQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)


#define API_TAG ZH_WORDS_GETTER("opnurse3.tags.log")

class PrintLogController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(PrintLogController);
public:
	ENDPOINT_INFO(queryRecords) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("opnurse3.records.summary");
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON_WRAPPER(PrintLogPageJsonVO);
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "patientId", ZH_WORDS_GETTER("opnurse3.field.patientId"), "", false);
		API_DEF_ADD_QUERY_PARAMS(Int32, "status", ZH_WORDS_GETTER("opnurse3.field.status"), -1, false);
		API_DEF_ADD_QUERY_PARAMS(String, "startDate", ZH_WORDS_GETTER("opnurse3.field.startDate"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "endDate", ZH_WORDS_GETTER("opnurse3.field.endDate"), "", false);
	}
	// GET /opnurse/records
	ENDPOINT(API_M_GET, "/opnurse/records", queryRecords, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, PrintLogQuery, params);
		return createDtoResponse(Status::CODE_200, executeQueryRecords(query));
	}

private:
	PrintLogPageJsonVO::Wrapper executeQueryRecords(const PrintLogQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif // !_PRINT_LOG_CONTROLLER_
