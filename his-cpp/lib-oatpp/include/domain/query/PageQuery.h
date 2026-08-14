#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:35:41

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
#ifndef _PAGE_QUERY_
#define _PAGE_QUERY_
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)
/**
 * 分页查询基类
 *
 * 所有分页查询参数类可继承此类，复用 pageIndex 和 pageSize 两个通用分页字段。
 * 默认从第1页开始，每页显示10条记录。
 */
class PageQuery : public oatpp::DTO
{
	// 初始化宏，注册 DTO 类型
	DTO_INIT(PageQuery, DTO);
	// 当前页码，默认值为1（第一页）
	DTO_FIELD(UInt64, pageIndex) = 1;
	DTO_FIELD_INFO(pageIndex) {
		info->required = true;
#ifndef LINUX
		info->description = u8"当前页码";
#else
		info->description = "curr page index";
#endif
	}
	// 每页显示数量，默认值为10
	DTO_FIELD(UInt64, pageSize) = 10;
	DTO_FIELD_INFO(pageSize) {
		info->required = true;
#ifndef LINUX
		info->description = u8"每页显示数量";
#else
		info->description = "curr page size";
#endif
	}
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PAGE_QUERY_
