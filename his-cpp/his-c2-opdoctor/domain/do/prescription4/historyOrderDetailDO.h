#pragma once
#ifndef _HISTORY_ORDER_DETAIL_DO_
#define _HISTORY_ORDER_DETAIL_DO_
#include "../DoInclude.h"

class HistoryOrderDetailDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, orderId, OrderId);
    MYSQL_SYNTHESIZE(string, orderType, OrderType);
    MYSQL_SYNTHESIZE(string, orderName, OrderName);
    MYSQL_SYNTHESIZE(double, quantity, Quantity);          // int ¡ú double
    MYSQL_SYNTHESIZE(double, executedCount, ExecutedCount); // int ¡ú double
    MYSQL_SYNTHESIZE(string, sampleType, SampleType);
    MYSQL_SYNTHESIZE(string, executeHospital, ExecuteHospital);
    MYSQL_SYNTHESIZE(string, createTime, CreateTime);
    MYSQL_SYNTHESIZE(string, diagnosis, Diagnosis);
    MYSQL_SYNTHESIZE(string, doctorName, DoctorName);
    MYSQL_SYNTHESIZE(int, isSkinTest, IsSkinTest);

public:
    HistoryOrderDetailDO() : BaseDO("med_medication_request")
    {
        MYSQL_ADD_FIELD_PK("order_id", "s", orderId);
        MYSQL_ADD_FIELD("order_type", "s", orderType);
        MYSQL_ADD_FIELD("order_name", "s", orderName);
        MYSQL_ADD_FIELD("quantity", "d", quantity);        // "i" ¡ú "d"
        MYSQL_ADD_FIELD("executed_count", "d", executedCount); // "i" ¡ú "d"
        MYSQL_ADD_FIELD_NULLABLE("sample_type", "s", sampleType, false);
        MYSQL_ADD_FIELD("execute_hospital", "s", executeHospital);
        MYSQL_ADD_FIELD("create_time", "s", createTime);
        MYSQL_ADD_FIELD("diagnosis", "s", diagnosis);
        MYSQL_ADD_FIELD("doctor_name", "s", doctorName);
        MYSQL_ADD_FIELD_NULLABLE("is_skin_test", "i", isSkinTest, false);
    }
};

typedef std::shared_ptr<HistoryOrderDetailDO> PtrHistoryOrderDetailDO;

#endif // !_HISTORY_ORDER_DETAIL_DO_