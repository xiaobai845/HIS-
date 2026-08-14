#pragma once
#ifndef _RECEPTIONPATIENTCONTROLLER_H_
#define _RECEPTIONPATIENTCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/cycleCtrl1/ReceptionPatientQuery.h"
#include "domain/dto/cycleCtrl1/ReceptionPatientDTO.h"
#include "domain/vo/cycleCtrl1/ReceptionPatientVo.h"
#include "domain/GlobalInclude.h"
#include "service/cycleCtrl1/ReceptionPatientService.h"
#include "domain/dto/PayloadDTO.h" 

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("title.tags.text")


class RecePatientController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(RecePatientController);

public:
	//2.1 接口：将凭证传入 execQueryRece
	ENDPOINT(API_M_GET, "/cycleCtrl/reception", recePatient, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
	{
		// 将 query 解析为 DTO
		API_HANDLER_QUERY_PARAM(userQuery, RecePatientQuery, queryParams);
		// 把 authObject->getPayload() 
		API_HANDLER_RESP_VO(execQueryRece(userQuery, authObject->getPayload()));
	}
	//2.2 接口信息保持不变
	ENDPOINT_INFO(recePatient)
	{
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("rece.get.summary"));
		API_DEF_ADD_RSP_JSON_WRAPPER(RecePatientJsonVO);
		API_DEF_ADD_TAG(API_TAG);

		//只输入日期即可
		API_DEF_ADD_QUERY_PARAMS(String, "date", ZH_WORDS_GETTER("rece.param.visitTime"), "", true);
	}

private:
	// 修改签名：增加 payload 参数
	RecePatientJsonVO::Wrapper execQueryRece(const RecePatientQuery::Wrapper& query, const PayloadDTO& payload);

};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_RECEPTIONPATIENTCONTROLLER_H_
