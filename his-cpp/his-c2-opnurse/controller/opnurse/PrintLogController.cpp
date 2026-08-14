/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#include "stdafx.h"
#include "PrintLogController.h"
#include "../../service/opnurse/PrintLogService.h"

PrintLogPageJsonVO::Wrapper PrintLogController::executeQueryRecords(const PrintLogQuery::Wrapper& query)
{
	auto result = PrintLogService().listAll(query);
	auto jvo = PrintLogPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
}
