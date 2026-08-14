#ifndef __OUTPATIENTRECORDVO_H_
#define __OUTPATIENTRECORDVO_H_

#include "../../dto/outpatientrecord/OutpatientRecordDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class OutpatientRecordPageJsonVO : public JsonVO<OutpatientRecordPageDTO::Wrapper>
{
    DTO_INIT(OutpatientRecordPageJsonVO, JsonVO<OutpatientRecordPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !__OUTPATIENTRECORDVO_H_