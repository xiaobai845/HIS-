#include "stdafx.h"
#include "PatientLeaveService.h"


PatientLeaveJsonVO::Wrapper PatientLeaveService::execLeavePatient(const oatpp::String& tenantId, const oatpp::String& encounterId)
{
    auto vo = PatientLeaveJsonVO::createShared();

    //1. 查询就诊记录
    auto encounterDO = dao.selectEncounterById(tenantId, encounterId);
    if (!encounterDO)
    {
        vo->code = 10001;
        vo->message = u8"就诊记录不存在";
        vo->data = nullptr;
        return vo;
    }

    //2. 状态校验
    oatpp::String status = encounterDO->getStatusEnum();
    if (status == "onHold" || status == "finished")
    {
        vo->code = 10002;
        vo->message = u8"该患者已离院或已完诊，不能重复操作";
        vo->data = nullptr;
        return vo;
    }

   
    //3. 执行更新到离院状态 --> 前端要求在诊变成待诊(inProgress -> arrived)
    uint64_t affectRows = dao.updateEncounterToLeave(tenantId, encounterId);
    if (affectRows == 0)
    {
        vo->code = 10004;
        vo->message = u8"离院操作失败";
        vo->data = nullptr;
        return vo;
    }

    //4. 返回成功
    auto dto = PatientLeaveDTO::createShared();
    dto->encounterId = encounterId;
    

    vo->code = 10000;
    vo->message = u8"success";
    vo->data = dto;
    return vo;
}