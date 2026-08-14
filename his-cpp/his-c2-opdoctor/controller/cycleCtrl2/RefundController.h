#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/01 17:39:36

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _REFUNDCONTROLLER_H_
#define _REFUNDCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include"../../domain/query/cycleCtrl2-refund/RefundQuery.h"
#include"../../domain/vo/doctor/Refund2VO.h"
#include"../../domain/dto/doctor/Refund2ApplyDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("cyclectrl2.test.tag")

class Refund2Controller : public oatpp::web::server::api::ApiController
{
	//添加访问定义
	API_ACCESS_DECLARE(Refund2Controller);
public://定义接口
	// 3.1.1 定义获取退费清单接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("cyclectrl2.refund.query"), queryRefund, Refund2Query, Refund2DetailJsonVO::Wrapper, API_TAG);
	// 3.1.2 定义获取退费清单接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/cyclectrl/refund_query", queryRefund, Refund2Query, executeQueryRefund(query));
	// 3.2.1 定义提交退费申请接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("cyclectrl2.refund.apply"), applyRefund, StringJsonVO::Wrapper, API_TAG);
	// 3.2.2 定义提交退费申请接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/cyclectrl/refund_apply", applyRefund, BODY_DTO(Refund2ApplyDTO::Wrapper, dto), execApplyRefund(dto, authObject->getPayload()));
private://定义接口执行函数
	//3.3定义获取退费清单接口执行函数
	Refund2DetailJsonVO::Wrapper executeQueryRefund(const Refund2Query::Wrapper& query);
	//定义提交退费申请接口执行函数
	StringJsonVO::Wrapper execApplyRefund(const Refund2ApplyDTO::Wrapper& dto, const PayloadDTO& payload);
};
#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif