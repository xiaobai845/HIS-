#pragma once
#ifndef _ADMPATIENTDO_H_
#define _ADMPATIENTDO_H_
#include "../DoInclude.h"

class AdmPatientDO : public BaseDO
{
public:
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenant_id, TenantId);
    //患者姓名
    MYSQL_SYNTHESIZE(string, name, Name);
    //性别编码
    MYSQL_SYNTHESIZE(string, gender_enum, GenderEnum);
    //出生日期
    MYSQL_SYNTHESIZE(string, birth_date, BirthDate);
    //联系电话
    MYSQL_SYNTHESIZE(string, phone, Phone);

    MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
    MYSQL_SYNTHESIZE(int64_t, created_at, CreatedAt);
    MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
    MYSQL_SYNTHESIZE(int64_t, updated_at, UpdatedAt);
    MYSQL_SYNTHESIZE(bool, is_deleted, IsDeleted);
    MYSQL_SYNTHESIZE(int64_t, deleted_at, DeletedAt);
    MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
    MYSQL_SYNTHESIZE(int, version, Version);

public:
    AdmPatientDO() : BaseDO("adm_patient")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenant_id, false);
        MYSQL_ADD_FIELD_NULLABLE("name", "s", name, false);
        MYSQL_ADD_FIELD_NULLABLE("gender_enum", "s", gender_enum, true);
        MYSQL_ADD_FIELD_NULLABLE("birth_date", "s", birth_date, true);
        MYSQL_ADD_FIELD_NULLABLE("phone", "s", phone, true);

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
typedef std::shared_ptr<AdmPatientDO> PtrAdmPatientDO;
#endif