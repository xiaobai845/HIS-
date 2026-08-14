#pragma once
#ifndef __REFUNDAPPLYDTO_H_
#define __REFUNDAPPLYDTO_H_

#include "domain/dto/doctor/Refund2DetailDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class Refund2ApplyDTO :public oatpp::DTO
{
    DTO_INIT(Refund2ApplyDTO, DTO);

    // 患者id
    API_DTO_FIELD_DEFAULT(String, patientNo, ZH_WORDS_GETTER("cyclectrl2.patient.patientNo"));

    // 勾选项
    API_DTO_FIELD_DEFAULT(List<Object<Refund2DetailDTO>>, apply, ZH_WORDS_GETTER("cyclectrl2.patient.apply"));

    // 勾选数量
    API_DTO_FIELD_DEFAULT(Int32, applyNo, ZH_WORDS_GETTER("cyclectrl2.patient.applyNo"));

    // 已选合计费用
    API_DTO_FIELD_DEFAULT(Float64, applySum, ZH_WORDS_GETTER("cyclectrl2.patient.applySum"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_QUERY_H_
