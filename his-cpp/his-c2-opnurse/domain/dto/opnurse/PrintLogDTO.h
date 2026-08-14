#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_DTO_
#define _PRINT_LOG_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PrintLogDTO : public oatpp::DTO
{
	DTO_INIT(PrintLogDTO, DTO);
	DTO_FIELD(String, id);
	DTO_FIELD_INFO(id) { info->description = ZH_WORDS_GETTER("opnurse3.field.id"); }
	DTO_FIELD(String, printJobId);
	DTO_FIELD_INFO(printJobId) { info->description = ZH_WORDS_GETTER("opnurse3.field.printJobId"); }
	DTO_FIELD(String, docType);
	DTO_FIELD_INFO(docType) { info->description = ZH_WORDS_GETTER("opnurse3.field.docType"); }
	DTO_FIELD(String, name);
	DTO_FIELD_INFO(name) { info->description = ZH_WORDS_GETTER("opnurse3.field.patientName"); }
	DTO_FIELD(String, printTime);
	DTO_FIELD_INFO(printTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.printTime"); }
	DTO_FIELD(String, printer);
	DTO_FIELD_INFO(printer) { info->description = ZH_WORDS_GETTER("opnurse3.field.printerName"); }
	DTO_FIELD(Int32, isReprint);
	DTO_FIELD_INFO(isReprint) { info->description = ZH_WORDS_GETTER("opnurse3.field.isReprint"); }
	DTO_FIELD(Int32, status);
	DTO_FIELD_INFO(status) { info->description = ZH_WORDS_GETTER("opnurse3.field.status"); }
	DTO_FIELD(String, operatorName);
	DTO_FIELD_INFO(operatorName) { info->description = ZH_WORDS_GETTER("opnurse3.field.operator"); }
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) { info->description = ZH_WORDS_GETTER("opnurse3.field.remark"); }
};

class PrintLogPageDTO : public PageDTO<PrintLogDTO::Wrapper>
{
	DTO_INIT(PrintLogPageDTO, PageDTO<PrintLogDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRINT_LOG_DTO_
