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
#pragma once
#ifndef _NURSECONTROLLER_H_
#define _NURSECONTROLLER_H_

#include "domain/vo/nurse2/NurseExecutionResultJsonVO2.h"
#include "domain/dto/nurse2/NurseCancelDTO2.h"
#include "domain/dto/nurse2/NurseOperateDTO2.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("nurse2.tags.tag")

class NurseController2 : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(NurseController2);

public:
	// Execute endpoint
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("nurse2.modify.operate1"), operateNurse2, NurseExecutionResultJsonVO2::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/opnurse/operate1", operateNurse2, BODY_DTO(NurseOperateDTO2::Wrapper, dto), execOperateNurse(dto, authObject->getPayload()));

	// Cancel execute endpoint
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("nurse2.modify.operate2"), cancelNurse2, NurseExecutionResultJsonVO2::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/opnurse/operate2", cancelNurse2, BODY_DTO(NurseCancelDTO2::Wrapper, dto), execCancelNurse(dto, authObject->getPayload()));

private:
	// Execute implementation
	NurseExecutionResultJsonVO2::Wrapper execOperateNurse(const NurseOperateDTO2::Wrapper& dto, const PayloadDTO& payload);
	// Cancel execute implementation
	NurseExecutionResultJsonVO2::Wrapper execCancelNurse(const NurseCancelDTO2::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_NURSECONTROLLER_H_
