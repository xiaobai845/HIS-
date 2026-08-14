#pragma once
#ifndef _PATIENTLEAVEDTO_H
#define _PATIENTLEAVEDTO_H

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)


class PatientLeaveDTO : public oatpp::DTO
{
    DTO_INIT(PatientLeaveDTO, DTO);

    // 就诊状态
    API_DTO_FIELD_REQUIRE(String, visitStatus, ZH_WORDS_GETTER("leave.dto.newVisitStatus"), false);

	//相关状态arrived - 待诊，in-progress - 在诊，finished - 完诊
    API_DTO_FIELD_REQUIRE(String, arrived, ZH_WORDS_GETTER("leave.dto.arrived"), false);
	API_DTO_FIELD_REQUIRE(String, inProgress, ZH_WORDS_GETTER("leave.dto.inProgress"), false);
    API_DTO_FIELD_REQUIRE(String, finished, ZH_WORDS_GETTER("leave.dto.finished"), false);

    // 就诊id
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("leave.dto.encounterId"), true);
    
    //接诊医生
    API_DTO_FIELD_REQUIRE(String, attendingDoctorName, ZH_WORDS_GETTER("leave.dto.attendingDoctorName"), false);

    //接诊时间
    API_DTO_FIELD_REQUIRE(String, acceptedAt, ZH_WORDS_GETTER("leave.dto.acceptedAt"), false);


};

#include OATPP_CODEGEN_END(DTO)
#endif