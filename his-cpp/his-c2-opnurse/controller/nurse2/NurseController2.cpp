
#include "stdafx.h"
#include "NurseController2.h"
#include "../../service/nurse2/nurseService2.h"


NurseExecutionResultJsonVO2::Wrapper NurseController2::execOperateNurse(const NurseOperateDTO2::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = NurseExecutionResultJsonVO2::createShared();
	// Validate required fields
	if (!dto->encounterId || !dto->itemId)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// Execute nurse operation via service
	auto result = NurseExecutionResultDTO2::createShared();
	result->itemId = dto->itemId;
	if (NurseService2().NurseOperate2(dto, payload.getUsername()))
	{
		result->success = true;
		result->newStatus = dto->state ? dto->state : oatpp::String("COMPLETED");
		result->message = "OK";
		jvo->success(result);
	}
	else
	{
		result->success = false;
		result->newStatus = nullptr;
		result->message = "Update failed: item not found or encounter mismatch";
		jvo->fail(result);
	}
	return jvo;
}

NurseExecutionResultJsonVO2::Wrapper NurseController2::execCancelNurse(const NurseCancelDTO2::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = NurseExecutionResultJsonVO2::createShared();
	// Validate required fields
	if (!dto->encounterId || !dto->itemId || !dto->cancelReason)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// Cancel nurse execution via service
	auto result = NurseExecutionResultDTO2::createShared();
	result->itemId = dto->itemId;
	if (NurseService2().NurseCancel2(dto, payload.getUsername()))
	{
		result->success = true;
		result->newStatus = "CANCELLED";
		result->message = "OK";
		jvo->success(result);
	}
	else
	{
		result->success = false;
		result->newStatus = nullptr;
		result->message = "Cancel failed: item not found or encounter mismatch";
		jvo->fail(result);
	}
	return jvo;
}
