#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 11:01:02

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
#ifndef _PRESCRIPTIONVO_H_
#define _PRESCRIPTIONVO_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/doctor/Prescription2DetailDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 处方单列表响应VO
 */
class Prescription2DetailJsonVO : public ListJsonVO<Prescription2DetailDTO::Wrapper>
{
	DTO_INIT(Prescription2DetailJsonVO, ListJsonVO<Prescription2DetailDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRESCRIPTIONVO_H_
