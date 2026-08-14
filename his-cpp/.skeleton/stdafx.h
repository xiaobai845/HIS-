// stdafx.h: Precompiled header file.
// The headers listed below are compiled only once, improving build times for subsequent builds.
// This also enhances IntelliSense performance, including features such as code completion and navigation.
// However, if any of these headers are modified between builds, all of them will be rebuilt. 
// Do not add frequently changing headers here, as this will diminish the performance benefit.
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 23:00:54

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
#ifndef STDAFX_H
#define STDAFX_H

#ifndef LINUX
#include "OatppMacros.h"
// Import headers that define types needed before _HAS_STD_BYTE is defined
#include "id/UuidFacade.h"

// Resolve std::byte type redefinition
#ifdef _HAS_STD_BYTE
#undef _HAS_STD_BYTE
#endif
#define _HAS_STD_BYTE 0

// Add headers to be precompiled here
#include "mysql/jdbc.h"
#include "SqlSession.h"
#include "yaml-cpp/yaml.h"
#include "sw/redis++/redis++.h"

#endif // !LINUX

#endif //STDAFX_H
