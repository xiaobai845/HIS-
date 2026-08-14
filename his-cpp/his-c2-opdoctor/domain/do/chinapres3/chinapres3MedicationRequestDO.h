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
#ifndef _chinapres3MedicationRequestDO_H_
#define _chinapres3MedicationRequestDO_H_

#include "../DoInclude.h"

/**
 * Medication Request Data Object
 *
 * Database table: med_medication_request
 *
 * Field registration strategy:
 *   - All fields declared via MYSQL_SYNTHESIZE for result mapping and serialization.
 *   - DML-relevant fields registered in constructor (used by BaseDAO insert/update).
 */
class chinapres3MedicationRequestDO : public BaseDO
{
	// =============================
	// Primary Key
	// =============================
	MYSQL_SYNTHESIZE(string, id, Id);

	// =============================
	// DML Key Fields
	// =============================
	// Prescription number shared by multiple medication records under the same prescription
	MYSQL_SYNTHESIZE(string, prescriptionNo, PrescriptionNo);
	// Patient ID, references adm_patient.id
	MYSQL_SYNTHESIZE(string, patientId, PatientId);
	// Encounter ID, references adm_encounter.id
	MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
	// Status enum (DRAFT, ACTIVE, CANCELLED, etc.)
	MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);

	// =============================
	// Additional Fields Used by Service
	// =============================
	// Prescription type code, set to "TCM" on issue
	MYSQL_SYNTHESIZE(string, rxTypeCode, RxTypeCode);
	// Medication ID, references med_medication_definition.id
	MYSQL_SYNTHESIZE(string, medicationId, MedicationId);
	// Quantity prescribed
	MYSQL_SYNTHESIZE(double, quantity, Quantity);
	// Unit code for medication
	MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
	// Location ID (department), references adm_location.id
	MYSQL_SYNTHESIZE(string, locationId, LocationId);

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

public:
	chinapres3MedicationRequestDO() : BaseDO("med_medication_request")
	{
		// Primary Key
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// DML Key Fields (required for UPDATE)
		MYSQL_ADD_FIELD("prescription_no", "s", prescriptionNo);
		MYSQL_ADD_FIELD("patient_id", "s", patientId);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
		MYSQL_ADD_FIELD("status_enum", "s", statusEnum);

		// Additional Fields for UPDATE (set by Service on issue)
		MYSQL_ADD_FIELD("rx_type_code", "s", rxTypeCode);
		MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
		MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
	}
};

// Shared pointer type alias
typedef std::shared_ptr<chinapres3MedicationRequestDO> Ptrchinapres3MedicationRequestDO;

#endif // !_chinapres3MedicationRequestDO_H_
