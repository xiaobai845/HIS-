#pragma once
#ifndef _MEDICATIONDEFINITIONDO1_H_
#define _MEDICATIONDEFINITIONDO1_H_

#include "../DoInclude.h"

class MedicationDefinitionDO1: public BaseDO
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
    // 药品标识与名称
    MYSQL_SYNTHESIZE(string, busNo, BusNo);                     // 业务编号
    MYSQL_SYNTHESIZE(string, name, Name);                       // 药品名称（如"党参"）
    MYSQL_SYNTHESIZE(string, domainEnum, DomainEnum);           // 适用范围
    MYSQL_SYNTHESIZE(string, nameEn, NameEn);                   // 英文药名
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);                     // 拼音码（检索用）
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);                     // 五笔码（检索用）
    // 分类与商品名
    MYSQL_SYNTHESIZE(string, categoryCode, CategoryCode);       // 药品分类编码
    MYSQL_SYNTHESIZE(string, merchandiseName, MerchandiseName); // 商品名称
    MYSQL_SYNTHESIZE(string, merchandisePyStr, MerchandisePyStr); // 商品名拼音
    MYSQL_SYNTHESIZE(string, merchandiseWbStr, MerchandiseWbStr); // 商品名五笔
    // 单位（5类单位）
    MYSQL_SYNTHESIZE(string, purchaseUnitCode, PurchaseUnitCode);   // 采购单位
    MYSQL_SYNTHESIZE(string, splitUnitCode, SplitUnitCode);           // 拆零单位
    MYSQL_SYNTHESIZE(string, doseUnitCode, DoseUnitCode);             // 剂量单位
    MYSQL_SYNTHESIZE(string, packageUnitCode, PackageUnitCode);       // 销售/包装单位
    MYSQL_SYNTHESIZE(string, stockUnitCode, StockUnitCode);           // 库存单位
    // 规格与默认剂量
    MYSQL_SYNTHESIZE(string, totalVolume, TotalVolume);         // 规格（如"10g/包"）
    MYSQL_SYNTHESIZE(double, dose, Dose);                       // 默认单次剂量
    MYSQL_SYNTHESIZE(double, maxUnit, MaxUnit);                 // 单次最大剂量
    MYSQL_SYNTHESIZE(double, usageLimit, UsageLimit);           // 用量限定
    // 默认用法与频次
    MYSQL_SYNTHESIZE(string, methodCode, MethodCode);           // 默认用法编码
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);               // 默认频次编码
    // 厂家与状态
    MYSQL_SYNTHESIZE(string, manufacturerId, ManufacturerId);   // 生产厂家标识
    MYSQL_SYNTHESIZE(string, manufacturerText, ManufacturerText); // 生产厂家名称
    MYSQL_SYNTHESIZE(string, supplyId, SupplyId);               // 供应商标识
    MYSQL_SYNTHESIZE(bool, activeFlag, ActiveFlag);             // 启用标记
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);             // 生命周期状态
    // 机构与特殊标志
    MYSQL_SYNTHESIZE(string, orgId, OrgId);                     // 机构标识
    MYSQL_SYNTHESIZE(bool, rxFlag, RxFlag);                     // 处方药标志
    MYSQL_SYNTHESIZE(bool, skinTestFlag, SkinTestFlag);         // 皮试标志
    MYSQL_SYNTHESIZE(bool, infusionFlag, InfusionFlag);         // 注射标志
    MYSQL_SYNTHESIZE(bool, antibioticFlag, AntibioticFlag);     // 抗生素标志
    MYSQL_SYNTHESIZE(bool, basicFlag, BasicFlag);               // 基药标志
    // 门诊/住院默认单位
    MYSQL_SYNTHESIZE(string, defEncounterUnitCode, DefEncounterUnitCode);   // 默认门诊单位
    MYSQL_SYNTHESIZE(string, defInhospitalUnitCode, DefInhospitalUnitCode); // 默认住院单位
public:
    MedicationDefinitionDO1() : BaseDO("med_medication_definition")
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
        // 标识与名称
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD_NULLABLE("domain_enum", "s", domainEnum, false);
        MYSQL_ADD_FIELD_NULLABLE("name_en", "s", nameEn, false);
        MYSQL_ADD_FIELD_NULLABLE("py_str", "s", pyStr, false);
        MYSQL_ADD_FIELD_NULLABLE("wb_str", "s", wbStr, false);
        // 分类
        MYSQL_ADD_FIELD_NULLABLE("category_code", "s", categoryCode, false);
        MYSQL_ADD_FIELD_NULLABLE("merchandise_name", "s", merchandiseName, false);
        MYSQL_ADD_FIELD_NULLABLE("merchandise_py_str", "s", merchandisePyStr, false);
        MYSQL_ADD_FIELD_NULLABLE("merchandise_wb_str", "s", merchandiseWbStr, false);
        // 单位
        MYSQL_ADD_FIELD_NULLABLE("purchase_unit_code", "s", purchaseUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("split_unit_code", "s", splitUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("dose_unit_code", "s", doseUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("package_unit_code", "s", packageUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("stock_unit_code", "s", stockUnitCode, false);
        // 规格与剂量
        MYSQL_ADD_FIELD_NULLABLE("total_volume", "s", totalVolume, false);
        MYSQL_ADD_FIELD_NULLABLE("dose", "d", dose, false);
        MYSQL_ADD_FIELD_NULLABLE("max_unit", "d", maxUnit, false);
        MYSQL_ADD_FIELD_NULLABLE("usage_limit", "d", usageLimit, false);
        // 用法频次
        MYSQL_ADD_FIELD_NULLABLE("method_code", "s", methodCode, false);
        MYSQL_ADD_FIELD_NULLABLE("rate_code", "s", rateCode, false);
        // 厂家与状态
        MYSQL_ADD_FIELD_NULLABLE("manufacturer_id", "s", manufacturerId, false);
        MYSQL_ADD_FIELD_NULLABLE("manufacturer_text", "s", manufacturerText, false);
        MYSQL_ADD_FIELD_NULLABLE("supply_id", "s", supplyId, false);
        MYSQL_ADD_FIELD_NULLABLE("active_flag", "b", activeFlag, false);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        // 机构与标志
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD_NULLABLE("rx_flag", "b", rxFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("skin_test_flag", "b", skinTestFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("inject_flag", "b", infusionFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("antibiotic_flag", "b", antibioticFlag, false);
        MYSQL_ADD_FIELD_NULLABLE("basic_flag", "b", basicFlag, false);
        // 默认单位
        MYSQL_ADD_FIELD_NULLABLE("def_encounter_unit_code", "s", defEncounterUnitCode, false);
        MYSQL_ADD_FIELD_NULLABLE("def_inhospital_unit_code", "s", defInhospitalUnitCode, false);
    }
};

typedef std::shared_ptr<MedicationDefinitionDO1> PtrMedicationDefinitionDO;

#endif // !_MEDICATIONDEFINITIONDO1_H_