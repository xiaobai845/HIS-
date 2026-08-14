#include "stdafx.h"
#include "PatientQueueController.h"
#include "service/cycleCtrl1/PatientQueueService.h"
#include "RedisClient.h"
#include "../../../.skeleton/Macros.h"


PatientQueueJsonVO::Wrapper PatientQueueController::execQueryQueue(const PatientQueueQuery::Wrapper& query, const PayloadDTO& payload)
{
    auto jvo = PatientQueueJsonVO::createShared();

    // 必须的 query 和 date
    if (!query || !query->date) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 从 payload 获取 userId ，后续可能需要
    /*std::string userId = payload.getId();
    if (userId.empty()) {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }*/

    // 从 payload 获取 practitionerId
    std::string practitionerId = payload.getPractitionerId();

    // 创建 Redis 客户端以获取 tenantId
    RedisClient re("127.0.0.1", 6379, "01star");
    std::string tenantId = re.execute<std::string>([](Redis* r) {
        auto res = r->hget("his:login:context:u001", "tenantId");
        return res.value();
    });

    // 如果 practitionerId 或 tenantId 为空，则使用默认值
    if (practitionerId.empty() || tenantId.empty())
    {
        practitionerId = "";
        tenantId = "tenant_001";
    }

    // 调用 service 获取数据
    PatientQueueService service;
    auto dto = service.getPatientQueueList(query, tenantId, practitionerId);

    jvo->success(dto);
    return jvo;
}