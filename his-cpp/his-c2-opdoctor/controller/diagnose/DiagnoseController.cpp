#include "stdafx.h"

#include "DiagnoseController.h"

#include "service/diagnose/DiagnoseAddService.h"
#include "service/diagnose/DiagnoseDeleteService.h"
#include "service/diagnose/DiagnoseUsageService.h"
#include "service/diagnose/PatientDiagnoseService.h"

DiagnoseAddJsonVO::Wrapper
DiagnoseController::execDiagnoseAdd(const DiagnoseAddDTO::Wrapper& dto)
{
	DiagnoseAddJsonVO::Wrapper vo = DiagnoseAddJsonVO::createShared();

	if (!dto)
	{
		vo->fail({});
		return vo;
	}

	DiagnoseAddService das;
	DiagnoseAddVO::Wrapper data = das.DiagnoseAdd(dto);
	
	if (data)
		vo->success(data);
	else
		vo->fail({});

	return vo;
}

DiagnoseDeleteJsonVO::Wrapper
DiagnoseController::execDiagnoseDelete(const String& id)
{
	DiagnoseDeleteJsonVO::Wrapper vo = DiagnoseDeleteJsonVO::createShared();

	if (!id || id->empty())
	{
		vo->fail({});
		return vo;
	}

	DiagnoseDeleteService dds;
	DiagnoseDeleteVO::Wrapper data = dds.deleteDiagnose(id);

	if (data)
		vo->success(data);
	else
		vo->fail({});

	return vo;
}

DiagnoseUsagePageJsonVO::Wrapper
DiagnoseController::execQueryDiagnoseUsage(const DiagnoseUsageQuery::Wrapper& query)
{
	DiagnoseUsagePageJsonVO::Wrapper vo = DiagnoseUsagePageJsonVO::createShared();

	if (!query)
	{
		vo->fail({});
		return vo;
	}

	DiagnoseUsageService dus;
	PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper data = dus.queryDiagnoseUsage(query);

	if (data)
		vo->success(data);
	else
		vo->fail({});

	return vo;
}

PatientDiagnosePageJsonVO::Wrapper
DiagnoseController::execQueryPatientDiagnose(const PatientDiagnoseQuery::Wrapper& query)
{
	PatientDiagnosePageJsonVO::Wrapper vo = PatientDiagnosePageJsonVO::createShared();

	if (!query)
	{
		vo->fail({});
		return vo;
	}

	PatientDiagnoseService pds;
	PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper data = pds.queryPatientDiagnose(query);

	if (data)
		vo->success(data);
	else
		vo->fail({});

	return vo;
}