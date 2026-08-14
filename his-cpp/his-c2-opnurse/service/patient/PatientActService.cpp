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
#include "PatientActService.h"
#include <sstream>
#include <ctime>

oatpp::Object<PatientActWrapperDTO> PatientActService::queryServiceRequests(
	const std::string& encounterId)
{
	PatientActDAO dao;
	auto results = dao.queryServiceRequests(encounterId);

	// Fetch patient queue info for this encounter
	PatientQueueDAO queueDao;
	auto queueInfo = queueDao.queryByEncounterId(encounterId);
	std::string patientName = queueInfo.name;
	std::string patientGender = queueInfo.gender;
	if (patientGender == "M" || patientGender == "male") patientGender = "\xE7\x94\xB7";
	else if (patientGender == "F" || patientGender == "female") patientGender = "\xE5\xA5\xB3";
		int patientAge = 0;
	{
		std::string birthDate = queueInfo.birthDate;
		if (!birthDate.empty()) {
			std::istringstream iss(birthDate);
			int year = 0, month = 0, day = 0;
			char dash1, dash2;
			if (iss >> year >> dash1 >> month >> dash2 >> day) {
				auto now = std::time(nullptr);
				auto* tm = std::localtime(&now);
				int curYear = tm->tm_year + 1900;
				int curMonth = tm->tm_mon + 1;
				int curDay = tm->tm_mday;
				patientAge = curYear - year;
				if (curMonth < month || (curMonth == month && curDay < day))
					patientAge--;
			}
		}
	}

	// Build act item list
	auto items = oatpp::Vector<oatpp::Object<PatientActDTO>>::createShared();
	for (auto& s : results) {
		auto dto = PatientActDTO::createShared();
		dto->status = s.getStatusEnum();
		dto->orderContent = s.getEntrustContent();
		std::string price = s.getTotalPrice();
		if (!price.empty()) {
			std::ostringstream oss;
			oss << "\xE5\xB7\xB2\xE7\xBB\x93\xE7\xAE\x97\xEF\xBC\x9B" << price << "\xE5\x85\x83";
			dto->amount = oss.str();
		}
		else {
			dto->amount = "\xE6\x9C\xAA\xE7\xBB\x93\xE7\xAE\x97";
		}
		dto->isAct = s.getPerformFlag();
		items->push_back(dto);
	}

	// Build wrapper with patient info at top level
	auto wrapper = PatientActWrapperDTO::createShared();
	wrapper->name = patientName;
	wrapper->gender = patientGender;
	wrapper->age = patientAge;
	wrapper->items = items;

	return wrapper;
}
