#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2026/07/28

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
#ifndef _EmrDocument3DAO_H_
#define _EmrDocument3DAO_H_

#include "BaseDAO.h"
#include "EmrDocument3Mapper.h"
#include "../../domain/do/outpatientrecord3/EmrDocument3DO.h"

/**
 * 门诊病历文档数据访问对象
 *
 * 对应 emr_document 门诊病历数据表
 * 新增修改数据库直接继承 BaseDAO 能力。
 */
class EmrDocument3DAO : public BaseDAO
{
public:
	// Query a single record by primary key; returns nullptr if not found
	PtrEmrDocument3DO selectById(const std::string& id);

	// Query the active (non?deleted) document for a given encounter
	// Used for upsert: determine whether to insert or update
	PtrEmrDocument3DO selectByEncounterId(const std::string& encounterId);
};

#endif // !_EmrDocument3DAO_H_