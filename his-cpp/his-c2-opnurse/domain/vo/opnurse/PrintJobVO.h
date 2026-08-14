#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/20
*/
#ifndef _PRINT_JOB_VO_
#define _PRINT_JOB_VO_

#include "../../GlobalInclude.h"
#include "../../dto/opnurse/PrintApiDTO.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PrintResultJsonVO : public JsonVO<PrintResultDTO::Wrapper>
{
	DTO_INIT(PrintResultJsonVO, JsonVO<PrintResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRINT_JOB_VO_
