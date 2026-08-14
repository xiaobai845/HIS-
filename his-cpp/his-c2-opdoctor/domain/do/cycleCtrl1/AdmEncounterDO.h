#pragma once
#ifndef _ADMENCOUNTERDO_H_
#define _ADMENCOUNTERDO_H_
#include "../DoInclude.h"


class AdmEncounterDO : public BaseDO
{
public:
    //唯一标识
    MYSQL_SYNTHESIZE(string, id, Id);
    //租户ID
    MYSQL_SYNTHESIZE(string, tenant_id, TenantId);
    //患者ID
    MYSQL_SYNTHESIZE(string, patient_id, PatientId);
    //就诊流水号（病历号）
    MYSQL_SYNTHESIZE(string, bus_no, BusNo);
    //就诊状态枚举
    MYSQL_SYNTHESIZE(string, status_enum, StatusEnum);
    //接诊时间
    MYSQL_SYNTHESIZE(int64_t, reception_time, ReceptionTime);
    //就诊开始时间
    MYSQL_SYNTHESIZE(int64_t, start_time, StartTime);
    //就诊结束时间
    MYSQL_SYNTHESIZE(int64_t, end_time, EndTime);
    //医疗服务ID（普通号/专家号）
    MYSQL_SYNTHESIZE(string, service_type_id, ServiceTypeId);

    //通用审计字段
    MYSQL_SYNTHESIZE(string, created_by, CreatedBy);
    MYSQL_SYNTHESIZE(int64_t, created_at, CreatedAt);
    MYSQL_SYNTHESIZE(string, updated_by, UpdatedBy);
    MYSQL_SYNTHESIZE(int64_t, updated_at, UpdatedAt);
    MYSQL_SYNTHESIZE(bool, is_deleted, IsDeleted);
    MYSQL_SYNTHESIZE(int64_t, deleted_at, DeletedAt);
    MYSQL_SYNTHESIZE(string, deleted_by, DeletedBy);
    MYSQL_SYNTHESIZE(int, version, Version);

public:
    AdmEncounterDO() : BaseDO("adm_encounter")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenant_id, false);
        MYSQL_ADD_FIELD_NULLABLE("patient_id", "s", patient_id, false);
        MYSQL_ADD_FIELD_NULLABLE("bus_no", "s", bus_no, false);
        MYSQL_ADD_FIELD_NULLABLE("status_enum", "s", status_enum, false);
        MYSQL_ADD_FIELD_NULLABLE("reception_time", "ll", reception_time, false);
        MYSQL_ADD_FIELD_NULLABLE("start_time", "ll", start_time, true);
        MYSQL_ADD_FIELD_NULLABLE("end_time", "ll", end_time, true);
        MYSQL_ADD_FIELD_NULLABLE("service_type_id", "s", service_type_id, true);

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
typedef std::shared_ptr<AdmEncounterDO> PtrAdmEncounterDO;
#endif