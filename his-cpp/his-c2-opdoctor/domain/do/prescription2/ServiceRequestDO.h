#pragma once

#ifndef _SERVICEREQUESTDO_H_
#define _SERVICEREQUESTDO_H_

#include "../DoInclude.h"

class ServiceRequestDO : public BaseDO
{
    // 服务申请单标识
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // 就诊标识
    MYSQL_SYNTHESIZE(std::string, encounterId, EncounterId);
    // 乐观锁版本号
    MYSQL_SYNTHESIZE(int, version, Version);
    // 服务申请单状态
    MYSQL_SYNTHESIZE(std::string, statusEnum, StatusEnum);
    // 服务申请单类别
    MYSQL_SYNTHESIZE(std::string, categoryEnum, CategoryEnum);
    // 已完成打印次数
    MYSQL_SYNTHESIZE(int, printCount, PrintCount);

    MYSQL_SYNTHESIZE(std::string, updatedBy, UpdatedBy);
    // 最后更新时间
    MYSQL_SYNTHESIZE(std::string, updatedAt, UpdatedAt);

public:
    // 将字段绑定到 wkf_service_request 表
    ServiceRequestDO() : BaseDO("wkf_service_request")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("category_enum", "s", categoryEnum);
        MYSQL_ADD_FIELD("print_count", "i", printCount);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
    }
};

typedef std::shared_ptr<ServiceRequestDO> PtrServiceRequestDO;

#endif // !_SERVICEREQUESTDO_H_
