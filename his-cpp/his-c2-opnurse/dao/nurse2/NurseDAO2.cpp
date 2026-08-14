
#include "stdafx.h"
#include "NurseDAO2.h"
#include "NurseMapper2.h"

std::string NurseDAO2::queryConditionBuilder(const NurseQuery2::Wrapper& query, SqlParams& params)
{
	std::stringstream sqlCondition;
	sqlCondition << " WHERE 1=1";
	if (query->name_code) {
		sqlCondition << " AND `bus_no`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->name_code.getValue(""));
	}
	if (query->execu_project) {
		sqlCondition << " AND `category_enum`=?";
		SQLPARAMS_PUSH(params, "s", std::string, query->execu_project.getValue(""));
	}
	if (query->use_project) {
		sqlCondition << " AND `content_json` LIKE CONCAT('%',?,'%')";
		SQLPARAMS_PUSH(params, "s", std::string, query->use_project.getValue(""));
	}
	return sqlCondition.str();
}

uint64_t NurseDAO2::count(const NurseQuery2::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT COUNT(*) FROM wkf_service_request ";
	sql += queryConditionBuilder(query, params);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<NurseDO2> NurseDAO2::selectWithPage(const NurseQuery2::Wrapper& query)
{
	SqlParams params;
	std::string sql = "SELECT id, bus_no, status_enum, content_json, execution_count, performer_id, category_enum, remark, encounter_id FROM wkf_service_request ";
	sql += queryConditionBuilder(query, params);
	sql += " ORDER BY `id` DESC ";
	sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
	return sqlSession->executeQuery<NurseDO2>(sql, NurseMapper2(), params);
}

int NurseDAO2::updateExecutionStatus(const std::string& itemId, const std::string& encounterId,
	const std::string& status, int execCount, const std::string& performerId)
{
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, status);
	SQLPARAMS_PUSH(params, "i", int, execCount);
	SQLPARAMS_PUSH(params, "s", std::string, performerId);
	SQLPARAMS_PUSH(params, "s", std::string, itemId);
	SQLPARAMS_PUSH(params, "s", std::string, encounterId);
	std::string sql = "UPDATE wkf_service_request SET status_enum=?, execution_count=?, performer_id=?, updated_at=NOW() WHERE id=? AND encounter_id=?";
	return sqlSession->executeUpdate(sql, params);
}

int NurseDAO2::updateCancelStatus(const std::string& itemId, const std::string& encounterId,
	const std::string& cancelReason, const std::string& performerId)
{
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, performerId);
	SQLPARAMS_PUSH(params, "s", std::string, cancelReason);
	SQLPARAMS_PUSH(params, "s", std::string, itemId);
	SQLPARAMS_PUSH(params, "s", std::string, encounterId);
	std::string sql = "UPDATE wkf_service_request SET status_enum='CANCELLED', performer_id=?, remark=?, updated_at=NOW() WHERE id=? AND encounter_id=?";
	return sqlSession->executeUpdate(sql, params);
}
