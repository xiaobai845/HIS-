#pragma once
#ifndef _CHINAPRESVO1_H_
#define _CHINAPRESVO1_H_

#include "domain/dto/chinapres1/ChinapresListDTO1.h"
#include "domain/dto/chinapres1/ChinapresDetailDTO1.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ChinapresJsonVO1 : public JsonVO<ChinapresListDTO1::Wrapper>
{
	DTO_INIT(ChinapresJsonVO1, JsonVO<ChinapresListDTO1::Wrapper>);
};

class ChinapresDetailJsonVO1 : public JsonVO<ChinapresDetailDTO1::Wrapper>
{
	DTO_INIT(ChinapresDetailJsonVO1, JsonVO<ChinapresDetailDTO1::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif