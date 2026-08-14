#pragma once

#include "domain/dto/diagnose/DiagnoseAddDTO.h"
#include "domain/vo/diagnose/DiagnoseAddVO.h"
#include "../include/id/UuidFacade.h"


class DiagnoseAddService
{
public:
	// insert a new diagnose record
	DiagnoseAddVO::Wrapper DiagnoseAdd(const DiagnoseAddDTO::Wrapper& dto);
};