#pragma once
#ifndef _PATIENT_LEAVE_DAO_
#define _PATIENT_LEAVE_DAO_

#include "BaseDAO.h"
#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "dao/cycleCtrl1/PatientLeaveMapper.h"


class PatientLeaveDAO : public BaseDAO
{
public:
    // 根据encounterId查询就诊记录（离院专用，返回完整字段）
    std::shared_ptr<AdmEncounterDO> selectEncounterById(const oatpp::String& tenantId, const oatpp::String& encounterId);

    // 更新就诊状态为离院（LEFT）
    bool updateEncounterToLeave(const oatpp::String& tenantId, const oatpp::String& encounterId);

};

#endif // !_PATIENT_LEAVE_DAO_


