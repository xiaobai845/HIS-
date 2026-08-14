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
#include "historyOrderListService.h"

oatpp::List<HistoryOrderListDTO::Wrapper> HistoryOrderListService::convertToDTOList(const std::list<PtrHistoryOrderListDO>& doList)
{
    auto dtoList = oatpp::List<HistoryOrderListDTO::Wrapper>::createShared();

    for (auto& doItem : doList) {
        auto dto = HistoryOrderListDTO::createShared();
        dto->visitId = doItem->getVisitId();
        dto->visitTime = doItem->getVisitTime();
        dto->visitType = doItem->getVisitType();
        dto->mainDiagnosis = doItem->getMainDiagnosis();
        dto->doctorName = doItem->getDoctorName();
        dto->drugCount = v_int32(doItem->getDrugCount());
        dto->examCount = v_int32(doItem->getExamCount());
        dto->materialCount = v_int32(doItem->getMaterialCount());
        dtoList->push_back(dto);
    }

    return dtoList;
}

PageDTO<HistoryOrderListDTO::Wrapper>::Wrapper HistoryOrderListService::listAll(const HistoryOrderListQuery::Wrapper& query)
{
    auto doList = dao.selectWithPage(query);
    auto total = dao.count(query);
    auto dtoList = convertToDTOList(doList);

    auto pageDto = PageDTO<HistoryOrderListDTO::Wrapper>::createShared();
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
