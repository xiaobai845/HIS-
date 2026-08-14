#include "stdafx.h"
#include "outpatientrecord3Controller.h"

outpatientrecord3SaveResultVO::Wrapper
outpatientrecord33Controller::execSaveoutpatientrecord3(
	const outpatientrecord3SaveDTO::Wrapper& dto,
	const PayloadDTO& payload)
{
	return service.save(dto, payload);
}
