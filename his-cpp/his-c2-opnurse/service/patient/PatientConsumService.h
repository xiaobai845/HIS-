#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: AI Assistant
 @Date: 2026/07/24 18:30:00

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
#ifndef _PATIENTCONSUMSERVICE_H_
#define _PATIENTCONSUMSERVICE_H_

#include "dao/patient/PatientConsumDAO.h"
#include "domain/dto/patient/PatientConsumableDTO.h"

/**
 * Service for handling patient consumable business logic.
 *
 * Query consumable items for a patient identified by encounterId.
 */
class PatientConsumService
{
public:
	/*
	 * Query device requests for a patient encounter.
	 * @param encounterId encounter ID (uniquely identifies the visit)
	 * @param consumableRoom optional filter (maps to status enum)
	 * @return list of PatientConsumableDTO
	 */
	oatpp::List<PatientConsumableDTO::Wrapper> queryDeviceRequests(
		const std::string& encounterId,
		const std::string& consumableRoom);
};

#endif // !_PATIENTCONSUMSERVICE_H_
