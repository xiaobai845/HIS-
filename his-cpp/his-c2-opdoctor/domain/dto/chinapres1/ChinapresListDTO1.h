#pragma once
#ifndef _CHINAPRESLISTDTO1_H_
#define _CHINAPRESLISTDTO1_H_

#include "ChinapresDTO1.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ChinapresListDTO1 : public oatpp::DTO
{
	DTO_INIT(ChinapresListDTO1, DTO);

	API_DTO_FIELD_REQUIRE(List<Object<ChinapresDTO1>>, records, ZH_WORDS_GETTER("chinapres1.field.records"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif