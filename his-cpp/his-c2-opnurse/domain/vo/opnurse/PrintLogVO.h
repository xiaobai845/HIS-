#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/21
*/
#ifndef _PRINT_LOG_VO_
#define _PRINT_LOG_VO_

#include "../../GlobalInclude.h"
#include "../../dto/opnurse/PrintLogDTO.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PrintLogPageJsonVO : public JsonVO<PrintLogPageDTO::Wrapper>
{
	DTO_INIT(PrintLogPageJsonVO, JsonVO<PrintLogPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRINT_LOG_VO_
