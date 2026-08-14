/*
 Copyright Zero One Star. All rights reserved.

 @Author: fa-mian-tuan
 @Date: 2026/08/01

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
#include "stdafx.h"
#include "nurseService2.h"
#include "dao/nurse2/NurseDAO2.h"

bool NurseService2::NurseOperate2(const NurseOperateDTO2::Wrapper& dto, const std::string& username)
{
	// Extract fields from DTO
	std::string encounterId = dto->encounterId.getValue("");
	std::string itemId = dto->itemId.getValue("");
	std::string status = dto->state ? dto->state.getValue("") : "COMPLETED";
	int execCount = dto->amount ? dto->amount.getValue(0) : 1;

	// Update service request by primary key with encounter validation
	NurseDAO2 dao;
	return dao.updateExecutionStatus(itemId, encounterId, status, execCount, username) == 1;
}

bool NurseService2::NurseCancel2(const NurseCancelDTO2::Wrapper& dto, const std::string& username)
{
	// Extract fields from DTO
	std::string encounterId = dto->encounterId.getValue("");
	std::string itemId = dto->itemId.getValue("");
	std::string cancelReason = dto->cancelReason ? dto->cancelReason.getValue("") : "";

	// Cancel service request by primary key with encounter validation
	NurseDAO2 dao;
	return dao.updateCancelStatus(itemId, encounterId, cancelReason, username) == 1;
}
