#include "stdafx.h"
#include "chinapres3MedicationRequestDAO.h"
#include "chinapres3MedicationRequestMapper.h"
#include "SqlSession.h"
#include <sstream>

#define QUERY_HEAD "SELECT id,prescription_no,patient_id,encounter_id,status_enum,rx_type_code," \
                    "medication_id,quantity,unit_code,location_id," \
                    "created_by,created_at,updated_by,updated_at FROM med_medication_request "
std::string chinapres3MedicationRequestDAO::queryConditionBuilder(const chinapres3MedicationRequestQuery::Wrapper& query, SqlParams& params)
{
	std::ostringstream sql;
	// 1 for prescriptionNo
	if (query->prescriptionNo) {
		auto val = query->prescriptionNo.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND prescription_no LIKE CONCAT('%',?,'%')";
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
	// 4 for statusEnum
	if (query->statusEnum) {
		auto val = query->statusEnum.getValue("");
		params.push_back(SqlParam("s", std::make_shared<std::string>(val)));
		if (!val.empty()) sql << " AND status_enum=?";
	}
	return sql.str();
}

uint64_t chinapres3MedicationRequestDAO::count(const chinapres3MedicationRequestQuery::Wrapper& query)
{
	std::ostringstream sql;
	if (!query) {
		sql << "SELECT COUNT(*) FROM med_medication_request;";
	}
	else {
		SqlParams params;
		sql << "SELECT COUNT(*) FROM med_medication_request ";
		std::string condition = queryConditionBuilder(query, params);
		sql << "WHERE 1=1" << condition;
		std::string countSql = sql.str();
		return sqlSession->executeQueryNumerical(countSql, params);
	}
	std::string countSql = sql.str();
	return sqlSession->executeQueryNumerical(countSql);
}

std::list<Ptrchinapres3MedicationRequestDO> chinapres3MedicationRequestDAO::selectWithPage(const chinapres3MedicationRequestQuery::Wrapper& query)
{
	std::ostringstream sql;
	SqlParams params;
	sql << QUERY_HEAD;
	std::string condition = queryConditionBuilder(query, params);
	sql << "WHERE 1=1" << condition;
	sql << " ORDER BY IFNULL(updated_at, created_at) DESC, id DESC ";
	sql << "LIMIT " << ((query->pageIndex - 1) * query->pageSize) << "," << query->pageSize;
	chinapres3MedicationRequestMapper mapper;
	return sqlSession->executeQuery<Ptrchinapres3MedicationRequestDO>(sql.str(), mapper, params);
}

Ptrchinapres3MedicationRequestDO chinapres3MedicationRequestDAO::selectById(const std::string& id)
{
	std::ostringstream sql;
	sql << QUERY_HEAD;
	sql << "WHERE id=?";
	chinapres3MedicationRequestMapper mapper;
	SqlParams params = { SqlParam("s", std::make_shared<std::string>(id)) };
	auto list = sqlSession->executeQuery<Ptrchinapres3MedicationRequestDO>(sql.str(), mapper, params);
	if (list.empty())
		return nullptr;
	return list.front();
}

uint64_t chinapres3MedicationRequestDAO::countByPrescriptionNo(const std::string& prescriptionNo, const std::string& statusEnum)
{
	std::ostringstream sql;
	sql << "SELECT COUNT(*) FROM med_medication_request WHERE prescription_no=? AND status_enum=? AND is_deleted=0";
	SqlParams params = {
		SqlParam("s", std::make_shared<std::string>(prescriptionNo)),
		SqlParam("s", std::make_shared<std::string>(statusEnum))
	};
	return sqlSession->executeQueryNumerical(sql.str(), params);
}
