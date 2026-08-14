#include "stdafx.h"
#include "ChinapresController1.h"
#include "service/chinapres1/ChinapresService1.h"

ChinapresJsonVO1::Wrapper ChinapresController1::executeQueryChinapres(const ChinapresQuery1::Wrapper& query)
{
	ChinapresService1 service;
	auto jvo = ChinapresJsonVO1::createShared();
	auto list = service.queryList(query);
	jvo->success(list);
	return jvo;
}

ChinapresDetailJsonVO1::Wrapper ChinapresController1::executeQueryChinapresDetail(const ChinapresDetailQuery1::Wrapper& query)
{
	ChinapresService1 service;
	auto jvo = ChinapresDetailJsonVO1::createShared();
	auto detail = service.queryDetail(query);
	if (detail) {
		jvo->success(detail);
	}
	else {
		jvo->fail({});
	}
	return jvo;
}
