#include "stdafx.h"
#include "chinapres3ChargeItemDAO.h"
#include "chinapres3ChargeItemMapper.h"
#include "SqlSession.h"
#include <sstream>

#define QUERY_HEAD "SELECT id,service_table,service_id,patient_id,encounter_id,prescription_no," \
                    "definition_id,total_price,quantity_value,quantity_unit,unit_price," \
                    "account_id,org_id,condition_id,encounter_diagnosis_id,generate_source_enum,context_enum," \
                    "created_by,created_at,updated_by,updated_at,is_deleted FROM adm_charge_item "
std::string chinapres3ChargeItemDAO::queryConditionBuilder(const chinapres3ChargeItemQuery::Wrapper& query, SqlParams& params)
{
	std::ostringstream sql;
	// 1 for serviceTable
	if (query->serviceTable) {
		auto val = query->serviceTable.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND service_table=?";
	}
	// 2 for serviceId
	if (query->serviceId) {
		auto val = query->serviceId.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND service_id=?";
	}
	// 3 for prescriptionNo
	if (query->prescriptionNo) {
		auto val = query->prescriptionNo.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND prescription_no=?";
	}
	// 4 for patientId
	if (query->patientId) {
		auto val = query->patientId.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND patient_id=?";
	}
	// 5 for encounterId
	if (query->encounterId) {
		auto val = query->encounterId.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND encounter_id=?";
	}
	// ---- revoke-related filter ----
	// 6 for isDeleted
	if (query->isDeleted) {
		auto val = query->isDeleted.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND is_deleted=?";
	}
	return sql.str();
}

uint64_t chinapres3ChargeItemDAO::count(const chinapres3ChargeItemQuery::Wrapper& query)
{
	std::ostringstream sql;
	if (!query) {
		sql << "SELECT COUNT(*) FROM adm_charge_item;";
	}
	else {
		SqlParams params;
		sql << "SELECT COUNT(*) FROM adm_charge_item ";
		std::string condition = queryConditionBuilder(query, params);
		sql << "WHERE 1=1" << condition;
		std::string countSql = sql.str();
		return sqlSession->executeQueryNumerical(countSql, params);
	}
	std::string countSql = sql.str();
	return sqlSession->executeQueryNumerical(countSql);
}

std::list<Ptrchinapres3ChargeItemDO> chinapres3ChargeItemDAO::selectWithPage(const chinapres3ChargeItemQuery::Wrapper& query)
{
	std::ostringstream sql;
	SqlParams params;
	sql << QUERY_HEAD;
	std::string condition = queryConditionBuilder(query, params);
	sql << "WHERE 1=1" << condition;
	sql << " ORDER BY IFNULL(updated_at, created_at) DESC, id DESC ";
	sql << "LIMIT " << ((query->pageIndex - 1) * query->pageSize) << "," << query->pageSize;
	chinapres3ChargeItemMapper mapper;
	return sqlSession->executeQuery<Ptrchinapres3ChargeItemDO>(sql.str(), mapper, params);
}

Ptrchinapres3ChargeItemDO chinapres3ChargeItemDAO::selectById(const std::string& id)
{
	std::ostringstream sql;
	sql << QUERY_HEAD;
	sql << "WHERE id=?";
	chinapres3ChargeItemMapper mapper;
	SqlParams params = { SqlParam("s", std::make_shared<std::string>(id)) };
	auto list = sqlSession->executeQuery<Ptrchinapres3ChargeItemDO>(sql.str(), mapper, params);
	if (list.empty())
		return nullptr;
	return list.front();
}
