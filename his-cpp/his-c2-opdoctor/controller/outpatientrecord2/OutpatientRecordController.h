#ifndef __OUTPATIENTRECORDCONTROLLER_H_
#define __OUTPATIENTRECORDCONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/outpatientrecord2/OutpatientRecordQuery.h"
#include "domain/vo/outpatientrecord2/OutpatientRecordVO.h"
#include "domain/dto/outpatientrecord2/OutpatientRecordDetailDTO.h"  // 新增

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("outpatientRecord.tags.tag")

class OutpatientRecordController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(OutpatientRecordController);
public:
    // 1. 列表查询（原接口，改名为查询列表）
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("outpatientRecord.queryList.summary"), queryRecordList,
        OutpatientRecordQuery, OutpatientRecordPageJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/outpatientrecord2", queryRecordList,
        OutpatientRecordQuery, execQueryRecordList(query));

    // 2. 新增详情接口
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("outpatientRecord.detail.summary"), getRecordDetail,
        OutpatientRecordDetailDTO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/outpatientrecord2/detail/{encounterId}", getRecordDetail,
        PATH(String, encounterId), execGetRecordDetail(encounterId, authObject->getPayload()));

private:
    OutpatientRecordPageJsonVO::Wrapper execQueryRecordList(const OutpatientRecordQuery::Wrapper& query);
    OutpatientRecordDetailDTO::Wrapper execGetRecordDetail(const String& encounterId, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif