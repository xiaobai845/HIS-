#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2025/07/26

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
#ifndef _chinapres3MedicationDispenseDO_H_
#define _chinapres3MedicationDispenseDO_H_

#include "../DoInclude.h"

/**
 * Medication Dispense Data Object
 *
 * Database table: med_medication_dispense
 *
 * Field registration strategy:
 *   - All fields declared via MYSQL_SYNTHESIZE for result mapping and serialization.
 *   - DML-relevant fields registered in constructor (used by BaseDAO insert/update).
 */
class chinapres3MedicationDispenseDO : public BaseDO
{
	// =============================
	// Primary Key
	// =============================
	MYSQL_SYNTHESIZE(string, id, Id);

	// =============================
	// DML Key Fields
	// =============================
	// Medication request ID, references med_medication_request.id
	MYSQL_SYNTHESIZE(string, medReqId, MedReqId);
	// Patient ID, references adm_patient.id
	MYSQL_SYNTHESIZE(string, patientId, PatientId);
	// Encounter ID, references adm_encounter.id
	MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
	// Business serial number (bus prefix + snowflake ID)
	MYSQL_SYNTHESIZE(string, busNo, BusNo);
	// Status enum (PREPARATION, DISPENSED, etc.)
	MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);

	// =============================
	// Additional Fields Used by Service
	// =============================
	// Dispense type enum (OUTPATIENT, INPATIENT, etc.)
	MYSQL_SYNTHESIZE(string, dispenseEnum, DispenseEnum);
	// Location ID (dispensing department), references adm_location.id
	MYSQL_SYNTHESIZE(string, locationId, LocationId);
	// Medication ID, references med_medication_definition.id
	MYSQL_SYNTHESIZE(string, medicationId, MedicationId);
	// Quantity to dispense
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	// Unit code for medication
	MYSQL_SYNTHESIZE(string, unitCode, UnitCode);

	// =============================
	// Audit Fields
	// =============================
	// Created by (operator)
	MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
	// Created at (timestamp)
	MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
	// Updated by (operator)
	MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
	// Updated at (timestamp)
	MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);

	// ---- revoke-related field ----
	// Logical delete flag (0 = active, 1 = deleted), used by revoke flow
	MYSQL_SYNTHESIZE(string, isDeleted, IsDeleted);

public:
	chinapres3MedicationDispenseDO() : BaseDO("med_medication_dispense")
	{
		// Primary Key
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// DML Key Fields
		MYSQL_ADD_FIELD("med_req_id", "s", medReqId);
		MYSQL_ADD_FIELD("patient_id", "s", patientId);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
		MYSQL_ADD_FIELD("bus_no", "s", busNo);
		MYSQL_ADD_FIELD("status_enum", "s", statusEnum);

		// Additional Fields (set by Service on insert)
		MYSQL_ADD_FIELD("dispense_enum", "s", dispenseEnum);
		MYSQL_ADD_FIELD("location_id", "s", locationId);
		MYSQL_ADD_FIELD("medication_id", "s", medicationId);
		MYSQL_ADD_FIELD("quantity", "d", quantity);
		MYSQL_ADD_FIELD("unit_code", "s", unitCode);
		MYSQL_ADD_FIELD("created_by", "s", createdBy);
		MYSQL_ADD_FIELD("created_at", "s", createdAt);

		// ---- revoke-related DML registration ----
		MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
		MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
		MYSQL_ADD_FIELD("is_deleted", "s", isDeleted);
	}
};

// Shared pointer type alias
typedef std::shared_ptr<chinapres3MedicationDispenseDO> Ptrchinapres3MedicationDispenseDO;

#endif // !_chinapres3MedicationDispenseDO_H_
