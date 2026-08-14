
#ifndef _NURSE_MAPPER2_
#define _NURSE_MAPPER2_
#include "Mapper.h"
#include "domain/do/nurse2/nurseDO2.h"

/**
 * ResultSet to NurseDO2 mapper for wkf_service_request table
 */
class NurseMapper2 : public Mapper<NurseDO2>
{
public:
	NurseDO2 mapper(ResultSet* resultSet) const override
	{
		NurseDO2 data;
		data.setId(resultSet->getString("id"));
		data.setName(resultSet->getString("bus_no"));
		data.setState(resultSet->getString("status_enum"));
		data.setContent(resultSet->getString("content_json"));
		data.setAmount(resultSet->getInt("execution_count"));
		data.setPerson(resultSet->getString("performer_id"));
		data.setOperate(resultSet->getString("category_enum"));
		data.setRemark(resultSet->getString("remark"));
		data.setEncounterId(resultSet->getString("encounter_id"));
		return data;
	}
};

#endif // !_NURSE_MAPPER2_
