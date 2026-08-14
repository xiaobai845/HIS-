#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2025/07/26

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
#ifndef _chinapres3MedicationDispenseDAO_H_
#define _chinapres3MedicationDispenseDAO_H_

#include "BaseDAO.h"
#include "chinapres3MedicationDispenseMapper.h"
#include "../../domain/do/chinapres3/chinapres3MedicationDispenseDO.h"
#include "../../domain/query/chinapres3/chinapres3MedicationDispenseQuery.h"

/**
 * 中药发药记录数据访问对象
 *
 * 对应 med_medication_dispense 表查询逻辑
 * 新增/修改/删除操作直接使用 BaseDAO 提供的 insert/update/deleteById 方法
 */
class chinapres3MedicationDispenseDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const chinapres3MedicationDispenseQuery::Wrapper& query, SqlParams& params);

public:
	uint64_t count(const chinapres3MedicationDispenseQuery::Wrapper& query);
	// BaseDO 为智能指针封装，selectWithPage/selectById 返回 shared_ptr 容器
	std::list<Ptrchinapres3MedicationDispenseDO> selectWithPage(const chinapres3MedicationDispenseQuery::Wrapper& query);
	Ptrchinapres3MedicationDispenseDO selectById(const std::string& id);
};

#endif // !_chinapres3MedicationDispenseDAO_H_