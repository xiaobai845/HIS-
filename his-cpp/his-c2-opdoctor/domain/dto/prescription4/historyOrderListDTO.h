#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/07/27

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _HISTORY_ORDER_LIST_DTO_H_
#define _HISTORY_ORDER_LIST_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class HistoryOrderListDTO : public oatpp::DTO {
	DTO_INIT(HistoryOrderListDTO, DTO);

	API_DTO_FIELD_REQUIRE(String, visitId, ZH_WORDS_GETTER("historyOrder.field.visitId"), true);
	API_DTO_FIELD_REQUIRE(String, visitTime, ZH_WORDS_GETTER("historyOrder.field.visitTime"), true);
	API_DTO_FIELD_REQUIRE(String, visitType, ZH_WORDS_GETTER("historyOrder.field.visitType"), true);
	API_DTO_FIELD_REQUIRE(String, mainDiagnosis, ZH_WORDS_GETTER("historyOrder.field.mainDiagnosis"), true);
	API_DTO_FIELD_REQUIRE(String, doctorName, ZH_WORDS_GETTER("historyOrder.field.doctorName"), true);
	API_DTO_FIELD_REQUIRE(Int32, drugCount, ZH_WORDS_GETTER("historyOrder.field.drugCount"), true);
	API_DTO_FIELD_REQUIRE(Int32, examCount, ZH_WORDS_GETTER("historyOrder.field.examCount"), true);
	API_DTO_FIELD_REQUIRE(Int32, materialCount, ZH_WORDS_GETTER("historyOrder.field.materialCount"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _HISTORY_ORDER_LIST_DTO_H_
