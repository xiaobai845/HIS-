/*
 Copyright Zero One Star. All rights reserved.

 @Author: AI Assistant
 @Date: 2026/07/24 18:30:00

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "PatientActDAO.h"
#include <sstream>

ServiceRequestDO ServiceRequestMapper::mapper(ResultSet* rs) const
{
	ServiceRequestDO d;
	d.setId(rs->getString("id"));
	if (!rs->isNull("patient_id"))
		d.setPatientId(rs->getString("patient_id"));
	if (!rs->isNull("encounter_id"))
		d.setEncounterId(rs->getString("encounter_id"));
	if (!rs->isNull("status_enum"))
		d.setStatusEnum(rs->getString("status_enum"));
	if (!rs->isNull("entrust_content"))
		d.setEntrustContent(rs->getString("entrust_content"));
	d.setPerformFlag(rs->getInt("perform_flag"));
	if (!rs->isNull("activity_id"))
		d.setActivityId(rs->getString("activity_id"));
	if (!rs->isNull("category_enum"))
		d.setCategoryEnum(rs->getString("category_enum"));
	if (!rs->isNull("quantity"))
		d.setQuantity(rs->getDouble("quantity"));
	if (!rs->isNull("unit_code"))
		d.setUnitCode(rs->getString("unit_code"));
	if (!rs->isNull("authored_time"))
		d.setAuthoredTime(rs->getString("authored_time"));
	if (!rs->isNull("remark"))
		d.setRemark(rs->getString("remark"));
	if (!rs->isNull("total_price")) {
		std::ostringstream oss;
		oss.setf(std::ios::fixed);
		oss.precision(2);
		oss << rs->getDouble("total_price");
		d.setTotalPrice(oss.str());
	}
	return d;
}

std::list<ServiceRequestDO> PatientActDAO::queryServiceRequests(const std::string& encounterId)
{
	std::ostringstream sql;
	sql << "SELECT sr.id, sr.patient_id, sr.encounter_id, sr.status_enum, "
		<< "sr.entrust_content, sr.perform_flag, sr.activity_id, "
		<< "sr.category_enum, sr.quantity, sr.unit_code, sr.authored_time, sr.remark, "
		<< "ci.total_price "
		<< "FROM wkf_service_request sr "
		<< "LEFT JOIN adm_charge_item ci ON ci.service_table = 'wkf_service_request' "
		<< "AND ci.service_id = sr.id "
		<< "WHERE sr.is_deleted = 0 ";

	SqlParams params;
	if (!encounterId.empty()) {
		sql << "AND sr.encounter_id = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, encounterId);
	}

	sql << "ORDER BY sr.authored_time DESC";

	ServiceRequestMapper mapper;
	return sqlSession->executeQuery<ServiceRequestDO>(sql.str(), mapper, params);
}
