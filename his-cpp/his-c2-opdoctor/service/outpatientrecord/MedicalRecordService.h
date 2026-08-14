#pragma once
#ifndef _EMRDOCUMENTSERVICE_H_
#define _EMRDOCUMENTSERVICE_H_

#include "domain/dto/outpatientrecord/MedicalRecordPageDTO.h"
#include "domain/query/outpatientrecord/MedicalRecordQuery.h"

class MedicalRecordService
{
public:
	// 分页查询病历文书列表
	MedicalRecordPageDTO::Wrapper queryList(const MedicalRecordQuery::Wrapper& query);
};

#endif // !_EMRDOCUMENTSERVICE_H_