
#ifndef _NURSEEXECUTIONRESULTJSONVO_H_
#define _NURSEEXECUTIONRESULTJSONVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/nurse2/NurseExecutionResultDTO2.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// Structured JSON response for execute / cancel operations
class NurseExecutionResultJsonVO2 : public JsonVO<NurseExecutionResultDTO2::Wrapper>
{
	DTO_INIT(NurseExecutionResultJsonVO2, JsonVO<NurseExecutionResultDTO2::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_NURSEEXECUTIONRESULTJSONVO_H_
