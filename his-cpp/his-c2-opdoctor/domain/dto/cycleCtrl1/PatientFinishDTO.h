#pragma once
#ifndef _PATIENTFINISHDTO_H_
#define _PATIENTFINISHDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PatientFinishDTO : public oatpp::DTO
{
    DTO_INIT(PatientFinishDTO, DTO);

  
    // 更新后最新就诊状态
    API_DTO_FIELD_REQUIRE(String, visitStatus, ZH_WORDS_GETTER("finish.dto.newVisitStatus"), true);

    //就诊ID
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("finish.dto.encounterId"),true);

    //相关就诊状态arrived - 待诊，in-progress - 在诊，finished - 完诊
    API_DTO_FIELD_REQUIRE(String, arrived, ZH_WORDS_GETTER("finish.dto.arrived"),false);
    API_DTO_FIELD_REQUIRE(String, inProgress, ZH_WORDS_GETTER("finish.dto.inProgress"),false);
    API_DTO_FIELD_REQUIRE(String, finished, ZH_WORDS_GETTER("finish.dto.finished"),false);

    //完诊时间
    API_DTO_FIELD_REQUIRE(String, completedAt, ZH_WORDS_GETTER("finish.dto.completedAt"),true);

};


#include OATPP_CODEGEN_END(DTO)

#endif // !_PATIENTFINISHDTO_H_
