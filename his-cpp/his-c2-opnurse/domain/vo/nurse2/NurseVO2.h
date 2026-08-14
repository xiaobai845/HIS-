#pragma once

#ifndef _NURSEVO_H_
#define _NURSEVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/nurse2/NurseDetailDTO2.h"


#include OATPP_CODEGEN_BEGIN(DTO)

//说什么是分页相关的

/**
 * 定义一个用户信息分页显示JsonVO对象，用于响应给客户端
 */
class NurseDetailPageJsonVO2 : public JsonVO<NurseDetailPageDTO::Wrapper>    //这个是dto下的分页相关的
{
	DTO_INIT(NurseDetailPageJsonVO2, JsonVO<NurseDetailPageDTO::Wrapper>);
};




#include OATPP_CODEGEN_END(DTO)

#endif