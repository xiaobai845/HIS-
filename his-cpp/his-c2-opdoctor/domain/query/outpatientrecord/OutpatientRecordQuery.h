#ifndef _OUTPATIENTRECORDQUERY_H_
#define _OUTPATIENTRECORDQUERY_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class OutpatientRecordQuery : public PageQuery
{
    DTO_INIT(OutpatientRecordQuery, PageQuery);

    // 患者姓名（模糊）
    API_DTO_FIELD_REQUIRE(String, patientName, ZH_WORDS_GETTER("outpatientRecord.field.patientName"), false);
    // 就诊开始日期（格式 yyyy-MM-dd）
    API_DTO_FIELD_REQUIRE(String, startDate, ZH_WORDS_GETTER("outpatientRecord.field.startDate"), false);
    // 就诊结束日期
    API_DTO_FIELD_REQUIRE(String, endDate, ZH_WORDS_GETTER("outpatientRecord.field.endDate"), false);
    // 诊断名称（模糊）
    API_DTO_FIELD_REQUIRE(String, diagnosis, ZH_WORDS_GETTER("outpatientRecord.field.diagnosis"), false);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_OUTPATIENTRECORDQUERY_H_