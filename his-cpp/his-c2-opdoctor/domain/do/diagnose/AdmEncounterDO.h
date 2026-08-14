#pragma once

#include "domain/do/DoInclude.h"

class AdmEncounterDO : public BaseDO
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
	MYSQL_SYNTHESIZE(std::string, patientId, PatientId);
	MYSQL_SYNTHESIZE(std::string, groupId, GroupId);
	MYSQL_SYNTHESIZE(std::string, busNo, BusNo);
	MYSQL_SYNTHESIZE(std::string, statusEnum, StatusEnum);
	MYSQL_SYNTHESIZE(std::string, classEnum, ClassEnum);
	MYSQL_SYNTHESIZE(std::string, ybClassEnum, YbClassEnum);
	MYSQL_SYNTHESIZE(std::string, ybClassText, YbClassText);
	MYSQL_SYNTHESIZE(std::string, classJson, ClassJson);
	MYSQL_SYNTHESIZE(std::string, priorityEnum, PriorityEnum);
	MYSQL_SYNTHESIZE(std::string, typeEnum, TypeEnum);
	MYSQL_SYNTHESIZE(std::string, serviceTypeId, ServiceTypeId);
	MYSQL_SYNTHESIZE(std::string, subjectStatusEnum, SubjectStatusEnum);
	MYSQL_SYNTHESIZE(std::string, startTime, StartTime);
	MYSQL_SYNTHESIZE(std::string, endTime, EndTime);
	MYSQL_SYNTHESIZE(std::string, organizationId, OrganizationId);
	MYSQL_SYNTHESIZE(int, displayOrder, DisplayOrder);
	MYSQL_SYNTHESIZE(std::string, firstEnum, FirstEnum);
	MYSQL_SYNTHESIZE(std::string, admitSourceCode, AdmitSourceCode);
	MYSQL_SYNTHESIZE(std::string, inWayCode, InWayCode);
	MYSQL_SYNTHESIZE(std::string, receptionTime, ReceptionTime);
	MYSQL_SYNTHESIZE(std::string, registrarId, RegistrarId);
	MYSQL_SYNTHESIZE(std::string, ambEncounterId, AmbEncounterId);
	MYSQL_SYNTHESIZE(std::string, outWayCode, OutWayCode);

public:
	AdmEncounterDO() : BaseDO("adm_encounter")
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
		MYSQL_ADD_FIELD("patient_id", "s", patientId);
		MYSQL_ADD_FIELD_NULLABLE("group_id", "s", groupId, true);
		MYSQL_ADD_FIELD("bus_no", "s", busNo);
		MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
		MYSQL_ADD_FIELD("class_enum", "s", classEnum);
		MYSQL_ADD_FIELD_NULLABLE("yb_class_enum", "s", ybClassEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("yb_class_text", "s", ybClassText, true);
		MYSQL_ADD_FIELD_NULLABLE("class_json", "s", classJson, true);
		MYSQL_ADD_FIELD_NULLABLE("priority_enum", "s", priorityEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("type_enum", "s", typeEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("service_type_id", "s", serviceTypeId, true);
		MYSQL_ADD_FIELD_NULLABLE("subject_status_enum", "s", subjectStatusEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("start_time", "dt", startTime, true);
		MYSQL_ADD_FIELD_NULLABLE("end_time", "dt", endTime, true);
		MYSQL_ADD_FIELD("organization_id", "s", organizationId);
		MYSQL_ADD_FIELD_NULLABLE("display_order", "i", displayOrder, true);
		MYSQL_ADD_FIELD_NULLABLE("first_enum", "s", firstEnum, true);
		MYSQL_ADD_FIELD_NULLABLE("admit_source_code", "s", admitSourceCode, true);
		MYSQL_ADD_FIELD_NULLABLE("in_way_code", "s", inWayCode, true);
		MYSQL_ADD_FIELD_NULLABLE("reception_time", "dt", receptionTime, true);
		MYSQL_ADD_FIELD_NULLABLE("registrar_id", "s", registrarId, true);
		MYSQL_ADD_FIELD_NULLABLE("amb_encounter_id", "s", ambEncounterId, true);
		MYSQL_ADD_FIELD_NULLABLE("out_way_code", "s", outWayCode, true);
	}
};

using PtrAdmEncounterDO = std::shared_ptr<AdmEncounterDO>;