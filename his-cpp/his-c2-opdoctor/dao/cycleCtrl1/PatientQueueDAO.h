#pragma once
#ifndef _PATIENTQUEUEDAO_H_
#define _PATIENTQUEUEDAO_H_

#include "BaseDAO.h"
#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "domain/do/cycleCtrl1/AdmPatientDO.h"
#include "domain/do/cycleCtrl1/AdmHealthcareServiceDO.h"
#include "domain/do/cycleCtrl1/AdmEncounterLocationDO.h"
#include "domain/do/cycleCtrl1/AdmEncounterParticipantDO.h"
#include "dao/cycleCtrl1/PatientQueueMapper.h"
#include "domain/query/cycleCtrl1/PatientQueueQuery.h"
#include <list>

class PatientQueueDAO : public BaseDAO
{
public:
	//日期是必须传入，患者名搜索是可选的，状态是可选的（默认是全部）
	std::list<PtrPatientQueueCombineDO> queryPatientQueue(const PatientQueueQuery::Wrapper& query,
		const std::string& tenantId,const std::string& practitionerId);
		
	
};


#endif // !PATIENTQUEUEDAO_H_
