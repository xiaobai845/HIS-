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
#include "stdafx.h"
#include "PatientController.h"
#include "service/patient/PatientQueueService.h"
#include <regex>

#define MAX_PAGE_SIZE 100

PatientQueuePageJsonVO::Wrapper PatientController::execQueryPatient(
	const PatientQuery::Wrapper& query, const std::string& userId)
{
	// --- Extract parameters (with defaults) ---
	std::string keyword = query->keyword ? query->keyword.getValue("") : "";
	std::string startDate = query->startDate ? query->startDate.getValue("") : "";
	std::string endDate = query->endDate ? query->endDate.getValue("") : "";

	int pageIndex = 1;
	int pageSize = 10;
	if (query->pageIndex) pageIndex = static_cast<int>(query->pageIndex.getValue(1));
	if (query->pageSize) pageSize = static_cast<int>(query->pageSize.getValue(10));

	// --- Validate input ---
	if (pageIndex < 1) {
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->code = 9995;
		vo->message = "pageIndex must be >= 1";
		return vo;
	}
	if (pageSize < 1 || pageSize > MAX_PAGE_SIZE) {
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->code = 9995;
		vo->message = "pageSize must be between 1 and 100";
		return vo;
	}
	// Validate date format (yyyy-MM-dd)
	std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
	if (!startDate.empty() && !std::regex_match(startDate, datePattern)) {
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->code = 9995;
		vo->message = "startDate format must be yyyy-MM-dd";
		return vo;
	}
	if (!endDate.empty() && !std::regex_match(endDate, datePattern)) {
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->code = 9995;
		vo->message = "endDate format must be yyyy-MM-dd";
		return vo;
	}

	// --- Exception handling ---
	try {
		// Call service layer
		PatientQueueService service;
		auto pageData = service.queryPatientQueue(keyword, startDate, endDate, userId, pageIndex, pageSize);

		// Build JSON response
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->success(pageData);

		return vo;
	} catch (const std::exception& ex) {
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->code = 9994;
		vo->message = ex.what();
		return vo;
	} catch (...) {
		auto vo = PatientQueuePageJsonVO::createShared();
		vo->code = 9999;
		vo->message = "unknown server error";
		return vo;
	}
}
