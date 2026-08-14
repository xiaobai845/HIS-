#ifndef __OUTPATIENTRECORDDTO_H_
#define __OUTPATIENTRECORDDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class OutpatientRecordDTO : public oatpp::DTO
{
    DTO_INIT(OutpatientRecordDTO, DTO);

    // 就诊ID
    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("outpatientRecord.field.id"), true);
    // 患者姓名
    API_DTO_FIELD_REQUIRE(String, patientName, ZH_WORDS_GETTER("outpatientRecord.field.patientName"), true);
    // 性别（字典编码，如 MALE/FEMALE）
    API_DTO_FIELD_REQUIRE(String, gender, ZH_WORDS_GETTER("outpatientRecord.field.gender"), false);
    // 就诊日期（使用 start_time）
    API_DTO_FIELD_REQUIRE(String, visitDate, ZH_WORDS_GETTER("outpatientRecord.field.visitDate"), true);
    // 诊断（取主诊断 description）
    API_DTO_FIELD_REQUIRE(String, diagnosis, ZH_WORDS_GETTER("outpatientRecord.field.diagnosis"), true);
    // 医生姓名（通过参与者获取）
    API_DTO_FIELD_REQUIRE(String, doctorName, ZH_WORDS_GETTER("outpatientRecord.field.doctorName"), false);
    // 科室名称（organization_id）
    API_DTO_FIELD_REQUIRE(String, deptName, ZH_WORDS_GETTER("outpatientRecord.field.deptName"), false);
    // 备注（暂未取，可填空）
    API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("outpatientRecord.field.remark"), false);
};

class OutpatientRecordPageDTO : public PageDTO<OutpatientRecordDTO::Wrapper>
{
    DTO_INIT(OutpatientRecordPageDTO, PageDTO<OutpatientRecordDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !__OUTPATIENTRECORDDTO_H_