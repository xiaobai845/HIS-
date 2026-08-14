#pragma once

#ifndef _MEDICATIONREQUESTDAO_H_
#define _MEDICATIONREQUESTDAO_H_

#include "BaseDAO.h"
#include "domain/do/prescription2/MedicationRequestDO.h"

class MedicationRequestDAO : public BaseDAO
{
public:
    // 按就诊查询一条医嘱记录
    PtrMedicationRequestDO selectById(const std::string& id,
        const std::string& encounterId);
    // 查询并锁定一条用于状态流转的医嘱记录
    PtrMedicationRequestDO selectByIdForUpdate(const std::string& id,
        const std::string& encounterId);
    // 查询并锁定同一医嘱组中的全部医嘱标识
    std::list<std::string> selectIdsByGroupForUpdate(
        const std::string& encounterId, const std::string& groupId);
    // 结合版本号和期望状态校验更新医嘱状态
    int updateStatus(const MedicationRequestDO& data, const std::string& expectedStatus,
        int expectedVersion, bool updateCheckFields);
};

#endif // !_MEDICATIONREQUESTDAO_H_
