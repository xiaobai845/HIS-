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
#ifndef _outpatientrecord3SAVEDTO_H_
#define _outpatientrecord3SAVEDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Save/upsert request DTO for outpatient medical record.
 *
 * Receives form body for outpatientrecord3/save endpoint.
 * outpatientrecord3Id empty = create, non-empty = update.
 * patientId is removed from DTO: derived server-side from adm_encounter.
 * templateId is optional (frontend removed template feature).
 */
class outpatientrecord3SaveDTO : public oatpp::DTO
{
	DTO_INIT(outpatientrecord3SaveDTO, DTO);

	// Record ID: empty for insert, non-empty for update
	API_DTO_FIELD_REQUIRE(
		String,
		outpatientrecord3Id,
		ZH_WORDS_GETTER("outpatientrecord3.field.outpatientrecord3Id"),
		false);

	// Encounter ID, required
	API_DTO_FIELD_REQUIRE(
		String,
		encounterId,
		ZH_WORDS_GETTER("outpatientrecord3.field.encounterId"),
		true);

	// Title: optional, auto-generated when empty
	API_DTO_FIELD_REQUIRE(
		String,
		title,
		ZH_WORDS_GETTER("outpatientrecord3.field.title"),
		false);

	// Template ID: optional (frontend removed template feature)
	DTO_FIELD(String, templateId);
	DTO_FIELD_INFO(templateId) {
		info->description = ZH_WORDS_GETTER("outpatientrecord3.field.templateId");
	}

	// Medical record content (Tiptap/ProseMirror JSON), required
	API_DTO_FIELD_REQUIRE(
		String,
		content,
		ZH_WORDS_GETTER("outpatientrecord3.field.content"),
		true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_outpatientrecord3SAVEDTO_H_
