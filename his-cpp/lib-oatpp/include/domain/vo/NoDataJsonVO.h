#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/11/28 21:05:58

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
#ifndef _NO_DATA_JSON_VO_H_
#define _NO_DATA_JSON_VO_H_
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "ResultStatus.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 无数据JsonVO（基类）
 *
 * 所有 JSON 响应对象的基类，仅包含 code（状态码）和 message（提示信息）两个字段，
 * 不包含 data 字段。适用于不需要返回业务数据的接口响应（如纯操作结果通知）。
 *
 * @see JsonVO 带数据字段的扩展版本
 */
class NoDataJsonVO : public oatpp::DTO
{
	// 初始化宏，注册 DTO 类型
	DTO_INIT(NoDataJsonVO, DTO);

	// 状态码，标识请求处理结果（如 10000 表示成功）
	DTO_FIELD_INFO(code) {
#ifndef LINUX
		info->description = u8"状态码";
#else
		info->description = "status code";
#endif
		info->required = true;
	}
	DTO_FIELD(Int32, code, "code") = 10000;
	// 提示信息，对状态码的文本说明（如 "success"、"操作失败"）
	DTO_FIELD_INFO(message) {
#ifndef LINUX
		info->description = u8"提示信息";
#else
		info->description = "info message";
#endif
		info->required = true;
	}
	DTO_FIELD(String, message, "message") = "success";
public:
	// 使用 ResultStatus 初始化 code 和 message
	void init(ResultStatus resultStatus) {
		this->code = resultStatus.getCode();
		this->message = resultStatus.getMessage();
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_NO_DATA_JSON_VO_H_
