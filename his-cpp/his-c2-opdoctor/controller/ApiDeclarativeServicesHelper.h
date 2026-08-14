#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/09/26 20:17:49

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
#ifndef _APIDECLARATIVESERVICESHELPER_H_
#define _APIDECLARATIVESERVICESHELPER_H_
/**
 * Declarative service invocation macro definitions.
 * This file centralizes the import of declarative service class headers,
 * making them easier to manage and invoke.
 */

 // Required header imports
#include "oatpp/core/data/mapping/ObjectMapper.hpp"
#include "oatpp/web/client/HttpRequestExecutor.hpp"
//////////////////////////////////////////////////////////////////////////
// #TIP: Import project ApiClient headers here



//////////////////////////////////////////////////////////////////////////

/**
 * Macro for creating an API client instance.
 * @param _VAR_CLIENT_: Name of the client variable to be created
 * @param _VAR_MAPPER_: Name of the ObjectMapper variable for JSON serialization/deserialization
 * @param _CLASS_CLIENT_: Client class name
 * @param _EXECUTOR_NAME_: Name of the HttpRequestExecutor component (e.g., "gateway")
 */
#define API_CLIENT_CREATE(_VAR_CLIENT_, _VAR_MAPPER_, _CLASS_CLIENT_, _EXECUTOR_NAME_) \
OATPP_COMPONENT(std::shared_ptr<oatpp::web::client::HttpRequestExecutor>, requestExecutor, _EXECUTOR_NAME_); \
OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, _VAR_MAPPER_); \
auto _VAR_CLIENT_ = _CLASS_CLIENT_::createShared(requestExecutor, _VAR_MAPPER_)

#endif // !_APIDECLARATIVESERVICESHELPER_H_