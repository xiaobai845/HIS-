#include "stdafx.h"

#include "PatientDiagnoseDAO.h"
#include "DiagnoseMapper.h"

uint64_t
PatientDiagnoseDAO::countDiagnosesByPatientId(
	const std::string& patientId,
	const std::string& keyword,
	const std::string& diagTypeCode,
	const std::string& startDate,
	const std::string& endDate)
{
	// Build SQL with JOIN between adm_encounter and adm_encounter_diagnosis
	std::string sql = "SELECT COUNT(*) FROM adm_encounter e "
		"INNER JOIN adm_encounter_diagnosis d ON e.id = d.encounter_id "
		"WHERE e.patient_id = ? AND e.is_deleted = 0 AND d.is_deleted = 0";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, patientId);

	// Keyword filter on diagnosis description
	if (!keyword.empty())
	{
		sql += " AND d.description LIKE ?";
		SQLPARAMS_PUSH(params, "s", std::string, keyword);
	}

	// Diag type code filter
	if (!diagTypeCode.empty())
	{
		sql += " AND d.diag_type_code = ?";
		SQLPARAMS_PUSH(params, "s", std::string, diagTypeCode);
	}

	// Start date filter
	if (!startDate.empty())
	{
		sql += " AND d.created_at >= ?";
		SQLPARAMS_PUSH(params, "s", std::string, startDate);
	}

	// End date filter
	if (!endDate.empty())
	{
		sql += " AND d.created_at <= ?";
		SQLPARAMS_PUSH(params, "s", std::string, endDate);
	}

	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrAdmEncounterDiagnosisDO>
PatientDiagnoseDAO::selectDiagnosesByPatientId(
	const std::string& patientId,
	const std::string& keyword,
	const std::string& diagTypeCode,
	const std::string& startDate,
	const std::string& endDate,
	uint64_t offset,
	uint64_t pageSize)
{
	// Build SQL with JOIN between adm_encounter and adm_encounter_diagnosis
	std::string sql = "SELECT d.id, d.encounter_id, d.condition_id, d.description, ";
	sql += "d.diag_type_code, d.diag_code, d.rank, d.primary_flag, d.highest_diag_flag, ";
	sql += "d.tcm_flag, d.tcm_syndrome_group, d.med_type, d.condition_code, d.created_at ";
	sql += "FROM adm_encounter e ";
	sql += "INNER JOIN adm_encounter_diagnosis d ON e.id = d.encounter_id ";
	sql += "WHERE e.patient_id = ? AND e.is_deleted = 0 AND d.is_deleted = 0";

	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, patientId);

	// Keyword filter on diagnosis description
	if (!keyword.empty())
	{
		sql += " AND d.description LIKE ?";
		SQLPARAMS_PUSH(params, "s", std::string, keyword);
	}

	// Diag type code filter
	if (!diagTypeCode.empty())
	{
		sql += " AND d.diag_type_code = ?";
		SQLPARAMS_PUSH(params, "s", std::string, diagTypeCode);
	}

	// Start date filter
	if (!startDate.empty())
	{
		sql += " AND d.created_at >= ?";
		SQLPARAMS_PUSH(params, "s", std::string, startDate);
	}

	// End date filter
	if (!endDate.empty())
	{
		sql += " AND d.created_at <= ?";
		SQLPARAMS_PUSH(params, "s", std::string, endDate);
	}

	// Order and pagination
	sql += " ORDER BY d.created_at DESC LIMIT ? OFFSET ?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, pageSize);
	SQLPARAMS_PUSH(params, "ull", uint64_t, offset);

	return sqlSession->executeQuery<PtrAdmEncounterDiagnosisDO>(sql, DiagnoseMapper(), params);
}
