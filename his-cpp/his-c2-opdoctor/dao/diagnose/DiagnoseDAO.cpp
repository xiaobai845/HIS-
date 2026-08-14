#include "stdafx.h"

#include "DiagnoseDAO.h"
#include "DiagnoseMapper.h"

int
DiagnoseDAO::insertDiagnose(const AdmEncounterDiagnosisDO& diagnoseDo)
{
	return insert(diagnoseDo);
}

PtrAdmEncounterDiagnosisDO
DiagnoseDAO::getCreatedAtById(const std::string& id)
{
	std::string sql = "SELECT created_at FROM adm_encounter_diagnosis WHERE id = ?";
	return sqlSession->executeQueryOne<PtrAdmEncounterDiagnosisDO>(sql, DiagnoseMapper(), "%s", id);
}

int
DiagnoseDAO::deleteById(const std::string& id)
{
	return deleteById(id, "");
}

int
DiagnoseDAO::deleteById(const std::string& id, const std::string& deletedBy)
{
	SqlParams params;
	std::string sql;
	if (deletedBy.empty())
	{
		sql = "UPDATE adm_encounter_diagnosis SET is_deleted = 1, deleted_at = NOW() "
			  "WHERE id = ? AND is_deleted = 0";
		SQLPARAMS_PUSH(params, "s", std::string, id);
	}
	else
	{
		sql = "UPDATE adm_encounter_diagnosis SET is_deleted = 1, deleted_at = NOW(), deleted_by = ? "
			  "WHERE id = ? AND is_deleted = 0";
		SQLPARAMS_PUSH(params, "s", std::string, deletedBy);
		SQLPARAMS_PUSH(params, "s", std::string, id);
	}
	return sqlSession->executeUpdate(sql, params);
}

PtrAdmEncounterDiagnosisDO
DiagnoseDAO::selectById(const std::string& id)
{
	std::string sql = "SELECT encounter_id, condition_id, deleted_at, deleted_by "
					  "FROM adm_encounter_diagnosis WHERE id = ?";
	return sqlSession->executeQueryOne<PtrAdmEncounterDiagnosisDO>(sql, DiagnoseMapper(), "%s", id);
}

// ---- helper: build shared WHERE clause for diagnose usage queries ----
static void buildDiagnoseUsageWhere(std::string& sql, SqlParams& params,
	const DiagnoseUsageQuery::Wrapper& query)
{
	sql += " WHERE is_deleted = 0";

	if (query->keyword)
	{
		sql += " AND description LIKE ?";
		SQLPARAMS_PUSH(params, "%%%s%%", std::string, query->keyword.getValue(""));
	}

	if (query->diagTypeCode)
	{
		sql += " AND diag_type_code = ?";
		SQLPARAMS_PUSH(params, "%s", std::string, query->diagTypeCode.getValue(""));
	}

	if (query->startDate)
	{
		sql += " AND created_at >= ?";
		SQLPARAMS_PUSH(params, "%s", std::string, query->startDate.getValue(""));
	}

	if (query->endDate)
	{
		sql += " AND created_at <= ?";
		SQLPARAMS_PUSH(params, "%s", std::string, query->endDate.getValue(""));
	}
}
// ----------------------------------------------------------------------

uint64_t
DiagnoseDAO::countDiagnoseUsageHistory(const DiagnoseUsageQuery::Wrapper& query)
{
	std::string sql = "SELECT COUNT(*) FROM adm_encounter_diagnosis";
	SqlParams params;
	buildDiagnoseUsageWhere(sql, params, query);
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrAdmEncounterDiagnosisDO>
DiagnoseDAO::selectDiagnoseUsageHistory(const DiagnoseUsageQuery::Wrapper& query)
{
	std::string sql = "SELECT id, encounter_id, condition_id, description, ";
	sql += "diag_type_code, diag_code, rank, primary_flag, highest_diag_flag, ";
	sql += "tcm_flag, tcm_syndrome_group, med_type, condition_code, created_at ";
	sql += "FROM adm_encounter_diagnosis";

	SqlParams params;
	buildDiagnoseUsageWhere(sql, params, query);

	sql += " ORDER BY created_at DESC LIMIT ? OFFSET ?";

	uint64_t pageIndex = query->pageIndex.getValue(1);
	uint64_t pageSize = query->pageSize.getValue(10);
	uint64_t offset = (pageIndex - 1) * pageSize;
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);
	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);

	return sqlSession->executeQuery<PtrAdmEncounterDiagnosisDO>(sql, DiagnoseMapper(), params);
}
