#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
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
#ifndef _HISTORY_ORDER_DETAIL_VO_H_
#define _HISTORY_ORDER_DETAIL_VO_H_

#include "../../dto/prescription4/historyOrderDetailDTO.h"
#include "domain/dto/PageDTO.h"
#include "domain/vo/BaseJsonVO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class HistoryOrderDetailPageJsonVO : public JsonVO<PageDTO<HistoryOrderDetailDTO::Wrapper>::Wrapper> {
	DTO_INIT(HistoryOrderDetailPageJsonVO, JsonVO<PageDTO<HistoryOrderDetailDTO::Wrapper>::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // _HISTORY_ORDER_DETAIL_VO_H_
