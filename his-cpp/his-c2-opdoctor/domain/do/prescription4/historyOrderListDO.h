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
#ifndef _HISTORY_ORDER_LIST_DO_
#define _HISTORY_ORDER_LIST_DO_
#include "../DoInclude.h"

class HistoryOrderListDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, visitId, VisitId);
    MYSQL_SYNTHESIZE(string, visitTime, VisitTime);
    MYSQL_SYNTHESIZE(string, visitType, VisitType);
    MYSQL_SYNTHESIZE(string, mainDiagnosis, MainDiagnosis);
    MYSQL_SYNTHESIZE(string, doctorName, DoctorName);
    MYSQL_SYNTHESIZE(int, drugCount, DrugCount);
    MYSQL_SYNTHESIZE(int, examCount, ExamCount);
    MYSQL_SYNTHESIZE(int, materialCount, MaterialCount);

public:
    HistoryOrderListDO() : BaseDO("adm_encounter")
    {
        MYSQL_ADD_FIELD_PK("visit_id", "s", visitId);
        MYSQL_ADD_FIELD("visit_time", "s", visitTime);
        MYSQL_ADD_FIELD("visit_type", "s", visitType);
        MYSQL_ADD_FIELD("main_diagnosis", "s", mainDiagnosis);
        MYSQL_ADD_FIELD("doctor_name", "s", doctorName);
        MYSQL_ADD_FIELD("drug_count", "i", drugCount);
        MYSQL_ADD_FIELD("exam_count", "i", examCount);
        MYSQL_ADD_FIELD("material_count", "i", materialCount);
    }
};

typedef std::shared_ptr<HistoryOrderListDO> PtrHistoryOrderListDO;

#endif // !_HISTORY_ORDER_LIST_DO_
