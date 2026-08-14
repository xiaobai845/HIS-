#include "stdafx.h"
#include "OutpatientRecordController.h"
#include "../../service/outpatientrecord2/OutpatientRecordService.h"

// 列表查询（保持不变）
OutpatientRecordPageJsonVO::Wrapper OutpatientRecordController::execQueryRecordList(const OutpatientRecordQuery::Wrapper& query)
{
    auto jvo = OutpatientRecordPageJsonVO::createShared();
    OutpatientRecordService service;
    auto pageDto = service.listAll(query);
    jvo->success(pageDto);
    return jvo;
}

// 详情接口（直接返回 DTO）
OutpatientRecordDetailDTO::Wrapper
OutpatientRecordController::execGetRecordDetail(const String& encounterId, const PayloadDTO& payload)
{
    if (!encounterId || encounterId->empty()) {
        throw std::runtime_error("encounterId is required");
    }
    OutpatientRecordService service;
    return service.getDetail(encounterId->c_str(), payload);
}