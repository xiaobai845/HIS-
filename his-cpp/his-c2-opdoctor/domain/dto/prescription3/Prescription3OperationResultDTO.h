#pragma once

#ifndef _PRESCRIPTION3_OPERATION_RESULT_DTO_H_
#define _PRESCRIPTION3_OPERATION_RESULT_DTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class Prescription3AffectedOrderDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3AffectedOrderDTO, DTO);

    API_DTO_FIELD(String, adviceId,
        ZH_WORDS_GETTER("prescription3.field.adviceId"), true,
        "331100000000000001");
    API_DTO_FIELD(String, type,
        ZH_WORDS_GETTER("prescription3.field.orderType"), true,
        "MEDICATION");
    API_DTO_FIELD(String, groupId,
        ZH_WORDS_GETTER("prescription3.field.resultGroupId"), true,
        "331234567890123456");
};

class Prescription3DeleteResultDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3DeleteResultDTO, DTO);

    API_DTO_FIELD(Boolean, success,
        ZH_WORDS_GETTER("prescription3.field.success"), true, true);
    API_DTO_FIELD(Int32, affectedCount,
        ZH_WORDS_GETTER("prescription3.field.affectedCount"), true, 3);
    API_DTO_FIELD(List<Object<Prescription3AffectedOrderDTO>>,
        affectedOrders,
        ZH_WORDS_GETTER("prescription3.field.affectedOrders"), true, {});
    API_DTO_FIELD(Int32, version,
        ZH_WORDS_GETTER("prescription3.field.resultVersion"), true, 3);
    API_DTO_FIELD(String, updatedAt,
        ZH_WORDS_GETTER("prescription3.field.updatedAt"), true,
        "2026-07-18 10:30:00.123456");
    API_DTO_FIELD(String, message,
        ZH_WORDS_GETTER("prescription3.field.message"), true,
        "Orders deleted successfully");
};

class Prescription3MergeResultDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3MergeResultDTO, DTO);

    API_DTO_FIELD(Boolean, success,
        ZH_WORDS_GETTER("prescription3.field.success"), true, true);
    API_DTO_FIELD(Int32, affectedCount,
        ZH_WORDS_GETTER("prescription3.field.affectedCount"), true, 3);
    API_DTO_FIELD(String, groupId,
        ZH_WORDS_GETTER("prescription3.field.groupId"), true,
        "331234567890123456");
    API_DTO_FIELD(List<Object<Prescription3AffectedOrderDTO>>,
        affectedOrders,
        ZH_WORDS_GETTER("prescription3.field.affectedOrders"), true, {});
    API_DTO_FIELD(Int32, version,
        ZH_WORDS_GETTER("prescription3.field.resultVersion"), true, 3);
    API_DTO_FIELD(String, updatedAt,
        ZH_WORDS_GETTER("prescription3.field.updatedAt"), true,
        "2026-07-18 10:30:00.123456");
    API_DTO_FIELD(String, message,
        ZH_WORDS_GETTER("prescription3.field.message"), true,
        "Orders merged successfully");
};

class Prescription3SplitResultDTO : public oatpp::DTO
{
    DTO_INIT(Prescription3SplitResultDTO, DTO);

    API_DTO_FIELD(Boolean, success,
        ZH_WORDS_GETTER("prescription3.field.success"), true, true);
    API_DTO_FIELD(Int32, affectedCount,
        ZH_WORDS_GETTER("prescription3.field.affectedCount"), true, 3);
    API_DTO_FIELD(List<Object<Prescription3AffectedOrderDTO>>,
        affectedOrders,
        ZH_WORDS_GETTER("prescription3.field.affectedOrders"), true, {});
    API_DTO_FIELD(Int32, version,
        ZH_WORDS_GETTER("prescription3.field.resultVersion"), true, 3);
    API_DTO_FIELD(String, updatedAt,
        ZH_WORDS_GETTER("prescription3.field.updatedAt"), true,
        "2026-07-18 10:30:00.123456");
    API_DTO_FIELD(String, message,
        ZH_WORDS_GETTER("prescription3.field.message"), true,
        "Order group split successfully");
};

#include OATPP_CODEGEN_END(DTO)

#endif
