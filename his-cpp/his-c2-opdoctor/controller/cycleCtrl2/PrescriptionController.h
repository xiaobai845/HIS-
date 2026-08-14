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
#ifndef _PRESCRIPTIONCONTROLLER_H_
#define _PRESCRIPTIONCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include"domain/query/cycleCtrl2-prescription/PrescriptionQuery.h"
#include"domain/vo/doctor/Prescription2VO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG1 ZH_WORDS_GETTER("cyclectrl2.test.tag")

class PrescriptionController2 : public oatpp::web::server::api::ApiController
{
	//添加访问定义
	API_ACCESS_DECLARE(PrescriptionController2);
public://定义接口
	// 3.1.1 定义处方单单接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("cyclectrl2.prescription.query"), query2Prescription, Prescription2Query, Prescription2DetailJsonVO::Wrapper, API_TAG1);
	// 3.1.2 定义处方单接口处理
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/cyclectrl/prescription_query", query2Prescription, Prescription2Query, executeQueryPrescription(query));
private://定义接口执行函数
	//3.3定义处方单接口执行函数
	Prescription2DetailJsonVO::Wrapper executeQueryPrescription(const Prescription2Query::Wrapper& query);
};
#undef API_TAG1

#include OATPP_CODEGEN_END(ApiController)
#endif