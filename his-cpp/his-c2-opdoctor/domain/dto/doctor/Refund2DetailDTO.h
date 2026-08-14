#pragma once
#ifndef __REFUNDDETAILDTO_H_
#define __REFUNDDETAILDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class Refund2DetailDTO :public oatpp::DTO
{
    DTO_INIT(Refund2DetailDTO, DTO);

    //姓名
    API_DTO_FIELD_DEFAULT(String, patientName, ZH_WORDS_GETTER("cyclectrl2.patient.patientName"));

    //支付单号
    API_DTO_FIELD_DEFAULT(String, paymentNo, ZH_WORDS_GETTER("cyclectrl2.patient.paymentNo"));

    // 收费项目名称
    API_DTO_FIELD_DEFAULT(String, itemName, ZH_WORDS_GETTER("cyclectrl2.patient.itemName"));

    //数量
    API_DTO_FIELD_DEFAULT(String, quantity, ZH_WORDS_GETTER("cyclectrl2.patient.quantity"));

    //金额
    API_DTO_FIELD_DEFAULT(String, amount, ZH_WORDS_GETTER("cyclectrl2.patient.amount"));

    //收费状态
    API_DTO_FIELD_DEFAULT(String, chargeStatus, ZH_WORDS_GETTER("cyclectrl2.patient.chargeStatus"));

    //退费状态
    API_DTO_FIELD_DEFAULT(String, refundStatus, ZH_WORDS_GETTER("cyclectrl2.patient.refundStatus"));

};

#include OATPP_CODEGEN_END(DTO)

#endif // !_QUERY_H_

