#include "stdafx.h"
#include "MedicationRequestDAO.h"
#include "MedicationRequestMapper.h"

namespace
{
// 医嘱状态流转所需字段
const std::string MEDICATION_REQUEST_COLUMNS =
    "id, encounter_id, version, group_id, status_enum, execute_num, "
    "status_changed_time, performer_check_id, check_time, updated_by, updated_at ";
}

PtrMedicationRequestDO MedicationRequestDAO::selectById(
    const std::string& id, const std::string& encounterId)
{
    // 将查询限制在指定就诊范围内
    const std::string sql =
        "SELECT " + MEDICATION_REQUEST_COLUMNS +
        "FROM med_medication_request "
        "WHERE id=? AND encounter_id=? AND is_deleted=0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id);
    SQLPARAMS_PUSH(params, "s", std::string, encounterId);
    return sqlSession->executeQueryOne<PtrMedicationRequestDO>(
        sql, PtrMedicationRequestMapper(), params);
}

PtrMedicationRequestDO MedicationRequestDAO::selectByIdForUpdate(
    const std::string& id, const std::string& encounterId)
{
    // 锁定匹配记录，供外层事务使用
    const std::string sql =
        "SELECT " + MEDICATION_REQUEST_COLUMNS +
        "FROM med_medication_request "
        "WHERE id=? AND encounter_id=? AND is_deleted=0 FOR UPDATE";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id);
    SQLPARAMS_PUSH(params, "s", std::string, encounterId);
    return sqlSession->executeQueryOne<PtrMedicationRequestDO>(
        sql, PtrMedicationRequestMapper(), params);
}

std::list<std::string> MedicationRequestDAO::selectIdsByGroupForUpdate(
    const std::string& encounterId, const std::string& groupId)
{
    // 校验医嘱组完整性前锁定其中的全部记录
    const std::string sql =
        "SELECT id FROM med_medication_request "
        "WHERE encounter_id=? AND group_id=? AND is_deleted=0 FOR UPDATE";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, encounterId);
    SQLPARAMS_PUSH(params, "s", std::string, groupId);
    return sqlSession->executeQuery<std::string>(
        sql, MedicationRequestIdMapper(), params);
}

int MedicationRequestDAO::updateStatus(const MedicationRequestDO& data,
    const std::string& expectedStatus, int expectedVersion,
    bool updateCheckFields)
{
    // 构建带条件的更新，防止并发状态变更
    std::string sql =
        "UPDATE med_medication_request "
        "SET status_enum=?, status_changed_time=?, updated_by=?, updated_at=?";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, data.getStatusEnum());
    SQLPARAMS_PUSH(params, "s", std::string, data.getStatusChangedTime());
    SQLPARAMS_PUSH(params, "s", std::string, data.getUpdatedBy());
    SQLPARAMS_PUSH(params, "s", std::string, data.getUpdatedAt());

    if (updateCheckFields)
    {
        // 签发操作还会记录签发用户和签发时间
        sql += ", performer_check_id=?, check_time=?";
        SQLPARAMS_PUSH(params, "s", std::string, data.getPerformerCheckId());
        SQLPARAMS_PUSH(params, "s", std::string, data.getCheckTime());
    }

    sql += " , version=? "
        "WHERE id=? AND encounter_id=? AND version=? "
        "AND status_enum=? AND is_deleted=0";
    SQLPARAMS_PUSH(params, "i", int, data.getVersion());
    SQLPARAMS_PUSH(params, "s", std::string, data.getId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getEncounterId());
    SQLPARAMS_PUSH(params, "i", int, expectedVersion);
    SQLPARAMS_PUSH(params, "s", std::string, expectedStatus);
    return sqlSession->executeUpdate(sql, params);
}
