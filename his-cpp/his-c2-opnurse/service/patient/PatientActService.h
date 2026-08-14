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
#ifndef _PATIENTACTSERVICE_H_
#define _PATIENTACTSERVICE_H_

#include "dao/patient/PatientActDAO.h"
#include "dao/patient/PatientQueueDAO.h"
#include "domain/dto/patient/PatientActDTO.h"

/**
 * Service for handling patient service request (act) business logic.
 *
 * Query act items for a patient identified by encounterId.
 * Returns a wrapper DTO with patient info at the top level
 * and act items in a nested list, matching the UI layout.
 */
class PatientActService
{
public:
	/*
	 * Query all service requests for a patient encounter.
	 * @param encounterId encounter ID (uniquely identifies the visit)
	 * @return wrapper DTO with patient info and act item list
	 */
	oatpp::Object<PatientActWrapperDTO> queryServiceRequests(
		const std::string& encounterId);
};

#endif // !_PATIENTACTSERVICE_H_
