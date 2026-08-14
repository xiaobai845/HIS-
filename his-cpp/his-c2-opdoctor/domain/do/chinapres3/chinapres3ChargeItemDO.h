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
#ifndef _chinapres3ChargeItemDO_H_
#define _chinapres3ChargeItemDO_H_

#include "../DoInclude.h"

/**
 * Charge Item Data Object
 *
 * Database table: adm_charge_item
 *
 * Field registration strategy:
 *   - All fields declared via MYSQL_SYNTHESIZE for result mapping and serialization.
 *   - DML-relevant fields registered in constructor (used by BaseDAO insert/update).
 */
class chinapres3ChargeItemDO : public BaseDO
{
	// =============================
	// Primary Key
	// =============================
	MYSQL_SYNTHESIZE(string, id, Id);

	// =============================
	// DML Key Fields
	// =============================
	// Service source table, fixed "med_medication_request"
	MYSQL_SYNTHESIZE(string, serviceTable, ServiceTable);
	// Service source record ID, references med_medication_request.id
	MYSQL_SYNTHESIZE(string, serviceId, ServiceId);
	// Patient ID, references adm_patient.id
	MYSQL_SYNTHESIZE(string, patientId, PatientId);
	// Encounter ID, references adm_encounter.id
	MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
	// Prescription number for display and traceability
	MYSQL_SYNTHESIZE(string, prescriptionNo, PrescriptionNo);

	// =============================
	// Charge Definition Fields
	// =============================
	// Charge item definition ID, references adm_charge_item_definition
	MYSQL_SYNTHESIZE(string, definitionId, DefinitionId);
	// Total price (set to 0.0 initially, updated by pricing engine)
	MYSQL_SYNTHESIZE(double, totalPrice, TotalPrice);
	// Quantity value
	MYSQL_SYNTHESIZE(double, quantityValue, QuantityValue);
	// Quantity unit (measurement unit)
	MYSQL_SYNTHESIZE(string, quantityUnit, QuantityUnit);
	// Unit price (set to 0.0 initially, updated by pricing engine)
	MYSQL_SYNTHESIZE(double, unitPrice, UnitPrice);

	// =============================
	// Business Context Fields
	// =============================
	// Accounting item ID for financial categorization
	MYSQL_SYNTHESIZE(string, accountId, AccountId);
	// Organization ID, references the operating organization
	MYSQL_SYNTHESIZE(string, orgId, OrgId);
	// Condition definition ID, references cln_condition_definition
	MYSQL_SYNTHESIZE(string, conditionId, ConditionId);
	// Encounter diagnosis ID, references adm_encounter_diagnosis
	MYSQL_SYNTHESIZE(string, encounterDiagnosisId, EncounterDiagnosisId);
	// Generate source enum (TCM_ISSUE, MANUAL, etc.)
	MYSQL_SYNTHESIZE(string, generateSourceEnum, GenerateSourceEnum);
	// Context enum (OUTPATIENT, INPATIENT, etc.)
	MYSQL_SYNTHESIZE(string, contextEnum, ContextEnum);

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
	chinapres3ChargeItemDO() : BaseDO("adm_charge_item")
	{
		// Primary Key
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// DML Key Fields
		MYSQL_ADD_FIELD("service_table", "s", serviceTable);
		MYSQL_ADD_FIELD("service_id", "s", serviceId);
		MYSQL_ADD_FIELD("patient_id", "s", patientId);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
		MYSQL_ADD_FIELD("prescription_no", "s", prescriptionNo);

		// Charge Definition Fields (set by Service on insert)
		MYSQL_ADD_FIELD("generate_source_enum", "s", generateSourceEnum);
		MYSQL_ADD_FIELD("context_enum", "s", contextEnum);
		MYSQL_ADD_FIELD("total_price", "d", totalPrice);
		MYSQL_ADD_FIELD("quantity_value", "d", quantityValue);
		MYSQL_ADD_FIELD("unit_price", "d", unitPrice);
		MYSQL_ADD_FIELD("org_id", "s", orgId);
		MYSQL_ADD_FIELD("created_by", "s", createdBy);
		MYSQL_ADD_FIELD("created_at", "s", createdAt);

		// ---- revoke-related DML registration ----
		MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
		MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
		MYSQL_ADD_FIELD("is_deleted", "s", isDeleted);
	}
};

// Shared pointer type alias
typedef std::shared_ptr<chinapres3ChargeItemDO> Ptrchinapres3ChargeItemDO;

#endif // !_chinapres3ChargeItemDO_H_
