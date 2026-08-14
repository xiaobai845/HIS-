#pragma once

#include "domain/do/DoInclude.h"

class ClnConditionDO : public BaseDO
{
	MYSQL_SYNTHESIZE(std::string, id, Id);
	MYSQL_SYNTHESIZE(std::string, tenantId, TenantId);
	MYSQL_SYNTHESIZE(std::string, createAt, CreateAt);
	MYSQL_SYNTHESIZE(std::string, updateAt, UpdateAt);
	MYSQL_SYNTHESIZE(std::string, createBy, CreateBy);
	MYSQL_SYNTHESIZE(std::string, updateBy, UpdateBy);
	MYSQL_SYNTHESIZE(int8_t, isDeleted, IsDeleted);
	MYSQL_SYNTHESIZE(std::string, deletedAt, DeletedAt);
	MYSQL_SYNTHESIZE(std::string, deletedBy, DeletedBy);
	MYSQL_SYNTHESIZE(int, version, Version);
	MYSQL_SYNTHESIZE(std::string, verificationStatusEnum, VerificationStatusEnum);
	MYSQL_SYNTHESIZE(std::string, clinicalStatusEnum, ClinicalStatusEnum);
	MYSQL_SYNTHESIZE(std::string, categoryEnum, CategoryEnum);
	MYSQL_SYNTHESIZE(std::string, severityEnum, SeverityEnum);
	MYSQL_SYNTHESIZE(std::string, busNo, BusNo);
	MYSQL_SYNTHESIZE(std::string, bodySiteJson, BodySiteJson);
	MYSQL_SYNTHESIZE(std::string, bodyStructureId, BodyStructureId);
	MYSQL_SYNTHESIZE(std::string, patientId, PatientId);
	MYSQL_SYNTHESIZE(std::string, description, Description);
	MYSQL_SYNTHESIZE(string, onsetDatetime, OnsetDatetime);
	MYSQL_SYNTHESIZE(int, onsetAge, OnsetAge);
	MYSQL_SYNTHESIZE(std::string, onsetText, OnsetText);
	MYSQL_SYNTHESIZE(std::string, abatementDatetime, AbatementDatetime);
	MYSQL_SYNTHESIZE(int, abatementAge, AbatementAge);
	MYSQL_SYNTHESIZE(std::string, abatementString, AbatementString);
	MYSQL_SYNTHESIZE(std::string, recordedDatetime, RecordedDatetime);
	MYSQL_SYNTHESIZE(std::string, recorderId, RecorderId);
	MYSQL_SYNTHESIZE(std::string, stageSummaryText, StageSummaryText);
	MYSQL_SYNTHESIZE(std::string, evidence, Evidence);
	MYSQL_SYNTHESIZE(std::string, ybNo, YbNo);
	MYSQL_SYNTHESIZE(std::string, definitionId, DefinitionId);
	MYSQL_SYNTHESIZE(int8_t, tcmFlag, TcmFlag);
	MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);

public:
	ClnConditionDO() : BaseDO("cln_condition")
	{
		MYSQL_ADD_FIELD_PK("id", "s", Id);
		MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", TenantId, true);
		MYSQL_ADD_FIELD("created_at", "dt", CreateAt);
		MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", UpdateAt, true);
		MYSQL_ADD_FIELD_NULLABLE("created_by", "s", CreateBy, true);
		MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", UpdateBy, true);
		MYSQL_ADD_FIELD("is_deleted", "i", IsDeleted);
		MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", DeletedAt, true);
		MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", DeletedBy, true);
		MYSQL_ADD_FIELD("version", "i", Version);
		MYSQL_ADD_FIELD_NULLABLE("verification_status_enum", "s", VerificationStatusEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("clinical_status_enum", "s", ClinicalStatusEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("category_enum", "s", CategoryEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("severity_enum", "s", SeverityEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", BusNo, true);
		MYSQL_ADD_FIELD_NULLABLE("body_site_json", "s", BodySiteJson, true);
		MYSQL_ADD_FIELD_NULLABLE("body_structure_id", "s", BodyStructureId, true);
		MYSQL_ADD_FIELD("patient_id", "s", ParentId);
		MYSQL_ADD_FIELD_NULLABLE("description", "s", Description, true);
		MYSQL_ADD_FIELD_NULLABLE("onset_datetime", "dt", OnsetDatetime, true);
		MYSQL_ADD_FIELD_NULLABLE("onset_age", "i", OnsetAge, true);
		MYSQL_ADD_FIELD_NULLABLE("onset_text", "s", OnsetText, true);
		MYSQL_ADD_FIELD_NULLABLE("abatement_datetime", "dt", AbatementDatetime, true);
		MYSQL_ADD_FIELD_NULLABLE("abatement_age", "i", AbatementAge, true);
		MYSQL_ADD_FIELD_NULLABLE("abatement_string", "s", AbatementString, true);
		MYSQL_ADD_FIELD_NULLABLE("recorded_datetime", "dt", RecordedDatetime, true);
		MYSQL_ADD_FIELD_NULLABLE("recorder_id", "s", RecordedId, true);
		MYSQL_ADD_FIELD_NULLABLE("stage_summary_text", "s", StageSummaryText, true);
		MYSQL_ADD_FIELD_NULLABLE("evidence", "s", Evidence, true);
		MYSQL_ADD_FIELD_NULLABLE("yb_no", "s", YbNo, true);
		MYSQL_ADD_FIELD_NULLABLE("definition_id", "s", DefinitionId, true);
		MYSQL_ADD_FIELD_NULLABLE("tcm_flag", "i", TcmFlag, true);
		MYSQL_ADD_FIELD_NULLABLE("encounter_id", "s", EncounterId, true);
	}
};

using PtrClnConditionDO = std::shared_ptr<ClnConditionDO>;