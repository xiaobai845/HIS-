#include "stdafx.h"
#include "PatientLeaveDAO.h"

std::shared_ptr<AdmEncounterDO> PatientLeaveDAO::selectEncounterById(const oatpp::String& tenantId, const oatpp::String& encounterId)
{
    //select时字段要和Mapper里对应，不然data里没有值
    std::string sql = "SELECT id, tenant_id, status_enum, is_deleted "
                      "FROM adm_encounter "
                      "WHERE id = ? AND tenant_id = ? AND is_deleted = 0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, encounterId->c_str());
    SQLPARAMS_PUSH(params, "s", std::string, tenantId ? tenantId->c_str() : "");
    return getSqlSession()->executeQueryOne<std::shared_ptr<AdmEncounterDO>>(sql, PatientLeaveMapper(), params);
}

bool PatientLeaveDAO::updateEncounterToLeave(const oatpp::String& tenantId, const oatpp::String& encounterId)
{
    // 暂离仅修改就诊状态 --> 在诊变成待诊
    std::string sql = "UPDATE adm_encounter SET status_enum = 'arrived' WHERE id = ? AND tenant_id = ? AND is_deleted = 0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, encounterId->c_str());
    SQLPARAMS_PUSH(params, "s", std::string, tenantId ? tenantId->c_str() : "");
    return getSqlSession()->executeUpdate(sql, params);
}