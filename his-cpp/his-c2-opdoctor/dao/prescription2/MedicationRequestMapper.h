#pragma once

#ifndef _MEDICATIONREQUESTMAPPER_H_
#define _MEDICATIONREQUESTMAPPER_H_

#include "Mapper.h"
#include "domain/do/prescription2/MedicationRequestDO.h"

class PtrMedicationRequestMapper : public Mapper<PtrMedicationRequestDO>
{
public:
    // 将医嘱查询列映射为数据库对象
    PtrMedicationRequestDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<MedicationRequestDO>();
        data->setId(resultSet->getString(1));
        data->setEncounterId(resultSet->getString(2));
        data->setVersion(resultSet->getInt(3));
        if (!resultSet->isNull(4)) data->setGroupId(resultSet->getString(4));
        data->setStatusEnum(resultSet->getString(5));
        data->setExecuteNum(resultSet->isNull(6) ? 0 : resultSet->getInt(6));
        if (!resultSet->isNull(7)) data->setStatusChangedTime(resultSet->getString(7));
        if (!resultSet->isNull(8)) data->setPerformerCheckId(resultSet->getString(8));
        if (!resultSet->isNull(9)) data->setCheckTime(resultSet->getString(9));
        if (!resultSet->isNull(10)) data->setUpdatedBy(resultSet->getString(10));
        if (!resultSet->isNull(11)) data->setUpdatedAt(resultSet->getString(11));
        return data;
    }
};

class MedicationRequestIdMapper : public Mapper<std::string>
{
public:
    // 将查询结果的第一列映射为医嘱标识
    std::string mapper(ResultSet* resultSet) const override
    {
        return resultSet->getString(1);
    }
};

#endif // !_MEDICATIONREQUESTMAPPER_H_
