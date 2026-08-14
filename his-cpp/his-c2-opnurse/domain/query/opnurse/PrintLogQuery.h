#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_QUERY_
#define _PRINT_LOG_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PrintLogQuery : public PageQuery
{
	DTO_INIT(PrintLogQuery, PageQuery);
	DTO_FIELD(String, patientId);
	DTO_FIELD_INFO(patientId) { info->description = ZH_WORDS_GETTER("opnurse3.field.patientId"); }
	DTO_FIELD(Int32, status);
	DTO_FIELD_INFO(status) { info->description = ZH_WORDS_GETTER("opnurse3.field.status"); }
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) { info->description = ZH_WORDS_GETTER("opnurse3.field.startDate"); }
	DTO_FIELD(String, endDate);
	DTO_FIELD_INFO(endDate) { info->description = ZH_WORDS_GETTER("opnurse3.field.endDate"); }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRINT_LOG_QUERY_
