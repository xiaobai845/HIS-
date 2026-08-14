#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_MAPPER_
#define _PRINT_LOG_MAPPER_

#include "Mapper.h"
#include "../../domain/do/opnurse/PrintLogDO.h"

class PrintLogMapper : public Mapper<PrintLogDO>
{
public:
	PrintLogDO mapper(ResultSet* resultSet) const override
	{
		PrintLogDO data;
		data.setId(resultSet->getString(1));
		data.setPrintJobId(resultSet->getString(2));
		data.setDocType(resultSet->getString(3));
		data.setPatientName(resultSet->getString(4));
		data.setPrintTime(resultSet->getString(5));
		data.setPrinterName(resultSet->getString(6));
		data.setIsReprint(resultSet->getInt(7));
		data.setStatus(resultSet->getInt(8));
		data.setOperatorName(resultSet->getString(9));
		data.setRemark(resultSet->getString(10));
		data.setCreateTime(resultSet->getString(11));
		return data;
	}
};

#endif // !_PRINT_LOG_MAPPER_
