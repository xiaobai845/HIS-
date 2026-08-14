#pragma once
#ifndef _CHARGE_ITEM_DEFINITION_MAPPER_1_H_
#define _CHARGE_ITEM_DEFINITION_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/ChargeItemDefinitionDO1.h"

/**
 * 收费项目定义表字段匹配映射
 */
class ChargeItemDefinitionMapper1 : public Mapper<ChargeItemDefinitionDO1>
{
public:
    ChargeItemDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        ChargeItemDefinitionDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setInstanceTable(resultSet->getString("instance_table"));
        data.setInstanceId(resultSet->getString("instance_id"));
        data.setChargeName(resultSet->getString("charge_name"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setTypeCode(resultSet->getString("type_code"));
        data.setYbType(resultSet->getString("yb_type"));
        data.setPriceTypeCode(resultSet->getString("price_type_code"));
        data.setLotNo(resultSet->getString("lot_no"));
        data.setPriceValue(resultSet->getDouble("price_value"));
        data.setPriority(resultSet->getInt("priority"));
        return data;
    }
};

#endif // !_CHARGE_ITEM_DEFINITION_MAPPER_1_H_