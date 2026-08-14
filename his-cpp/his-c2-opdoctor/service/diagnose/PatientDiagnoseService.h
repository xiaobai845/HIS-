#pragma once

#include "domain/query/diagnose/PatientDiagnoseQuery.h"
#include "domain/dto/diagnose/DiagnoseUsageDTO.h"

class PatientDiagnoseService
{
public:
	PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper
		queryPatientDiagnose(const PatientDiagnoseQuery::Wrapper& query);
};