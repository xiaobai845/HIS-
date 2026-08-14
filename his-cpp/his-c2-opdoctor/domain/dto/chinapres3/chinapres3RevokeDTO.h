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
#ifndef _chinapres3RevokeDTO_H_
#define _chinapres3RevokeDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Revoke request DTO.
 *
 * Accepts a list of medication record IDs (med_medication_request.id).
 * All drug lines under the same prescription must be included (all-or-nothing).
 */
class chinapres3RevokeDTO : public oatpp::DTO
{
    DTO_INIT(chinapres3RevokeDTO, DTO);

    // Medication request record IDs to revoke
    API_DTO_FIELD_REQUIRE(
        Vector<String>,
        medicationRequestIds,
        ZH_WORDS_GETTER("chinapres3.field.medicationRequestId"),
        true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_chinapres3RevokeDTO_H_
