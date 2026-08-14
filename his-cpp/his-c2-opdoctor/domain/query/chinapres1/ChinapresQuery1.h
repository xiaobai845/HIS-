#pragma once
#ifndef _CHINAPRESQUERY1_H_
#define _CHINAPRESQUERY1_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class ChinapresQuery1 : public oatpp::DTO
{
	DTO_INIT(ChinapresQuery1, DTO);
	// 患者档案ID
	API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("chinapres1.field.patientid"), true);
	// 就诊ID
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("chinapres1.field.encounterid"), true);
	// 处方号
	API_DTO_FIELD_REQUIRE(String, presId, ZH_WORDS_GETTER("chinapres1.field.presid"), false);
	// 关键词
	API_DTO_FIELD_REQUIRE(String, keyword, ZH_WORDS_GETTER("chinapres1.field.keyword"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CHINAPRESQUERY1_H_