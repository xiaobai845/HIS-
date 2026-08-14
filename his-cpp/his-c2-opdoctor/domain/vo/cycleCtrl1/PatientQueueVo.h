#pragma once
#ifndef _PATIENTQUEUEVO_H_
#define _PATIENTQUEUEVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/cycleCtrl1/PatientQueueDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 返回列表时，VO 的模板参数应为 Vector<DTO::Wrapper>
class PatientQueueJsonVO : public JsonVO<oatpp::Vector<PatientQueueDTO::Wrapper>>
{
	DTO_INIT(PatientQueueJsonVO, JsonVO<oatpp::Vector<PatientQueueDTO::Wrapper>>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PATIENTQUEUEVO_H_
