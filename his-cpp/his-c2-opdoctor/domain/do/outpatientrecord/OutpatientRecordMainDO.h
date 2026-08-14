#pragma once
#ifndef _OUTPATIENTRECORD_MAIN_DO_
#define _OUTPATIENTRECORD_MAIN_DO_

#include "../DoInclude.h"

/**
 * 就诊主表 DO (对应表 adm_encounter)
 * 只包含分页查询需要用到的字段
 */
class OutpatientRecordMainDO : public BaseDO
{
    // 就诊主键
    MYSQL_SYNTHESIZE(string, id, Id);
    // 患者ID
    MYSQL_SYNTHESIZE(string, patientId, PatientId);
    // 科室ID (organization_id)
    MYSQL_SYNTHESIZE(string, organizationId, OrganizationId);
    // 就诊开始时间 (start_time)
    MYSQL_SYNTHESIZE(string, startTime, StartTime);
    // 创建时间
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    // 就诊状态 (status_enum)
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    // 就诊类别 (class_enum, 如 AMB/IMP)
    MYSQL_SYNTHESIZE(string, classEnum, ClassEnum);
    // 业务编号
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    // 软删标记 (is_deleted)
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);

public:
    OutpatientRecordMainDO() : BaseDO("adm_encounter")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("patient_id", "s", patientId);
        MYSQL_ADD_FIELD("organization_id", "s", organizationId);
        MYSQL_ADD_FIELD("start_time", "s", startTime);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("class_enum", "s", classEnum);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
    }
};

typedef std::shared_ptr<OutpatientRecordMainDO> PtrOutpatientRecordMainDO;

#endif // !_OUTPATIENTRECORD_MAIN_DO_