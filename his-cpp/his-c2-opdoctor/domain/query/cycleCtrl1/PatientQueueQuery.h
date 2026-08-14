#pragma once
#ifndef _QUEUEQUERY_H
#define _QUEUEQUERY_H

#include "../../GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)


//患者队列查询query类
class PatientQueueQuery : public oatpp::DTO
{
	DTO_INIT(PatientQueueQuery,DTO);

	//日期
	API_DTO_FIELD_REQUIRE(String, date, ZH_WORDS_GETTER("queue.query.date"), true);
	//搜索患者
	API_DTO_FIELD_REQUIRE(String, patientName, ZH_WORDS_GETTER("queue.query.patientName"), false);
	//visitStatus -> 待诊、在诊、完诊
	API_DTO_FIELD_REQUIRE(String, visitStatus, ZH_WORDS_GETTER("queue.query.visitStatus"), false);

	
};

#include OATPP_CODEGEN_END(DTO)


#endif // !_QUEUEQUERY_H
