---
name: api-interface-generator
description: 基于业务需求快速生成RESTful API控制器代码，符合项目规范和路由配置
type: code-generation
---

# API接口快速生成器

## 功能描述
基于业务需求快速生成RESTful API控制器代码，符合项目规范和路由配置。

## 职责范围
**本技能只负责Controller控制器相关构建：**
- Controller头文件 (.h)
- Controller实现文件 (.cpp)
- 路由配置更新

## 输入要求
```
模块名称: order
API端点:
1. GET /order/query-one - 根据ID查询
2. GET /order/query-all - 分页查询列表
3. POST /order/add - 新增订单
4. PUT /order/modify - 修改订单
5. DELETE /order/remove - 删除订单
```

## 输出内容

### 1. Controller头文件 (controller/xxx/XxxController.h)

```cpp
#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: [Author Name]
 @Date: [YYYY/MM/DD HH:MM:SS]

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
#ifndef _XXX_CONTROLLER_
#define _XXX_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/xxx/XxxQuery.h"
#include "domain/dto/xxx/XxxDTO.h"
#include "domain/vo/xxx/XxxVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("xxx.tags.t1")

class XxxController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(XxxController);
public:
    // Query by ID
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("xxx.query-one.summary"), queryOne, XxxJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("xxx.field.id"), "", true);
    );
    API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/{module}/query-one", queryOne, QUERY(String, id), execQueryOne(id));

    // Query all with pagination
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("xxx.query-all.summary"), queryAll, XxxQuery, XxxPageJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/{module}/query-all", queryAll, XxxQuery, execQueryAll(query));

    // Add new
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("xxx.add.summary"), addXxx, StringJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/{module}/add", addXxx, BODY_DTO(XxxAddDTO::Wrapper, dto), execAddXxx(dto));

    // Modify
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("xxx.modify.summary"), modifyXxx, StringJsonVO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/{module}/modify", modifyXxx, BODY_DTO(XxxDTO::Wrapper, dto), execModifyXxx(dto));

    // Remove
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("xxx.remove.summary"), removeXxx, ListJsonVO<String>::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/{module}/remove", removeXxx, BODY_DTO(List<String>, ids), execRemoveXxx(ids));

private:
    XxxJsonVO::Wrapper execQueryOne(const String& id);
    XxxPageJsonVO::Wrapper execQueryAll(const XxxQuery::Wrapper& query);
    StringJsonVO::Wrapper execAddXxx(const XxxAddDTO::Wrapper& dto);
    StringJsonVO::Wrapper execModifyXxx(const XxxDTO::Wrapper& dto);
    ListJsonVO<String>::Wrapper execRemoveXxx(const List<String>& ids);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)
#endif // !_XXX_CONTROLLER_
```

### 2. Controller实现文件 (controller/xxx/XxxController.cpp)

**重要：execute方法定义直接返回{}空对象，保证编译通过**

```cpp
/*
 Copyright Zero One Star. All rights reserved.

 @Author: [Author Name]
 @Date: [YYYY/MM/DD HH:MM:SS]

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
#include "stdafx.h"
#include "XxxController.h"

XxxJsonVO::Wrapper XxxController::execQueryOne(const String& id)
{
    return {};
}

XxxPageJsonVO::Wrapper XxxController::execQueryAll(const XxxQuery::Wrapper& query)
{
    return {};
}

StringJsonVO::Wrapper XxxController::execAddXxx(const XxxAddDTO::Wrapper& dto)
{
    return {};
}

StringJsonVO::Wrapper XxxController::execModifyXxx(const XxxDTO::Wrapper& dto)
{
    return {};
}

ListJsonVO<String>::Wrapper XxxController::execRemoveXxx(const List<String>& ids)
{
    return {};
}
```

### 3. DTO模板 (domain/dto/xxx/XxxDTO.h)

```cpp
#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: [Author Name]
 @Date: [YYYY/MM/DD HH:MM:SS]

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
#ifndef _XXX_DTO_
#define _XXX_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class XxxAddDTO : public oatpp::DTO
{
    DTO_INIT(XxxAddDTO, DTO);
    DTO_FIELD(String, field1);
    DTO_FIELD_INFO(field1) {
        info->description = ZH_WORDS_GETTER("xxx.field.field1");
    }
    DTO_FIELD(Int32, field2);
    DTO_FIELD_INFO(field2) {
        info->description = ZH_WORDS_GETTER("xxx.field.field2");
    }
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
    std::string validate()
    {
        if (!field1 || field1->empty())
            return "field1 invalidate.";
        if (!field2 || field2 < 0)
            return "field2 invalidate.";
        return "";
    }
};

class XxxDTO : public XxxAddDTO
{
    DTO_INIT(XxxDTO, XxxAddDTO);
    DTO_FIELD(String, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("xxx.field.id");
    }
};

class XxxPageDTO : public PageDTO<XxxDTO::Wrapper>
{
    DTO_INIT(XxxPageDTO, PageDTO<XxxDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_XXX_DTO_
```

### 4. VO模板 (domain/vo/xxx/XxxVO.h)

```cpp
#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: [Author Name]
 @Date: [YYYY/MM/DD HH:MM:SS]

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
#ifndef _XXX_VO_
#define _XXX_VO_

#include "../../GlobalInclude.h"
#include "../../dto/xxx/XxxDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class XxxJsonVO : public JsonVO<XxxDTO::Wrapper> {
    DTO_INIT(XxxJsonVO, JsonVO<XxxDTO::Wrapper>);
};

class XxxPageJsonVO : public JsonVO<XxxPageDTO::Wrapper> {
    DTO_INIT(XxxPageJsonVO, JsonVO<XxxPageDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_XXX_VO_
```

### 5. Query模板 (domain/query/xxx/XxxQuery.h)

```cpp
#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: [Author Name]
 @Date: [YYYY/MM/DD HH:MM:SS]

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
#ifndef _XXX_QUERY_
#define _XXX_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class XxxQuery : public PageQuery
{
    DTO_INIT(XxxQuery, PageQuery);
    DTO_FIELD(String, keyword);
    DTO_FIELD_INFO(keyword) {
        info->description = ZH_WORDS_GETTER("xxx.field.keyword");
    }
    DTO_FIELD(Int32, status);
    DTO_FIELD_INFO(status) {
        info->description = ZH_WORDS_GETTER("xxx.field.status");
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_XXX_QUERY_
```

### 6. 更新Router.cpp

添加控制器路由绑定：
```cpp
#include "{module}/XxxController.h"
ROUTER_SIMPLE_BIND(XxxController);
```

### 7. 更新zh-dict.yaml

更新项目模块下的 `zh-dict.yaml` 文件，添加模块的中文词典配置：

```yaml
模块名称:
  tags:
    t1: 模块名称接口
  query-one:
    summary: 根据ID查询数据
  query-all:
    summary: 分页查询数据列表
  add:
    summary: 新增数据
  modify:
    summary: 修改数据
  remove:
    summary: 删除数据
  field:
    id: 编号
    name: 名称
    field1: 字段1
    field2: 字段2
```

**配置说明：**
- `tags.t1`: Controller的API_TAG
- `query-one.summary`: GET /{module}/query-one 接口描述
- `query-all.summary`: GET /{module}/query-all 接口描述
- `add.summary`: POST /{module}/add 接口描述
- `modify.summary`: PUT /{module}/modify 接口描述
- `remove.summary`: DELETE /{module}/remove 接口描述
- `field.*`: 各字段的中文描述

## 重要提示
**生成代码时，所有注释必须使用英文，不要使用中文注释。**
- 文件头版权注释使用英文
- 代码行内注释使用英文
- 避免因中文字符导致的编码问题

**zh-dict.yaml配置必须使用中文描述。**
- zh-dict.yaml是中文词典，用于API文档显示，**必须使用中文**
- 例如：`summary: 根据ID查询用户`、`field.name: 用户姓名`
