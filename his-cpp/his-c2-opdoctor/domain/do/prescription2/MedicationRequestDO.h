#pragma once

#ifndef _MEDICATIONREQUESTDO_H_
#define _MEDICATIONREQUESTDO_H_

#include "../DoInclude.h"

class MedicationRequestDO : public BaseDO
{
    // 医嘱标识
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // 就诊标识
    MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);
    // 乐观锁版本号
    MYSQL_SYNTHESIZE(int, version, Version);
    // 医嘱组标识
    MYSQL_SYNTHESIZE(std::string, groupId, GroupId);
    // 医嘱状态
    MYSQL_SYNTHESIZE(std::string, statusEnum, StatusEnum);
    // 已完成执行次数
    MYSQL_SYNTHESIZE(int, executeNum, ExecuteNum);
    // 状态变更时间
    MYSQL_SYNTHESIZE(std::string, statusChangedTime, StatusChangedTime);
    // 签发医生标识
    MYSQL_SYNTHESIZE(std::string, performerCheckId, PerformerCheckId);
    // 签发时间
    MYSQL_SYNTHESIZE(std::string, checkTime, CheckTime);

    MYSQL_SYNTHESIZE(std::string, updatedBy, UpdatedBy);
    // 最后更新时间
    MYSQL_SYNTHESIZE(std::string, updatedAt, UpdatedAt);

public:
    // 将字段绑定到 med_medication_request 表
    MedicationRequestDO() : BaseDO("med_medication_request")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("group_id", "s", groupId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("execute_num", "i", executeNum);
        MYSQL_ADD_FIELD("status_changed_time", "s", statusChangedTime);
        MYSQL_ADD_FIELD("performer_check_id", "s", performerCheckId);
        MYSQL_ADD_FIELD("check_time", "s", checkTime);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
    }
};

typedef std::shared_ptr<MedicationRequestDO> PtrMedicationRequestDO;

#endif // !_MEDICATIONREQUESTDO_H_
