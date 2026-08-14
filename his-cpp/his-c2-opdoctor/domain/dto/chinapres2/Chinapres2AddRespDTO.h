#ifndef __CHINAPRES2ADDRESPDTO_H_
#define __CHINAPRES2ADDRESPDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Chinapres2AddRespDTO : public oatpp::DTO {
    DTO_INIT(Chinapres2AddRespDTO, DTO);

    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("chinapres2.resp.id"), false);
    API_DTO_FIELD_REQUIRE(String, prescriptionNo, ZH_WORDS_GETTER("chinapres2.resp.prescriptionNo"), false);
    API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("chinapres2.resp.status"), false);
    API_DTO_FIELD_REQUIRE(Int64, version, ZH_WORDS_GETTER("chinapres2.resp.version"), false);
    API_DTO_FIELD_REQUIRE(String, createdAt, ZH_WORDS_GETTER("chinapres2.resp.createdAt"), false);
    API_DTO_FIELD_REQUIRE(Int32, herbCount, ZH_WORDS_GETTER("chinapres2.resp.herbCount"), false);
    API_DTO_FIELD_REQUIRE(Float64, singleDoseAmount, ZH_WORDS_GETTER("chinapres2.resp.singleDoseAmount"), false);
    API_DTO_FIELD_REQUIRE(Float64, totalAmount, ZH_WORDS_GETTER("chinapres2.resp.totalAmount"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif