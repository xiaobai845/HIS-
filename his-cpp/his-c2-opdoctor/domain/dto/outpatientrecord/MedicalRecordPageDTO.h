#ifndef _MEDICALRECORD_PAGE_DTO_H_
#define _MEDICALRECORD_PAGE_DTO_H_

#include "../../GlobalInclude.h"
#include "domain/dto/PageDTO.h"
#include "MedicalRecordDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MedicalRecordPageDTO : public PageDTO<MedicalRecordDTO::Wrapper>
{
	DTO_INIT(MedicalRecordPageDTO, PageDTO<MedicalRecordDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_MEDICALRECORD_PAGE_DTO_H_