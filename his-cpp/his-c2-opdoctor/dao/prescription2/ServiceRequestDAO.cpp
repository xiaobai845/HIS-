#include "stdafx.h"
#include "ServiceRequestDAO.h"
#include "ServiceRequestMapper.h"

namespace
{
// 服务申请单打印所需字段
const std::string SERVICE_REQUEST_COLUMNS =
    "id, encounter_id, version, status_enum, category_enum, print_count, updated_by, updated_at ";
}

PtrServiceRequestDO ServiceRequestDAO::selectById(
    const std::string& id)
{
    // 查询一条有效的服务申请单
    const std::string sql =
        "SELECT " + SERVICE_REQUEST_COLUMNS +
        "FROM wkf_service_request "
        "WHERE id=? AND is_deleted=0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id);
    return sqlSession->executeQueryOne<PtrServiceRequestDO>(
        sql, PtrServiceRequestMapper(), params);
}

PtrServiceRequestDO ServiceRequestDAO::selectByIdForUpdate(
    const std::string& id)
{
    // 锁定匹配申请单，供外层事务使用
    const std::string sql =
        "SELECT " + SERVICE_REQUEST_COLUMNS +
        "FROM wkf_service_request "
        "WHERE id=? AND is_deleted=0 FOR UPDATE";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id);
    return sqlSession->executeQueryOne<PtrServiceRequestDO>(
        sql, PtrServiceRequestMapper(), params);
}

int ServiceRequestDAO::incrementPrintCount(
    const ServiceRequestDO& data, int expectedVersion)
{
    // 仅更新打印次数和审计字段
    const std::string sql =
        "UPDATE wkf_service_request "
        "SET print_count=?, updated_by=?, updated_at=?, version=? "
        "WHERE id=? AND version=? AND is_deleted=0";
    SqlParams params;
    SQLPARAMS_PUSH(params, "i", int, data.getPrintCount());
    SQLPARAMS_PUSH(params, "s", std::string, data.getUpdatedBy());
    SQLPARAMS_PUSH(params, "s", std::string, data.getUpdatedAt());
    SQLPARAMS_PUSH(params, "i", int, data.getVersion());
    SQLPARAMS_PUSH(params, "s", std::string, data.getId());
    SQLPARAMS_PUSH(params, "i", int, expectedVersion);
    return sqlSession->executeUpdate(sql, params);
}
