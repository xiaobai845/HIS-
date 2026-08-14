#pragma once
#ifndef _OUTPATIENTRECORD_SERVICE_
#define _OUTPATIENTRECORD_SERVICE_

#include "../../domain/query/outpatientrecord/OutpatientRecordQuery.h"
#include "../../domain/vo/outpatientrecord/OutpatientRecordVO.h"
#include "../../domain/dto/outpatientrecord/OutpatientRecordDTO.h"
#include "../../dao/outpatientrecord/OutpatientRecordDAO.h"

class OutpatientRecordService
{
private:
    OutpatientRecordDAO dao;
    oatpp::List<OutpatientRecordDTO::Wrapper> convertToDTOList(const std::list<PtrOutpatientRecordViewDO>& doList);

public:
    OutpatientRecordPageDTO::Wrapper listAll(const OutpatientRecordQuery::Wrapper& query);
};

#endif // !_OUTPATIENTRECORD_SERVICE_