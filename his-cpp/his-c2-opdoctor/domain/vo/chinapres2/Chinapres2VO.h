#if 0
#ifndef __CHINAPRES2VO_H_
#define __CHINAPRES2VO_H_

#include "../../dto/chinapres2/Chinapres2DetailDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)


// 定义一个租户信息分页显示JsonVO对象，用于响应给客户端

class Chinapres2DetailPageJsonVO : public JsonVO<Chinapres2DetailPageDTO::Wrapper>
{
    DTO_INIT(Chinapres2DetailPageJsonVO, JsonVO<Chinapres2DetailPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !__CHINAPRES2VO_H_

#endif