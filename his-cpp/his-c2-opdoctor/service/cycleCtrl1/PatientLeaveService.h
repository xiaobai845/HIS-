#pragma once
#ifndef _PATIENT_LEAVE_SERVICE_
#define _PATIENT_LEAVE_SERVICE_

#include "dao/cycleCtrl1/PatientLeaveDAO.h"
#include "domain/dto/cycleCtrl1/PatientLeaveDTO.h"
#include "domain/vo/cycleCtrl1/PatientLeaveVo.h"


class PatientLeaveService
{
public:
    // ÔÝÀëÒµÎñÈë¿Ú
    PatientLeaveJsonVO::Wrapper execLeavePatient(const oatpp::String& tenantId, const oatpp::String& encounterId);

private:
    PatientLeaveDAO dao; 
};

#endif // !_PATIENT_LEAVE_SERVICE_
