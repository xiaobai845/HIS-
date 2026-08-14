#pragma once
#ifndef _RECEPTIONPATIENTVO_H_
#define _RECEPTIONPATIENTVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/cycleCtrl1/ReceptionPatientDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class RecePatientJsonVO : public JsonVO<RecePatientDTO::Wrapper>
{
	DTO_INIT(RecePatientJsonVO, JsonVO<RecePatientDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)


#endif // !_RECEPTIONPATIENTVO_H_
