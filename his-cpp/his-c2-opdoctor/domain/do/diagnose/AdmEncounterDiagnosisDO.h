#pragma once

#include "domain/do/DoInclude.h"

class AdmEncounterDiagnosisDO : public BaseDO
{
	MYSQL_SYNTHESIZE(std::string, id, Id);
	MYSQL_SYNTHESIZE(std::string, tenantId, TenantId);
	MYSQL_SYNTHESIZE(std::string, createdAt, CreatedAt);
	MYSQL_SYNTHESIZE(std::string, updatedAt, UpdatedAt);
	MYSQL_SYNTHESIZE(std::string, createdBy, CreatedBy);
	MYSQL_SYNTHESIZE(std::string, updatedBy, UpdatedBy);
	MYSQL_SYNTHESIZE(int8_t, isDeleted, IsDeleted);
	MYSQL_SYNTHESIZE(std::string, deletedAt, DeletedAt);
	MYSQL_SYNTHESIZE(std::string, deletedBy, DeletedBy);
	MYSQL_SYNTHESIZE(int, version, Version);
	MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);
	MYSQL_SYNTHESIZE(std::string, conditionId, ConditionId);
	MYSQL_SYNTHESIZE(int8_t, primaryFlag, PrimaryFlag);
	MYSQL_SYNTHESIZE(int, rank, Rank);
	MYSQL_SYNTHESIZE(std::string, description, Description);
	MYSQL_SYNTHESIZE(std::string, diagTypeCode, DiagTypeCode);
	MYSQL_SYNTHESIZE(int, diagCode, DiagCode);
	MYSQL_SYNTHESIZE(int, conditionCode, ConditionCode);
	MYSQL_SYNTHESIZE(std::string, medType, MedType);
	MYSQL_SYNTHESIZE(int8_t, highestDiagFlag, HighestDiagFlag);
	MYSQL_SYNTHESIZE(std::string, tcmSyndromeGroup, TcmSyndromeGroup);
	MYSQL_SYNTHESIZE(int8_t, tcmFlag, TcmFlag);

public:
	AdmEncounterDiagnosisDO() : BaseDO("adm_encounter_diagnosis")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, true);
		MYSQL_ADD_FIELD("created_at", "dt", createdAt);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updatedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "s", createdBy, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updatedBy, true);
		MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
		MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", deletedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deletedBy, true);
		MYSQL_ADD_FIELD("version", "i", version);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
		MYSQL_ADD_FIELD("condition_id", "s", conditionId);
		MYSQL_ADD_FIELD_NULLABLE("primary_flag", "i", primaryFlag, true);
		MYSQL_ADD_FIELD_NULLABLE("rank", "i", rank, true);
		MYSQL_ADD_FIELD_NULLABLE("description", "s", description, true);
		MYSQL_ADD_FIELD_NULLABLE("diag_type_code", "s", diagTypeCode, true);
		MYSQL_ADD_FIELD_NULLABLE("diag_code", "i", diagCode, true);
		MYSQL_ADD_FIELD_NULLABLE("condition_code", "i", conditionCode, true);
		MYSQL_ADD_FIELD_NULLABLE("med_type", "s", medType, true);
		MYSQL_ADD_FIELD_NULLABLE("highest_diag_flag", "i", highestDiagFlag, true);
		MYSQL_ADD_FIELD_NULLABLE("tcm_syndrome_group", "s", tcmSyndromeGroup, true);
		MYSQL_ADD_FIELD_NULLABLE("tcm_flag", "i", tcmFlag, true);
	}
};

using PtrAdmEncounterDiagnosisDO = std::shared_ptr<AdmEncounterDiagnosisDO>;