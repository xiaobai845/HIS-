#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/07/27

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _HISTORY_ORDER_DETAIL_MAPPER_
#define _HISTORY_ORDER_DETAIL_MAPPER_

#include "Mapper.h"
#include "../../domain/do/prescription4/historyOrderDetailDO.h"

class PtrHistoryOrderDetailMapper : public Mapper<PtrHistoryOrderDetailDO>
{
public:
    PtrHistoryOrderDetailDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<HistoryOrderDetailDO>();
        data->setOrderId(resultSet->getString("order_id"));
        data->setOrderType(resultSet->getString("order_type"));
        data->setOrderName(resultSet->getString("order_name"));
        data->setQuantity(resultSet->getDouble("quantity"));
        data->setExecutedCount(resultSet->getDouble("executed_count"));
        data->setSampleType(resultSet->getString("sample_type"));
        data->setExecuteHospital(resultSet->getString("execute_hospital"));
        data->setCreateTime(resultSet->getString("create_time"));
        data->setDiagnosis(resultSet->getString("diagnosis"));
        data->setDoctorName(resultSet->getString("doctor_name"));
        data->setIsSkinTest(resultSet->getInt("is_skin_test"));
        return data;
    }
};

#endif // !_HISTORY_ORDER_DETAIL_MAPPER_
