#ifndef __CHINAPRES2REMOVERESPDTO_H_
#define __CHINAPRES2REMOVERESPDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Chinapres2RemoveRespDTO : public oatpp::DTO {
    DTO_INIT(Chinapres2RemoveRespDTO, DTO);
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("chinapres2.field.id"), false);
    API_DTO_FIELD_REQUIRE(Int64, version, ZH_WORDS_GETTER("chinapres2.field.version"), false);
    API_DTO_FIELD_REQUIRE(String, updatedAt, ZH_WORDS_GETTER("chinapres2.field.updatedAt"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif