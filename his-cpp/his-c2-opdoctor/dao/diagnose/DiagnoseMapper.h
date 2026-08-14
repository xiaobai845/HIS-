#pragma once

#include "Mapper.h"

class DiagnoseMapper : public Mapper<PtrAdmEncounterDiagnosisDO>
{
public:
	PtrAdmEncounterDiagnosisDO mapper(ResultSet* resultSet) const override
	{
		PtrAdmEncounterDiagnosisDO ptrDiagnoseDo =
			std::make_shared<AdmEncounterDiagnosisDO>();

		ptrDiagnoseDo->setId(resultSet->getString("id"));
		ptrDiagnoseDo->setTenantId(resultSet->getString("tenant_id"));
		ptrDiagnoseDo->setCreatedAt(resultSet->getString("created_at"));
		ptrDiagnoseDo->setUpdatedAt(resultSet->getString("updated_at"));
		ptrDiagnoseDo->setCreatedBy(resultSet->getString("created_by"));
		ptrDiagnoseDo->setUpdatedBy(resultSet->getString("updated_by"));
		ptrDiagnoseDo->setIsDeleted(resultSet->getInt("is_deleted"));
		ptrDiagnoseDo->setDeletedAt(resultSet->getString("deleted_at"));
		ptrDiagnoseDo->setDeletedBy(resultSet->getString("deleted_by"));
		ptrDiagnoseDo->setVersion(resultSet->getInt("version"));
		ptrDiagnoseDo->setEncounterId(resultSet->getString("encounter_id"));
		ptrDiagnoseDo->setConditionId(resultSet->getString("condition_id"));
		ptrDiagnoseDo->setPrimaryFlag(resultSet->getInt("primary_flag"));
		ptrDiagnoseDo->setRank(resultSet->getInt("rank"));
		ptrDiagnoseDo->setDescription(resultSet->getString("description"));
		ptrDiagnoseDo->setDiagTypeCode(resultSet->getString("diag_type_code"));
		ptrDiagnoseDo->setDiagCode(resultSet->getInt("diag_code"));
		ptrDiagnoseDo->setConditionCode(resultSet->getInt("condition_code"));
		ptrDiagnoseDo->setMedType(resultSet->getString("med_type"));
		ptrDiagnoseDo->setHighestDiagFlag(resultSet->getInt("highest_diag_flag"));
		ptrDiagnoseDo->setTcmSyndromeGroup(resultSet->getString("tcm_syndrome_group"));
		ptrDiagnoseDo->setTcmFlag(resultSet->getInt("tcm_flag"));

		return ptrDiagnoseDo;
	}
};