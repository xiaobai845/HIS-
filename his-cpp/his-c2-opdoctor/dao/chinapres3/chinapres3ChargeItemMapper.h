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
#ifndef _chinapres3ChargeItemMapper_H_
#define _chinapres3ChargeItemMapper_H_

#include "Mapper.h"
#include "../../domain/do/chinapres3/chinapres3ChargeItemDO.h"

/**
 * Charge Item Mapper
 *
 * Maps database ResultSet to chinapres3ChargeItemDO objects.
 * Corresponds to database table: adm_charge_item
 */
class chinapres3ChargeItemMapper : public Mapper<Ptrchinapres3ChargeItemDO>
{
public:
	Ptrchinapres3ChargeItemDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<chinapres3ChargeItemDO>();
		// Primary Key
		data->setId(resultSet->getString("id"));
		// DML Business Key Fields
		data->setServiceTable(resultSet->getString("service_table"));
		data->setServiceId(resultSet->getString("service_id"));
		data->setPatientId(resultSet->getString("patient_id"));
		data->setEncounterId(resultSet->getString("encounter_id"));
		data->setPrescriptionNo(resultSet->getString("prescription_no"));
		// Charge Definition Fields
		data->setDefinitionId(resultSet->getString("definition_id"));
		data->setTotalPrice(resultSet->getDouble("total_price"));
		data->setQuantityValue(resultSet->getDouble("quantity_value"));
		data->setQuantityUnit(resultSet->getString("quantity_unit"));
		data->setUnitPrice(resultSet->getDouble("unit_price"));
		data->setAccountId(resultSet->getString("account_id"));
		data->setOrgId(resultSet->getString("org_id"));
		data->setConditionId(resultSet->getString("condition_id"));
		data->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));
		data->setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
		data->setContextEnum(resultSet->getString("context_enum"));
		// Audit Fields
		data->setCreatedBy(resultSet->getString("created_by"));
		data->setCreatedAt(resultSet->getString("created_at"));
		data->setUpdatedBy(resultSet->getString("updated_by"));
		data->setUpdatedAt(resultSet->getString("updated_at"));
		// ---- revoke-related mapping ----
		data->setIsDeleted(resultSet->getString("is_deleted"));
		return data;
	}
};

#endif // !_chinapres3ChargeItemMapper_H_
