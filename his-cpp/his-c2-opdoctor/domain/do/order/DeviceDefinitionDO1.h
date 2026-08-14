#pragma once
#ifndef _DEVICE_DEFINITION_DO_1_H_
#define _DEVICE_DEFINITION_DO_1_H_

#include "../DoInclude.h"

/**
 * 耗材定义实体类
 * 对应表: adm_device_definition
 */
class DeviceDefinitionDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);

    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);
    MYSQL_SYNTHESIZE(string, categoryCode, CategoryCode);
    MYSQL_SYNTHESIZE(string, typeCode, TypeCode);
    MYSQL_SYNTHESIZE(string, purchaseUnitCode, PurchaseUnitCode);
    MYSQL_SYNTHESIZE(string, totalVolume, TotalVolume);
    MYSQL_SYNTHESIZE(double, itemMinQuantity, ItemMinQuantity);
    MYSQL_SYNTHESIZE(double, itemMaxQuantity, ItemMaxQuantity);
    MYSQL_SYNTHESIZE(string, splitUnitCode, SplitUnitCode);
    MYSQL_SYNTHESIZE(string, merchandiseName, MerchandiseName);
    MYSQL_SYNTHESIZE(string, merchandisePyStr, MerchandisePyStr);
    MYSQL_SYNTHESIZE(string, merchandiseWbStr, MerchandiseWbStr);
    MYSQL_SYNTHESIZE(string, defEncounterUnitCode, DefEncounterUnitCode);
    MYSQL_SYNTHESIZE(string, defInhospitalUnitCode, DefInhospitalUnitCode);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(string, locationId, LocationId);
    MYSQL_SYNTHESIZE(string, modelNumber, ModelNumber);
    MYSQL_SYNTHESIZE(int, hvcmFlag, HvcmFlag);
    MYSQL_SYNTHESIZE(string, doseUnitCode, DoseUnitCode);
    MYSQL_SYNTHESIZE(string, packageUnitCode, PackageUnitCode);
    MYSQL_SYNTHESIZE(string, stockUnitCode, StockUnitCode);
    MYSQL_SYNTHESIZE(string, approvalNumber, ApprovalNumber);
    MYSQL_SYNTHESIZE(string, manufacturerId, ManufacturerId);
    MYSQL_SYNTHESIZE(string, manufacturerText, ManufacturerText);
    MYSQL_SYNTHESIZE(string, supplyId, SupplyId);
    MYSQL_SYNTHESIZE(string, description, Description);
    MYSQL_SYNTHESIZE(string, jurisdiction, Jurisdiction);
    MYSQL_SYNTHESIZE(string, deviceVersion, DeviceVersion);
    MYSQL_SYNTHESIZE(string, substanceText, SubstanceText);
    MYSQL_SYNTHESIZE(int, allergenFlag, AllergenFlag);
    MYSQL_SYNTHESIZE(int, rxFlag, RxFlag);
    MYSQL_SYNTHESIZE(int, ybFlag, YbFlag);
    MYSQL_SYNTHESIZE(string, ybNo, YbNo);
    MYSQL_SYNTHESIZE(string, ybOrgNo, YbOrgNo);
    MYSQL_SYNTHESIZE(int, ybMatchFlag, YbMatchFlag);
    MYSQL_SYNTHESIZE(int, chrgitmLv, ChrgitmLv);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(int, activeFlag, ActiveFlag);
    MYSQL_SYNTHESIZE(string, ybMappingCode, YbMappingCode);
    MYSQL_SYNTHESIZE(double, doseUnitRatio, DoseUnitRatio);
    MYSQL_SYNTHESIZE(double, purchaseUnitRatio, PurchaseUnitRatio);
    MYSQL_SYNTHESIZE(double, stockUnitRatio, StockUnitRatio);
    MYSQL_SYNTHESIZE(double, packageUnitRatio, PackageUnitRatio);

public:
    DeviceDefinitionDO1() : BaseDO("adm_device_definition")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("py_str", "s", pyStr);
        MYSQL_ADD_FIELD("wb_str", "s", wbStr);
        MYSQL_ADD_FIELD("category_code", "s", categoryCode);
        MYSQL_ADD_FIELD("type_code", "s", typeCode);
        MYSQL_ADD_FIELD("purchase_unit_code", "s", purchaseUnitCode);
        MYSQL_ADD_FIELD("total_volume", "s", totalVolume);
        MYSQL_ADD_FIELD("item_min_quantity", "d", itemMinQuantity);
        MYSQL_ADD_FIELD("item_max_quantity", "d", itemMaxQuantity);
        MYSQL_ADD_FIELD("split_unit_code", "s", splitUnitCode);
        MYSQL_ADD_FIELD("merchandise_name", "s", merchandiseName);
        MYSQL_ADD_FIELD("merchandise_py_str", "s", merchandisePyStr);
        MYSQL_ADD_FIELD("merchandise_wb_str", "s", merchandiseWbStr);
        MYSQL_ADD_FIELD("def_encounter_unit_code", "s", defEncounterUnitCode);
        MYSQL_ADD_FIELD("def_inhospital_unit_code", "s", defInhospitalUnitCode);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
        MYSQL_ADD_FIELD("model_number", "s", modelNumber);
        MYSQL_ADD_FIELD("hvcm_flag", "i", hvcmFlag);
        MYSQL_ADD_FIELD("dose_unit_code", "s", doseUnitCode);
        MYSQL_ADD_FIELD("package_unit_code", "s", packageUnitCode);
        MYSQL_ADD_FIELD("stock_unit_code", "s", stockUnitCode);
        MYSQL_ADD_FIELD("approval_number", "s", approvalNumber);
        MYSQL_ADD_FIELD("manufacturer_id", "s", manufacturerId);
        MYSQL_ADD_FIELD("manufacturer_text", "s", manufacturerText);
        MYSQL_ADD_FIELD("supply_id", "s", supplyId);
        MYSQL_ADD_FIELD("description", "s", description);
        MYSQL_ADD_FIELD("jurisdiction", "s", jurisdiction);
        MYSQL_ADD_FIELD("device_version", "s", deviceVersion);
        MYSQL_ADD_FIELD("substance_text", "s", substanceText);
        MYSQL_ADD_FIELD("allergen_flag", "i", allergenFlag);
        MYSQL_ADD_FIELD("rx_flag", "i", rxFlag);
        MYSQL_ADD_FIELD("yb_flag", "i", ybFlag);
        MYSQL_ADD_FIELD("yb_no", "s", ybNo);
        MYSQL_ADD_FIELD("yb_org_no", "s", ybOrgNo);
        MYSQL_ADD_FIELD("yb_match_flag", "i", ybMatchFlag);
        MYSQL_ADD_FIELD("chrgitm_lv", "i", chrgitmLv);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("active_flag", "i", activeFlag);
        MYSQL_ADD_FIELD("yb_mapping_code", "s", ybMappingCode);
        MYSQL_ADD_FIELD("dose_unit_ratio", "d", doseUnitRatio);
        MYSQL_ADD_FIELD("purchase_unit_ratio", "d", purchaseUnitRatio);
        MYSQL_ADD_FIELD("stock_unit_ratio", "d", stockUnitRatio);
        MYSQL_ADD_FIELD("package_unit_ratio", "d", packageUnitRatio);
    }
};

typedef std::shared_ptr<DeviceDefinitionDO1> PtrDeviceDefinitionDO1;

#endif // !_DEVICE_DEFINITION_DO_1_H_