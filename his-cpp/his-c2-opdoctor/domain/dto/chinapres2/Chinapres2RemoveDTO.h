#ifndef __CHINAPRES2REMOVEDTO_H_
#define __CHINAPRES2REMOVEDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Chinapres2RemoveDTO : public oatpp::DTO {
    DTO_INIT(Chinapres2RemoveDTO, DTO);

    // 处方ID（必填）
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("chinapres2.field.id"), true);
    // 就诊ID（必填）
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("chinapres2.field.encounterId"), true);
    // 版本号（必填）
    API_DTO_FIELD_REQUIRE(Int64, version, ZH_WORDS_GETTER("chinapres2.field.version"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif