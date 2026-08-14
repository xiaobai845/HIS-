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
#ifndef _PATIENTACTDAO_H_
#define _PATIENTACTDAO_H_

#include "BaseDAO.h"
#include "domain/do/patient/ServiceRequestDO.h"

/**
 * ResultSet mapper for ServiceRequestDO.
 */
class ServiceRequestMapper : public Mapper<ServiceRequestDO>
{
public:
	ServiceRequestDO mapper(ResultSet* rs) const override;
};

/**
 * DAO for querying patient service request (act) data.
 *
 * Note: queries are filtered by encounter_id only. The patient_id
 * is no longer required because every encounter belongs to exactly
 * one patient, so filtering by encounter transitively scopes the
 * result to a single patient.
 */
class PatientActDAO : public BaseDAO
{
public:
	/*
	 * Query all service requests for an encounter.
	 * @param encounterId encounter ID (uniquely identifies the visit)
	 * @return list of ServiceRequestDO
	 */
	std::list<ServiceRequestDO> queryServiceRequests(const std::string& encounterId);
};

#endif // !_PATIENTACTDAO_H_
