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
#include "PatientConsumDAO.h"
#include <sstream>

DeviceConsumResult DeviceConsumMapper::mapper(ResultSet* rs) const
{
	DeviceConsumResult result;
	// Map DeviceRequestDO fields
	result.request.setId(rs->getString("id"));
	if (!rs->isNull("patient_id"))
		result.request.setPatientId(rs->getString("patient_id"));
	if (!rs->isNull("encounter_id"))
		result.request.setEncounterId(rs->getString("encounter_id"));
	if (!rs->isNull("device_def_id"))
		result.request.setDeviceDefId(rs->getString("device_def_id"));
	if (!rs->isNull("status_enum"))
		result.request.setStatusEnum(rs->getString("status_enum"));
	result.request.setPerformFlag(rs->getInt("perform_flag"));
	result.request.setQuantity(rs->getDouble("quantity"));
	if (!rs->isNull("unit_code"))
		result.request.setUnitCode(rs->getString("unit_code"));

	// Map DeviceDefinitionDO fields
	if (!rs->isNull("dev_name"))
		result.definition.setName(rs->getString("dev_name"));
	if (!rs->isNull("model_number"))
		result.definition.setModelNumber(rs->getString("model_number"));
	if (!rs->isNull("merchandise_name"))
		result.definition.setMerchandiseName(rs->getString("merchandise_name"));
	if (!rs->isNull("total_volume"))
		result.definition.setTotalVolume(rs->getString("total_volume"));

	// Map extended joined fields
	if (!rs->isNull("status_name"))
		result.statusName = rs->getString("status_name");
	if (!rs->isNull("unit_name"))
		result.unitName = rs->getString("unit_name");
	return result;
}

std::list<DeviceConsumResult> PatientConsumDAO::queryDeviceRequests(
	const std::string& encounterId,
	const std::string& consumableRoom)
{
	std::ostringstream sql;
	sql << "SELECT dr.id, dr.patient_id, dr.encounter_id, dr.device_def_id, "
		<< "dr.status_enum, dr.perform_flag, dr.quantity, dr.unit_code, "
		<< "dd.name AS dev_name, dd.model_number, dd.merchandise_name, dd.total_volume, "
		<< "st.display_name AS status_name, "
		<< "uc.display_name AS unit_name "
		<< "FROM wkf_device_request dr "
		<< "JOIN adm_device_definition dd ON dr.device_def_id = dd.id "
		<< "LEFT JOIN adm_code_dict st ON st.code = dr.status_enum "
		<< "AND st.category = 'device_request_status' "
		<< "LEFT JOIN adm_code_dict uc ON uc.code = dr.unit_code "
		<< "AND uc.category = 'unit_code' "
		<< "WHERE dr.is_deleted = 0 ";

	SqlParams params;
	if (!encounterId.empty()) {
		sql << "AND dr.encounter_id = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, encounterId);
	}
	if (!consumableRoom.empty()) {
		sql << "AND dr.status_enum = ? ";
		SQLPARAMS_PUSH(params, "s", std::string, consumableRoom);
	}

	sql << "ORDER BY dr.id DESC";

	DeviceConsumMapper mapper;
	return sqlSession->executeQuery<DeviceConsumResult>(sql.str(), mapper, params);
}
