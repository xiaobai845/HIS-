#include "stdafx.h"
#include "ReceptionPatientController.h"
#include "service/cycleCtrl1/ReceptionPatientService.h"
#include "RedisClient.h"


RecePatientJsonVO::Wrapper RecePatientController::execQueryRece(const RecePatientQuery::Wrapper& query, const PayloadDTO& payload)
{
    auto jvo = RecePatientJsonVO::createShared();

    // 参数校验
    if (!query || !query->date)
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }

    // 从payload读取practitionerId
    std::string practitionerId = payload.getPractitionerId();

    // 创建 Redis 客户端以获取 tenantId
    RedisClient re("127.0.0.1", 6379, "01star");
    std::string tenantId = re.execute<std::string>([](Redis* r) {
        auto res = r->hget("his:login:context:u001", "tenantId");
        return res.value();
        });

	//如果practitionerid和tenantId为空，则使用默认值
    if (practitionerId.empty() || tenantId.empty())
    {
        practitionerId = "doc_001";
        tenantId = "tenant_001";
    }

    auto dto = ReceptionPatientService().getRecePatient(query, tenantId, practitionerId);

    // 包装为成功响应
    jvo->success(dto);
    return jvo;
}