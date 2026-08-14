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
#include "historyOrderDetailService.h"

oatpp::List<HistoryOrderDetailDTO::Wrapper> HistoryOrderDetailService::convertToDTOList(const std::list<PtrHistoryOrderDetailDO>& doList)
{
    auto dtoList = oatpp::List<HistoryOrderDetailDTO::Wrapper>::createShared();

    for (auto& doItem : doList) {
        auto dto = HistoryOrderDetailDTO::createShared();
        dto->orderId = doItem->getOrderId();
        dto->orderType = doItem->getOrderType();
        dto->orderName = doItem->getOrderName();
        dto->quantity = static_cast<v_int32>(doItem->getQuantity());
        dto->executedCount = static_cast<v_int32>(doItem->getExecutedCount());
        dto->sampleType = doItem->getSampleType();
        dto->executeHospital = doItem->getExecuteHospital();
        dto->createTime = doItem->getCreateTime();
        dto->diagnosis = doItem->getDiagnosis();
        dto->doctorName = doItem->getDoctorName();
        dto->isSkinTest = v_int32(doItem->getIsSkinTest());
        dtoList->push_back(dto);
    }

    return dtoList;
}

PageDTO<HistoryOrderDetailDTO::Wrapper>::Wrapper HistoryOrderDetailService::listAll(const HistoryOrderDetailQuery::Wrapper& query)
{
    auto doList = dao.selectWithPage(query);
    auto total = dao.count(query);
    auto dtoList = convertToDTOList(doList);

    auto pageDto = PageDTO<HistoryOrderDetailDTO::Wrapper>::createShared();
    pageDto->initAll(
        query->pageIndex,
        query->pageSize,
        v_int64(total),
        v_int64(0),
        dtoList
    );
    pageDto->calcPages();

    return pageDto;
}
