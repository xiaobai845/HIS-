#pragma once

#ifndef _SERVICEREQUESTDAO_H_
#define _SERVICEREQUESTDAO_H_

#include "BaseDAO.h"
#include "domain/do/prescription2/ServiceRequestDO.h"

class ServiceRequestDAO : public BaseDAO
{
public:
    // 查询一条服务申请单
    PtrServiceRequestDO selectById(const std::string& id);
    // 查询并锁定一条用于打印操作的服务申请单
    PtrServiceRequestDO selectByIdForUpdate(const std::string& id);
    // 通过版本校验增加打印次数
    int incrementPrintCount(const ServiceRequestDO& data, int expectedVersion);
};

#endif // !_SERVICEREQUESTDAO_H_
