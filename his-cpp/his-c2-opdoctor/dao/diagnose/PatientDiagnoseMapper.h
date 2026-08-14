#pragma once

#include "Mapper.h"

// Mapper for extracting encounter ID strings from adm_encounter query results.
class EncounterIdMapper : public Mapper<std::string>
{
public:
	std::string mapper(ResultSet* resultSet) const override
	{
		return resultSet->getString("id");
	}
};
