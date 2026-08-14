#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2025/07/26

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
#ifndef _chinapres3IssueResultVO_H_
#define _chinapres3IssueResultVO_H_

#include "../../GlobalInclude.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Issue result data transfer object.
 *
 * Records summary info for the current issue batch:
 *   - Count of processed medication items
 *   - Count of involved prescriptions
 *   - Prescription numbers that were issued
 *   - Resulting status and issue timestamp
 *   - Dispense business serial numbers (busNos): used by pharmacy
 *     system to track and update dispensing status.
 *     Format: "BUS" + snowflake ID, generated per drug line.
 */
class chinapres3IssueResultDTO : public oatpp::DTO
{
    DTO_INIT(chinapres3IssueResultDTO, DTO);

    // Number of medication drug-line rows successfully processed
    API_DTO_FIELD_REQUIRE(
        Int32,
        processedCount,
        ZH_WORDS_GETTER("chinapres3.field.processedCount"),
        true);

    // Number of distinct prescriptions involved (one prescription may have multiple drug lines)
    API_DTO_FIELD_REQUIRE(
        Int32,
        prescriptionCount,
        ZH_WORDS_GETTER("chinapres3.field.prescriptionCount"),
        true);

    // List of issued prescription numbers, for front-end display
    DTO_FIELD(Vector<String>, prescriptionNos);
    DTO_FIELD_INFO(prescriptionNos) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.prescriptionNos");
    }

    // Prescription status after successful issue, always "ACTIVE"
    DTO_FIELD(String, statusEnum);
    DTO_FIELD_INFO(statusEnum) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.statusEnum");
    }

    // Issue timestamp (server time when the transaction committed)
    DTO_FIELD(String, issuedAt);
    DTO_FIELD_INFO(issuedAt) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.issuedAt");
    }

    // Dispense business serial numbers (busNos).
    // One busNo per drug line, format "BUS" + snowflake ID.
    // Used by downstream pharmacy system via bus_no lookup.
    DTO_FIELD(Vector<String>, busNos);
    DTO_FIELD_INFO(busNos) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.busNos");
    }
};

/**
 * Issue result standard JSON response wrapper.
 *
 * Outer envelope: { code, message, data: { processedCount, prescriptionCount,
 *   prescriptionNos, statusEnum, issuedAt, busNos } }
 */
class chinapres3IssueResultVO : public JsonVO<chinapres3IssueResultDTO::Wrapper>
{
    DTO_INIT(chinapres3IssueResultVO, JsonVO<chinapres3IssueResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_chinapres3IssueResultVO_H_
