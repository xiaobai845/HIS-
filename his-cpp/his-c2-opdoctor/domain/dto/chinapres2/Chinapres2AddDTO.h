#ifndef __CHINAPRES2ADDDTO_H_
#define __CHINAPRES2ADDDTO_H_

#include "../../GlobalInclude.h"
#include "Chinapres2DetailAddDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class Chinapres2AddDTO : public oatpp::DTO {
    DTO_INIT(Chinapres2AddDTO, DTO);

    // ---------- 核心关联（必须由前端传递） ----------
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("chinapres2.field.encounterId"), true);
    API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("chinapres2.field.patientId"), true);
    API_DTO_FIELD_REQUIRE(String, encounterDiagnosisId, ZH_WORDS_GETTER("chinapres2.field.encounterDiagnosisId"), true);

    // ---------- 处方业务字段 ----------
    API_DTO_FIELD_REQUIRE(String, usage, ZH_WORDS_GETTER("chinapres2.field.usage"), true);
    API_DTO_FIELD_REQUIRE(String, frequency, ZH_WORDS_GETTER("chinapres2.field.frequency"), true);
    API_DTO_FIELD_REQUIRE(Int32, days, ZH_WORDS_GETTER("chinapres2.field.days"), true);
    API_DTO_FIELD_REQUIRE(Int32, copies, ZH_WORDS_GETTER("chinapres2.field.copies"), true);
    API_DTO_FIELD_REQUIRE(Int32, decoction, ZH_WORDS_GETTER("chinapres2.field.decoction"), false); // 改为 Int32
    API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("chinapres2.field.remark"), false);

    // ---------- 乐观锁版本（预留） ----------
    API_DTO_FIELD_REQUIRE(Int64, version, ZH_WORDS_GETTER("chinapres2.field.version"), false);

    // ---------- 药材明细（至少一条） ----------
    API_DTO_FIELD_REQUIRE(oatpp::List<Chinapres2DetailAddDTO::Wrapper>, details, ZH_WORDS_GETTER("chinapres2.field.details"), true);

public:
    std::string validate() {
        if (!encounterId || encounterId->empty()) return "encounterId is required.";
        if (!patientId || patientId->empty()) return "patientId is required.";
        if (!encounterDiagnosisId || encounterDiagnosisId->empty()) return "encounterDiagnosisId is required.";
        if (!usage || usage->empty()) return "usage is required.";
        if (!frequency || frequency->empty()) return "frequency is required.";
        if (!days || *days <= 0) return "days must be positive.";
        if (!copies || *copies <= 0) return "copies must be positive.";
        if (!details || details->empty()) return "details list cannot be empty.";
        for (auto& d : *details) {
            if (!d->medicineId || d->medicineId->empty()) return "medicineId is required.";
            if (!d->quantity || *d->quantity <= 0) return "quantity must be positive.";
        }
        return "";
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif