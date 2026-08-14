#include "stdafx.h"
#include "AdmEncounterDAO.h"
#include "AdmEncounterMapper.h"
#include "SqlSession.h"
#include <sstream>

PtrAdmEncounter3DO AdmEncounterDAO::selectById(const std::string& id, const std::string& tenantId)
{
	std::ostringstream sql;
	sql << "SELECT id, patient_id, status_enum FROM adm_encounter "
		<< "WHERE id=? AND tenant_id=? AND is_deleted=0";
	AdmEncounterMapper mapper;
	SqlParams params = {
		SqlParam("s", std::make_shared<std::string>(id)),
		SqlParam("s", std::make_shared<std::string>(tenantId))
	};
	auto list = sqlSession->executeQuery<PtrAdmEncounter3DO>(sql.str(), mapper, params);
	if (list.empty())
		return nullptr;
	return list.front();
}
