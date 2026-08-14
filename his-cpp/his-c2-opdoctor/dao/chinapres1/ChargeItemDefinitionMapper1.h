#pragma once
#ifndef _CHARGEITEMDEFINITIONMAPPER1_H_
#define _CHARGEITEMDEFINITIONMAPPER1_H_

#include "Mapper.h"
#include "domain/do/chinapres1/ChargeItemDefinitionDO1.h"

class ChargeItemDefinitionMapper1 : public Mapper<PtrChargeItemDefinitionDO>
{
public:
	PtrChargeItemDefinitionDO mapper(ResultSet* resultSet) const override
	{
		PtrChargeItemDefinitionDO chargeDO = std::make_shared<ChargeItemDefinitionDO1>();
		// 通用字段
		chargeDO->setId(resultSet->getString("id"));
		chargeDO->setTenantId(resultSet->getString("tenant_id"));
		chargeDO->setCreatedAt(resultSet->getString("created_at"));
		chargeDO->setUpdatedAt(resultSet->getString("updated_at"));
		chargeDO->setCreatedBy(resultSet->getString("created_by"));
		chargeDO->setUpdatedBy(resultSet->getString("updated_by"));
		chargeDO->setIsDeleted(resultSet->getInt("is_deleted"));
		chargeDO->setVersion(resultSet->getInt("version"));
		// 业务实例关联
		chargeDO->setInstanceTable(resultSet->getString("instance_table"));
		chargeDO->setInstanceId(resultSet->getString("instance_id"));
		// 收费展示与状态
		chargeDO->setChargeName(resultSet->getString("charge_name"));
		chargeDO->setStatusEnum(resultSet->getString("status_enum"));
		chargeDO->setOrgId(resultSet->getString("org_id"));
		// 价格核心
		chargeDO->setTypeCode(resultSet->getString("type_code"));
		chargeDO->setPriceTypeCode(resultSet->getString("price_type_code"));
		chargeDO->setPriceValue(resultSet->getDouble("price_value"));
		chargeDO->setLotNo(resultSet->getString("lot_no"));
		chargeDO->setPriority(resultSet->getInt("priority"));
		// 医保
		chargeDO->setYbType(resultSet->getString("yb_type"));

		return chargeDO;
	}
};

#endif // !_CHARGEITEMDEFINITIONMAPPER1_H_