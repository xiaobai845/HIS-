#include "stdafx.h"
#include "OutpatientRecordService.h"

inline oatpp::List<OutpatientRecordDTO::Wrapper> OutpatientRecordService::convertToDTOList(const std::list<PtrOutpatientRecordViewDO>& doList)
{
    auto dtoList = oatpp::List<OutpatientRecordDTO::Wrapper>::createShared();
    for (auto& doItem : doList) {
        auto dto = OutpatientRecordDTO::createShared();
        dto->id = doItem->getId();
        dto->patientName = doItem->getPatientName();
        dto->gender = doItem->getGender();
        dto->visitDate = doItem->getStartTime();   // 使用 start_time
        dto->diagnosis = doItem->getDiagnosis();
        dto->doctorName = doItem->getDoctorName();
        dto->deptName = doItem->getDeptName();
        dto->remark = doItem->getRemark();
        dtoList->push_back(dto);
    }
    return dtoList;
}

inline OutpatientRecordPageDTO::Wrapper OutpatientRecordService::listAll(const OutpatientRecordQuery::Wrapper& query)
{
    auto doList = dao.selectWithPage(query);
    auto total = dao.count(query);
    auto dtoList = convertToDTOList(doList);

    auto pageDto = OutpatientRecordPageDTO::createShared();
    pageDto->rows = dtoList;
    pageDto->total = total;
    pageDto->pageIndex = query->pageIndex ? query->pageIndex.getValue(1) : 1;
    pageDto->pageSize = query->pageSize ? query->pageSize.getValue(10) : 10;
    pageDto->pages = (total + pageDto->pageSize - 1) / pageDto->pageSize;
    return pageDto;
}