#pragma once

#ifndef _CHINAPRESDTO1_H_
#define _CHINAPRESDTO1_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ChinapresDTO1 : public  oatpp::DTO
{
	DTO_INIT(ChinapresDTO1, DTO);
	//处方编号
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("chinapres1.field.id"), true);
	//处方数量
	API_DTO_FIELD_REQUIRE(String, count, ZH_WORDS_GETTER("chinapres1.field.count"), true);
	//哪些药材
	API_DTO_FIELD_REQUIRE(String, herbs, ZH_WORDS_GETTER("chinapres1.field.herbs"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CHINAPRESDTO1_H_