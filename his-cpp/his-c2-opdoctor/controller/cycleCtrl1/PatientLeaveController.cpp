#include "stdafx.h"
#include "PatientLeaveController.h"
#include "service/cycleCtrl1/PatientLeaveService.h"
#include "RedisClient.h"

PatientLeaveJsonVO::Wrapper PatientLeaveController::execLeavePatient(const PatientLeaveQuery::Wrapper& dto, const PayloadDTO& payload)
{
    auto vo = PatientLeaveJsonVO::createShared();

    //请求体获取参数
    oatpp::String encounterId = dto->encounterId;
   
    // 创建 Redis 客户端以获取 tenantId
    RedisClient re("127.0.0.1", 6379, "01star");
    std::string tenantId = re.execute<std::string>([](Redis* r) {
        auto res = r->hget("his:login:context:u001", "tenantId");
        return res.value();
    });

    if(tenantId.empty() || encounterId == nullptr)
    {
        tenantId = "tenant_001";
        encounterId = "enc_002";
	}

    PatientLeaveService service;
    return service.execLeavePatient(tenantId, encounterId);
}