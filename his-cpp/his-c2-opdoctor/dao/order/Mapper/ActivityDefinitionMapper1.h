#pragma once
#ifndef _ACTIVITY_DEFINITION_MAPPER_1_H_
#define _ACTIVITY_DEFINITION_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/ActivityDefinitionDO1.h"

/**
 * 诊疗项目定义表字段匹配映射
 */
class ActivityDefinitionMapper1 : public Mapper<ActivityDefinitionDO1>
{
public:
    ActivityDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        ActivityDefinitionDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setName(resultSet->getString("name"));
        data.setPyStr(resultSet->getString("py_str"));
        data.setWbStr(resultSet->getString("wb_str"));
        data.setCategoryCode(resultSet->getString("category_code"));
        data.setDescriptionText(resultSet->getString("description_text"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setLocationId(resultSet->getString("location_id"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setTypeEnum(resultSet->getString("type_enum"));
        data.setPackageUnitCode(resultSet->getString("package_unit_code"));
        data.setBodySiteCode(resultSet->getString("body_site_code"));
        data.setSpecimenCode(resultSet->getString("specimen_code"));
        data.setRuleId(resultSet->getInt("rule_id"));
        data.setPricingFlag(resultSet->getInt("pricing_flag"));
        data.setYbFlag(resultSet->getInt("yb_flag"));
        data.setYbNo(resultSet->getString("yb_no"));
        data.setYbMatchFlag(resultSet->getInt("yb_match_flag"));
        data.setChrgitmLv(resultSet->getInt("chrgitm_lv"));
        data.setChildrenJson(resultSet->getString("children_json"));
        data.setChildrenFlag(resultSet->getInt("children_flag"));
        data.setActivityVersion(resultSet->getString("activity_version"));
        data.setMerchandiseName(resultSet->getString("merchandise_name"));
        data.setMerchandisePyStr(resultSet->getString("merchandise_py_str"));
        data.setMerchandiseWbStr(resultSet->getString("merchandise_wb_str"));
        data.setDefEncounterUnitCode(resultSet->getString("def_encounter_unit_code"));
        data.setDefInhospitalUnitCode(resultSet->getString("def_inhospital_unit_code"));
        return data;
    }
};

/**
 * 诊疗项目定义表字段匹配映射-智能指针版本
 */
class PtrActivityDefinitionMapper1 : public Mapper<PtrActivityDefinitionDO1>
{
public:
    PtrActivityDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<ActivityDefinitionDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setUpdatedAt(resultSet->getString("updated_at"));
        data->setCreatedBy(resultSet->getString("created_by"));
        data->setUpdatedBy(resultSet->getString("updated_by"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setVersion(resultSet->getInt("version"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setName(resultSet->getString("name"));
        data->setPyStr(resultSet->getString("py_str"));
        data->setWbStr(resultSet->getString("wb_str"));
        data->setCategoryCode(resultSet->getString("category_code"));
        data->setDescriptionText(resultSet->getString("description_text"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setLocationId(resultSet->getString("location_id"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setTypeEnum(resultSet->getString("type_enum"));
        data->setPackageUnitCode(resultSet->getString("package_unit_code"));
        data->setBodySiteCode(resultSet->getString("body_site_code"));
        data->setSpecimenCode(resultSet->getString("specimen_code"));
        data->setRuleId(resultSet->getInt("rule_id"));
        data->setPricingFlag(resultSet->getInt("pricing_flag"));
        data->setYbFlag(resultSet->getInt("yb_flag"));
        data->setYbNo(resultSet->getString("yb_no"));
        data->setYbMatchFlag(resultSet->getInt("yb_match_flag"));
        data->setChrgitmLv(resultSet->getInt("chrgitm_lv"));
        data->setChildrenJson(resultSet->getString("children_json"));
        data->setChildrenFlag(resultSet->getInt("children_flag"));
        data->setActivityVersion(resultSet->getString("activity_version"));
        data->setMerchandiseName(resultSet->getString("merchandise_name"));
        data->setMerchandisePyStr(resultSet->getString("merchandise_py_str"));
        data->setMerchandiseWbStr(resultSet->getString("merchandise_wb_str"));
        data->setDefEncounterUnitCode(resultSet->getString("def_encounter_unit_code"));
        data->setDefInhospitalUnitCode(resultSet->getString("def_inhospital_unit_code"));
        return data;
    }
};

#endif // !_ACTIVITY_DEFINITION_MAPPER_1_H_