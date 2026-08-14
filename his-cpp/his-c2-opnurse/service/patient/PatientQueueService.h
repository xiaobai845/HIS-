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
#ifndef _PATIENTQUEUESERVICE_H_
#define _PATIENTQUEUESERVICE_H_

#include "dao/patient/PatientQueueDAO.h"
#include "domain/dto/patient/PatientQueueDTO.h"

/**
 * Service for handling patient queue business logic.
 */
class PatientQueueService
{
public:
	/*
	 * Query patient queue with pagination.
	 * @param keyword optional filter (patient name or queue number)
	 * @param startDate optional start date filter
	 * @param endDate optional end date filter
	 * @param userId current user ID for tenant lookup
	 * @param pageIndex page index (1-based)
	 * @param pageSize page size
	 * @return page DTO with patient queue items and total count
	 */
	PatientQueuePageDTO::Wrapper queryPatientQueue(
		const std::string& keyword,
		const std::string& startDate,
		const std::string& endDate,
		const std::string& userId,
		int pageIndex,
		int pageSize);

private:
	/*
	 * Calculate age from birth date string (yyyy-MM-dd).
	 */
	int calcAge(const std::string& birthDate);

	/*
	 * Convert gender enum code to display text.
	 */
	std::string convertGender(const std::string& genderEnum);

	/*
	 * Get tenant ID from Redis by user ID.
	 */
	std::string getTenantIdFromRedis(const std::string& userId);
};

#endif // !_PATIENTQUEUESERVICE_H_
