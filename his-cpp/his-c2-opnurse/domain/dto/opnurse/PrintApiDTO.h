#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_API_DTO_
#define _PRINT_API_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// POST /opnurse/print request
class PrintRequestDTO : public oatpp::DTO
{
	DTO_INIT(PrintRequestDTO, DTO);
	// encounterId
	DTO_FIELD(String, encounterId);
	DTO_FIELD_INFO(encounterId) {
		info->description = ZH_WORDS_GETTER("opnurse3.field.encounterId");
		info->required = true;
	}
	// documentIds
	DTO_FIELD(List<String>, documentIds);
	DTO_FIELD_INFO(documentIds) {
		info->description = ZH_WORDS_GETTER("opnurse3.field.documentIds");
		info->required = true;
	}
	// documentType
	DTO_FIELD(String, documentType);
	DTO_FIELD_INFO(documentType) {
		info->description = ZH_WORDS_GETTER("opnurse3.field.documentType");
		info->required = true;
	}
	// reprint
	DTO_FIELD(Boolean, reprint);
	DTO_FIELD_INFO(reprint) {
		info->description = ZH_WORDS_GETTER("opnurse3.field.reprint");
	}
};

// POST /opnurse/print response
class PrintResultDTO : public oatpp::DTO
{
	DTO_INIT(PrintResultDTO, DTO);
	DTO_FIELD(Boolean, success);
	DTO_FIELD_INFO(success) { info->description = ZH_WORDS_GETTER("opnurse3.field.printSuccess"); }
	DTO_FIELD(String, printer);
	DTO_FIELD_INFO(printer) { info->description = ZH_WORDS_GETTER("opnurse3.field.printerName"); }
	DTO_FIELD(String, message);
	DTO_FIELD_INFO(message) { info->description = ZH_WORDS_GETTER("opnurse3.field.printMsg"); }
	DTO_FIELD(String, pdfBase64);
	DTO_FIELD_INFO(pdfBase64) { info->description = ZH_WORDS_GETTER("opnurse3.field.pdfBase64"); }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRINT_API_DTO_
