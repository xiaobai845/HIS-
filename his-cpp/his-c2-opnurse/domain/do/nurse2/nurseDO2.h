/*
 Copyright Zero One Star. All rights reserved.

 @Author: fa-mian-tuan
 @Date: 2026/08/01

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
#ifndef _NURSEDO2_
#define _NURSEDO2_
#include "../DoInclude.h"

/**
 * Nurse2 database object, maps to wkf_service_request table
 */
class NurseDO2 : public BaseDO
{
	// Primary key ID
	MYSQL_SYNTHESIZE(string, id, Id);
	// Queue number / patient name (bus_no column)
	MYSQL_SYNTHESIZE(string, name, Name);
	// Execution status (status_enum column)
	MYSQL_SYNTHESIZE(string, state, State);
	// Medical order content (content_json column)
	MYSQL_SYNTHESIZE(string, content, Content);
	// Execution count (execution_count column)
	MYSQL_SYNTHESIZE(int, amount, Amount);
	// Executor (performer_id column)
	MYSQL_SYNTHESIZE(string, person, Person);
	// Operation category (category_enum column)
	MYSQL_SYNTHESIZE(string, operate, Operate);
	// Remark (remark column)
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// Encounter ID (encounter_id column)
	MYSQL_SYNTHESIZE(string, encounterId, EncounterId);

public:
	NurseDO2() : BaseDO("wkf_service_request")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("bus_no", "s", name);
		MYSQL_ADD_FIELD("status_enum", "s", state);
		MYSQL_ADD_FIELD("content_json", "s", content);
		MYSQL_ADD_FIELD("execution_count", "i", amount);
		MYSQL_ADD_FIELD("performer_id", "s", person);
		MYSQL_ADD_FIELD("category_enum", "s", operate);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
	}
};

// Define shared pointer type for convenience
typedef std::shared_ptr<NurseDO2> PtrNurseDO2;

#endif // !_NURSEDO2_
