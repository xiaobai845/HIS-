#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2026/07/27

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
#ifndef _chinapres3RevokeResultVO_H_
#define _chinapres3RevokeResultVO_H_

#include "../../GlobalInclude.h"
#include "domain/vo/JsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Revoke result data DTO.
 *
 * Reports how many prescriptions and medication lines were revoked,
 * along with the revoke timestamp. The operation is atomic: all
 * requested prescriptions succeed together or fail together.
 */
class chinapres3RevokeResultDTO : public oatpp::DTO
{
    DTO_INIT(chinapres3RevokeResultDTO, DTO);

    // Number of prescriptions successfully revoked
    API_DTO_FIELD_REQUIRE(
        Int32,
        revokedPrescriptionCount,
        ZH_WORDS_GETTER("chinapres3.field.revokedPrescriptionCount"),
        true);

    // Number of medication-request rows reverted to DRAFT
    API_DTO_FIELD_REQUIRE(
        Int32,
        revokedMedicationCount,
        ZH_WORDS_GETTER("chinapres3.field.revokedMedicationCount"),
        true);

    // Prescription numbers that were revoked
    DTO_FIELD(Vector<String>, revokedPrescriptionNos);
    DTO_FIELD_INFO(revokedPrescriptionNos) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.revokedPrescriptionNos");
    }

    // Revoke timestamp (server time when the transaction committed)
    DTO_FIELD(String, revokedAt);
    DTO_FIELD_INFO(revokedAt) {
        info->description = ZH_WORDS_GETTER("chinapres3.field.revokedAt");
    }
};

/**
 * Revoke result view object.
 *
 * Standard JSON response: { code, message, data: { ... } }
 */
class chinapres3RevokeResultVO : public JsonVO<chinapres3RevokeResultDTO::Wrapper>
{
    DTO_INIT(chinapres3RevokeResultVO, JsonVO<chinapres3RevokeResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_chinapres3RevokeResultVO_H_
