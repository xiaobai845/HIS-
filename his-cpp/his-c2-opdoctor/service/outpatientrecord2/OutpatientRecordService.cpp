#include "stdafx.h"
#include "OutpatientRecordService.h"

oatpp::List<OutpatientRecordDTO::Wrapper> OutpatientRecordService::convertToDTOList(const std::list<PtrOutpatientRecordViewDO>& doList)
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

OutpatientRecordPageDTO::Wrapper OutpatientRecordService::listAll(const OutpatientRecordQuery::Wrapper& query)
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


OutpatientRecordDetailDTO::Wrapper OutpatientRecordService::getDetail(const std::string& encounterId, const PayloadDTO& payload)
{
    if (encounterId.empty()) {
        throw std::runtime_error("encounterId is required");
    }

    // 测试环境：跳过权限校验（生产环境请启用）
    // std::string practitionerId = payload.getPractitionerId();
    // if (practitionerId.empty()) {
    //     practitionerId = "308791351298756608";
    // }
    // if (!dao.checkAccessPermission(encounterId, practitionerId)) {
    //     throw std::runtime_error("Access denied: You do not have permission to view this medical record");
    // }

    // ========== 2. 获取就诊摘要信息 ==========
    std::string patientName, diagnosis, doctorName, deptName, visitDate, status;
    if (!dao.getEncounterSummary(encounterId, patientName, diagnosis, doctorName, deptName, visitDate, status)) {
        throw std::runtime_error("Encounter not found");
    }

    // ========== 3. 获取病历内容 ==========
    auto detailDO = dao.selectDetailByEncounterId(encounterId);
    if (!detailDO) {
        throw std::runtime_error("Medical record content not found");
    }

    // ========== 4. 判断是否可编辑 ==========
    bool editable = (status != "FINISHED" && status != "CANCELLED" && status != "ARCHIVED");

    // ========== 5. 组装响应 ==========
    auto dto = OutpatientRecordDetailDTO::createShared();
    dto->id = detailDO->getId();
    dto->encounterId = encounterId;
    dto->content = detailDO->getContent();
    dto->version = detailDO->getVersion();
    dto->updatedAt = detailDO->getUpdatedAt();
    dto->patientName = patientName;
    dto->diagnosis = diagnosis;
    dto->doctorName = doctorName;
    dto->deptName = deptName;
    dto->visitDate = visitDate;
    dto->editable = editable;

    return dto;
}