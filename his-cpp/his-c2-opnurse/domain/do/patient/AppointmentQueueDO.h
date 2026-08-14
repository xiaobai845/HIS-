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
#ifndef _APPOINTMENTQUEUEDO_H_
#define _APPOINTMENTQUEUEDO_H_

#include "../DoInclude.h"

class AppointmentQueueDO : public BaseDO {
    // Primary key
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // FK -> adm_patient
    MYSQL_SYNTHESIZE(std::string, patientId, PatientId);
    // FK -> adm_encounter
    MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);
    // Business number (displayed queue number)
    MYSQL_SYNTHESIZE(std::string, busNo, BusNo);
    // Display order (queue sequence)
    MYSQL_SYNTHESIZE(int, displayOrder, DisplayOrder);
    // Planned start time (visit time)
    MYSQL_SYNTHESIZE(std::string, startInstant, StartInstant);
    // Booking date (visit date)
    MYSQL_SYNTHESIZE(std::string, bookingDate, BookingDate);
    // Triage level (status)
    MYSQL_SYNTHESIZE(std::string, triageLevel, TriageLevel);
    // Last called time
    MYSQL_SYNTHESIZE(std::string, calledAt, CalledAt);
    // Tenant ID
    MYSQL_SYNTHESIZE(std::string, tenantId, TenantId);

public:
    AppointmentQueueDO() : BaseDO("wkf_appointment_queue") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("display_order", "i", displayOrder);
        MYSQL_ADD_FIELD("start_instant", "s", startInstant);
        MYSQL_ADD_FIELD("booking_date", "s", bookingDate);
        MYSQL_ADD_FIELD("triage_level", "s", triageLevel);
        MYSQL_ADD_FIELD("called_at", "s", calledAt);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
    }
};

typedef std::shared_ptr<AppointmentQueueDO> PtrAppointmentQueueDO;

#endif // !_APPOINTMENTQUEUEDO_H_
