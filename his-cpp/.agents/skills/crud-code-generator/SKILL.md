---
name: crud-code-generator
description: 根据数据库表结构或业务需求，自动生成完整的CRUD代码，包括DO/DAO/Mapper/Service层
type: code-generation
---

# CRUD代码生成器

## 功能描述
根据数据库表结构或业务需求，自动生成完整的CRUD代码，包括DO（数据库对象）、DAO（数据访问层）、Mapper（结果映射器）、Service（业务逻辑层）。

## 职责范围
**本技能负责生成：**
- DO类（数据库对象）
- Mapper类（结果集映射器）
- DAO类（数据访问层）
- Service类（业务逻辑层）

## 工作流程
**第一步：完成DAO、Service层构建**
**第二步：调用api-interface-generator完成Controller层构建**
**第三步：Controller中execute方法调用Service逻辑**

## 输入要求
### 方式一：基于数据库表结构
```
表名: sample_order
字段信息:
- id: varchar(32), 主键, 唯一订单编号
- total_sales: double, 销售总量
- status: int, 订单状态
- create_time: varchar(32), 创建时间
- update_time: varchar(32), 更新时间
```

### 方式二：基于业务需求描述
```
业务模块: 订单管理
表名: sample_order
字段: id, totalSales, status, createTime, updateTime
```

## 输出内容

### 1. DO模板 (domain/do/xxx/XxxDO.h)

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
#ifndef _XXX_DO_
#define _XXX_DO_
#include "../DoInclude.h"

class XxxDO : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, sex, Sex);
    MYSQL_SYNTHESIZE(int, age, Age);
    MYSQL_SYNTHESIZE(string, createBy, CreateBy);
    MYSQL_SYNTHESIZE(string, createTime, CreateTime);
    MYSQL_SYNTHESIZE(string, updateBy, UpdateBy);
    MYSQL_SYNTHESIZE(string, updateTime, UpdateTime);
public:
    XxxDO() : BaseDO("table_name")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("sex", "s", sex);
        MYSQL_ADD_FIELD("age", "i", age);
        MYSQL_ADD_FIELD("create_by", "s", createBy);
        MYSQL_ADD_FIELD("create_time", "s", createTime);
        MYSQL_ADD_FIELD("update_by", "s", updateBy);
        MYSQL_ADD_FIELD("update_time", "s", updateTime);
    }
};

typedef std::shared_ptr<XxxDO> PtrXxxDO;
#endif // !_XXX_DO_
```

### 2. Mapper模板 (dao/xxx/XxxMapper.h)

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
#ifndef _XXX_MAPPER_
#define _XXX_MAPPER_
#include "Mapper.h"
#include "domain/do/xxx/XxxDO.h"

class XxxMapper : public Mapper<PtrXxxDO>
{
public:
    PtrXxxDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<XxxDO>();
        data->setId(resultSet->getString("id"));
        data->setName(resultSet->getString("name"));
        data->setSex(resultSet->getString("sex"));
        data->setAge(resultSet->getInt("age"));
        return data;
    }
};
#endif // !_XXX_MAPPER_
```

### 3. DAO头文件模板 (dao/xxx/XxxDAO.h)

**重要：DAO只扩展查询逻辑，不扩展新增、修改、删除方法**

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
#ifndef _XXX_DAO_
#define _XXX_DAO_
#include "BaseDAO.h"
#include "domain/do/xxx/XxxDO.h"
#include "domain/query/xxx/XxxQuery.h"

class XxxDAO : public BaseDAO
{
private:
    inline std::string queryConditionBuilder(const XxxQuery::Wrapper& query, SqlParams& params);
public:
    uint64_t count(const XxxQuery::Wrapper& query);
    std::list<XxxDO> selectWithPage(const XxxQuery::Wrapper& query);
    std::list<XxxDO> selectByName(const string& name);
    PtrXxxDO selectById(std::string id);
};
#endif // !_XXX_DAO_
```

### 4. DAO实现文件模板 (dao/xxx/XxxDAO.cpp)

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
#include "XxxDAO.h"
#include "XxxMapper.h"

std::string XxxDAO::queryConditionBuilder(const XxxQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE 1=1";
    if (query->name) {
        sqlCondition << " AND `name`=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->name.getValue(""));
    }
    if (query->sex) {
        sqlCondition << " AND sex=?";
        SQLPARAMS_PUSH(params, "s", std::string, query->sex.getValue(""));
    }
    if (query->age) {
        sqlCondition << " AND age=?";
        SQLPARAMS_PUSH(params, "i", int, query->age.getValue(0));
    }
    return sqlCondition.str();
}

uint64_t XxxDAO::count(const XxxQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM table_name ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<XxxDO> XxxDAO::selectWithPage(const XxxQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT id,name,sex,age FROM table_name ";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY IFNULL(`update_time`, `create_time`) DESC, `id` DESC ";
    sql += " LIMIT " + std::to_string(((query->pageIndex - 1) * query->pageSize)) + "," + std::to_string(query->pageSize);
    return sqlSession->executeQuery<XxxDO>(sql, XxxMapper(), params);
}

std::list<XxxDO> XxxDAO::selectByName(const string& name)
{
    string sql = "SELECT id,name,sex,age FROM table_name WHERE `name` LIKE CONCAT('%',?,'%')";
    return sqlSession->executeQuery<XxxDO>(sql, XxxMapper(), "%s", name);
}

PtrXxxDO XxxDAO::selectById(std::string id)
{
    string sql = "SELECT id,name,sex,age FROM table_name WHERE `id`=?";
    return sqlSession->executeQueryOne<PtrXxxDO>(sql, XxxMapper(), "%s", id);
}
```

### 5. Service头文件模板 (service/xxx/XxxService.h)

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
#ifndef _XXX_SERVICE_
#define _XXX_SERVICE_
#include "domain/vo/xxx/XxxVO.h"
#include "domain/query/xxx/XxxQuery.h"
#include "domain/dto/xxx/XxxDTO.h"

class XxxService
{
public:
    XxxPageDTO::Wrapper listAll(const XxxQuery::Wrapper& query);
    XxxDTO::Wrapper getById(std::string id);
    std::string saveData(const XxxAddDTO::Wrapper& dto);
    bool updateData(const XxxDTO::Wrapper& dto);
    bool removeData(const oatpp::List<oatpp::String>& ids);
};

#endif // !_XXX_SERVICE_
```

### 6. Service实现文件模板 (service/xxx/XxxService.cpp)

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
#include "XxxService.h"
#include "dao/xxx/XxxDAO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

XxxPageDTO::Wrapper XxxService::listAll(const XxxQuery::Wrapper& query)
{
    auto pages = XxxPageDTO::createShared();
    pages->pageIndex = query->pageIndex;
    pages->pageSize = query->pageSize;

    XxxDAO dao;
    uint64_t count = dao.count(query);
    if (count <= 0)
    {
        return pages;
    }

    pages->total = count;
    pages->calcPages();
    list<XxxDO> result = dao.selectWithPage(query);

    for (XxxDO& sub : result)
    {
        auto dto = XxxDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, sub, id, Id, name, Name, sex, Sex, age, Age);
        pages->addData(dto);
    }
    return pages;
}

XxxDTO::Wrapper XxxService::getById(std::string id)
{
    XxxDAO dao;
    auto res = dao.selectById(id);
    if (!res)
        return nullptr;

    auto dto = XxxDTO::createShared();
    ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res, id, Id, name, Name, sex, Sex, age, Age);
    return dto;
}

std::string XxxService::saveData(const XxxAddDTO::Wrapper& dto)
{
    XxxDO data;
    ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Name, name, Sex, sex, Age, age);
    UuidFacade uf;
    data.setId(uf.genUuid());
    data.setCreateBy(dto->getPayload()->getUsername());
    data.setCreateTime(SimpleDateTimeFormat::format());
    XxxDAO dao;
    return dao.insert(data) == 1 ? data.getId() : "";
}

bool XxxService::updateData(const XxxDTO::Wrapper& dto)
{
    XxxDO data;
    ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Name, name, Sex, sex, Age, age, Id, id);
    data.setUpdateBy(dto->getPayload()->getUsername());
    data.setUpdateTime(SimpleDateTimeFormat::format());
    XxxDAO dao;
    return dao.update(data) == 1;
}

bool XxxService::removeData(const oatpp::List<oatpp::String>& ids)
{
    XxxDAO dao;
    std::list<std::string> datas;
    for (auto one : *ids.get())
        datas.emplace_back(one.getValue({}));
    int rows = dao.deleteByIds<XxxDO>(datas);
    if (rows == ids->size())
        return true;
    return false;
}
```

### 7. Controller实现文件模板 (controller/xxx/XxxController.cpp)

**重要：Controller调用Service层逻辑（工作流第三步）**

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
#include "../../service/xxx/XxxService.h"

XxxJsonVO::Wrapper XxxController::execQueryOne(const String& id)
{
    auto jvo = XxxJsonVO::createShared();
    if (!id)
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    auto res = XxxService().getById(id.getValue({}));
    jvo->success(res);
    return jvo;
}

XxxPageJsonVO::Wrapper XxxController::execQueryAll(const XxxQuery::Wrapper& query)
{
    auto result = XxxService().listAll(query);
    auto jvo = XxxPageJsonVO::createShared();
    jvo->success(result);
    return jvo;
}

StringJsonVO::Wrapper XxxController::execAddXxx(const XxxAddDTO::Wrapper& dto)
{
    auto jvo = StringJsonVO::createShared();
    std::string errmsg = dto->validate();
    if (errmsg != "")
    {
        jvo->init(errmsg, RS_PARAMS_INVALID);
        return jvo;
    }
    std::string id = XxxService().saveData(dto);
    if (id != "") {
        jvo->success(id);
    }
    else
    {
        jvo->fail("");
    }
    return jvo;
}

StringJsonVO::Wrapper XxxController::execModifyXxx(const XxxDTO::Wrapper& dto)
{
    auto jvo = StringJsonVO::createShared();
    if (!dto->id)
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    if (XxxService().updateData(dto)) {
        jvo->success(dto->id);
    }
    else
    {
        jvo->fail(dto->id);
    }
    return jvo;
}

ListJsonVO<String>::Wrapper XxxController::execRemoveXxx(const List<String>& ids)
{
    auto jvo = ListJsonVO<String>::createShared();
    if (ids->empty())
    {
        jvo->init(nullptr, RS_PARAMS_INVALID);
        return jvo;
    }
    if (XxxService().removeData(ids)) {
        jvo->success(ids);
    }
    else
    {
        jvo->fail(nullptr);
    }
    return jvo;
}
```

## 代码规范

### DAO职责
- **只扩展查询逻辑**：count、selectWithPage、selectById等
- **不扩展新增、修改、删除方法**：直接使用BaseDAO父类方法
- DAO查询方法必须使用Mapper

### Service职责
- **直接调用BaseDAO的增删改方法**：insert、update、deleteById等
- **负责DO与DTO之间的转换**
- **使用宏 `ZO_STAR_DOMAIN_DO_TO_DTO` 进行DO到DTO转换**

### 命名规范
- 类名使用大驼峰命名法（PascalCase）
- 方法名使用小驼峰命名法（camelCase）

## 重要提示
**生成代码时，所有注释必须使用英文，不要使用中文注释。**
- 文件头版权注释使用英文
- 代码行内注释使用英文
- 避免因中文字符导致的编码问题
