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
#include "PatientQueueService.h"
#include "Macros.h"
#include "NacosClient.h"
#include "RedisClient.h"
#include <ctime>
#include <sstream>
#include <stdexcept>

PatientQueuePageDTO::Wrapper PatientQueueService::queryPatientQueue(
	const std::string& keyword, const std::string& startDate, const std::string& endDate,
	const std::string& userId,
	int pageIndex, int pageSize)
{
	// Get tenant ID from Redis by current user ID
	std::string tenantId = getTenantIdFromRedis(userId);
	if (tenantId.empty()) {
		throw std::runtime_error("tenant not found in redis");
	}

	PatientQueueDAO dao;
	// Query data with tenant isolation
	auto results = dao.queryPatientQueue(keyword, startDate, endDate, tenantId, pageIndex, pageSize);
	auto total = dao.countPatientQueue(keyword, startDate, endDate, tenantId);

	// Convert DO to DTO
	auto dtos = oatpp::List<PatientQueueDTO::Wrapper>::createShared();
	for (auto& res : results) {
		auto dto = PatientQueueDTO::createShared();
		dto->encounterId = res.queue.getEncounterId();
		dto->name = res.patient.getName();
		dto->gender = convertGender(res.patient.getGenderEnum());
		dto->age = calcAge(res.patient.getBirthDate());
		dto->visitTime = res.queue.getStartInstant();
		dto->queueNumber = res.queue.getBusNo();
		std::string paymentType = res.paymentType;
		if (paymentType.empty()) paymentType = "\xE8\x87\xAA\xE8\xB4\xB9";
		dto->paymentType = paymentType;
		dtos->push_back(dto);
	}

	// Build page result
	auto page = PatientQueuePageDTO::createShared();
	page->pageIndex = pageIndex;
	page->pageSize = pageSize;
	page->total = static_cast<oatpp::Int64>(total);
	page->pages = (total + pageSize - 1) / pageSize;
	page->rows = dtos;

	return page;
}

int PatientQueueService::calcAge(const std::string& birthDate)
{
	if (birthDate.empty()) return 0;
	// Parse yyyy-MM-dd format
	std::istringstream iss(birthDate);
	int year = 0, month = 0, day = 0;
	char dash1, dash2;
	if (!(iss >> year >> dash1 >> month >> dash2 >> day)) return 0;

	// Get current date
	auto now = std::time(nullptr);
	auto* tm = std::localtime(&now);
	int curYear = tm->tm_year + 1900;
	int curMonth = tm->tm_mon + 1;
	int curDay = tm->tm_mday;

	int age = curYear - year;
	if (curMonth < month || (curMonth == month && curDay < day))
		age--;
	return age;
}

std::string PatientQueueService::convertGender(const std::string& genderEnum)
{
	if (genderEnum == "M" || genderEnum == "male") return "\xE7\x94\xB7";
	if (genderEnum == "F" || genderEnum == "female") return "\xE5\xA5\xB3";
	return genderEnum;
}

std::string PatientQueueService::getTenantIdFromRedis(const std::string& userId)
{
	// Redis key: user:session:{userId}, Hash type
	// Field: tenant_id - currently selected tenant ID
	// Ref: Redis data design doc section 4
	ZO_CREATE_REDIS_CLIENT(redisClient);
	std::string key = "user:session:" + userId;
	return redisClient.execute<std::string>([&key](Redis* redis) -> std::string {
		auto val = redis->hget(key, "tenant_id");
		if (val) {
			return *val;
		}
		return std::string("");
	});
}
