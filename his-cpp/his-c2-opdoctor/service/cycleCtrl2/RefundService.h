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
#ifndef _REFUND_SERVICE_
#define _REFUND_SERVICE_
#include "domain/query/cycleCtrl2-refund/RefundQuery.h"
#include "domain/dto/doctor/Refund2ApplyDTO.h"
#include "domain/dto/doctor/Refund2DetailDTO.h"

class RefundService
{
public:
	oatpp::List<oatpp::Object<Refund2DetailDTO>> queryRefundList(const Refund2Query::Wrapper& query);
	bool applyRefund(const Refund2ApplyDTO::Wrapper& dto, const std::string& operatorId);
};

#endif // !_REFUND_SERVICE_
