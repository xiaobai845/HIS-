#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/29
*/
#ifndef _EXECUTION_DAO_
#define _EXECUTION_DAO_
#include "BaseDAO.h"
#include "../../domain/do/opnurse/ExecutionDO.h"

class ExecutionDAO : public BaseDAO
{
public:
	// Query multiple execution items by document IDs
	std::list<ExecutionDO> selectByIds(const std::list<std::string>& ids);
	// Query single execution item
	ExecutionDO selectOne(const std::string& id);
};
#endif // !_EXECUTION_DAO_
