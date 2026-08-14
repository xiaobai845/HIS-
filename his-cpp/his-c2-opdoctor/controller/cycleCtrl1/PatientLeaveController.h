#pragma once
#ifndef _PATIENTLEAVECONTROLLER_H_
#define _PATIENTLEAVECONTROLLER_H_

#include "domain/dto/cycleCtrl1/PatientLeaveDTO.h"        
#include "domain/query/cycleCtrl1/PatientLeaveQuery.h"
#include "domain/vo/cycleCtrl1/PatientLeaveVo.h"
#include "domain/GlobalInclude.h"
#include "domain/dto/PayloadDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)


#define API_TAG ZH_WORDS_GETTER("title.tags.text")

class PatientLeaveController : public oatpp::web::server::api::ApiController
{

    API_ACCESS_DECLARE(PatientLeaveController);
public:
    // 请求体只需要encounterId
    ENDPOINT(API_M_PUT, "/cycleCtrl/leave", leavePatient, BODY_DTO(Object<PatientLeaveQuery>, leaveParam), API_HANDLER_AUTH_PARAME)
    {
        API_HANDLER_RESP_VO(execLeavePatient(leaveParam, authObject->getPayload()));
    }

    ENDPOINT_INFO(leavePatient)
    {
        //定义授权描述
        API_DEF_ADD_AUTH();
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("leave.get.summary"));
        //定义标签
        API_DEF_ADD_TAG(API_TAG);

        API_DEF_ADD_RSP_JSON_WRAPPER(PatientLeaveJsonVO);
    }

private:
    PatientLeaveJsonVO::Wrapper execLeavePatient(const PatientLeaveQuery::Wrapper& dto, const PayloadDTO& payload);
};



#include OATPP_CODEGEN_END(ApiController)

#endif // !_PATIENTLEAVECONTROLLER_H_
