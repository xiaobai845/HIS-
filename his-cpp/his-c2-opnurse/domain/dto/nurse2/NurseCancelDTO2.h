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
#ifndef _NURSECANCELDTO_H_
#define _NURSECANCELDTO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// Cancel execution DTO
class NurseCancelDTO2 : public oatpp::DTO
{
	DTO_INIT(NurseCancelDTO2, DTO);

	// Encounter ID (required)
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("nurse2.field.encounter_id"), true);
	// Service request item ID to cancel (required)
	API_DTO_FIELD_REQUIRE(String, itemId, ZH_WORDS_GETTER("nurse2.field.item_id"), true);
	// Cancel reason (required)
	API_DTO_FIELD_REQUIRE(String, cancelReason, ZH_WORDS_GETTER("nurse2.field.cancel_reason"), true);
	// Optimistic lock version (optional)
	API_DTO_FIELD_REQUIRE(Int32, version, ZH_WORDS_GETTER("nurse2.field.version"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_NURSECANCELDTO_H_
