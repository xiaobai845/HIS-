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
#ifndef _SERVICEREQUESTDO_H_
#define _SERVICEREQUESTDO_H_

#include "../DoInclude.h"

class ServiceRequestDO : public BaseDO {
    // Primary key
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // FK -> adm_patient
    MYSQL_SYNTHESIZE(std::string, patientId, PatientId);
    // FK -> adm_encounter
    MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);
    // Status enum value
    MYSQL_SYNTHESIZE(std::string, statusEnum, StatusEnum);
    // Order content text
    MYSQL_SYNTHESIZE(std::string, entrustContent, EntrustContent);
    // Execution flag
    MYSQL_SYNTHESIZE(int, performFlag, PerformFlag);
    // FK -> adm_charge_item_definition
    MYSQL_SYNTHESIZE(std::string, activityId, ActivityId);
    // Category enum (type: execute / skin-test / infusion)
    MYSQL_SYNTHESIZE(std::string, categoryEnum, CategoryEnum);
    // Quantity
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    // Unit code
    MYSQL_SYNTHESIZE(std::string, unitCode, UnitCode);
    // Order authored time
    MYSQL_SYNTHESIZE(std::string, authoredTime, AuthoredTime);
    // Remark
    MYSQL_SYNTHESIZE(std::string, remark, Remark);
    // Total price from adm_charge_item (not persisted in this table)
    std::string totalPrice;

public:
    ServiceRequestDO() : BaseDO("wkf_service_request") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("entrust_content", "s", entrustContent);
        MYSQL_ADD_FIELD("perform_flag", "i", performFlag);
        MYSQL_ADD_FIELD("activity_id", "s", activityId);
        MYSQL_ADD_FIELD("category_enum", "s", categoryEnum);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
        MYSQL_ADD_FIELD("authored_time", "s", authoredTime);
        MYSQL_ADD_FIELD("remark", "s", remark);
    }

    void setTotalPrice(const std::string& price) { totalPrice = price; }
    std::string getTotalPrice() const { return totalPrice; }
};

typedef std::shared_ptr<ServiceRequestDO> PtrServiceRequestDO;

#endif // !_SERVICEREQUESTDO_H_
