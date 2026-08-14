#pragma once

#include "domain/vo/diagnose/DiagnoseDeleteVO.h"
#include "oatpp/web/server/api/ApiController.hpp"

class DiagnoseDeleteService
{
public:
	// delete a diagnose record by id (deletedBy defaults to system)
	DiagnoseDeleteVO::Wrapper deleteDiagnose(const std::string& id);
	// delete a diagnose record by id with specified deletedBy
	DiagnoseDeleteVO::Wrapper deleteDiagnose(const std::string& id, const std::string& deletedBy);
};