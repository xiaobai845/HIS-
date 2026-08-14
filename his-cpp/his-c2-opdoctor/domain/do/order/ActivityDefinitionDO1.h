#pragma once
#ifndef _ACTIVITY_DEFINITION_DO_1_H_
#define _ACTIVITY_DEFINITION_DO_1_H_

#include "../DoInclude.h"

/**
 * 诊疗项目定义实体类
 * 对应表: wkf_activity_definition
 */
class ActivityDefinitionDO1 : public BaseDO
{
    // 主键
    MYSQL_SYNTHESIZE(string, id, Id);
    // 租户标识
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    // 创建时间
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
    // 更新时间
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    // 创建人
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
    // 更新人
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    // 软删标记
    MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
    // 乐观锁版本号
    MYSQL_SYNTHESIZE(int, version, Version);

    // 业务编码
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    // 项目名称
    MYSQL_SYNTHESIZE(string, name, Name);
    // 拼音码
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);
    // 五笔码
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);
    // 分类编码
    MYSQL_SYNTHESIZE(string, categoryCode, CategoryCode);
    // 说明文本
    MYSQL_SYNTHESIZE(string, descriptionText, DescriptionText);
    // 所属机构标识
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    // 位置标识
    MYSQL_SYNTHESIZE(string, locationId, LocationId);
    // 发布状态
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    // 诊疗类型枚举
    MYSQL_SYNTHESIZE(string, typeEnum, TypeEnum);
    // 销售/计价单位编码
    MYSQL_SYNTHESIZE(string, packageUnitCode, PackageUnitCode);
    // 身体部位编码
    MYSQL_SYNTHESIZE(string, bodySiteCode, BodySiteCode);
    // 标本编码
    MYSQL_SYNTHESIZE(string, specimenCode, SpecimenCode);
    // 计费规则标识
    MYSQL_SYNTHESIZE(int, ruleId, RuleId);
    // 划价标记
    MYSQL_SYNTHESIZE(int, pricingFlag, PricingFlag);
    // 医保标记
    MYSQL_SYNTHESIZE(int, ybFlag, YbFlag);
    // 医保编码
    MYSQL_SYNTHESIZE(string, ybNo, YbNo);
    // 医保对码标记
    MYSQL_SYNTHESIZE(int, ybMatchFlag, YbMatchFlag);
    // 医保等级
    MYSQL_SYNTHESIZE(int, chrgitmLv, ChrgitmLv);
    // 子项 JSON
    MYSQL_SYNTHESIZE(string, childrenJson, ChildrenJson);
    // 子项标记
    MYSQL_SYNTHESIZE(int, childrenFlag, ChildrenFlag);
    // 业务版本
    MYSQL_SYNTHESIZE(string, activityVersion, ActivityVersion);
    // 商品名称
    MYSQL_SYNTHESIZE(string, merchandiseName, MerchandiseName);
    // 商品名拼音码
    MYSQL_SYNTHESIZE(string, merchandisePyStr, MerchandisePyStr);
    // 商品名五笔码
    MYSQL_SYNTHESIZE(string, merchandiseWbStr, MerchandiseWbStr);
    // 默认门诊单位
    MYSQL_SYNTHESIZE(string, defEncounterUnitCode, DefEncounterUnitCode);
    // 默认住院单位
    MYSQL_SYNTHESIZE(string, defInhospitalUnitCode, DefInhospitalUnitCode);

public:
    ActivityDefinitionDO1() : BaseDO("wkf_activity_definition")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("created_at", "s", createdAt);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("created_by", "s", createdBy);
        MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
        MYSQL_ADD_FIELD("is_deleted", "i", isDeleted);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("py_str", "s", pyStr);
        MYSQL_ADD_FIELD("wb_str", "s", wbStr);
        MYSQL_ADD_FIELD("category_code", "s", categoryCode);
        MYSQL_ADD_FIELD("description_text", "s", descriptionText);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("location_id", "s", locationId);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("type_enum", "s", typeEnum);
        MYSQL_ADD_FIELD("package_unit_code", "s", packageUnitCode);
        MYSQL_ADD_FIELD("body_site_code", "s", bodySiteCode);
        MYSQL_ADD_FIELD("specimen_code", "s", specimenCode);
        MYSQL_ADD_FIELD("rule_id", "i", ruleId);
        MYSQL_ADD_FIELD("pricing_flag", "i", pricingFlag);
        MYSQL_ADD_FIELD("yb_flag", "i", ybFlag);
        MYSQL_ADD_FIELD("yb_no", "s", ybNo);
        MYSQL_ADD_FIELD("yb_match_flag", "i", ybMatchFlag);
        MYSQL_ADD_FIELD("chrgitm_lv", "i", chrgitmLv);
        MYSQL_ADD_FIELD("children_json", "s", childrenJson);
        MYSQL_ADD_FIELD("children_flag", "i", childrenFlag);
        MYSQL_ADD_FIELD("activity_version", "s", activityVersion);
        MYSQL_ADD_FIELD("merchandise_name", "s", merchandiseName);
        MYSQL_ADD_FIELD("merchandise_py_str", "s", merchandisePyStr);
        MYSQL_ADD_FIELD("merchandise_wb_str", "s", merchandiseWbStr);
        MYSQL_ADD_FIELD("def_encounter_unit_code", "s", defEncounterUnitCode);
        MYSQL_ADD_FIELD("def_inhospital_unit_code", "s", defInhospitalUnitCode);
    }
};

typedef std::shared_ptr<ActivityDefinitionDO1> PtrActivityDefinitionDO1;

#endif // !_ACTIVITY_DEFINITION_DO_1_H_