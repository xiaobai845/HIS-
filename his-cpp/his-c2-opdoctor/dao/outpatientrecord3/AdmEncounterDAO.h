#pragma once
#ifndef _AdmEncounterDAO_H_
#define _AdmEncounterDAO_H_

#include "BaseDAO.h"
#include "AdmEncounterMapper.h"
#include "../../domain/do/outpatientrecord3/AdmEncounter3DO.h"

/**
 * Data access object for adm_encounter table.
 * Provides lookup by encounter id (filtered by tenant).
 */
class AdmEncounterDAO : public BaseDAO
{
public:
	// Query a single encounter by id (with tenant_id guard and soft-delete filter)
	PtrAdmEncounter3DO selectById(const std::string& id, const std::string& tenantId);
};

#endif // !_AdmEncounterDAO_H_
