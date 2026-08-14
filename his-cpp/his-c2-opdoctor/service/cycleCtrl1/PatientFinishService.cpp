#include "stdafx.h"
#include "PatientFinishService.h"

PatientFinishJsonVO::Wrapper PatientFinishService::execFinishPatient(const oatpp::String& tenantId, const oatpp::String& encounterId)
{
    //1. 查询就诊记录
    auto encounterDO = dao.selectEncounterById(tenantId, encounterId);
    if (!encounterDO)
    {
        auto vo = PatientFinishJsonVO::createShared();
        vo->code = 10001;
        vo->message = u8"就诊记录不存在";
        vo->data = nullptr;
        return vo;
    }

    //2. 业务状态校验
    oatpp::String status = encounterDO->getStatusEnum();
    if (status == "finished")
    {
        auto vo = PatientFinishJsonVO::createShared();
        vo->code = 10002;
        vo->message = u8"该患者已经完诊，请勿重复操作";
        vo->data = nullptr;
        return vo;
    }
    
    if (status != "arrived" && status != "onHold")
    {
        auto vo = PatientFinishJsonVO::createShared();
        vo->code = 10003;
        vo->message = u8"当前就诊状态不允许执行完诊";
        vo->data = nullptr;
        return vo;
    }

    //3. 执行更新
    bool updateOk = dao.updateEncounterToFinish(tenantId, encounterId);
    if (!updateOk)
    {
        auto vo = PatientFinishJsonVO::createShared();
        vo->code = 10004;
        vo->message = u8"完诊操作失败";
        vo->data = nullptr;
        return vo;
    }

    //4. 成功返回
    auto dto = PatientFinishDTO::createShared();
    dto->encounterId = encounterId;
    dto->visitStatus = "finished";

    auto vo = PatientFinishJsonVO::createShared();
    vo->code = 10000;
    vo->message = u8"success";
    vo->data = dto;
    return vo;
}