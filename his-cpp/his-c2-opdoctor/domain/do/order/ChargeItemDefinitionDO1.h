#pragma once
#ifndef _CHARGE_ITEM_DEFINITION_DO_1_H_
#define _CHARGE_ITEM_DEFINITION_DO_1_H_

#include "../DoInclude.h"

/**
 * 收费项目定义实体类
 * 对应表: adm_charge_item_definition
 */
class ChargeItemDefinitionDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);

    MYSQL_SYNTHESIZE(string, instanceTable, InstanceTable);
    MYSQL_SYNTHESIZE(string, instanceId, InstanceId);
    MYSQL_SYNTHESIZE(string, chargeName, ChargeName);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(string, typeCode, TypeCode);
    MYSQL_SYNTHESIZE(string, ybType, YbType);
    MYSQL_SYNTHESIZE(string, priceTypeCode, PriceTypeCode);
    MYSQL_SYNTHESIZE(string, lotNo, LotNo);
    MYSQL_SYNTHESIZE(double, priceValue, PriceValue);
    MYSQL_SYNTHESIZE(int, priority, Priority);

public:
    ChargeItemDefinitionDO1() : BaseDO("adm_charge_item_definition")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("instance_table", "s", instanceTable);
        MYSQL_ADD_FIELD("instance_id", "s", instanceId);
        MYSQL_ADD_FIELD("charge_name", "s", chargeName);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("type_code", "s", typeCode);
        MYSQL_ADD_FIELD("yb_type", "s", ybType);
        MYSQL_ADD_FIELD("price_type_code", "s", priceTypeCode);
        MYSQL_ADD_FIELD("lot_no", "s", lotNo);
        MYSQL_ADD_FIELD("price_value", "d", priceValue);
        MYSQL_ADD_FIELD("priority", "i", priority);
    }
};

typedef std::shared_ptr<ChargeItemDefinitionDO1> PtrChargeItemDefinitionDO1;

#endif // !_CHARGE_ITEM_DEFINITION_DO_1_H_