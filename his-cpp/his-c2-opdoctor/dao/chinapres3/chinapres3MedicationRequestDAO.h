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
#ifndef _chinapres3MedicationRequestDAO_H_
#define _chinapres3MedicationRequestDAO_H_

#include "BaseDAO.h"
#include "chinapres3MedicationRequestMapper.h"
#include "../../domain/do/chinapres3/chinapres3MedicationRequestDO.h"
#include "../../domain/query/chinapres3/chinapres3MedicationRequestQuery.h"

/**
 * 处方药品申请数据访问对象
 *
 * 对应 med_medication_request 查询逻辑
 * 新增/修改/删除直接使用 BaseDAO 提供的 insert/update/deleteById 方法
 */
class chinapres3MedicationRequestDAO : public BaseDAO
{
private:
	std::string queryConditionBuilder(const chinapres3MedicationRequestQuery::Wrapper& query, SqlParams& params);

public:
	uint64_t count(const chinapres3MedicationRequestQuery::Wrapper& query);
	// Count DRAFT drug?line rows for a given prescription number
	// Used for all?or?nothing issue validation
	uint64_t countByPrescriptionNo(const std::string& prescriptionNo, const std::string& statusEnum);
	// BaseDO 为模板封装 selectWithPage/selectById 返回 shared_ptr 列表
	std::list<Ptrchinapres3MedicationRequestDO> selectWithPage(const chinapres3MedicationRequestQuery::Wrapper& query);
	Ptrchinapres3MedicationRequestDO selectById(const std::string& id);
};

#endif // !_chinapres3MedicationRequestDAO_H_