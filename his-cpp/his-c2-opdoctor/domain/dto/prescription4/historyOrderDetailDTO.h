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
#ifndef _HISTORY_ORDER_DETAIL_DTO_H_
#define _HISTORY_ORDER_DETAIL_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class HistoryOrderDetailDTO : public oatpp::DTO {
	DTO_INIT(HistoryOrderDetailDTO, DTO);

	API_DTO_FIELD_REQUIRE(String, orderId, ZH_WORDS_GETTER("historyOrder.field.orderId"), true);
	API_DTO_FIELD_REQUIRE(String, orderType, ZH_WORDS_GETTER("historyOrder.field.orderType"), true);
	API_DTO_FIELD_REQUIRE(String, orderName, ZH_WORDS_GETTER("historyOrder.field.orderName"), true);
	API_DTO_FIELD_REQUIRE(Int32, quantity, ZH_WORDS_GETTER("historyOrder.field.quantity"), true);
	API_DTO_FIELD_REQUIRE(Int32, executedCount, ZH_WORDS_GETTER("historyOrder.field.executedCount"), true);
	API_DTO_FIELD_REQUIRE(String, sampleType, ZH_WORDS_GETTER("historyOrder.field.sampleType"), false);
	API_DTO_FIELD_REQUIRE(String, executeHospital, ZH_WORDS_GETTER("historyOrder.field.executeHospital"), true);
	API_DTO_FIELD_REQUIRE(String, createTime, ZH_WORDS_GETTER("historyOrder.field.createTime"), true);
	API_DTO_FIELD_REQUIRE(String, diagnosis, ZH_WORDS_GETTER("historyOrder.field.diagnosis"), true);
	API_DTO_FIELD_REQUIRE(String, doctorName, ZH_WORDS_GETTER("historyOrder.field.doctorName"), true);
	API_DTO_FIELD_REQUIRE(Int32, isSkinTest, ZH_WORDS_GETTER("historyOrder.field.isSkinTest"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _HISTORY_ORDER_DETAIL_DTO_H_
