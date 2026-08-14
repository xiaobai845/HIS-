#pragma once

#include "domain/GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class DiagnoseAddDTO : public oatpp::DTO
{
    DTO_INIT(DiagnoseAddDTO, DTO)

    // necessary
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("diagnose.add.encounterId"), true);
    API_DTO_FIELD_REQUIRE(String, conditionId, ZH_WORDS_GETTER("diagnose.add.conditionId"), true);
    API_DTO_FIELD_REQUIRE(String, description, ZH_WORDS_GETTER("diagnose.add.description"), true);
    API_DTO_FIELD_REQUIRE(String, diagTypeCode, ZH_WORDS_GETTER("diagnose.add.diagTypeCode"), true);
    API_DTO_FIELD_REQUIRE(Int32, diagCode, ZH_WORDS_GETTER("diagnose.add.diagCode"), true);

    // optional
    API_DTO_FIELD_DEFAULT(Int32, rank, ZH_WORDS_GETTER("diagnose.add.rank"));
    API_DTO_FIELD_DEFAULT(Int8, primaryFlag, ZH_WORDS_GETTER("diagnose.add.primaryFlag"));
    API_DTO_FIELD_DEFAULT(Int8, highestDiagFlag, ZH_WORDS_GETTER("diagnose.add.highestDiagFlag"));
    API_DTO_FIELD_DEFAULT(Int8, tcmFlag, ZH_WORDS_GETTER("diagnose.add.tcmFlag"));
    API_DTO_FIELD_DEFAULT(String, tcmSyndromeGroup, ZH_WORDS_GETTER("diagnose.add.tcmSyndromeGroup"));
    API_DTO_FIELD_DEFAULT(String, medType, ZH_WORDS_GETTER("diagnose.add.medType"));
    API_DTO_FIELD_DEFAULT(Int32, conditionCode, ZH_WORDS_GETTER("diagnose.add.conditionCode"));

};

#include OATPP_CODEGEN_END(DTO)