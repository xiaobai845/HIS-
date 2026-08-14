#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_DAO_
#define _PRINT_LOG_DAO_
#include "BaseDAO.h"
#include "../../domain/do/opnurse/PrintLogDO.h"
#include "../../domain/query/opnurse/PrintLogQuery.h"

class PrintLogDAO : public BaseDAO
{
private:
	inline std::string queryConditionBuilder(const PrintLogQuery::Wrapper& query, SqlParams& params);
public:
	uint64_t count(const PrintLogQuery::Wrapper& query);
	std::list<PrintLogDO> selectWithPage(const PrintLogQuery::Wrapper& query);
};
#endif // !_PRINT_LOG_DAO_
