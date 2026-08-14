#ifndef __CHINAPRES2DETAILADDDTO_H_
#define __CHINAPRES2DETAILADDDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 处方明细新增DTO（对应每味药材）
 */
class Chinapres2DetailAddDTO : public oatpp::DTO
{
    DTO_INIT(Chinapres2DetailAddDTO, DTO);

    // 药材ID（关联字典表，必填）
    API_DTO_FIELD_REQUIRE(String, medicineId, ZH_WORDS_GETTER("chinapres2.field.medicineId"), true);

    // 数量（如 10，必填）
    API_DTO_FIELD_REQUIRE(Float64, quantity, ZH_WORDS_GETTER("chinapres2.field.quantity"), true);

    // 单位（如 g，非必填）
    API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("chinapres2.field.unit"), false);

    // 单次剂量（非必填）
    API_DTO_FIELD_REQUIRE(Float64, dose, ZH_WORDS_GETTER("chinapres2.field.dose"), false);

    // 剂量单位（非必填）
    API_DTO_FIELD_REQUIRE(String, doseUnit, ZH_WORDS_GETTER("chinapres2.field.doseUnit"), false);

    // 排序号（前端控制顺序，非必填）
    API_DTO_FIELD_REQUIRE(Int32, sortNo, ZH_WORDS_GETTER("chinapres2.field.sortNo"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !__CHINAPRES2DETAILADDDTO_H_