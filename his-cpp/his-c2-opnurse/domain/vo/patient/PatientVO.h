#ifndef _PATIENTVO_H_
#define _PATIENTVO_H_

#include "domain/vo/BaseJsonVO.h"
#include "../../dto/patient/PatientQueueDTO.h"
#include "../../dto/patient/PatientActDTO.h"
#include "../../dto/patient/PatientConsumableDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Paginated JSON VO for patient queue list response.
 */
class PatientQueuePageJsonVO : public JsonVO<PatientQueuePageDTO::Wrapper>
{
	DTO_INIT(PatientQueuePageJsonVO, JsonVO<PatientQueuePageDTO::Wrapper>);
};

/**
 * Wrapper JSON VO for patient act response.
 * Contains patient info at top level and items list below.
 * Example: { "code":0, "msg":"success", "data":{ "name":"...", "items":[...] } }
 */
class PatientActListJsonVO : public JsonVO<PatientActWrapperDTO::Wrapper>
{
	DTO_INIT(PatientActListJsonVO, JsonVO<PatientActWrapperDTO::Wrapper>);
};

/**
 * Non-paginated JSON VO for patient consumable list response.
 */
class PatientConsumListJsonVO : public ListJsonVO<PatientConsumableDTO::Wrapper>
{
	DTO_INIT(PatientConsumListJsonVO, ListJsonVO<PatientConsumableDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTVO_H_
