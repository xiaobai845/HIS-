#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_DO_
#define _PRINT_LOG_DO_

#include "../DoInclude.h"


class PrintLogDO : public BaseDO
{
	//×Ö¶ÎÉùÃ÷
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, printJobId, PrintJobId);
	MYSQL_SYNTHESIZE(string, docType, DocType);
	MYSQL_SYNTHESIZE(string, patientName, PatientName);
	MYSQL_SYNTHESIZE(string, printTime, PrintTime);
	MYSQL_SYNTHESIZE(string, printerName, PrinterName);
	MYSQL_SYNTHESIZE(int, isReprint, IsReprint);
	MYSQL_SYNTHESIZE(int, status, Status);
	MYSQL_SYNTHESIZE(string, operatorName, OperatorName);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, createTime, CreateTime);

public:
	PrintLogDO() : BaseDO("print_log")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("print_job_id", "s", printJobId);
		MYSQL_ADD_FIELD("doc_type", "s", docType);
		MYSQL_ADD_FIELD("patient_name", "s", patientName);
		MYSQL_ADD_FIELD("print_time", "dt", printTime);
		MYSQL_ADD_FIELD("printer_name", "s", printerName);
		MYSQL_ADD_FIELD("is_reprint", "i", isReprint);
		MYSQL_ADD_FIELD("status", "i", status);
		MYSQL_ADD_FIELD("operator", "s", operatorName);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("create_time", "dt", createTime);
	}
};

typedef std::shared_ptr<PrintLogDO> PtrPrintLogDO;
#endif // !_PRINT_LOG_DO_
