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
#ifndef _outpatientrecord3Service_H_
#define _outpatientrecord3Service_H_

#include "../../domain/dto/outpatientrecord3/outpatientrecord3SaveDTO.h"
#include "../../domain/vo/outpatientrecord3/outpatientrecord3SaveResultVO.h"
#include "../../dao/outpatientrecord3/EmrDocument3DAO.h"
#include "../../dao/outpatientrecord3/AdmEncounterDAO.h"

/**
 * Outpatient medical record business service.
 *
 * Save/upsert flow:
 *   1. Validate required params (encounterId, content)
 *   2. Look up adm_encounter to derive patientId and check status
 *   3. Validate encounter is in editable status
 *   4. Validate content size and structure
 *   5. Upsert: query by encounterId, insert or update
 *   6. Idempotency: skip write if content unchanged
 *   7. Return structured result (id, encounterId, updatedAt)
 */
class outpatientrecord3Service
{
	EmrDocument3DAO emrDocument3DAO;
	AdmEncounterDAO admEncounterDAO;

	// Content size limit in bytes (512 KB)
	static const size_t MAX_CONTENT_SIZE = 512 * 1024;

	// Encounter statuses that disallow editing
	bool isEncounterEditable(const std::string& statusEnum);
	// Basic content validation (size + JSON structure)
	bool validateContent(const std::string& content, std::string& errorMsg);

public:
	/**
	 * Save or update outpatient medical record.
	 *
	 * @param dto Request body with encounterId, content, optional id/title/templateId
	 * @param payload JWT payload containing current user and tenant info
	 * @return Structured JSON response with id, encounterId, updatedAt
	 */
	outpatientrecord3SaveResultVO::Wrapper save(
		const outpatientrecord3SaveDTO::Wrapper& dto,
		const PayloadDTO& payload);
};

#endif // !_outpatientrecord3Service_H_
