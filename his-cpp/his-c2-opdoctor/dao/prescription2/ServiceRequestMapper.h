#pragma once

#ifndef _SERVICEREQUESTMAPPER_H_
#define _SERVICEREQUESTMAPPER_H_

#include "Mapper.h"
#include "domain/do/prescription2/ServiceRequestDO.h"

class PtrServiceRequestMapper : public Mapper<PtrServiceRequestDO>
{
public:
    // 将服务申请单查询列映射为数据库对象
    PtrServiceRequestDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<ServiceRequestDO>();
        data->setId(resultSet->getString(1));
        data->setEncounterId(resultSet->getString(2));
        data->setVersion(resultSet->getInt(3));
        data->setStatusEnum(resultSet->getString(4));
        data->setCategoryEnum(resultSet->getString(5));
        data->setPrintCount(resultSet->isNull(6) ? 0 : resultSet->getInt(6));
        if (!resultSet->isNull(7)) data->setUpdatedBy(resultSet->getString(7));
        if (!resultSet->isNull(8)) data->setUpdatedAt(resultSet->getString(8));
        return data;
    }
};

#endif // !_SERVICEREQUESTMAPPER_H_
