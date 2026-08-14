#pragma once

#include "domain/dto/diagnose/DiagnoseAddDTO.h"
#include "domain/query/diagnose/DiagnoseUsageQuery.h"
#include "domain/query/diagnose/PatientDiagnoseQuery.h"
#include "domain/vo/diagnose/DiagnoseAddVO.h"
#include "domain/vo/diagnose/DiagnoseDeleteVO.h"
#include "domain/vo/diagnose/DiagnoseUsageVO.h"
#include "domain/vo/diagnose/PatientDiagnoseVO.h"

using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("diagnose.tag")

class DiagnoseController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(DiagnoseController);

public:
	// diagnose add controller
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("diagnose.add.summary"),
		diagnoseAdd,
		DiagnoseAddJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/opdoctor/diagnose/add",
		diagnoseAdd,
		BODY_DTO(DiagnoseAddDTO::Wrapper, dto),
		execDiagnoseAdd(dto)
	);

	// diagnose delete controller
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("diagnose.delete.summary"),
		diagnoseDelete,
		DiagnoseDeleteJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_AUTH(
		API_M_DEL,
		"/opdoctor/diagnose/delete/{id}",
		diagnoseDelete,
		PATH(String, id),
		execDiagnoseDelete(id)
	);

	// diagnose usage controller
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("diagnose.usage.summary"),
		queryDiagnoseUsage,
		DiagnoseUsageQuery,
		DiagnoseUsagePageJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,
		"/opdoctor/diagnose/usage",
		queryDiagnoseUsage,
		DiagnoseUsageQuery,
		execQueryDiagnoseUsage(query)
	);

	// patient diagnose controller
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("diagnose.patient.summary"),
		queryPatientDiagnose,
		PatientDiagnoseQuery,
		PatientDiagnosePageJsonVO::Wrapper,
		API_TAG
	);
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,
		"/opdoctor/diagnose/patient",
		queryPatientDiagnose,
		PatientDiagnoseQuery,
		execQueryPatientDiagnose(query)
	);

private:
	DiagnoseAddJsonVO::Wrapper execDiagnoseAdd(const DiagnoseAddDTO::Wrapper& dto);
	DiagnoseDeleteJsonVO::Wrapper execDiagnoseDelete(const String& id);
	DiagnoseUsagePageJsonVO::Wrapper
		execQueryDiagnoseUsage(const DiagnoseUsageQuery::Wrapper& query);
	PatientDiagnosePageJsonVO::Wrapper
		execQueryPatientDiagnose(const PatientDiagnoseQuery::Wrapper& query);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)