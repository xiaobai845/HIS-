#include "stdafx.h"
#include "PatientFinishController.h"
#include "domain/query/cycleCtrl1/PatientFinishQuery.h"
#include "service/cycleCtrl1/PatientFinishService.h"
#include "RedisClient.h"

PatientFinishJsonVO::Wrapper PatientFinishController::execFinishPatient(const PatientFinishQuery::Wrapper& dto, const PayloadDTO& payload)
{
    auto vo = PatientFinishJsonVO::createShared();

    //参数校验
    if (!dto)
    {
        vo->init(nullptr, RS_PARAMS_INVALID);
        return vo;
    }

    // 使用请求体中的encounterId
    oatpp::String encounterId = dto->encounterId;
    
    // 创建 Redis 客户端以获取 tenantId
    RedisClient re("127.0.0.1", 6379, "01star");
    std::string tenantId = re.execute<std::string>([](Redis* r) {
        auto res = r->hget("his:login:context:u001", "tenantId");
        return res.value();
    });


    if (tenantId.empty()|| encounterId == nullptr)
    {
        tenantId = "tenant_001";
        encounterId = "enc_001";
    }

    PatientFinishService service;
    return service.execFinishPatient(tenantId, encounterId);
}