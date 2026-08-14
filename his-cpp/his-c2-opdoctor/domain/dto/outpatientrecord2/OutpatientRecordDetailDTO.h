#ifndef __OUTPATIENTRECORDDETAILDTO_H_
#define __OUTPATIENTRECORDDETAILDTO_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class OutpatientRecordDetailDTO : public oatpp::DTO
{
    DTO_INIT(OutpatientRecordDetailDTO, DTO);

    API_DTO_FIELD_REQUIRE(String, id, ZH_WORDS_GETTER("outpatientRecord.field.id"), true);
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("outpatientRecord.field.encounterId"), true);
    API_DTO_FIELD_REQUIRE(String, content, ZH_WORDS_GETTER("outpatientRecord.field.content"), false);
    API_DTO_FIELD_REQUIRE(Int64, version, ZH_WORDS_GETTER("outpatientRecord.field.version"), true);
    API_DTO_FIELD_REQUIRE(String, updatedAt, ZH_WORDS_GETTER("outpatientRecord.field.updatedAt"), true);
    API_DTO_FIELD_REQUIRE(String, patientName, ZH_WORDS_GETTER("outpatientRecord.field.patientName"), false);
    API_DTO_FIELD_REQUIRE(String, diagnosis, ZH_WORDS_GETTER("outpatientRecord.field.diagnosis"), false);
    API_DTO_FIELD_REQUIRE(String, doctorName, ZH_WORDS_GETTER("outpatientRecord.field.doctorName"), false);
    API_DTO_FIELD_REQUIRE(String, deptName, ZH_WORDS_GETTER("outpatientRecord.field.deptName"), false);
    API_DTO_FIELD_REQUIRE(String, visitDate, ZH_WORDS_GETTER("outpatientRecord.field.visitDate"), false);
    API_DTO_FIELD_REQUIRE(Boolean, editable, ZH_WORDS_GETTER("outpatientRecord.field.editable"), false);
};

#include OATPP_CODEGEN_END(DTO)
#endif