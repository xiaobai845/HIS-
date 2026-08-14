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
#ifndef _HISTORY_ORDER_LIST_MAPPER_
#define _HISTORY_ORDER_LIST_MAPPER_

#include "Mapper.h"
#include "../../domain/do/prescription4/historyOrderListDO.h"

class PtrHistoryOrderListMapper : public Mapper<PtrHistoryOrderListDO>
{
public:
    PtrHistoryOrderListDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<HistoryOrderListDO>();
        data->setVisitId(resultSet->getString("visit_id"));
        data->setVisitTime(resultSet->getString("visit_time"));
        data->setVisitType(resultSet->getString("visit_type"));
        data->setMainDiagnosis(resultSet->getString("main_diagnosis"));
        data->setDoctorName(resultSet->getString("doctor_name"));
        data->setDrugCount(resultSet->getInt("drug_count"));
        data->setExamCount(resultSet->getInt("exam_count"));
        data->setMaterialCount(resultSet->getInt("material_count"));
        return data;
    }
};

#endif // !_HISTORY_ORDER_LIST_MAPPER_
