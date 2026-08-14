#pragma once
#ifndef _OUTPATIENTRECORD_DETAIL_DO_
#define _OUTPATIENTRECORD_DETAIL_DO_

#include "../DoInclude.h"

/**
 * 病历详情 DO（对应 emr_document 表，或类似病历内容表）
 * 假设字段：encounter_id, content, version, updated_at
 */
class OutpatientRecordDetailDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);                  // 文档ID
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
    MYSQL_SYNTHESIZE(string, content, Content);        // 富文本内容
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(int64_t, version, Version);       // 乐观锁

public:
    OutpatientRecordDetailDO() : BaseDO("emr_document")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
        MYSQL_ADD_FIELD("content", "s", content);
        MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
        MYSQL_ADD_FIELD("version", "i", version);
    }
};

typedef std::shared_ptr<OutpatientRecordDetailDO> PtrOutpatientRecordDetailDO;

#endif