#include"stdafx.h"
#include"RefundController.h"
#include"../../service/cycleCtrl2/RefundService.h"

Refund2DetailJsonVO::Wrapper Refund2Controller::executeQueryRefund(const Refund2Query::Wrapper& query)
{
	auto jvo = Refund2DetailJsonVO::createShared();
	// Parameter validation
	if (!query->num || query->num.getValue("").empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// Execute query
	auto result = RefundService().queryRefundList(query);
	jvo->success(result);
	return jvo;
}

StringJsonVO::Wrapper Refund2Controller::execApplyRefund(const Refund2ApplyDTO::Wrapper& dto, const PayloadDTO& payload)
{
	auto jvo = StringJsonVO::createShared();
	// Parameter validation
	if (!dto->patientNo || dto->patientNo.getValue("").empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	if (!dto->apply || dto->apply->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// Execute refund application
	std::string operatorId = payload.getUsername();
	bool success = RefundService().applyRefund(dto, operatorId);
	if (success)
	{
		jvo->success(nullptr);
	}
	else
	{
		jvo->fail(nullptr);
	}
	return jvo;
}
