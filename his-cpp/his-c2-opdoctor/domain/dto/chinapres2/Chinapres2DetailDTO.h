#if 0
#ifndef __CHINAPRES2DETAILDTO_H_
#define __CHINAPRES2DETAILDTO_H_

#include "Chinapres2AddDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class Chinapres2DetailDTO : public Chinapres2AddDTO
{
    DTO_INIT(Chinapres2DetailDTO, Chinapres2AddDTO);
    //处方ID
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("chinapres2.field.id"), true);
};

/**
 * 定义一个处方信息分页传输对象
 */
class Chinapres2DetailPageDTO : public PageDTO<Chinapres2DetailDTO::Wrapper>
{
    DTO_INIT(Chinapres2DetailPageDTO, PageDTO<Chinapres2DetailDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !__CHINAPRES2DETAILDTO_H_

#endif