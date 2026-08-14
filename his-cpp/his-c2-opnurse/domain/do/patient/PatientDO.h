#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: AI Assistant
 @Date: 2026/07/24 18:05:00

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
#ifndef _PATIENTDO_H_
#define _PATIENTDO_H_

#include "../DoInclude.h"

class PatientDO : public BaseDO {
    // Primary key
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // Patient name
    MYSQL_SYNTHESIZE(std::string, name, Name);
    // Gender enum code
    MYSQL_SYNTHESIZE(std::string, genderEnum, GenderEnum);
    // Birth date (used to calculate age)
    MYSQL_SYNTHESIZE(std::string, birthDate, BirthDate);
    // Tenant ID
    MYSQL_SYNTHESIZE(std::string, tenantId, TenantId);

public:
    PatientDO() : BaseDO("adm_patient") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("gender_enum", "s", genderEnum);
        MYSQL_ADD_FIELD("birth_date", "s", birthDate);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
    }
};

typedef std::shared_ptr<PatientDO> PtrPatientDO;

#endif // !_PATIENTDO_H_
