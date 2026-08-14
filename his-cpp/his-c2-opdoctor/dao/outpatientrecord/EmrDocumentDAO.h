#pragma once
#ifndef _EMRDOCUMENTDAO_H_
#define _EMRDOCUMENTDAO_H_

#include "BaseDAO.h"
#include "domain/do/outpatientrecord/EmrDocumentDO.h"
#include"domain/query/outpatientrecord/MedicalRecordQuery.h"

class EmrDocumentDAO : public BaseDAO
{
public:
	
	uint64_t count(const MedicalRecordQuery::Wrapper& query);
	std::list<PtrEmrDocumentDO> selectList(const MedicalRecordQuery::Wrapper& query);

};

#endif // !_EMRDOCUMENTDAO_H_