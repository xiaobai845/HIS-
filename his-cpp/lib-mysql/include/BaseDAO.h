#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 10:50:10

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
#ifndef _ABSTRACT_DAO_
#define _ABSTRACT_DAO_
#include <sstream>
#include "SqlSession.h"
#include "BaseDO.h"

/**
 * 定义一个基础的DAO类，方便管理，后续定义DAO都需要继承它
 */
class BaseDAO
{
private:
	// 是否自动释放SQLSession
	bool isAutoRelease;
protected:
	// 定义一个SqlSession
	SqlSession* sqlSession;
	/**
	 * 字段域数据提取
	 * @param DOField* field 字段域对象
	 * @param SqlParams* params 参数对象
	 * @return 返回true表示此字段域需要处理数据，返回false表示此字段域不需要处理数据
	 */
	bool extractFieldValue(DOField* field, SqlParams* params);
	/**
	 * 字段域数据提取，为空的数据设置为NULL，并检查非空数据是否为NULL
	 * @param DOField* field 字段域对象
	 * @param SqlParams* params 参数对象
	 */
	void extractFieldValueWithNul(DOField* field, SqlParams* params);
public:
	BaseDAO();
	virtual ~BaseDAO();
	// 获取SqlSession
	SqlSession* getSqlSession();
	// 设置SqlSession
	void setSqlSession(SqlSession* session);
	// 设置是否自动释放SqlSession
	void setAutoRelease(bool release);
	/**
	 * 插入数据,主键为自增
	 * @param const BaseDO& bd 数据对象
	 * @return 返回自增主键
	 */
	uint64_t insertAutoPk(const BaseDO& bd);
	/**
	 * 批量插入数据,主键为自增
	 * @param const std::list<T>& bdList 数据对象列表
	 * @param int batchSize 插入批次数量，根据数据量自行设置，默认1000
	 * @return 影响行数
	 */
	template<typename T>
	int insertAutoPkBatch(const std::list<T>& bdList, int batchSize = 1000);
	/**
	 * 插入数据,主键为非自增
	 * @param const BaseDO& bd 数据对象
	 * @return 影响行数
	 */
	int insert(const BaseDO& bd);
	/**
	 * 批量插入数据,主键为非自增
	 * @param const std::list<T>& bdList 数据对象列表
	 * @param int batchSize 插入批次数量，根据数据量自行设置，默认1000
	 * @return 影响行数
	 */
	template<typename T>
	int insertBatch(const std::list<T>& bdList, int batchSize = 1000);
	/**
	 * 修改数据，更新条件为主键
	 * @param const BaseDO& bd 数据对象
	 * @return 影响行数
	 */
	int update(const BaseDO& bd);
	/**
	 * 修改数据，指定更新条件数据
	 * @param const BaseDO& bd 更新数据对象
	 * @param const std::string& where 更新条件，如：(name='test' AND sex='男') OR id=1
	 * @return 影响行数
	 */
	int update(const BaseDO& bd, const std::string& where);
	/**
	 * 批量修改数据，更新条件为主键
	 * @param const std::list<T>& bdList 数据对象列表
	 * @return 影响行数
	 */
	template<typename T>
	int updateBatch(const std::list<T>& bdList);
	/**
	 * 删除数据，根据主键删除
	 * @param const std::string& id 主键值
	 * @return 影响行数
	 */
	template<typename T>
	int deleteById(const std::string& id);
	/**
	 * 批量删除数据，根据主键删除
	 * @param const std::list<std::string>& ids 主键值列表
	 * @return 影响行数
	 */
	template<typename T>
	int deleteByIds(const std::list<std::string>& ids);
};

template<typename T>
int BaseDAO::insertAutoPkBatch(const std::list<T>& bdList, int batchSize /*= 1000*/)
{
	// 检测T是否继承自BaseDO
	static_assert(std::is_base_of<BaseDO, T>::value, "T must be derived from BaseDO");
	// 开启事务
	sqlSession->beginTransaction();
	// 构建列数据
	std::ostringstream col;
	col << " (";
	auto& oneBd = bdList.front();
	bool first = true;
	for (auto& field : oneBd.getFields())
	{
		if (!first) col << " ,";
		else first = false;
		col << field->getColumn();
	}
	col << " )";
	// 构建值数据
	SqlParams params;
	std::ostringstream val;
	int current = 0;
	int rows = 0;
	first = true;
	try
	{
		for (auto& bd : bdList)
		{
			// 拼接数据字段
			if (!first) val << ",";
			else first = false;
			bool valfirst = true;
			for (auto field : bd.getFields())
			{
				extractFieldValueWithNul(field, &params);
				if (!valfirst) val << " ,";
				else
				{
					valfirst = false;
					val << " ( ";
				}
				val << "?";
			}
			val << " ) ";
			current++;
			// 达到批次容量或最后一个数据
			if (current % batchSize == 0 || current >= bdList.size())
			{
				// 执行数据插入
				std::ostringstream sql;
				sql << "INSERT INTO " << bd.getTable();
				sql << col.str() << " VALUES " << val.str();
				rows += sqlSession->executeUpdate(sql.str(), params);
				// 重置拼接数据
				val = std::ostringstream();
				params.clear();
				first = true;
			}
		}
	}
	catch (...)
	{
		// 回滚事务
		sqlSession->rollbackTransaction();
		throw;
	}
	// 提交事务
	if (rows == bdList.size())
	{
		sqlSession->commitTransaction();
		return rows;
	}
	// 回滚事务
	sqlSession->rollbackTransaction();
	return 0;
}

template<typename T>
int BaseDAO::insertBatch(const std::list<T>& bdList, int batchSize /*= 1000*/)
{
	// 检测T是否继承自BaseDO
	static_assert(std::is_base_of<BaseDO, T>::value, "T must be derived from BaseDO");
	// 开启事务
	sqlSession->beginTransaction();
	// 构建列数据
	auto& oneBd = bdList.front();
	std::ostringstream col;
	col << " ( ";
	// 添加主键列
	col << oneBd.getPrimaryField()->getColumn();
	// 添加普通列
	for (auto& field : oneBd.getFields())
	{
		col << ", " << field->getColumn();
	}
	col << " )";
	// 构建值数据
	SqlParams params;
	std::ostringstream val;
	int current = 0;
	int rows = 0;
	bool first = true;
	try
	{
		for (auto& bd : bdList)
		{
			// 拼接数据分隔符
			if (!first) val << ",";
			else first = false;
			// 如果主键为空
			if (!bd.getPrimaryField()->get())
				throw std::runtime_error("Primary field is null.");
			// 主键列值
			extractFieldValueWithNul(bd.getPrimaryField(), &params);
			val << "( ?";
			// 普通列值
			for (auto field : bd.getFields())
			{
				extractFieldValueWithNul(field, &params);
				val << ", ?";
			}
			val << " ) ";
			current++;
			// 达到批次容量或最后一个数据
			if (current % batchSize == 0 || current >= bdList.size())
			{
				// 执行数据插入
				std::ostringstream sql;
				sql << "INSERT INTO " << bd.getTable();
				sql << col.str() << " VALUES " << val.str();
				rows += sqlSession->executeUpdate(sql.str(), params);
				// 重置拼接数据
				val = std::ostringstream();
				params.clear();
				first = true;
			}
		}
	}
	catch (...)
	{
		// 回滚事务
		sqlSession->rollbackTransaction();
		throw;
	}
	// 提交事务
	if (rows == bdList.size())
	{
		sqlSession->commitTransaction();
		return rows;
	}
	// 回滚事务
	sqlSession->rollbackTransaction();
	return 0;
}

template<typename T>
int BaseDAO::updateBatch(const std::list<T>& bdList)
{
	// 检测T是否继承自BaseDO
	static_assert(std::is_base_of<BaseDO, T>::value, "T must be derived from BaseDO");
	// 开启事务
	sqlSession->beginTransaction();
	// 创建SQL语句
	SqlParams params;
	int rows = 0;
	try
	{
		for (auto& bd : bdList)
		{
			// 如果主键为空
			if (!bd.getPrimaryField()->get())
				throw std::runtime_error("Primary field is null.");
			// 构建更新SQL
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

			// 执行数据更新
			rows += sqlSession->executeUpdate(sql.str(), params);
			params.clear();
		}
	}
	catch (...)
	{
		// 回滚事务
		sqlSession->rollbackTransaction();
		throw;
	}
	// 提交事务
	if (rows == bdList.size())
	{
		sqlSession->commitTransaction();
		return rows;
	}
	// 回滚事务
	sqlSession->rollbackTransaction();
	return 0;
}

template<typename T>
int BaseDAO::deleteById(const std::string& id)
{
	// 检测T是否继承自BaseDO
	static_assert(std::is_base_of<BaseDO, T>::value, "T must be derived from BaseDO");
	// 构建删除语句与参数
	T bd;
	std::ostringstream sql;
	sql << "DELETE FROM " << bd.getTable() << " WHERE " << bd.getPrimaryField()->getColumn() << " = ?";
	// 执行删除
	return sqlSession->executeUpdate(sql.str(), "%s", id);
}

template<typename T>
int BaseDAO::deleteByIds(const std::list<std::string>& ids)
{
	// 检测T是否继承自BaseDO
	static_assert(std::is_base_of<BaseDO, T>::value, "T must be derived from BaseDO");
	// 构建删除语句与参数
	T bd;
	SqlParams params;
	std::ostringstream sql;
	bool isFirst = true;
	sql << "DELETE FROM " << bd.getTable() << " WHERE " << bd.getPrimaryField()->getColumn() << " IN (";
	for (auto it = ids.begin(); it != ids.end(); ++it)
	{
		if (isFirst) isFirst = false;
		else sql << ",";
		sql << "?";
		params.push_back(SqlParam("s", std::make_shared<std::string>(*it)));
	}
	sql << ")";
	// 执行删除
	return sqlSession->executeUpdate(sql.str(), params);
}

#endif // !_ABSTRACT_DAO_
