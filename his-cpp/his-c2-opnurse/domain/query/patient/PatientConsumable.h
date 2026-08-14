#ifndef _PATIENTCONSUMQUERY_H_
#define _PATIENTCONSUMQUERY_H_
#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Query DTO for patient consumable list.
 *
 * NOTE: patientId / encounterId are NOT declared here.
 *   - encounterId is a PATH parameter (implicit filter, identifies the visit).
 *   - patientId is NOT required: the backend derives the patient
 *     from the encounter via adm_encounter.patient_id, so the caller
 *     only needs to know which encounter to query.
 *
 * The Swagger "Query Parameters" list therefore only contains the
 * real filter condition (consumableRoom).
 */
class PatientConsumQuery : public oatpp::DTO
{
	DTO_INIT(PatientConsumQuery, DTO);
	// Consumable room
	API_DTO_FIELD_REQUIRE(String, consumableRoom, ZH_WORDS_GETTER("patientconsumable1.field.consumableRoom"), false);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTCONSUMQUERY_H_
