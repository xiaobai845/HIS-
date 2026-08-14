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
#ifndef _DEVICEREQUESTDO_H_
#define _DEVICEREQUESTDO_H_

#include "../DoInclude.h"

class DeviceRequestDO : public BaseDO {
    // Primary key
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // FK -> adm_patient
    MYSQL_SYNTHESIZE(std::string, patientId, PatientId);
    // FK -> adm_encounter
    MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);
    // FK -> adm_device_definition
    MYSQL_SYNTHESIZE(std::string, deviceDefId, DeviceDefId);
    // Status enum value
    MYSQL_SYNTHESIZE(std::string, statusEnum, StatusEnum);
    // Execution flag
    MYSQL_SYNTHESIZE(int, performFlag, PerformFlag);
    // Quantity
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    // Unit code
    MYSQL_SYNTHESIZE(std::string, unitCode, UnitCode);

public:
    DeviceRequestDO() : BaseDO("wkf_device_request") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("device_def_id", "s", deviceDefId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("perform_flag", "i", performFlag);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
    }
};

typedef std::shared_ptr<DeviceRequestDO> PtrDeviceRequestDO;

#endif // !_DEVICEREQUESTDO_H_
