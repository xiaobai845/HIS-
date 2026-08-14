#pragma once
#ifndef _MEDICATION_DEFINITION_DO_1_H_
#define _MEDICATION_DEFINITION_DO_1_H_
#include "../DoInclude.h"

/**
 * 药品/耗材定义实体类
 * 对应表: med_medication_definition
 */
class MedicationDefinitionDO1 : public BaseDO
{
    // ===== 主键 & 审计 =====
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(int, version, Version);

    // ===== 业务核心 =====
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, nameEn, NameEn);
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);

    // ===== 分类 & 规格 =====
    MYSQL_SYNTHESIZE(string, categoryCode, CategoryCode);
    MYSQL_SYNTHESIZE(string, totalVolume, TotalVolume);
    MYSQL_SYNTHESIZE(string, doseFormCode, DoseFormCode);
    MYSQL_SYNTHESIZE(string, doseUnitCode, DoseUnitCode);
    MYSQL_SYNTHESIZE(string, packageUnitCode, PackageUnitCode);
    MYSQL_SYNTHESIZE(string, stockUnitCode, StockUnitCode);

    // ===== 药品属性 =====
    MYSQL_SYNTHESIZE(int, skinTestFlag, SkinTestFlag);
    MYSQL_SYNTHESIZE(int, injectFlag, InjectFlag);
    MYSQL_SYNTHESIZE(int, rxFlag, RxFlag);
    MYSQL_SYNTHESIZE(int, antibioticFlag, AntibioticFlag);
    MYSQL_SYNTHESIZE(int, basicFlag, BasicFlag);

    // ===== 厂家 & 医保 =====
    MYSQL_SYNTHESIZE(string, manufacturerText, ManufacturerText);
    MYSQL_SYNTHESIZE(string, manufacturerId, ManufacturerId);
    MYSQL_SYNTHESIZE(string, approvalNumber, ApprovalNumber);
    MYSQL_SYNTHESIZE(string, ybNo, YbNo);
    MYSQL_SYNTHESIZE(int, ybMatchFlag, YbMatchFlag);
    MYSQL_SYNTHESIZE(int, chrgitmLv, ChrgitmLv);

    // ===== 默认用法 & 剂量 =====
    MYSQL_SYNTHESIZE(string, methodCode, MethodCode);
    MYSQL_SYNTHESIZE(string, rateCode, RateCode);
    MYSQL_SYNTHESIZE(double, dose, Dose);
    MYSQL_SYNTHESIZE(double, maxUnit, MaxUnit);
    MYSQL_SYNTHESIZE(string, dosageInstruction, DosageInstruction);

    // ===== 状态 & 机构 =====
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(int, activeFlag, ActiveFlag);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(string, locationId, LocationId);

public:
    MedicationDefinitionDO1() : BaseDO("med_medication_definition")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("name_en", "s", nameEn);
        MYSQL_ADD_FIELD("py_str", "s", pyStr);
        MYSQL_ADD_FIELD("wb_str", "s", wbStr);
        MYSQL_ADD_FIELD("category_code", "s", categoryCode);
        MYSQL_ADD_FIELD("total_volume", "s", totalVolume);
        MYSQL_ADD_FIELD("dose_form_code", "s", doseFormCode);
        MYSQL_ADD_FIELD("dose_unit_code", "s", doseUnitCode);
        MYSQL_ADD_FIELD("package_unit_code", "s", packageUnitCode);
        MYSQL_ADD_FIELD("stock_unit_code", "s", stockUnitCode);
        MYSQL_ADD_FIELD("skin_test_flag", "i", skinTestFlag);
        MYSQL_ADD_FIELD("inject_flag", "i", injectFlag);
        MYSQL_ADD_FIELD("rx_flag", "i", rxFlag);
        MYSQL_ADD_FIELD("antibiotic_flag", "i", antibioticFlag);
        MYSQL_ADD_FIELD("basic_flag", "i", basicFlag);
        MYSQL_ADD_FIELD("manufacturer_text", "s", manufacturerText);
        MYSQL_ADD_FIELD("manufacturer_id", "s", manufacturerId);
        MYSQL_ADD_FIELD("approval_number", "s", approvalNumber);
        MYSQL_ADD_FIELD("yb_no", "s", ybNo);
        MYSQL_ADD_FIELD("yb_match_flag", "i", ybMatchFlag);
        MYSQL_ADD_FIELD("chrgitm_lv", "i", chrgitmLv);
        MYSQL_ADD_FIELD("method_code", "s", methodCode);
        MYSQL_ADD_FIELD("rate_code", "s", rateCode);
        MYSQL_ADD_FIELD("dose", "d", dose);
        MYSQL_ADD_FIELD("max_unit", "d", maxUnit);
        MYSQL_ADD_FIELD("dosage_instruction", "s", dosageInstruction);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("active_flag", "i", activeFlag);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
    }
};

typedef std::shared_ptr<MedicationDefinitionDO1> PtrMedicationDefinitionDO1;
#endif // !_MEDICATION_DEFINITION_DO_1_H_