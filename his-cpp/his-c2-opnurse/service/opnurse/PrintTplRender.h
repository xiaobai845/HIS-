#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/23
*/
#ifndef _PRINT_TPL_RENDER_
#define _PRINT_TPL_RENDER_
#include "PdfComponent.h"
#include "domain/bo/PdfReportBO.h"
#include "domain/dto/opnurse/PrintDataDTO.h"

class PrintTplRender
{
public:
	// Register all 8 document type template render callbacks
	static void registerAll();
};

#endif // !_PRINT_TPL_RENDER_
