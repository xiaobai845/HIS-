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
#ifndef _DEVICEDEFINITIONDO_H_
#define _DEVICEDEFINITIONDO_H_

#include "../DoInclude.h"

class DeviceDefinitionDO : public BaseDO {
    // Primary key
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // Device name
    MYSQL_SYNTHESIZE(std::string, name, Name);
    // Model / spec number
    MYSQL_SYNTHESIZE(std::string, modelNumber, ModelNumber);
    // Merchandise name
    MYSQL_SYNTHESIZE(std::string, merchandiseName, MerchandiseName);
    // Package spec description
    MYSQL_SYNTHESIZE(std::string, totalVolume, TotalVolume);

public:
    DeviceDefinitionDO() : BaseDO("adm_device_definition") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("model_number", "s", modelNumber);
        MYSQL_ADD_FIELD("merchandise_name", "s", merchandiseName);
        MYSQL_ADD_FIELD("total_volume", "s", totalVolume);
    }
};

typedef std::shared_ptr<DeviceDefinitionDO> PtrDeviceDefinitionDO;

#endif // !_DEVICEDEFINITIONDO_H_
