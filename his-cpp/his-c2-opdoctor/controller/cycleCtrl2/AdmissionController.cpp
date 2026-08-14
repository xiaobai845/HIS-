#include"stdafx.h"
#include"AdmissionController.h"
#include"../../service/cycleCtrl2/AdmissionService.h"

StringJsonVO::Wrapper Admission2Controller::executeApplyAdmission(const Admission2Query::Wrapper& query)
{
	auto jvo = StringJsonVO::createShared();

	// 必填校验
	if (!query->num || query->num.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->admissionDepartment || query->admissionDepartment.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->admissionWard || query->admissionWard.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->diagnosisType || query->diagnosisType.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->admissionDiagnosis || query->admissionDiagnosis.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->admissionType || query->admissionType.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->admissionMethod || query->admissionMethod.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }
	if (!query->priority || query->priority.getValue("").empty())
		{ jvo->init(nullptr, RS_PARAMS_INVALID); return jvo; }

	std::string result = AdmissionService().applyAdmission(query, query->num.getValue(""), "");
	if (!result.empty())
		jvo->success(result);
	else
		jvo->fail(nullptr);
	return jvo;
}
