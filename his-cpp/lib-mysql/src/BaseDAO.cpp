/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 12:10:04

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
#include "../include/BaseDAO.h"

bool BaseDAO::extractFieldValue(DOField* field, SqlParams* params)
{
	void* val = field->get();
	if (val)
	{
		// 创建一个智能指针，并修改删除指针函数为空，然后添加到参数列表中
		params->emplace_back(SqlParam(field->getType(), std::shared_ptr<void>(val, [](void*) {})));
		return true;
	}
	return false;
}

void BaseDAO::extractFieldValueWithNul(DOField* field, SqlParams* params)
{
	void* val = field->get();
	if (val)
		// 创建一个智能指针，并修改删除指针函数为空，然后添加到参数列表中
		params->emplace_back(SqlParam(field->getType(), std::shared_ptr<void>(val, [](void*) {})));
	else if (field->getIsNullable())
		// 设置允许为NULL
		params->emplace_back(SqlParam("nul", std::make_shared<int>(1)));
	else
		throw std::runtime_error(string("Field(") + field->getColumn() + string(") value is null except not null."));
}

BaseDAO::BaseDAO()
{
	isAutoRelease = true;
	sqlSession = new SqlSession();
}

BaseDAO::~BaseDAO()
{
	if (isAutoRelease && sqlSession) delete sqlSession;
}

SqlSession* BaseDAO::getSqlSession()
{
	return this->sqlSession;
}

void BaseDAO::setSqlSession(SqlSession* session)
{
	if (sqlSession)
		delete sqlSession;
	this->sqlSession = session;
}

void BaseDAO::setAutoRelease(bool release)
{
	this->isAutoRelease = release;
}

uint64_t BaseDAO::insertAutoPk(const BaseDO& bd)
{
	SqlParams params;
	std::ostringstream col;
	std::ostringstream val;
	val << ") VALUES (";
	// 数据字段解析
	bool isFirst = true;
	for (auto field : bd.getFields())
	{
		if (extractFieldValue(field, &params))
		{
			if (!isFirst)
			{
				col << " ,";
				val << " ,";
			}
			else
				isFirst = false;
			col << field->getColumn();
			val << "?";
		}
	}
	// 构造SQL
	std::ostringstream sql;
	sql << "INSERT INTO " << bd.getTable() << " (";
	sql << col.str() << val.str() << " )";
	return sqlSession->executeInsert(sql.str(), params);
}

int BaseDAO::insert(const BaseDO& bd)
{
	// 如果主键为空
	if (!bd.getPrimaryField()->get())
		throw std::runtime_error("Primary field is null.");
	SqlParams params;
	std::ostringstream col;
	std::ostringstream val;
	val << ") VALUES (";
	// 主键字段
	col << bd.getPrimaryField()->getColumn();
	val << "?";
	extractFieldValue(bd.getPrimaryField(), &params);
	// 普通字段
	for (auto field : bd.getFields())
	{
		if (extractFieldValue(field, &params))
		{
			col << " ," << field->getColumn();
			val << " ,?";
		}
	}
	// 构造SQL
	std::ostringstream sql;
	sql << "INSERT INTO " << bd.getTable() << " (";
	sql << col.str() << val.str() << " )";
	return sqlSession->executeUpdate(sql.str(), params);
}

int BaseDAO::update(const BaseDO& bd)
{
	// 如果主键为空
	if (!bd.getPrimaryField()->get())
		throw std::runtime_error("Primary field is null.");
	SqlParams params;
	std::ostringstream sql;
	sql << "UPDATE " << bd.getTable() << " SET ";
	// 处理更新数据部分
	bool isFirst = true;
	for (auto field : bd.getFields())
	{
		if (extractFieldValue(field, &params))
		{
			if (!isFirst) sql << ", ";
			else isFirst = false;
			sql << field->getColumn() << " = ?";
		}
	}
	// 构建更新条件
	extractFieldValue(bd.getPrimaryField(), &params);
	sql << " WHERE " << bd.getPrimaryField()->getColumn() << " = ?";
	// 执行更新
	return sqlSession->executeUpdate(sql.str(), params);
}

int BaseDAO::update(const BaseDO& bd, const std::string& where)
{
	SqlParams params;
	std::ostringstream sql;
	sql << "UPDATE " << bd.getTable() << " SET ";
	// 构建更新数据部分
	bool isFirst = true;
	for (auto field : bd.getFields())
	{
		if (extractFieldValue(field, &params))
		{
			if (!isFirst) sql << ", ";
			else isFirst = false;
			sql << field->getColumn() << " = ?";
		}
	}
	// 拼接更新条件
	sql << " WHERE " << where;
	// 执行更新
	return sqlSession->executeUpdate(sql.str(), params);
}
