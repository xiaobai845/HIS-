#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/25
*/
#ifndef _CHINAPRES2_DETAIL_MAPPER_
#define _CHINAPRES2_DETAIL_MAPPER_

#include "Mapper.h"
#include "../../domain/do/chinapres2/Chinapres2DetailDO.h"

/**
 * 处方明细表 Mapper
 */
class Chinapres2DetailMapper : public Mapper<Chinapres2DetailDO>
{
public:
    Chinapres2DetailDO mapper(ResultSet* resultSet) const override
    {
        Chinapres2DetailDO data;
        data.setId(resultSet->getString("id"));
        data.setRequestId(resultSet->getString("request_id"));
        data.setMedicationId(resultSet->getString("medication_id"));
        data.setQuantity(resultSet->getDouble("quantity"));
        data.setUnitCode(resultSet->getString("unit_code"));
        data.setDose(resultSet->getDouble("dose"));
        data.setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data.setSortNo(resultSet->getInt("sort_no"));
        data.setCreateBy(resultSet->getString("create_by"));
        data.setCreateTime(resultSet->getString("create_time"));
        data.setUpdateBy(resultSet->getString("update_by"));
        data.setUpdateTime(resultSet->getString("update_time"));
        return data;
    }
};

/**
 * 处方明细表智能指针 Mapper
 */
class PtrChinapres2DetailMapper : public Mapper<PtrChinapres2DetailDO>
{
public:
    PtrChinapres2DetailDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<Chinapres2DetailDO>();
        data->setId(resultSet->getString("id"));
        data->setRequestId(resultSet->getString("request_id"));
        data->setMedicationId(resultSet->getString("medication_id"));
        data->setQuantity(resultSet->getDouble("quantity"));
        data->setUnitCode(resultSet->getString("unit_code"));
        data->setDose(resultSet->getDouble("dose"));
        data->setDoseUnitCode(resultSet->getString("dose_unit_code"));
        data->setSortNo(resultSet->getInt("sort_no"));
        data->setCreateBy(resultSet->getString("create_by"));
        data->setCreateTime(resultSet->getString("create_time"));
        data->setUpdateBy(resultSet->getString("update_by"));
        data->setUpdateTime(resultSet->getString("update_time"));
        return data;
    }
};

#endif // !_CHINAPRES2_DETAIL_MAPPER_