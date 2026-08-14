#pragma once
#ifndef _PATIENTQUEUEDTO_H_
#define _PATIENTQUEUEDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 患者队列列表返回VO
class PatientQueueDTO : public oatpp::DTO
{
    // VO专用初始化标识，框架区分返回模型
    DTO_INIT(PatientQueueDTO, DTO);

    //患者ID
    API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("queue.dto.patientId"), false);

    //就诊ID
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("queue.dto.encounterId"), false);

    // 患者姓名
    API_DTO_FIELD_REQUIRE(String, patientName, ZH_WORDS_GETTER("queue.dto.patientName"), true);

    // 性别
    API_DTO_FIELD_REQUIRE(String, gender, ZH_WORDS_GETTER("queue.dto.gender"), true);
    // 年龄
    API_DTO_FIELD_REQUIRE(Int32, age, ZH_WORDS_GETTER("queue.dto.age"), true);
    // 挂号类型（普通号/专家号）
    API_DTO_FIELD_REQUIRE(String, registerType, ZH_WORDS_GETTER("queue.dto.registerType"), true);

    // 就诊时间
    API_DTO_FIELD_REQUIRE(String, visitTime, ZH_WORDS_GETTER("queue.dto.visitTime"), true);
    // 病历号
    API_DTO_FIELD_REQUIRE(String, visitNo, ZH_WORDS_GETTER("queue.dto.visitNum"), true);
    // 支付类型 自费/省医保/市医保
    API_DTO_FIELD_REQUIRE(String, payType, ZH_WORDS_GETTER("queue.dto.payType"), true);
    // 就诊状态 待诊、在诊、完诊
    API_DTO_FIELD_REQUIRE(String, visitStatus, ZH_WORDS_GETTER("queue.dto.visitStatus"), true);

    //排队号
    API_DTO_FIELD_REQUIRE(Int32, queueNumber, ZH_WORDS_GETTER("queue.dto.queueNum"), false);

    //挂号科室
    API_DTO_FIELD_REQUIRE(String, departmentName, ZH_WORDS_GETTER("queue.dto.departmentName"), false);
    
    //优先级名称
    API_DTO_FIELD_REQUIRE(String, priorityName, ZH_WORDS_GETTER("queue.dto.priorityName"), false);

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_PATIENTQUEUEDTO_H_





