#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/08/04 21:47:06

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
#ifndef _SQL_HELPER_H_
#define _SQL_HELPER_H_

/**
 * 定义受保护的变量（最终类型是智能指针），并提供get、set方法
 * @param varType: 变量类型
 * @param varName: 变量名称
 * @param funName: get set 方法名称
 */
#define MYSQL_SYNTHESIZE(varType, varName, funName)\
protected: std::shared_ptr<varType> varName = nullptr;\
public: \
std::shared_ptr<varType> get##funName##Ptr(void) const { return varName; }\
varType get##funName(void) const { return *varName.get(); }\
public: void set##funName(varType var){	varName = std::make_shared<varType>(var);}

/**
 * 给DO的添加普通字段域
 * @param __COL_NAME__: 对应数据库的字段名称，如："name"、"sex"、"age"
 * @param __COL_TYPE__: 对应数据类型占位符，如："i"、"s"、"d"、"b"、"dt"、"nul"、"bi"、"ull"、"ll"、"ui"
 * @param __PROP_VAR__: 字段在DO中对应成员变量名
 */
#define MYSQL_ADD_FIELD(__COL_NAME__, __COL_TYPE__, __PROP_VAR__) \
addColField(new DOField(__COL_NAME__, __COL_TYPE__, [this]() {return __PROP_VAR__.get(); }))

/**
 * 给DO的添加普通字段域, 可以指定是否允许为NULL
 * @param __COL_NAME__: 对应数据库的字段名称，如："name"、"sex"、"age"
 * @param __COL_TYPE__: 对应数据类型占位符，如："i"、"s"、"d"、"b"、"dt"、"nul"、"bi"、"ull"、"ll"、"ui"
 * @param __PROP_VAR__: 字段在DO中对应成员变量名
 * @param __NULL_ABLE__: 是否允许为NULL，true允许为NULL，false不允许为NULL
 */
#define MYSQL_ADD_FIELD_NULLABLE(__COL_NAME__, __COL_TYPE__, __PROP_VAR__, __NULL_ABLE__) \
addColField(new DOField(__COL_NAME__, __COL_TYPE__, [this]() {return __PROP_VAR__.get(); }, __NULL_ABLE__))

/**
 * 给DO的添加主键字段域
 * @param __COL_NAME__: 对应数据库的字段名称，如："name"、"sex"、"age"
 * @param __COL_TYPE__: 对应数据类型占位符，如："i"、"s"、"d"、"b"、"dt"、"nul"、"bi"、"ull"、"ll"、"ui"
 * @param __PROP_VAR__: 字段在DO中对应成员变量名
 */
#define MYSQL_ADD_FIELD_PK(__COL_NAME__, __COL_TYPE__, __PROP_VAR__) \
addColField(new DOField(__COL_NAME__, __COL_TYPE__, [this]() {return __PROP_VAR__.get(); }, false, true))

#endif // !_SQL_HELPER_H_