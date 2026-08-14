#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2026/07/28

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
#ifndef _outpatientrecord33Controller_H_
#define _outpatientrecord33Controller_H_

#include "../../domain/dto/outpatientrecord3/outpatientrecord3SaveDTO.h"
#include "../../domain/vo/outpatientrecord3/outpatientrecord3SaveResultVO.h"
#include "../../service/outpatientrecord3/Outpatientrecord3Service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("outpatientrecord3.tags.tag")

/**
 * Outpatient medical record controller.
 * Provides save/upsert endpoint for outpatient medical records.
 */
class outpatientrecord33Controller
	: public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(outpatientrecord33Controller);

public:

	// Swagger endpoint documentation
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("outpatientrecord3.save.summary"),
		saveoutpatientrecord3,
		outpatientrecord3SaveResultVO::Wrapper,
		API_TAG);

	// Route binding: POST /outpatientrecord3/save
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/outpatientrecord3/save",
		saveoutpatientrecord3,
		BODY_DTO(outpatientrecord3SaveDTO::Wrapper, dto),
		execSaveoutpatientrecord3(dto, authObject->getPayload()));

private:
	outpatientrecord3Service service;

	/**
	 * Execute save/upsert business logic.
	 * @param dto Request body DTO
	 * @param payload JWT payload with current user info
	 * @return Structured JSON response
	 */
	outpatientrecord3SaveResultVO::Wrapper
		execSaveoutpatientrecord3(
			const outpatientrecord3SaveDTO::Wrapper& dto,
			const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif
