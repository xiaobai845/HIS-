#pragma once

#include "domain/dto/diagnose/DiagnoseUsageDTO.h"
#include "domain/query/diagnose/DiagnoseUsageQuery.h"

class DiagnoseUsageService
{
public:
	PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper
		queryDiagnoseUsage(const DiagnoseUsageQuery::Wrapper& query);
};