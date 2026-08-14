#pragma once
#ifndef _CHARGEITEMDEFINITIONDO1_H_
#define _CHARGEITEMDEFINITIONDO1_H_

#include "../DoInclude.h"

class ChargeItemDefinitionDO1: public BaseDO
{
    // 通用字段
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(bool, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);
    // 业务实例关联（用这个字段关联到药品/项目）
    MYSQL_SYNTHESIZE(string, instanceTable, InstanceTable);     // 业务实例表名（
    MYSQL_SYNTHESIZE(string, instanceId, InstanceId);         // 业务实例主键（如药品ID）-> 用这个查价格
    // 收费展示与状态
    MYSQL_SYNTHESIZE(string, chargeName, ChargeName);           // 收费展示名称
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);           // 状态枚举（默认 ACTIVE）
    MYSQL_SYNTHESIZE(string, orgId, OrgId);                     // 所属机构（空=全局）
    // 价格核心字段（页面上的"?0.15/g"）
    MYSQL_SYNTHESIZE(string, typeCode, TypeCode);               // 收费类型编码
    MYSQL_SYNTHESIZE(string, priceTypeCode, PriceTypeCode);     // 价格类型编码
    MYSQL_SYNTHESIZE(double, priceValue, PriceValue);           // 价格数值（元）-> 核心！
    MYSQL_SYNTHESIZE(string, lotNo, LotNo);                     // 批次号
    MYSQL_SYNTHESIZE(int, priority, Priority);                   // 优先级（同实例多价时）
    // 医保相关
    MYSQL_SYNTHESIZE(string, ybType, YbType);                   // 医保类别

public:
    ChargeItemDefinitionDO1() : BaseDO("adm_charge_item_definition")
    {
        // 通用
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, false);
        MYSQL_ADD_FIELD("created_at", "dt", createdAt);
        MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updatedAt, false);
        MYSQL_ADD_FIELD_NULLABLE("created_by", "s", createdBy, false);
        MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updatedBy, false);
        MYSQL_ADD_FIELD("is_deleted", "b", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        // 业务实例关联
        MYSQL_ADD_FIELD_NULLABLE("instance_table", "s", instanceTable, false);
        MYSQL_ADD_FIELD("instance_id", "s", instanceId);
        // 收费展示
        MYSQL_ADD_FIELD_NULLABLE("charge_name", "s", chargeName, false);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD_NULLABLE("org_id", "s", orgId, false);
        // 价格核心
        MYSQL_ADD_FIELD("type_code", "s", typeCode);
        MYSQL_ADD_FIELD("price_type_code", "s", priceTypeCode);
        MYSQL_ADD_FIELD("price_value", "d", priceValue);
        MYSQL_ADD_FIELD_NULLABLE("lot_no", "s", lotNo, false);
        MYSQL_ADD_FIELD_NULLABLE("priority", "i", priority, false);
        // 医保
        MYSQL_ADD_FIELD_NULLABLE("yb_type", "s", ybType, false);
    }
};

typedef std::shared_ptr<ChargeItemDefinitionDO1> PtrChargeItemDefinitionDO;

#endif // !_CHARGEITEMDEFINITIONDO1_H_