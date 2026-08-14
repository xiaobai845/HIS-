# AI开发规范 - C++微服务项目

> 本规范适用于所有AI辅助开发工具，必须严格遵守。

## 项目信息

- **项目类型**: C++微服务架构
- **Web框架**: oat++
- **构建工具**: CMake
- **支持平台**: Windows/Linux
- **服务注册**: Nacos
- **数据库**: MySQL
- **缓存**: Redis
- **消息队列**: RocketMQ

---

## 强制性规则

### 1. 代码注释规范（最高优先级）

**AI生成源码文件时，所有注释必须使用英文**

- 文件头版权注释使用英文
- 代码行内注释使用英文
- 避免因中文字符导致的编码问题

### 2. 项目目录结构

```
模块名称/
├── conf/                    # 配置文件（Windows）
│   └── data-source.yaml     # 数据库配置
│   └── third-services.yaml  # 第三方服务配置
├── controller/              # 控制器层
│   └── 模块名/
│       └── XxxController.h
│       └── XxxController.cpp
├── service/                 # 业务逻辑层
│   └── 模块名/
│       └── XxxService.h
│       └── XxxService.cpp
├── dao/                     # 数据访问层
│   └── 模块名/
│       └── XxxDAO.h
│       └── XxxDAO.cpp
├── domain/                  # 领域模型
│   ├── do/                  # 数据库对象
│   │   └── 模块名/
│   │       └── XxxDO.h
│   ├── dto/                 # 数据传输对象
│   │   └── 模块名/
│   │       └── XxxDTO.h
│   ├── vo/                  # 视图对象
│   │   └── 模块名/
│   │       └── XxxVO.h
│   └── query/               # 查询对象
│       └── 模块名/
│           └── XxxQuery.h
├── fonts/                   # 字体文件
├── tpl/                     # 模板文件
├── CMakeLists.txt           # CMake配置
├── Macros.h                 # 通用宏定义
├── ServerInfo.h/cpp         # 服务器信息单例
├── stdafx.h/cpp             # 预编译头（Windows）
├── main.cpp                 # 程序入口
├── public.pem               # RSA公钥
├── zh-dict.yaml             # 中文字典配置（UTF-8）
└── README.md                # 模块说明（UTF-8）
```

### 3. 命名规范

#### 类名 - 大驼峰命名法（PascalCase）

| 类型 | 命名格式 | 示例 |
|------|---------|------|
| DO类 | {表名}DO | UserDO, OrderDO |
| DTO类 | {业务名}DTO | UserAddDTO, OrderQueryDTO |
| VO类 | {功能名}VO | UserPageVO, OrderDetailVO |
| Query类 | {业务名}Query | UserQuery, OrderQuery |
| Controller | {模块}Controller | UserController, OrderController |
| Service | {模块}Service | UserService, OrderService |
| DAO | {模块}DAO | UserDAO, OrderDAO |

#### 方法名 - 小驼峰命名法（camelCase）

| 操作类型 | 前缀 | 示例 |
|---------|------|------|
| 查询单个 | query/get/select | queryById(), getUserInfo() |
| 查询多个 | query/list/select | queryAll(), listUsers() |
| 统计 | count | countUsers(), countByStatus() |
| 新增 | add/save/insert | addUser(), saveOrder() |
| 删除 | remove/delete | removeUser(), deleteOrder() |
| 修改 | modify/update | modifyUser(), updateStatus() |
| Controller执行 | exec | execQueryAll(), execAddUser() |

#### 变量名 - 小驼峰命名法

- 成员变量: `userName`, `orderList`
- 局部变量: `result`, `userData`
- 布尔变量: `isValid`, `hasMore`
- 指针变量: `ptrUser`, `userPtr`

#### 常量 - 全大写下划线分隔

```cpp
const int MAX_USER_COUNT = 100;
const std::string DEFAULT_STATUS = "active";
```

#### 宏定义 - 全大写下划线分隔

```cpp
#define MYSQL_SYNTHESIZE(type, name, Name) ...
#define API_HANDLER_ENDPOINT_AUTH(...) ...
```

### 4. 代码模板

#### 文件头模板

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
```

#### Controller模板

```cpp
#ifndef _USERCONTROLLER_H_
#define _USERCONTROLLER_H_
#include "domain/query/user/UserQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/user/UserVO.h"
using namespace oatpp;

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("user.tag")

class UserController : public oatpp::web::server::api::ApiController {
    API_ACCESS_DECLARE(UserController);
public:
    // Endpoint info definition
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("user.query-all.summary"),
                                      queryAllUser, UserQuery, UserPageVO::Wrapper, API_TAG);
    // Endpoint binding
    API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/user/query-all", queryAllUser,
                                    UserQuery, execQueryAll(query));
private:
    UserPageVO::Wrapper execQueryAll(const UserQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_USERCONTROLLER_H_
```

#### DO模板

```cpp
#ifndef _USERDO_H_
#define _USERDO_H_

#include "../DoInclude.h"

class UserDO : public BaseDO {
    // User ID
    MYSQL_SYNTHESIZE(std::string, id, Id);
    // User nickname
    MYSQL_SYNTHESIZE(std::string, nickname, Nickname);
    // User age
    MYSQL_SYNTHESIZE(int, age, Age);

public:
    UserDO() : BaseDO("sample_user") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("nickname", "s", nickname);
        MYSQL_ADD_FIELD("age", "i", age);
    }
};

typedef std::shared_ptr<UserDO> PtrUserDO;

#endif // !_USERDO_H_
```

### 5. API接口规范

#### 接口路径命名

```
查询单个: /{module}/query-by-{field} 或 /{module}/query-one
查询列表: /{module}/query-all 或 /{module}/list
新增:     /{module}/add-{entity}
修改:     /{module}/modify-{entity}
删除:     /{module}/remove-{entity}
```

#### 示例

```
GET    /user/query-all      查询用户列表
GET    /user/query-one      查询单个用户
POST   /user/add-user       新增用户
POST   /user/modify-user    修改用户
POST   /user/remove-user    删除用户
```

---

## 技术栈依赖

### 核心库

- oatpp - Web框架
- oatpp-swagger - API文档
- mysql-connector-c++ - MySQL连接
- yaml-cpp - YAML配置解析
- jwt-cpp - JWT认证

### 可选组件

- redis++ - Redis客户端
- rocketmq-client-cpp - 消息队列
- fastdfs-client - 文件存储
- xlnt - Excel处理
- haru - PDF生成
- zxing-cpp - 二维码
- bcrypt - 密码加密

### 工具库

- nacos-cli - Nacos服务注册
- gtest/gmock - 单元测试
- stduuid - UUID生成

---

## 代码验证清单

生成代码后必须验证以下项目：

- [ ] **注释检查**: 所有注释使用英文
- [ ] **编译检查**: 可在Visual Studio中正常编译
- [ ] **警告检查**: 无 `warning C4819` 编码警告
- [ ] **命名检查**: 类名、方法名、变量名符合规范
- [ ] **文件头检查**: 包含标准版权声明
- [ ] **路径检查**: 文件位置符合目录结构规范
- [ ] **依赖检查**: 必要的include文件已添加

---

## 常见错误与解决方案

### 注释错误

| 错误 | 原因 | 解决方案 |
|------|------|---------|
| 代码中使用中文注释 | 用了中文注释 | 替换为英文注释 |

### 命名错误

| 错误 | 原因 | 解决方案 |
|------|------|---------|
| 类名不符合规范 | 未使用大驼峰 | 重命名为PascalCase |
| 方法名缺少前缀 | Controller方法未加exec | 添加exec前缀 |
| 变量名使用下划线 | 使用了snake_case | 改为camelCase |

---

## AI技能列表

项目已配置以下AI技能（位于 `.agents/skills/`）：

1. **crud-code-generator** - 根据表结构生成DO/Mapper/DAO/Service/Controller代码
2. **api-interface-generator** - 生成RESTful API控制器（DTO/VO/Query/Controller）

## 创建新模块

使用项目提供的 `copy-resources.bat` 工具创建新模块：

```batch
cd 项目根目录
copy-resources.bat
# 输入模块名称
```

该工具会自动：
- 从 `.skeleton` 复制模板文件
- 创建必要的目录结构
- 替换 CMakeLists.txt 和 README.md 中的模块名

---

## 执行优先级

1. **最高优先级**: AI生成源码注释必须使用英文
2. **高优先级**: 命名规范必须正确
3. **中优先级**: 目录结构必须符合规范
4. **低优先级**: 代码注释和文档

---

## 违规处理

如果生成的代码不符合本规范：
1. ❌ 不要提交不符合规范的代码
2. 🔧 立即重新生成，使用正确的注释和命名
3. ✅ 验证所有检查项通过
4. 📋 记录问题，避免重复发生

---

**重要提示：本规范是强制性的，所有AI辅助开发都必须严格遵守。在开始任何代码生成前，请确认理解并同意遵守以上所有规则。**
