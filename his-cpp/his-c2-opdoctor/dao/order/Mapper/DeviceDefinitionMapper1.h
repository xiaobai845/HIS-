#pragma once
#ifndef _DEVICE_DEFINITION_MAPPER_1_H_
#define _DEVICE_DEFINITION_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/DeviceDefinitionDO1.h"

/**
 * 耗材定义表字段匹配映射
 */
class DeviceDefinitionMapper1 : public Mapper<DeviceDefinitionDO1>
{
public:
    DeviceDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        DeviceDefinitionDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setName(resultSet->getString("name"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setPyStr(resultSet->getString("py_str"));
        data.setWbStr(resultSet->getString("wb_str"));
        data.setCategoryCode(resultSet->getString("category_code"));
        data.setTypeCode(resultSet->getString("type_code"));
        data.setPurchaseUnitCode(resultSet->getString("purchase_unit_code"));
        data.setTotalVolume(resultSet->getString("total_volume"));
        data.setItemMinQuantity(resultSet->getDouble("item_min_quantity"));
        data.setItemMaxQuantity(resultSet->getDouble("item_max_quantity"));
        data.setSplitUnitCode(resultSet->getString("split_unit_code"));
        data.setMerchandiseName(resultSet->getString("merchandise_name"));
        data.setMerchandisePyStr(resultSet->getString("merchandise_py_str"));
        data.setMerchandiseWbStr(resultSet->getString("merchandise_wb_str"));
        data.setDefEncounterUnitCode(resultSet->getString("def_encounter_unit_code"));
        data.setDefInhospitalUnitCode(resultSet->getString("def_inhospital_unit_code"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setLocationId(resultSet->getString("location_id"));
        data.setModelNumber(resultSet->getString("model_number"));
        data.setHvcmFlag(resultSet->getInt("hvcm_flag"));
        data.setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data.setPackageUnitCode(resultSet->getString("package_unit_code"));
        data.setStockUnitCode(resultSet->getString("stock_unit_code"));
        data.setApprovalNumber(resultSet->getString("approval_number"));
        data.setManufacturerId(resultSet->getString("manufacturer_id"));
        data.setManufacturerText(resultSet->getString("manufacturer_text"));
        data.setSupplyId(resultSet->getString("supply_id"));
        data.setDescription(resultSet->getString("description"));
        data.setJurisdiction(resultSet->getString("jurisdiction"));
        data.setDeviceVersion(resultSet->getString("device_version"));
        data.setSubstanceText(resultSet->getString("substance_text"));
        data.setAllergenFlag(resultSet->getInt("allergen_flag"));
        data.setRxFlag(resultSet->getInt("rx_flag"));
        data.setYbFlag(resultSet->getInt("yb_flag"));
        data.setYbNo(resultSet->getString("yb_no"));
        data.setYbOrgNo(resultSet->getString("yb_org_no"));
        data.setYbMatchFlag(resultSet->getInt("yb_match_flag"));
        data.setChrgitmLv(resultSet->getInt("chrgitm_lv"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setActiveFlag(resultSet->getInt("active_flag"));
        data.setYbMappingCode(resultSet->getString("yb_mapping_code"));
        data.setDoseUnitRatio(resultSet->getDouble("dose_unit_ratio"));
        data.setPurchaseUnitRatio(resultSet->getDouble("purchase_unit_ratio"));
        data.setStockUnitRatio(resultSet->getDouble("stock_unit_ratio"));
        data.setPackageUnitRatio(resultSet->getDouble("package_unit_ratio"));
        return data;
    }
};

/**
 * 耗材定义表字段匹配映射-智能指针版本
 */
class PtrDeviceDefinitionMapper1 : public Mapper<PtrDeviceDefinitionDO1>
{
public:
    PtrDeviceDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<DeviceDefinitionDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setUpdatedAt(resultSet->getString("updated_at"));
        data->setCreatedBy(resultSet->getString("created_by"));
        data->setUpdatedBy(resultSet->getString("updated_by"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setVersion(resultSet->getInt("version"));
        data->setName(resultSet->getString("name"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setPyStr(resultSet->getString("py_str"));
        data->setWbStr(resultSet->getString("wb_str"));
        data->setCategoryCode(resultSet->getString("category_code"));
        data->setTypeCode(resultSet->getString("type_code"));
        data->setPurchaseUnitCode(resultSet->getString("purchase_unit_code"));
        data->setTotalVolume(resultSet->getString("total_volume"));
        data->setItemMinQuantity(resultSet->getDouble("item_min_quantity"));
        data->setItemMaxQuantity(resultSet->getDouble("item_max_quantity"));
        data->setSplitUnitCode(resultSet->getString("split_unit_code"));
        data->setMerchandiseName(resultSet->getString("merchandise_name"));
        data->setMerchandisePyStr(resultSet->getString("merchandise_py_str"));
        data->setMerchandiseWbStr(resultSet->getString("merchandise_wb_str"));
        data->setDefEncounterUnitCode(resultSet->getString("def_encounter_unit_code"));
        data->setDefInhospitalUnitCode(resultSet->getString("def_inhospital_unit_code"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setLocationId(resultSet->getString("location_id"));
        data->setModelNumber(resultSet->getString("model_number"));
        data->setHvcmFlag(resultSet->getInt("hvcm_flag"));
        data->setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data->setPackageUnitCode(resultSet->getString("package_unit_code"));
        data->setStockUnitCode(resultSet->getString("stock_unit_code"));
        data->setApprovalNumber(resultSet->getString("approval_number"));
        data->setManufacturerId(resultSet->getString("manufacturer_id"));
        data->setManufacturerText(resultSet->getString("manufacturer_text"));
        data->setSupplyId(resultSet->getString("supply_id"));
        data->setDescription(resultSet->getString("description"));
        data->setJurisdiction(resultSet->getString("jurisdiction"));
        data->setDeviceVersion(resultSet->getString("device_version"));
        data->setSubstanceText(resultSet->getString("substance_text"));
        data->setAllergenFlag(resultSet->getInt("allergen_flag"));
        data->setRxFlag(resultSet->getInt("rx_flag"));
        data->setYbFlag(resultSet->getInt("yb_flag"));
        data->setYbNo(resultSet->getString("yb_no"));
        data->setYbOrgNo(resultSet->getString("yb_org_no"));
        data->setYbMatchFlag(resultSet->getInt("yb_match_flag"));
        data->setChrgitmLv(resultSet->getInt("chrgitm_lv"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setActiveFlag(resultSet->getInt("active_flag"));
        data->setYbMappingCode(resultSet->getString("yb_mapping_code"));
        data->setDoseUnitRatio(resultSet->getDouble("dose_unit_ratio"));
        data->setPurchaseUnitRatio(resultSet->getDouble("purchase_unit_ratio"));
        data->setStockUnitRatio(resultSet->getDouble("stock_unit_ratio"));
        data->setPackageUnitRatio(resultSet->getDouble("package_unit_ratio"));
        return data;
    }
};

#endif // !_DEVICE_DEFINITION_MAPPER_1_H_