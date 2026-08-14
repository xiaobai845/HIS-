#pragma once
#ifndef _OUTPATIENTRECORD_DAO_
#define _OUTPATIENTRECORD_DAO_

#include "BaseDAO.h"
#include "../../domain/do/outpatientrecord2/OutpatientRecordMainDO.h"
#include "../../domain/do/outpatientrecord2/OutpatientRecordViewDO.h"
#include "../../domain/do/outpatientrecord2/OutpatientRecordDetailDO.h"
#include "../../domain/query/outpatientrecord2/OutpatientRecordQuery.h"

class OutpatientRecordDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const OutpatientRecordQuery::Wrapper& query, SqlParams& params);

public:
    uint64_t count(const OutpatientRecordQuery::Wrapper& query);
    std::list<PtrOutpatientRecordViewDO> selectWithPage(const OutpatientRecordQuery::Wrapper& query);
    // 在 public 区域添加
    PtrOutpatientRecordDetailDO selectDetailByEncounterId(const std::string& encounterId);
    // 获取就诊摘要信息（用于详情响应）
    bool getEncounterSummary(const std::string& encounterId, std::string& patientName, std::string& diagnosis,
        std::string& doctorName, std::string& deptName, std::string& visitDate, std::string& status);
    // 校验医生是否有权访问该就诊
    bool checkAccessPermission(const std::string& encounterId, const std::string& practitionerId);
};

#endif // !_OUTPATIENTRECORD_DAO_