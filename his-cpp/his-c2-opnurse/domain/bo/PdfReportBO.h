#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/11/28 15:19:56

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
#ifndef _PDFREPORTBO_H_
#define _PDFREPORTBO_H_
#include <list>
#include "oatpp/core/Types.hpp"

/**
 * 通用列表数据访问接口
 */
class IDataAccessor
{
public:
	virtual ~IDataAccessor() = default;
	// 获取当前元素指定字段值
	virtual std::string getField(const std::string& fieldName) const = 0;
	// 移动到下一个元素
	virtual void moveNext() = 0;
	// 是否有下一个元素
	virtual bool hasNext() = 0;
};

/**
 * 对应oatpp中的List列表数据的适配器
 */
template<typename T>
class OatppAccessor : public IDataAccessor
{
private:
	oatpp::List<T> wrapper_;
	typename std::list<T>::iterator iterator_;
public:
	explicit OatppAccessor(const oatpp::List<T>& wrapper) : wrapper_(wrapper)
	{
		iterator_ = wrapper_->begin();
	}

	std::string getField(const std::string& fieldName) const override
	{
		auto f = (*iterator_)[fieldName.c_str()];
		auto type = f.getValueType();
		if (type == oatpp::String::Class::getType())
			return f.template cast<oatpp::String>();
		else if (type == oatpp::Int32::Class::getType())
			return std::to_string(f.template cast<oatpp::Int32>());
		else if (type == oatpp::UInt32::Class::getType())
			return std::to_string(f.template cast<oatpp::UInt32>());
		else if (type == oatpp::Int64::Class::getType())
			return std::to_string(f.template cast<oatpp::Int64>());
		else if (type == oatpp::UInt64::Class::getType())
			return std::to_string(f.template cast<oatpp::UInt64>());
		else if (type == oatpp::Float32::Class::getType())
			return std::to_string(f.template cast<oatpp::Float32>());
		else if (type == oatpp::Float64::Class::getType())
			return std::to_string(f.template cast<oatpp::Float64>());
		else if (type == oatpp::Boolean::Class::getType())
			return std::to_string(f.template cast<oatpp::Boolean>());
		return "";
	}

	void moveNext() override
	{
		iterator_++;
	}

	bool hasNext() override
	{
		return iterator_ != wrapper_->end();
	}
};

/**
 * 表格列字段配置
 */
class FieldConfig
{
public:
	// 标题，如"编号"
	std::string title;
	// 属性，如"id"
	std::string prop;
	// 列宽，如果未指定，可以默认0或一个默认值
	float colwidth = 0;
};

#endif // !_PDFREPORTBO_H_