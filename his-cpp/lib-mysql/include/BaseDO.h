#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/08/04 15:17:29

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
#ifndef _BASEDO_H_
#define _BASEDO_H_
#include "SqlHelper.h"
#include <functional>
#include <string>
#include <vector>

/**
 * DO字段域，用于通过DO生成动态SQL语句
 */
class DOField final {
public:
	// 字段值获取函数
	using ValueGetter = std::function<void* ()>;
	// 构造函数
	DOField(std::string column, std::string type, ValueGetter getter, bool isNullable = true, bool isPrimaryKey = false);
	// 移动构造函数
	DOField(DOField&& other) noexcept;
	// 删除拷贝构造/赋值
	DOField(const DOField&) = delete;
	DOField& operator=(const DOField&) = delete;
	// 获取字段名称
	std::string getColumn() const;
	// 获取字段类型占位符
	std::string getType() const;
	// 获取是否为主键
	bool getIsPrimaryKey() const;
	// 获取字段是否允许为空
	bool getIsNullable() const;
	// 获取字段值指针
	void* get();
	// 获取字段值
	template<typename T>
	const T* getValue();
private:
	// 字段名称
	std::string column;
	// 字段类型占位符，如：s、i、b、d、dt
	std::string type;
	// 字段是否是主键
	bool isPrimaryKey;
	// 字段是否允许为空
	bool isNullable;
	// 获取字段值的函数
	ValueGetter getter;
};

template<typename T>
const T* DOField::getValue()
{
	void* value = getter();
	if (value) return static_cast<T*>(value);
	return nullptr;
}

/**
 * 定义一个基础的DO类，方便管理，后续定义DO都需要继承它
 */
class BaseDO
{
protected:
	// 添加字段域
	void addColField(DOField* field);
	// 构造时必须指定数据库表名
	BaseDO(std::string table);
private:
	// 表名
	std::string _table;
	// 主键字段域
	DOField* _primaryField;
	// 普通字段域
	std::vector<DOField*> _fields;
public:
	// 析构函数
	virtual ~BaseDO();
	// 删除拷贝构造/赋值
	BaseDO(const BaseDO&) = delete;
	BaseDO& operator=(const BaseDO&) = delete;
	// 移动构造函数
	BaseDO(BaseDO&& other) noexcept;
	// 移动赋值运算符
	BaseDO& operator=(BaseDO&& other) noexcept;
	// 获取表名
	std::string getTable() const;
	// 获取主键字段域
	DOField* getPrimaryField() const;
	// 获取普通字段域
	const std::vector<DOField*>& getFields() const;
};

#endif // !_BASEDO_H_