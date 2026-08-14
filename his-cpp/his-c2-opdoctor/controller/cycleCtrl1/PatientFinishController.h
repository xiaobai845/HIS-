#pragma once
#ifndef _PATIENTFINISHCONTROLLER_H_
#define _PATIENTFINISHCONTROLLER_H_

#include "domain/dto/cycleCtrl1/PatientFinishDTO.h"
#include "domain/query/cycleCtrl1/PatientFinishQuery.h"
#include "domain/vo/cycleCtrl1/PatientFinishVo.h"
#include "domain/GlobalInclude.h"
#include "domain/dto/PayloadDTO.h"



#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("title.tags.text")
class PatientFinishController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(PatientFinishController);
public:
    // 完诊接口 PUT
    ENDPOINT(API_M_PUT, "/cycleCtrl/finish", finishPatient, BODY_DTO(Object<PatientFinishQuery>, finishParam), API_HANDLER_AUTH_PARAME)
    {
        API_HANDLER_RESP_VO(execFinishPatient(finishParam, authObject->getPayload()));
    }
    ENDPOINT_INFO(finishPatient)
    {
        // 定义授权描述
        API_DEF_ADD_AUTH();
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("finish.get.summary"));
        // 定义标签
        API_DEF_ADD_TAG(API_TAG);
        API_DEF_ADD_RSP_JSON_WRAPPER(PatientFinishJsonVO);
    }

private:
    PatientFinishJsonVO::Wrapper execFinishPatient(const PatientFinishQuery::Wrapper& dto, const PayloadDTO& payload);
};

#include OATPP_CODEGEN_END(ApiController)


#endif // !_PATIENTFINISHCONTROLLER_H_
