#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:20:12

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

#include <list>
#include <string>

#include "BaseDAO.h"
#include "domain/do/diagnose/AdmEncounterDiagnosisDO.h"

/**
 * DAO for patient diagnosis queries.
 * JOIN between adm_encounter and adm_encounter_diagnosis is performed at the SQL level.
 */
class PatientDiagnoseDAO : public BaseDAO
{
public:
	// Count diagnoses by patient ID with JOIN (in-database JOIN)
	uint64_t countDiagnosesByPatientId(
		const std::string& patientId,
		const std::string& keyword,
		const std::string& diagTypeCode,
		const std::string& startDate,
		const std::string& endDate);

	// Select paginated diagnoses by patient ID with JOIN (in-database JOIN)
	std::list<PtrAdmEncounterDiagnosisDO> selectDiagnosesByPatientId(
		const std::string& patientId,
		const std::string& keyword,
		const std::string& diagTypeCode,
		const std::string& startDate,
		const std::string& endDate,
		uint64_t offset,
		uint64_t pageSize);
};
