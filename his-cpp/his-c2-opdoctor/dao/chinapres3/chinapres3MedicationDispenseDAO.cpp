#include "stdafx.h"
#include "chinapres3MedicationDispenseDAO.h"
#include "chinapres3MedicationDispenseMapper.h"
#include "SqlSession.h"
#include <sstream>

#define QUERY_HEAD "SELECT id,med_req_id,patient_id,encounter_id,bus_no,status_enum," \
                    "dispense_enum,location_id,medication_id,quantity,unit_code," \
                    "created_by,created_at,updated_by,updated_at,is_deleted FROM med_medication_dispense "
std::string chinapres3MedicationDispenseDAO::queryConditionBuilder(const chinapres3MedicationDispenseQuery::Wrapper& query, SqlParams& params)
{
	std::ostringstream sql;
	// 1 for medReqId
	if (query->medReqId) {
		auto val = query->medReqId.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND med_req_id=?";
	}
	// 2 for patientId
	if (query->patientId) {
		auto val = query->patientId.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND patient_id=?";
	}
	// 3 for encounterId
	if (query->encounterId) {
		auto val = query->encounterId.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND encounter_id=?";
	}
	// 4 for busNo
	if (query->busNo) {
		auto val = query->busNo.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND bus_no=?";
	}
	// 5 for statusEnum
	if (query->statusEnum) {
		auto val = query->statusEnum.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND status_enum=?";
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

uint64_t chinapres3MedicationDispenseDAO::count(const chinapres3MedicationDispenseQuery::Wrapper& query)
{
	std::ostringstream sql;
	if (!query) {
		sql << "SELECT COUNT(*) FROM med_medication_dispense;";
	}
	else {
		SqlParams params;
		sql << "SELECT COUNT(*) FROM med_medication_dispense ";
		std::string condition = queryConditionBuilder(query, params);
		sql << "WHERE 1=1" << condition;
		std::string countSql = sql.str();
		return sqlSession->executeQueryNumerical(countSql, params);
	}
	std::string countSql = sql.str();
	return sqlSession->executeQueryNumerical(countSql);
}

std::list<Ptrchinapres3MedicationDispenseDO> chinapres3MedicationDispenseDAO::selectWithPage(const chinapres3MedicationDispenseQuery::Wrapper& query)
{
	std::ostringstream sql;
	SqlParams params;
	sql << QUERY_HEAD;
	std::string condition = queryConditionBuilder(query, params);
	sql << "WHERE 1=1" << condition;
	sql << " ORDER BY IFNULL(updated_at, created_at) DESC, id DESC ";
	sql << "LIMIT " << ((query->pageIndex - 1) * query->pageSize) << "," << query->pageSize;
	chinapres3MedicationDispenseMapper mapper;
	return sqlSession->executeQuery<Ptrchinapres3MedicationDispenseDO>(sql.str(), mapper, params);
}

Ptrchinapres3MedicationDispenseDO chinapres3MedicationDispenseDAO::selectById(const std::string& id)
{
	std::ostringstream sql;
	sql << QUERY_HEAD;
	sql << "WHERE id=?";
	chinapres3MedicationDispenseMapper mapper;
	SqlParams params = { SqlParam("s", std::make_shared<std::string>(id)) };
	auto list = sqlSession->executeQuery<Ptrchinapres3MedicationDispenseDO>(sql.str(), mapper, params);
	if (list.empty())
		return nullptr;
	return list.front();
}
