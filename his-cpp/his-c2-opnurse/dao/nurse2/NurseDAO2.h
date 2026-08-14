
#ifndef _NURSE_DAO2_
#define _NURSE_DAO2_
#include "BaseDAO.h"
#include "domain/do/nurse2/nurseDO2.h"
#include "domain/query/nurse2/NurseQuery2.h"

class NurseDAO2 : public BaseDAO
{
private:
	// Build WHERE clause from query filters
	inline std::string queryConditionBuilder(const NurseQuery2::Wrapper& query, SqlParams& params);

public:
	// Count records by query filters
	uint64_t count(const NurseQuery2::Wrapper& query);
	// Select with pagination
	std::list<NurseDO2> selectWithPage(const NurseQuery2::Wrapper& query);

	// Execute a service request (update status, count, performer by pk + encounter validation)
	int updateExecutionStatus(const std::string& itemId, const std::string& encounterId,
		const std::string& status, int execCount, const std::string& performerId);
	// Cancel a service request (update status to CANCELLED by pk + encounter validation)
	int updateCancelStatus(const std::string& itemId, const std::string& encounterId,
		const std::string& cancelReason, const std::string& performerId);
};

#endif // !_NURSE_DAO2_
