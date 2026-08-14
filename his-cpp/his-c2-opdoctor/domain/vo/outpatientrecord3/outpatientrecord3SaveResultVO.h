#pragma once
#ifndef _outpatientrecord3SaveResultVO_H_
#define _outpatientrecord3SaveResultVO_H_

#include "../../GlobalInclude.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Inner result DTO returned after save/upsert.
 * Contains the fields needed by frontend to update its local snapshot.
 */
class outpatientrecord3SaveResultDTO : public oatpp::DTO
{
	DTO_INIT(outpatientrecord3SaveResultDTO, DTO);

	// Medical record ID (new or existing)
	API_DTO_FIELD_REQUIRE(
		String, id,
		ZH_WORDS_GETTER("outpatientrecord3.field.outpatientrecord3Id"),
		true);

	// Encounter ID
	API_DTO_FIELD_REQUIRE(
		String, encounterId,
		ZH_WORDS_GETTER("outpatientrecord3.field.encounterId"),
		true);

	// Last update timestamp (frontend uses this to detect unsaved changes)
	API_DTO_FIELD_REQUIRE(
		String, updatedAt,
		ZH_WORDS_GETTER("outpatientrecord3.field.updatedAt"),
		true);
};

/**
 * Standard JSON response wrapper for save/upsert.
 * Outer envelope: { code, message, data: { id, encounterId, updatedAt } }
 */
class outpatientrecord3SaveResultVO : public JsonVO<outpatientrecord3SaveResultDTO::Wrapper>
{
	DTO_INIT(outpatientrecord3SaveResultVO, JsonVO<outpatientrecord3SaveResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_outpatientrecord3SaveResultVO_H_
