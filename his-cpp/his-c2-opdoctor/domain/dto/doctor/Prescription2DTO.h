#pragma once
#ifndef __PRESCRIPTION2DTO_H_
#define __PRESCRIPTION2DTO_H_

#include "domain/dto/doctor/Prescription2DetailDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class Prescription2DTO :public oatpp::DTO
{
    DTO_INIT(Prescription2DTO, DTO);

    // 处方列表
    API_DTO_FIELD_DEFAULT(List<Object<Prescription2DetailDTO>>, prescription, ZH_WORDS_GETTER("cyclectrl2.prescription.tag"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !__PRESCRIPTION2DTO_H_
