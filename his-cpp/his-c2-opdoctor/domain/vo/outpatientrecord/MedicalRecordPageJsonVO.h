#ifndef _MEDICALRECORD_PAGE_JSON_VO_H_
#define _MEDICALRECORD_PAGE_JSON_VO_H_

#include "domain/dto/outpatientrecord/MedicalRecordPageDTO.h"
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MedicalRecordPageJsonVO : public JsonVO<MedicalRecordPageDTO::Wrapper>
{
	DTO_INIT(MedicalRecordPageJsonVO, JsonVO<MedicalRecordPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_MEDICALRECORD_PAGE_JSON_VO_H_