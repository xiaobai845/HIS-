#pragma once
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/cycleCtrl1/PatientQueueQuery.h"
#include "domain/dto/cycleCtrl1/PatientQueueDTO.h"
#include "domain/vo/cycleCtrl1/PatientQueueVo.h"
#include "domain/GlobalInclude.h"
#include "service/cycleCtrl1/PatientQueueService.h"
#include "domain/dto/PayloadDTO.h"


#ifdef API_TAG
#undef API_TAG
#endif
#define API_TAG ZH_WORDS_GETTER("title.tags.text")

#include OATPP_CODEGEN_BEGIN(ApiController)

class PatientQueueController : public oatpp::web::server::api::ApiController
{
	//定义接口控制器访问入口
	API_ACCESS_DECLARE(PatientQueueController);

public:
	//1.1定义患者队列的查询接口处理
	ENDPOINT(API_M_GET, "/cycleCtrl/queue", queryQueue, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME)
	{
		//解析查询参数为query的领域模型
		API_HANDLER_QUERY_PARAM(userQuery, PatientQueueQuery, queryParams);
		//调用执行函数
		API_HANDLER_RESP_VO(execQueryQueue(userQuery, authObject->getPayload()));
	}
	//1.2定义患者队列的查询接口描述	
	ENDPOINT_INFO(queryQueue)
	{
		//定义授权描述
		API_DEF_ADD_AUTH();
		//定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("queue.get.summary"));
		//定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(PatientQueueJsonVO);
		//定义标签
		API_DEF_ADD_TAG(API_TAG);

		
		// 1. 日期 -> PatientQueueQuery 中字段名为 `date`
		API_DEF_ADD_QUERY_PARAMS(String, "date", ZH_WORDS_GETTER("queue.param.startDate"), "", true);
		// 2. 患者姓名 -> `patientName`
		API_DEF_ADD_QUERY_PARAMS(String, "patientName", ZH_WORDS_GETTER("queue.param.patientName"), "", false);
		// 3. 待诊/在诊/完诊 -> DTO 字段为 `visitStatus` 状态 -> DTO 字段为 `visitStatus`
		API_DEF_ADD_QUERY_PARAMS(String, "visitStatus", ZH_WORDS_GETTER("queue.param.Status"), "", false);
	}

private:
	//1.3执行查询队列里的数据
	PatientQueueJsonVO::Wrapper execQueryQueue(const PatientQueueQuery::Wrapper& query, const PayloadDTO& payload);
};


#include OATPP_CODEGEN_END(ApiController)

#undef API_TAG
