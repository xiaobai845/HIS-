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
#ifndef _HISTORY_ORDER_DETAIL_DAO_
#define _HISTORY_ORDER_DETAIL_DAO_

#include "BaseDAO.h"
#include "../../domain/do/prescription4/historyOrderDetailDO.h"
#include "../../domain/query/prescription4/historyOrderDetailQuery.h"

class HistoryOrderDetailDAO : public BaseDAO
{
private:
    std::string buildFullQuerySql(const HistoryOrderDetailQuery::Wrapper& query, SqlParams& params);

public:
    uint64_t count(const HistoryOrderDetailQuery::Wrapper& query);
    std::list<PtrHistoryOrderDetailDO> selectWithPage(const HistoryOrderDetailQuery::Wrapper& query);
};

#endif // !_HISTORY_ORDER_DETAIL_DAO_
