#include "stdafx.h"
#include "MedicalRecordController.h"
#include"service/outpatientrecord/MedicalRecordService.h"

MedicalRecordPageJsonVO::Wrapper MedicalRecordController::executeQueryMedicalRecord(const MedicalRecordQuery::Wrapper& query)
{
	MedicalRecordService service;
	auto jvo = MedicalRecordPageJsonVO::createShared();
	auto page = service.queryList(query);
	if (page) {
		jvo->success(page);
	}
	else {
		jvo->fail({});
	}
	return jvo;
}
