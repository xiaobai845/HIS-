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
#include "stdafx.h"
#include "historyOrderListController.h"
#include "../../service/prescription4/historyOrderListService.h"
#include "domain/dto/PageDTO.h"

HistoryOrderListPageJsonVO::Wrapper HistoryOrderListController::execQueryHistoryOrderList(const HistoryOrderListQuery::Wrapper& query)
{
    auto jvo = HistoryOrderListPageJsonVO::createShared();
    typedef PageDTO<HistoryOrderListDTO::Wrapper>::Wrapper EmptyPageT;

    if (!query) {
        jvo->init(EmptyPageT::createShared(), RS_FAIL);
        return jvo;
    }
    if (query->patientId.getValue("").empty()) {
        jvo->init(EmptyPageT::createShared(), RS_FAIL);
        return jvo;
    }

    HistoryOrderListService service;
    auto pageDto = service.listAll(query);

    jvo->success(pageDto);
    return jvo;
}
