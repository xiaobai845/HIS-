#pragma once
#ifndef _RECEPTIONPATIENTDAO_H_
#define _RECEPTIONPATIENTDAO_H_

#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "domain/do/cycleCtrl1/AdmPatientDO.h"
#include "domain/do/cycleCtrl1/AdmEncounterParticipantDO.h"
#include "domain/do/cycleCtrl1/AdmEncounterLocationDO.h"
#include "domain/do/cycleCtrl1/AdmHealthcareServiceDO.h"
#include "domain/do/cycleCtrl1/AdmAccountDO.h"
#include "dao/cycleCtrl1/ReceptionPatientMapper.h"
#include "domain/query/cycleCtrl1/ReceptionPatientQuery.h"
#include "domain/dto/cycleCtrl1/ReceptionPatientDTO.h"
#include "BaseDAO.h"


class ReceptionPatientDAO : public BaseDAO
{
public:
	PtrCurrentReceptionCombineDO queryReceptionPatient(const RecePatientQuery::Wrapper& query, 
							const std::string& tenantId, const std::string& practitionerId);
};



#endif // !_RECEPTIONPATIENTDAO_H_
