#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/20 10:27:42
 @description: 这里定义了基本数据类型对应的响应JsonVO，用于向前端返回各种基础类型的数据。

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
#ifndef _BASE_JSON_VO_H_
#define _BASE_JSON_VO_H_
#include "JsonVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 字符串类型JsonVO，用于响应客户端的字符串类型数据
 */
class StringJsonVO : public JsonVO<String>
{
	DTO_INIT(StringJsonVO, JsonVO<String>);
};

/**
 * 32位整型JsonVO，用于响应客户端的整数类型数据
 */
class Int32JsonVO : public JsonVO<Int32>
{
	DTO_INIT(Int32JsonVO, JsonVO<Int32>);
};

/**
 * 无符号32位整型JsonVO，用于响应客户端的无符号整数类型数据
 */
class Uint32JsonVO : public JsonVO<UInt32>
{
	DTO_INIT(Uint32JsonVO, JsonVO<UInt32>);
};

/**
 * 64位整型JsonVO，用于响应客户端的长整数类型数据
 */
class Int64JsonVO : public JsonVO<Int64>
{
	DTO_INIT(Int64JsonVO, JsonVO<Int64>);
};

/**
 * 无符号64位整型JsonVO，用于响应客户端的无符号长整数类型数据
 */
class Uint64JsonVO : public JsonVO<UInt64>
{
	DTO_INIT(Uint64JsonVO, JsonVO<UInt64>);
};

/**
 * 单精度浮点型JsonVO，用于响应客户端的浮点数类型数据
 */
class FloatJsonVO : public JsonVO<Float32>
{
	DTO_INIT(FloatJsonVO, JsonVO<Float32>);
};

/**
 * 双精度浮点型JsonVO，用于响应客户端的双精度浮点数类型数据
 */
class DoubleJsonVO : public JsonVO<Float64>
{
	DTO_INIT(DoubleJsonVO, JsonVO<Float64>);
};

/**
 * 布尔类型JsonVO，用于响应客户端的布尔值类型数据
 */
class BooleanJsonVO : public JsonVO<Boolean>
{
	DTO_INIT(BooleanJsonVO, JsonVO<Boolean>);
};

/**
 * 列表类型JsonVO（泛型模板类），用于响应客户端的列表类型数据
 *
 * @tparam T 列表元素的数据类型，通常为 DTO::Wrapper 类型
 */
template<class T>
class ListJsonVO : public JsonVO<List<T>>
{
	DTO_INIT(ListJsonVO, JsonVO<List<T>>);
public:
	// 构造函数：初始化为空列表
	ListJsonVO() {
		this->data = {};
	}
	// 向列表中添加一个元素
	void addData(T data) {
		this->data->push_back(data);
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_BASE_JSON_VO_H_
