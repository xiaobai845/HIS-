/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#include "stdafx.h"
#include "PrintLogService.h"

PrintLogPageDTO::Wrapper PrintLogService::listAll(const PrintLogQuery::Wrapper& query)
{
	auto pages = PrintLogPageDTO::createShared();
	pages->pageIndex = query->pageIndex;
	pages->pageSize = query->pageSize;

	PrintLogDAO dao;
	uint64_t count = dao.count(query);
	if (count <= 0)
	{
		return pages;
	}

	pages->total = count;
	pages->calcPages();
	list<PrintLogDO> result = dao.selectWithPage(query);

	for (PrintLogDO& sub : result)
	{
		auto dto = PrintLogDTO::createShared();
		ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub,
			id, Id,
			printJobId, PrintJobId,
			docType, DocType,
			name, PatientName,
			printTime, PrintTime,
			printer, PrinterName,
			isReprint, IsReprint,
			status, Status,
			operatorName, OperatorName,
			remark, Remark
		);
		pages->addData(dto);
	}
	return pages;
}
