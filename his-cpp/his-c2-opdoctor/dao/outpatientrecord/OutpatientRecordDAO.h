#pragma once
#ifndef _OUTPATIENTRECORD_DAO_
#define _OUTPATIENTRECORD_DAO_

#include "BaseDAO.h"
#include "../../domain/do/outpatientrecord/OutpatientRecordMainDO.h"
#include "../../domain/do/outpatientrecord/OutpatientRecordViewDO.h"
#include "../../domain/query/outpatientrecord/OutpatientRecordQuery.h"

class OutpatientRecordDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const OutpatientRecordQuery::Wrapper& query, SqlParams& params);

public:
    uint64_t count(const OutpatientRecordQuery::Wrapper& query);
    std::list<PtrOutpatientRecordViewDO> selectWithPage(const OutpatientRecordQuery::Wrapper& query);
};

#endif // !_OUTPATIENTRECORD_DAO_