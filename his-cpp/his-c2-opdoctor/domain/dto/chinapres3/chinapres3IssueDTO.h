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
#ifndef _chinapres3ISSUEDTO_H_
#define _chinapres3ISSUEDTO_H_

#include "../../GlobalInclude.h"
#include "chinapres3SignTargetDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 处方签发DTO
 *
 * 用于处方整体签发业务入参
 * 需要传入待签发目标集合，对应处方数据记录
 * 每个目标使用 chinapres3SignTargetDTO 承载识别信息
 *
 * @see chinapres3SignTargetDTO
 */
class chinapres3IssueDTO : public oatpp::DTO
{
    DTO_INIT(chinapres3IssueDTO, DTO);


    //就诊ID校验边界 判断所有待签发目标是否属于同一就诊
    // Encounter ID, which uniquely positions this encounter.
    // Used to validate that sign targets belong to the same encounter.
    // patientId is no longer required: it is derived from the medication request record itself.
    API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("chinapres3.field.encounterId"), true);

    //待签发目标集合，每一项代表一条需要签发的药品
    //OBject对应oatpp对象写法
    API_DTO_FIELD_REQUIRE(Vector<Object<chinapres3SignTargetDTO>>, signTargets, ZH_WORDS_GETTER("chinapres3.field.signTargets"), true);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_chinapres3ISSUEDTO_H_