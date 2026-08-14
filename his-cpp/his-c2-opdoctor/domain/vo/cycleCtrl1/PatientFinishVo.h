#pragma once

#ifndef _PATIENTFINISHJSONVO_H
#define _PATIENTFINISHJSONVO_H

#include "../../GlobalInclude.h"
#include "../../dto/cycleCtrl1/PatientFinishDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientFinishJsonVO : public JsonVO<PatientFinishDTO::Wrapper>
{
    DTO_INIT(PatientFinishJsonVO, JsonVO<PatientFinishDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PATIENTFINISHJSONVO_H