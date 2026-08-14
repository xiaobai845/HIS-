#pragma once
#ifndef _INVENTORY_ITEM_DO_1_H_
#define _INVENTORY_ITEM_DO_1_H_
#include "../DoInclude.h"

/**
 * 库存项实体类
 * 对应表: wkf_inventory_item
 */
class InventoryItemDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);

    MYSQL_SYNTHESIZE(string, categoryCode, CategoryCode);
    MYSQL_SYNTHESIZE(string, itemTable, ItemTable);
    MYSQL_SYNTHESIZE(string, itemId, ItemId);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);
    MYSQL_SYNTHESIZE(string, inventoryStatusEnum, InventoryStatusEnum);
    MYSQL_SYNTHESIZE(string, supplierId, SupplierId);
    MYSQL_SYNTHESIZE(string, descriptionText, DescriptionText);
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
    MYSQL_SYNTHESIZE(double, quantity, Quantity);
    MYSQL_SYNTHESIZE(string, characteristicJson, CharacteristicJson);
    MYSQL_SYNTHESIZE(string, lotNumber, LotNumber);
    MYSQL_SYNTHESIZE(string, productionDate, ProductionDate);
    MYSQL_SYNTHESIZE(string, expirationDate, ExpirationDate);
    MYSQL_SYNTHESIZE(int, validityMon, ValidityMon);
    MYSQL_SYNTHESIZE(string, locationStoreId, LocationStoreId);
    MYSQL_SYNTHESIZE(string, locationId, LocationId);
    MYSQL_SYNTHESIZE(string, traceNo, TraceNo);
    MYSQL_SYNTHESIZE(int, packagingLevels, PackagingLevels);

public:
    InventoryItemDO1() : BaseDO("wkf_inventory_item")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("category_code", "s", categoryCode);
        MYSQL_ADD_FIELD("item_table", "s", itemTable);
        MYSQL_ADD_FIELD("item_id", "s", itemId);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("py_str", "s", pyStr);
        MYSQL_ADD_FIELD("wb_str", "s", wbStr);
        MYSQL_ADD_FIELD("inventory_status_enum", "s", inventoryStatusEnum);
        MYSQL_ADD_FIELD("supplier_id", "s", supplierId);
        MYSQL_ADD_FIELD("description_text", "s", descriptionText);
        MYSQL_ADD_FIELD("unit_code", "s", unitCode);
        MYSQL_ADD_FIELD("quantity", "d", quantity);
        MYSQL_ADD_FIELD("characteristic_json", "s", characteristicJson);
        MYSQL_ADD_FIELD("lot_number", "s", lotNumber);
        MYSQL_ADD_FIELD("production_date", "s", productionDate);
        MYSQL_ADD_FIELD("expiration_date", "s", expirationDate);
        MYSQL_ADD_FIELD("validity_mon", "i", validityMon);
        MYSQL_ADD_FIELD("location_store_id", "s", locationStoreId);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
        MYSQL_ADD_FIELD("trace_no", "s", traceNo);
        MYSQL_ADD_FIELD("packaging_levels", "i", packagingLevels);
    }
};

typedef std::shared_ptr<InventoryItemDO1> PtrInventoryItemDO1;
#endif // !_INVENTORY_ITEM_DO_1_H_