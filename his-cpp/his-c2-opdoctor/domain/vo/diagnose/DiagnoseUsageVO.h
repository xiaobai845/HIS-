#pragma once

#include "domain/GlobalInclude.h"
#include "domain/dto/diagnose/DiagnoseUsageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiagnoseUsagePageJsonVO :
	public JsonVO<PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper>
{
	DTO_INIT(DiagnoseUsagePageJsonVO, JsonVO<PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)