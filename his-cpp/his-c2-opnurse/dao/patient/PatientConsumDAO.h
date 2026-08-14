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
#ifndef _PATIENTCONSUNDAO_H_
#define _PATIENTCONSUNDAO_H_

#include "BaseDAO.h"
#include "domain/do/patient/DeviceRequestDO.h"
#include "domain/do/patient/DeviceDefinitionDO.h"

/**
 * Combined result for device request query (JOIN wkf_device_request + adm_device_definition + related dicts).
 */
struct DeviceConsumResult
{
	DeviceRequestDO request;
	DeviceDefinitionDO definition;
	// Extra fields from joined tables
	std::string statusName;
	std::string unitName;
};

/**
 * ResultSet mapper for DeviceConsumResult.
 */
class DeviceConsumMapper : public Mapper<DeviceConsumResult>
{
public:
	DeviceConsumResult mapper(ResultSet* rs) const override;
};

/**
 * DAO for querying device consumable data.
 *
 * Note: queries are filtered by encounter_id only. The patient_id
 * is no longer required because every encounter belongs to exactly
 * one patient, so filtering by encounter transitively scopes the
 * result to a single patient.
 */
class PatientConsumDAO : public BaseDAO
{
public:
	/*
	 * Query all device requests with device definition for an encounter.
	 * @param encounterId encounter ID (uniquely identifies the visit)
	 * @param consumableRoom optional consumable room filter
	 * @return list of DeviceConsumResult
	 */
	std::list<DeviceConsumResult> queryDeviceRequests(
		const std::string& encounterId,
		const std::string& consumableRoom);
};

#endif // !_PATIENTCONSUNDAO_H_
