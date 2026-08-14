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
#include "PatientConsumService.h"
#include <sstream>
#include <iomanip>

oatpp::List<PatientConsumableDTO::Wrapper> PatientConsumService::queryDeviceRequests(
	const std::string& encounterId,
	const std::string& consumableRoom)
{
	PatientConsumDAO dao;
	auto results = dao.queryDeviceRequests(encounterId, consumableRoom);

	auto dtos = oatpp::List<PatientConsumableDTO::Wrapper>::createShared();
	for (auto& res : results) {
		auto dto = PatientConsumableDTO::createShared();
		dto->consumableName = res.definition.getName();
		// Combine model number and total volume (package spec)
		std::ostringstream spec;
		spec << res.definition.getModelNumber();
		std::string totalVolume = res.definition.getTotalVolume();
		if (!totalVolume.empty()) {
			spec << "(" << totalVolume << ")";
		}
		dto->modelSpec = spec.str();
		// Quantity with unit
		std::ostringstream qty;
		qty << std::fixed << std::setprecision(0) << res.request.getQuantity();
		std::string unitCode = res.request.getUnitCode();
		if (!unitCode.empty()) {
			qty << "\xC3\x97" << unitCode;
		}
		dto->quantity = qty.str();
		dto->status = res.request.getStatusEnum();
		dto->consumableRoom = consumableRoom;
		dto->isEmpty = (res.request.getQuantity() <= 0) ? 1 : 0;
		dto->isAct = res.request.getPerformFlag();
		dtos->push_back(dto);
	}

	return dtos;
}
