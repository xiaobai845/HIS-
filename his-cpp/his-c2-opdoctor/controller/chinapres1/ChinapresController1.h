#pragma once

#ifndef _CHINAPRESCONTROLLER1_
#define _CHINAPRESCONTROLLER1_

#include "domain/vo/BaseJsonVO.h"
#include"domain/query/chinapres1/ChinapresQuery1.h"
#include"domain/query/chinapres1/ChinapresDetailQuery1.h"
#include"domain/vo/chinapres1/ChinapresVO1.h"

#include OATPP_CODEGEN_BEGIN(ApiController) 
#define API_TAG ZH_WORDS_GETTER("chinapres1.tags.tag")

class ChinapresController1: public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ChinapresController1);
public:

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("chinapres1.query.summary"), queryChinapres, ChinapresQuery1, ChinapresJsonVO1::Wrapper, API_TAG);

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("chinapres1.detail.summary"), queryChinapresdetails, ChinapresDetailQuery1, ChinapresDetailJsonVO1::Wrapper, API_TAG);
	//响应
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/chinapres", queryChinapres, ChinapresQuery1, executeQueryChinapres(query));
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/chinapres-datail", queryChinapresdetails, ChinapresDetailQuery1, executeQueryChinapresDetail(query));
private:
	ChinapresJsonVO1::Wrapper executeQueryChinapres(const ChinapresQuery1::Wrapper& query);
	ChinapresDetailJsonVO1::Wrapper executeQueryChinapresDetail(const ChinapresDetailQuery1::Wrapper&query);

};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController) 

#endif // _CHINAPRESCONTROLLER1_