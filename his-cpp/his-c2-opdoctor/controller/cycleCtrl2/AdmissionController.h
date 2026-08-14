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
#ifndef _ADMISSIONCONTROLLER_H_
#define _ADMISSIONCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include"domain/query/cycleCtrl2-admission/AdmissionQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG2 ZH_WORDS_GETTER("cyclectrl2.test.tag")

class Admission2Controller : public oatpp::web::server::api::ApiController
{
	//添加访问定义
	API_ACCESS_DECLARE(Admission2Controller);
public://定义接口
	// 3.1.1 定义办理住院接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("cyclectrl2.admission.apply"), apply2Admission, Admission2Query, StringJsonVO::Wrapper, API_TAG2);
	// 3.1.2 定义办理住院接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_POST, "/cyclectrl/admission_apply", apply2Admission, Admission2Query, executeApplyAdmission(query));
private://定义接口执行函数
	//3.3定义办理住院接口执行函数
	StringJsonVO::Wrapper executeApplyAdmission(const Admission2Query::Wrapper& query);
};
#undef API_TAG2

#include OATPP_CODEGEN_END(ApiController)
#endif 
