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
#ifndef _NURSE_SERVICE2_
#define _NURSE_SERVICE2_

#include "domain/dto/nurse2/NurseCancelDTO2.h"
#include "domain/dto/nurse2/NurseOperateDTO2.h"

/**
 * Nurse2 business logic service
 */
class NurseService2
{
public:
	/**
	 * Execute nurse operation -- update service request status by item ID
	 * @param dto execute DTO containing encounterId, itemId, state, amount
	 * @param username current operator username from auth payload
	 * @return true if update succeeded (1 row affected)
	 */
	bool NurseOperate2(const NurseOperateDTO2::Wrapper& dto, const std::string& username);

	/**
	 * Cancel nurse execution -- update service request status to CANCELLED
	 * @param dto cancel DTO containing encounterId, itemId, cancelReason
	 * @param username current operator username from auth payload
	 * @return true if update succeeded (1 row affected)
	 */
	bool NurseCancel2(const NurseCancelDTO2::Wrapper& dto, const std::string& username);
};

#endif // !_NURSE_SERVICE2_
