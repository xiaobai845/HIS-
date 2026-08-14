#pragma once
#ifndef _PATIENT_FINISH_SERVICE_
#define _PATIENT_FINISH_SERVICE_


#include "dao/cycleCtrl1/PatientFinishDAO.h"
#include "domain/dto/cycleCtrl1/PatientFinishDTO.h"
#include "domain/vo/cycleCtrl1/PatientFinishVo.h"

class PatientFinishService
{
public:
    // 完诊业务入口
    PatientFinishJsonVO::Wrapper execFinishPatient(const oatpp::String& tenantId, const oatpp::String& encounterId);

private:
    PatientFinishDAO dao;
};

#endif // !_PATIENT_FINISH_SERVICE_