#pragma once
#ifndef _MEDICATION_DEFINITION_MAPPER_1_H_
#define _MEDICATION_DEFINITION_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/MedicationDefinitionDO1.h"

/**
 * 药品定义表字段匹配映射
 */
class MedicationDefinitionMapper1 : public Mapper<MedicationDefinitionDO1>
{
public:
    MedicationDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        MedicationDefinitionDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setName(resultSet->getString("name"));
        data.setNameEn(resultSet->getString("name_en"));
        data.setPyStr(resultSet->getString("py_str"));
        data.setWbStr(resultSet->getString("wb_str"));
        data.setCategoryCode(resultSet->getString("category_code"));
        data.setTotalVolume(resultSet->getString("total_volume"));
        data.setDoseFormCode(resultSet->getString("dose_form_code"));
        data.setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data.setPackageUnitCode(resultSet->getString("package_unit_code"));
        data.setStockUnitCode(resultSet->getString("stock_unit_code"));
        data.setSkinTestFlag(resultSet->getInt("skin_test_flag"));
        data.setInjectFlag(resultSet->getInt("inject_flag"));
        data.setRxFlag(resultSet->getInt("rx_flag"));
        data.setAntibioticFlag(resultSet->getInt("antibiotic_flag"));
        data.setBasicFlag(resultSet->getInt("basic_flag"));
        data.setManufacturerText(resultSet->getString("manufacturer_text"));
        data.setManufacturerId(resultSet->getString("manufacturer_id"));
        data.setApprovalNumber(resultSet->getString("approval_number"));
        data.setYbNo(resultSet->getString("yb_no"));
        data.setYbMatchFlag(resultSet->getInt("yb_match_flag"));
        data.setChrgitmLv(resultSet->getInt("chrgitm_lv"));
        data.setMethodCode(resultSet->getString("method_code"));
        data.setRateCode(resultSet->getString("rate_code"));
        data.setDose(resultSet->getDouble("dose"));
        data.setMaxUnit(resultSet->getDouble("max_unit"));
        data.setDosageInstruction(resultSet->getString("dosage_instruction"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setActiveFlag(resultSet->getInt("active_flag"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setLocationId(resultSet->getString("location_id"));
        return data;
    }
};

/**
 * 药品定义表字段匹配映射-智能指针版本
 */
class PtrMedicationDefinitionMapper1 : public Mapper<PtrMedicationDefinitionDO1>
{
public:
    PtrMedicationDefinitionDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<MedicationDefinitionDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setCreatedBy(resultSet->getString("created_by"));
        data->setUpdatedBy(resultSet->getString("updated_by"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setUpdatedAt(resultSet->getString("updated_at"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setVersion(resultSet->getInt("version"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setName(resultSet->getString("name"));
        data->setNameEn(resultSet->getString("name_en"));
        data->setPyStr(resultSet->getString("py_str"));
        data->setWbStr(resultSet->getString("wb_str"));
        data->setCategoryCode(resultSet->getString("category_code"));
        data->setTotalVolume(resultSet->getString("total_volume"));
        data->setDoseFormCode(resultSet->getString("dose_form_code"));
        data->setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data->setPackageUnitCode(resultSet->getString("package_unit_code"));
        data->setStockUnitCode(resultSet->getString("stock_unit_code"));
        data->setSkinTestFlag(resultSet->getInt("skin_test_flag"));
        data->setInjectFlag(resultSet->getInt("inject_flag"));
        data->setRxFlag(resultSet->getInt("rx_flag"));
        data->setAntibioticFlag(resultSet->getInt("antibiotic_flag"));
        data->setBasicFlag(resultSet->getInt("basic_flag"));
        data->setManufacturerText(resultSet->getString("manufacturer_text"));
        data->setManufacturerId(resultSet->getString("manufacturer_id"));
        data->setApprovalNumber(resultSet->getString("approval_number"));
        data->setYbNo(resultSet->getString("yb_no"));
        data->setYbMatchFlag(resultSet->getInt("yb_match_flag"));
        data->setChrgitmLv(resultSet->getInt("chrgitm_lv"));
        data->setMethodCode(resultSet->getString("method_code"));
        data->setRateCode(resultSet->getString("rate_code"));
        data->setDose(resultSet->getDouble("dose"));
        data->setMaxUnit(resultSet->getDouble("max_unit"));
        data->setDosageInstruction(resultSet->getString("dosage_instruction"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setActiveFlag(resultSet->getInt("active_flag"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setLocationId(resultSet->getString("location_id"));
        return data;
    }
};

#endif // !_MEDICATION_DEFINITION_MAPPER_1_H_