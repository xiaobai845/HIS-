#ifndef _PATIENTACTQUERY_H_
#define _PATIENTACTQUERY_H_
#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Query DTO for patient service-request (act) list.
 *
 * NOTE: No query parameters. encounterId is a PATH parameter only.
 *   act / status / orderContent are RESPONSE fields, not filter params.
 *   The backend returns all acts for the encounter; frontend handles filtering.
 */
class PatientActQuery : public oatpp::DTO
{
	DTO_INIT(PatientActQuery, DTO);
};
#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTACTQUERY_H_
