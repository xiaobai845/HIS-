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
#ifndef _HISTORY_ORDER_LIST_DAO_
#define _HISTORY_ORDER_LIST_DAO_

#include "BaseDAO.h"
#include "../../domain/do/prescription4/historyOrderListDO.h"
#include "../../domain/query/prescription4/historyOrderListQuery.h"

class HistoryOrderListDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const HistoryOrderListQuery::Wrapper& query, SqlParams& params);

public:
    uint64_t count(const HistoryOrderListQuery::Wrapper& query);
    std::list<PtrHistoryOrderListDO> selectWithPage(const HistoryOrderListQuery::Wrapper& query);
};

#endif // !_HISTORY_ORDER_LIST_DAO_
