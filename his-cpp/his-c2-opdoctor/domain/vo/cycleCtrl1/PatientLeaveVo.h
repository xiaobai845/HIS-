#pragma once
#ifndef _PATIENTLEAVEJSONVO_H
#define _PATIENTLEAVEJSONVO_H

#include "../../GlobalInclude.h"
#include "../../dto/cycleCtrl1/PatientLeaveDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientLeaveJsonVO : public JsonVO<PatientLeaveDTO::Wrapper>
{
    DTO_INIT(PatientLeaveJsonVO, JsonVO<PatientLeaveDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif