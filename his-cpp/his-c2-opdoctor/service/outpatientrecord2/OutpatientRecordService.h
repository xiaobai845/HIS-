#pragma once
#ifndef _OUTPATIENTRECORD_SERVICE_
#define _OUTPATIENTRECORD_SERVICE_

#include "../../domain/query/outpatientrecord2/OutpatientRecordQuery.h"
#include "../../domain/vo/outpatientrecord2/OutpatientRecordVO.h"
#include "../../domain/dto/outpatientrecord2/OutpatientRecordDTO.h"
#include "../../domain/dto/outpatientrecord2/OutpatientRecordDetailDTO.h"
#include "../../dao/outpatientrecord2/OutpatientRecordDAO.h"
class OutpatientRecordService
{
private:
    OutpatientRecordDAO dao;
    oatpp::List<OutpatientRecordDTO::Wrapper> convertToDTOList(const std::list<PtrOutpatientRecordViewDO>& doList);

public:
    OutpatientRecordPageDTO::Wrapper listAll(const OutpatientRecordQuery::Wrapper& query);
    // 新增详情方法
    OutpatientRecordDetailDTO::Wrapper getDetail(const std::string& encounterId, const PayloadDTO& payload);
};

#endif // !_OUTPATIENTRECORD_SERVICE_