#include "stdafx.h"
#include "PatientFinishDAO.h"
#include "PatientFinishMapper.h"

std::shared_ptr<AdmEncounterDO> PatientFinishDAO::selectEncounterById(const oatpp::String& tenantId, const oatpp::String& encounterId)
{
    // 增加 tenant_id 到 SELECT 中，保证 mapper 能读取到 tenant_id
    std::string sql = "SELECT id, tenant_id, status_enum, is_deleted FROM adm_encounter WHERE id = ? AND tenant_id = ? AND is_deleted = 0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, encounterId->c_str());
    SQLPARAMS_PUSH(params, "s", std::string, tenantId->c_str());
    return sqlSession->executeQueryOne<std::shared_ptr<AdmEncounterDO>>(sql, PatientFinishMapper(), params);
}

bool PatientFinishDAO::updateEncounterToFinish(const oatpp::String& tenantId, const oatpp::String& encounterId)
{
    // 根据主键id更新
    std::string sql = "UPDATE adm_encounter SET status_enum = 'finished', end_time = NOW() WHERE id = ? AND tenant_id = ? AND is_deleted = 0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, encounterId->c_str());
    SQLPARAMS_PUSH(params, "s", std::string, tenantId->c_str());
    uint64_t affectRows = sqlSession->executeUpdate(sql, params);
    return affectRows > 0;
}