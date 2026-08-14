/*
 Copyright Zero One Star. All rights reserved.

 @Author: fa-mian-tuan
 @Date: 2026/08/01

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
#ifndef _NURSEDETAILDTO_H_
#define _NURSEDETAILDTO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// Nurse2 detail DTO (query response row) 这个似乎没用
class NurseDetailDTO2 : public oatpp::DTO
{
	DTO_INIT(NurseDetailDTO2, DTO);

	// Item ID (wkf_service_request.id)
	API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("nurse2.field.item_id"), true);
	// Name / queue number (bus_no)
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("nurse2.field.name_code"), false);
	// 执行状态 (status_enum)
	API_DTO_FIELD_REQUIRE(String, state, ZH_WORDS_GETTER("nurse2.field.state"), false);
	// 医嘱内容 (content_json)
	API_DTO_FIELD_REQUIRE(String, content, ZH_WORDS_GETTER("nurse2.field.content"), false);
	// 执行数量 (execution_count)
	API_DTO_FIELD_REQUIRE(Int32, amount, ZH_WORDS_GETTER("nurse2.field.amount"), false);
	// 执行人 (performer_id)
	API_DTO_FIELD_REQUIRE(String, person, ZH_WORDS_GETTER("nurse2.field.person"), false);
	// Operation category (category_enum)
	API_DTO_FIELD_REQUIRE(String, operate, ZH_WORDS_GETTER("nurse2.field.operate"), false);
	// Remark / cancel reason
	API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("nurse2.field.remark"), false);
	// Encounter ID
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("nurse2.field.encounter_id"), false);
};

// Nurse2 paged query response
class NurseDetailPageDTO : public PageDTO<NurseDetailDTO2::Wrapper>
{
	DTO_INIT(NurseDetailPageDTO, PageDTO<NurseDetailDTO2::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_NURSEDETAILDTO_H_
