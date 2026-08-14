#pragma once
#ifndef _MEDICATIONDEFINITIONMAPPER1_H_
#define _MEDICATIONDEFINITIONMAPPER1_H_

#include "Mapper.h"
#include "domain/do/chinapres1/MedicationDefinitionDO1.h"

class MedicationDefinitionMapper1 : public Mapper<PtrMedicationDefinitionDO>
{
public:
	PtrMedicationDefinitionDO mapper(ResultSet* resultSet) const override
	{
		PtrMedicationDefinitionDO medDO = std::make_shared<MedicationDefinitionDO1>();

		// 通用字段
		medDO->setId(resultSet->getString("id"));
		medDO->setTenantId(resultSet->getString("tenant_id"));
		medDO->setCreatedAt(resultSet->getString("created_at"));
		medDO->setUpdatedAt(resultSet->getString("updated_at"));
		medDO->setCreatedBy(resultSet->getString("created_by"));
		medDO->setUpdatedBy(resultSet->getString("updated_by"));
		medDO->setIsDeleted(resultSet->getInt("is_deleted"));
		medDO->setVersion(resultSet->getInt("version"));
		// 药品标识与名称
		medDO->setBusNo(resultSet->getString("bus_no"));
		medDO->setName(resultSet->getString("name"));
		medDO->setDomainEnum(resultSet->getString("domain_enum"));
		medDO->setNameEn(resultSet->getString("name_en"));
		medDO->setPyStr(resultSet->getString("py_str"));
		medDO->setWbStr(resultSet->getString("wb_str"));
		// 分类与商品名
		medDO->setCategoryCode(resultSet->getString("category_code"));
		medDO->setMerchandiseName(resultSet->getString("merchandise_name"));
		medDO->setMerchandisePyStr(resultSet->getString("merchandise_py_str"));
		medDO->setMerchandiseWbStr(resultSet->getString("merchandise_wb_str"));
		// 单位
		medDO->setPurchaseUnitCode(resultSet->getString("purchase_unit_code"));
		medDO->setSplitUnitCode(resultSet->getString("split_unit_code"));
		medDO->setDoseUnitCode(resultSet->getString("dose_unit_code"));
		medDO->setPackageUnitCode(resultSet->getString("package_unit_code"));
		medDO->setStockUnitCode(resultSet->getString("stock_unit_code"));
		// 规格与剂量
		medDO->setTotalVolume(resultSet->getString("total_volume"));
		medDO->setDose(resultSet->getDouble("dose"));
		medDO->setMaxUnit(resultSet->getDouble("max_unit"));
		medDO->setUsageLimit(resultSet->getDouble("usage_limit"));
		// 用法频次
		medDO->setMethodCode(resultSet->getString("method_code"));
		medDO->setRateCode(resultSet->getString("rate_code"));
		// 厂家与状态
		medDO->setManufacturerId(resultSet->getString("manufacturer_id"));
		medDO->setManufacturerText(resultSet->getString("manufacturer_text"));
		medDO->setSupplyId(resultSet->getString("supply_id"));
		medDO->setActiveFlag(resultSet->getInt("active_flag"));
		medDO->setStatusEnum(resultSet->getString("status_enum"));
		// 机构与标志
		medDO->setOrgId(resultSet->getString("org_id"));
		medDO->setRxFlag(resultSet->getInt("rx_flag"));
		medDO->setSkinTestFlag(resultSet->getInt("skin_test_flag"));
		medDO->setInfusionFlag(resultSet->getInt("inject_flag"));
		medDO->setAntibioticFlag(resultSet->getInt("antibiotic_flag"));
		medDO->setBasicFlag(resultSet->getInt("basic_flag"));
		// 默认单位
		medDO->setDefEncounterUnitCode(resultSet->getString("def_encounter_unit_code"));
		medDO->setDefInhospitalUnitCode(resultSet->getString("def_inhospital_unit_code"));

		return medDO;
	}
};

#endif // !_MEDICATIONDEFINITIONMAPPER1_H_