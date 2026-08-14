
#ifndef _NURSEEXECUTIONRESULTDTO_H_
#define _NURSEEXECUTIONRESULTDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 执行或取消后的返回
class NurseExecutionResultDTO2 : public oatpp::DTO
{
	DTO_INIT(NurseExecutionResultDTO2, DTO);

	// 执行成功
	API_DTO_FIELD_REQUIRE(Boolean, success, ZH_WORDS_GETTER("nurse2.field.success"), true);
	// The item ID that was processed
	API_DTO_FIELD_REQUIRE(String, itemId, ZH_WORDS_GETTER("nurse2.field.item_id"), false);
	// 执行后的状态
	API_DTO_FIELD_REQUIRE(String, newStatus, ZH_WORDS_GETTER("nurse2.field.state"), false);
	//结果消息 成功或者失败原因
	API_DTO_FIELD_REQUIRE(String, message, ZH_WORDS_GETTER("nurse2.field.message"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_NURSEEXECUTIONRESULTDTO_H_
