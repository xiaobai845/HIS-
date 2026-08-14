#pragma once
#ifndef _ADMACCOUNTDO_H_
#define _ADMACCOUNTDO_H_
#include "../DoInclude.h"

class AdmAccountDO : public BaseDO
{
public:
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenant_id, TenantId);
    MYSQL_SYNTHESIZE(string, encounter_id, EncounterId);
    //费用类型编码
    MYSQL_SYNTHESIZE(string, type_code, TypeCode);
    //是否为主账户
    MYSQL_SYNTHESIZE(bool, default_flag, DefaultFlag);

    MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
    MYSQL_SYNTHESIZE(int64_t, created_at, CreatedAt);
    MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
    MYSQL_SYNTHESIZE(int64_t, updated_at, UpdatedAt);
    MYSQL_SYNTHESIZE(bool, is_deleted, IsDeleted);
    MYSQL_SYNTHESIZE(int64_t, deleted_at, DeletedAt);
    MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
    MYSQL_SYNTHESIZE(int, version, Version);

public:
    AdmAccountDO() : BaseDO("adm_account")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenant_id, false);
        MYSQL_ADD_FIELD_NULLABLE("encounter_id", "s", encounter_id, false);
        MYSQL_ADD_FIELD_NULLABLE("type_code", "s", type_code, false);
        MYSQL_ADD_FIELD_NULLABLE("default_flag", "b", default_flag, false);

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
typedef std::shared_ptr<AdmAccountDO> PtrAdmAccountDO;
#endif