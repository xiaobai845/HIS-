#ifndef _MEDICALRECORD_DTO_H_
#define _MEDICALRECORD_DTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class MedicalRecordDTO : public oatpp::DTO
{
	DTO_INIT(MedicalRecordDTO, DTO);
	//病历ID
	API_DTO_FIELD_REQUIRE(String, recordId, ZH_WORDS_GETTER("medicalrecord.field.recordid"), true);
	//病历名称
	API_DTO_FIELD_REQUIRE(String, recordName, ZH_WORDS_GETTER("medicalrecord.field.recordname"), true);
	//状态
	API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("medicalrecord.field.status1"), true);
	//时间
	API_DTO_FIELD_REQUIRE(String, updatedTime, ZH_WORDS_GETTER("medicalrecord.field.updatetime"), true);
	//
	API_DTO_FIELD_REQUIRE(String, statusName, ZH_WORDS_GETTER("medicalrecord.field.statusname"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_MEDICALRECORD_DTO_H_