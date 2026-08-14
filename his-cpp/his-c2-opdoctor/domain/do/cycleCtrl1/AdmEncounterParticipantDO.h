#pragma once
#ifndef _ADMENCOUNTERPARTICIPANTDO_H_
#define _ADMENCOUNTERPARTICIPANTDO_H_
#include "../DoInclude.h"

class AdmEncounterParticipantDO : public BaseDO
{
public:
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenant_id, TenantId);
    MYSQL_SYNTHESIZE(string, encounter_id, EncounterId);
    //医生ID
    MYSQL_SYNTHESIZE(string, practitioner_id, PractitionerId);
    //参与者角色
    MYSQL_SYNTHESIZE(string, role_enum, RoleEnum);

    MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
    MYSQL_SYNTHESIZE(int64_t, created_at, CreatedAt);
    MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
    MYSQL_SYNTHESIZE(int64_t, updated_at, UpdatedAt);
    MYSQL_SYNTHESIZE(bool, is_deleted, IsDeleted);
    MYSQL_SYNTHESIZE(int64_t, deleted_at, DeletedAt);
    MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
    MYSQL_SYNTHESIZE(int, version, Version);

public:
    AdmEncounterParticipantDO() : BaseDO("adm_encounter_participant")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenant_id, false);
        MYSQL_ADD_FIELD_NULLABLE("encounter_id", "s", encounter_id, false);
        MYSQL_ADD_FIELD_NULLABLE("practitioner_id", "s", practitioner_id, false);
        MYSQL_ADD_FIELD_NULLABLE("role_enum", "s", role_enum, false);

        MYSQL_ADD_FIELD_NULLABLE("created_by", "s", created_by, true);
        MYSQL_ADD_FIELD_NULLABLE("created_at", "ll", created_at, true);
        MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updated_by, true);
        MYSQL_ADD_FIELD_NULLABLE("updated_at", "ll", updated_at, true);
        MYSQL_ADD_FIELD_NULLABLE("is_deleted", "b", is_deleted, false);
        MYSQL_ADD_FIELD_NULLABLE("deleted_at", "ll", deleted_at, true);
        MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deleted_by, true);
        MYSQL_ADD_FIELD_NULLABLE("version", "i", version, false);
    }
};
typedef std::shared_ptr<AdmEncounterParticipantDO> PtrAdmEncounterParticipantDO;
#endif