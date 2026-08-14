#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/20
*/
#ifndef _PRINT_JOB_CONTROLLER_
#define _PRINT_JOB_CONTROLLER_

#include "ApiHelper.h"
#include "domain/vo/opnurse/PrintJobVO.h"
#include "domain/dto/opnurse/PrintApiDTO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("print.tag.text")

#define API_TAG ZH_WORDS_GETTER("opnurse3.tags.job")

class PrintJobController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(PrintJobController);
public:
	ENDPOINT_INFO(printJob) {
		API_DEF_ADD_AUTH();
		info->summary = ZH_WORDS_GETTER("opnurse3.print.summary");
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(oatpp::Object<PrintResultJsonVO>);
		API_DEF_ADD_TAG(API_TAG);
	}
	// POST /opnurse/print
	ENDPOINT(API_M_POST, "/opnurse/print", printJob, BODY_DTO(PrintRequestDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		return createDtoResponse(Status::CODE_200, executePrint(dto));
	}

private:
	PrintResultJsonVO::Wrapper executePrint(const PrintRequestDTO::Wrapper& dto);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif // !_PRINT_JOB_CONTROLLER_
