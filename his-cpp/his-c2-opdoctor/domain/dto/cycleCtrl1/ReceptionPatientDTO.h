#pragma once
#ifndef _RECEPTIONPATIENTDTO_H_
#define _RECEPTIONPATIENTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class RecePatientDTO : public oatpp::DTO
{
	DTO_INIT(RecePatientDTO, DTO);

    // 患者ID
    API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("rece.dto.patientId"), false);

    //就诊号
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("rece.dto.encounterId"), false);

    // 患者姓名
    API_DTO_FIELD_REQUIRE(String, patientName, ZH_WORDS_GETTER("rece.dto.name"), true);

    // 就诊状态 -- 在诊
    API_DTO_FIELD_REQUIRE(String, visitStatus, ZH_WORDS_GETTER("rece.dto.visitStatus"), true);

    // 性别
    API_DTO_FIELD_REQUIRE(String, gender, ZH_WORDS_GETTER("rece.dto.gender"), true);
    // 年龄
    API_DTO_FIELD_REQUIRE(Int32, age, ZH_WORDS_GETTER("rece.dto.age"), true);
    // 挂号类型（普通号/专家号）
    API_DTO_FIELD_REQUIRE(String, registerType, ZH_WORDS_GETTER("rece.dto.registerType"), true);

    //病诊号
    API_DTO_FIELD_REQUIRE(String, visitNo, ZH_WORDS_GETTER("rece.dto.medicalRecordNum"), true);
    //病历性质（自费/医保）
    API_DTO_FIELD_REQUIRE(String, payType, ZH_WORDS_GETTER("rece.dto.recordType"), true);
    //就诊时间
    API_DTO_FIELD_REQUIRE(Int32, visitTime, ZH_WORDS_GETTER("rece.dto.time"), true);
    //挂号科室
    API_DTO_FIELD_REQUIRE(String, registerDept, ZH_WORDS_GETTER("rece.dto.registerDept"), true);
    //电话号
    API_DTO_FIELD_REQUIRE(String, phoneNum, ZH_WORDS_GETTER("rece.dto.phoneNum"), true);
    //过敏史
    API_DTO_FIELD_REQUIRE(String, allergyHistory, ZH_WORDS_GETTER("rece.dto.allergyHistory"), false);
    
    //接诊医生名字
    API_DTO_FIELD_REQUIRE(String, attendingDoctorName, ZH_WORDS_GETTER("rece.dto.attendingDoctorName"), false);

    //主诉
    API_DTO_FIELD_REQUIRE(String, chiefComplaint, ZH_WORDS_GETTER("rece.dto.chiefComplaint"), false);

    //紧急联系人
    API_DTO_FIELD_REQUIRE(String, emergencyContact, ZH_WORDS_GETTER("rece.dto.emergencyContact"), false);

    //分诊备注
    API_DTO_FIELD_REQUIRE(String, triageNote, ZH_WORDS_GETTER("rece.dto.triageNote"), false);

};




#include OATPP_CODEGEN_END(DTO)

#endif // !_RECEPTIONPATIENTDTO_H_
