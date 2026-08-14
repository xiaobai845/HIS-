#pragma once
#ifndef _PATIENT_FINISH_DAO_
#define _PATIENT_FINISH_DAO_

#include "BaseDAO.h"
#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "dao/cycleCtrl1/PatientFinishMapper.h"

class PatientFinishDAO : public BaseDAO
{
public:
    // 根据encounterId查询就诊记录
    std::shared_ptr<AdmEncounterDO> selectEncounterById(const oatpp::String& tenantId, const oatpp::String& encounterId);

    // 更新就诊状态为完诊
    bool updateEncounterToFinish(const oatpp::String& tenantId, const oatpp::String& encounterId);
};

#endif // !_PATIENT_FINISH_DAO_

