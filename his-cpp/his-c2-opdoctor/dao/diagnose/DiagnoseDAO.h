#pragma once

#include <list>
#include <string>

#include "BaseDAO.h"
#include "domain/do/diagnose/AdmEncounterDiagnosisDO.h"
#include "domain/query/diagnose/DiagnoseUsageQuery.h"

class DiagnoseDAO : public BaseDAO
{
public:
	// insert a new diagnose record and return the number of affected rows
	int insertDiagnose(const AdmEncounterDiagnosisDO& diagnoseDo);
	// get createdAt by id
	PtrAdmEncounterDiagnosisDO getCreatedAtById(const std::string& id);
	// soft delete a diagnose record by id
	int deleteById(const std::string& id);
	// soft delete a diagnose record by id with deletedBy
	int deleteById(const std::string& id, const std::string& deletedBy);
	// select a diagnose(encounterId, conditionId, deletedAt, deletedBy) record by id
	PtrAdmEncounterDiagnosisDO selectById(const std::string& id);
	// count diagnose usage history total
	uint64_t countDiagnoseUsageHistory(const DiagnoseUsageQuery::Wrapper& query);
	// select diagnose usage history (paginated)
	std::list<PtrAdmEncounterDiagnosisDO> selectDiagnoseUsageHistory(const DiagnoseUsageQuery::Wrapper& query);
};