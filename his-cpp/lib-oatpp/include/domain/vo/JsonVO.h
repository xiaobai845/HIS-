#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:24:25

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
#ifndef _JSON_VO_
#define _JSON_VO_
#include "NoDataJsonVO.h"
#include "Message.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 前端数据交互数据对象（泛型模板类）
 *
 * 继承自 NoDataJsonVO，在其基础上新增 data 字段，用于承载业务数据。
 * 通过模板参数 T 指定 data 字段的数据类型，实现类型安全的 JSON 序列化/反序列化。
 *
 * 提供以下便捷方法：
 *   - success(T data)：快速构造成功响应
 *   - fail(T data)：快速构造失败响应
 *   - setStatus(ResultStatus)：设置响应状态
 *
 * @tparam T data 字段的数据类型，通常为 DTO::Wrapper 类型
 *
 * @see NoDataJsonVO 不含 data 字段的基础版本
 */
template<class T>
class JsonVO : public NoDataJsonVO
{
	// 初始化宏，注册 DTO 类型（继承自 NoDataJsonVO）
	DTO_INIT(JsonVO, NoDataJsonVO);

	// 数据对象，承载业务层返回的实际数据
	DTO_FIELD(T, data, "data");
	DTO_FIELD_INFO(data) {
#ifndef LINUX
		info->description = u8"数据对象";
#else
		info->description = "data object";
#endif
	}

public:
	// 设置响应状态码和提示信息
	void setStatus(ResultStatus resultStatus) {
		this->message = resultStatus.getMessage();
		this->code = resultStatus.getCode();
	}
	// 同时初始化 data 和状态信息
	void init(T data, ResultStatus resultStatus) {
		this->data = data;
		this->setStatus(resultStatus);
	}
	// 便捷方法：构造成功响应（状态码 = SUCCESS）
	void success(T data) {
		this->setStatus(RS_SUCCESS);
		this->data = data;
	}
	// 便捷方法：构造失败响应（状态码 = FAIL）
	void fail(T data) {
		this->setStatus(RS_FAIL);
		this->data = data;
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_JSON_VO_
