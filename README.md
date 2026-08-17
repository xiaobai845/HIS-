🚀HIS
相关概念参考：

百度百科-HIS
维基百科-HIS
医院常见的HIS、CIS、LIS、EMR、PACS、RIS都是指哪些系统？
📖 项目简介
zero-one-his集十大核心模块于一体，涵盖目录管理、基础数据配置、个性化设置、门诊/住院全流程管理、药房药库智能管控、精细化耗材管理、财务核算体系、医保合规对接及多维报表分析等功能模块，共计372项标准化功能。 系统深度适配民营及公立一二级医院业务场景，支持单体医院、集团化运营及区域医疗协同等多种部署模式，并通过国家信创认证体系，确保全栈技术自主可控。

核心功能

门诊收费
门诊医生站
门诊护士站
住院收费
住院医生站
住院护士站
药房管理
财务管理
医保管理
库房管理
报表管理
目录管理
基础数据
智能助手
🏗️ 系统架构图
项目主体骨架基于Spring Cloud Alibaba生态体系，融合Spring AI与Spring AI Alibaba提供智能应用能力，使用MySQL进行数据持久化管理，采用Vue3生态体系与Element Plus UI框架构建前端，同时提供C++微服务开发解决方案，并通过Jenkins实现CI/CD。

architecture

📁 项目结构说明
zero-one-his

.gitignore -- 忽略提交配置

README.md -- 项目自述文件

documents -- 环境搭建、编码规范、项目需求等等文档资源

his-cpp -- C++项目主体

his-frontend -- 前端项目主体

🛠️ 软件架构
☕ Java技术栈
🔧 后端核心技术栈
技术	说明	版本	备注
Spring	容器	6.2.7	https://spring.io/
Spring Web MVC	MVC框架	6.2.7	https://docs.spring.io/spring-framework/reference/6.2/web/webmvc.html
Beanvalidation	实体属性校验	3.5.0	https://beanvalidation.org/3.0/
MyBatis	ORM框架	3.5.19	https://mybatis.org/mybatis-3/zh_CN/index.html
MyBatis Plus	MyBatis的增强工具	3.5.16	https://baomidou.com/
MyBatis Plus Generator	代码生成器	3.5.16	https://github.com/baomidou/mybatis-plus/tree/v3.5.16
Druid	数据库连接池	1.2.27	https://github.com/alibaba/druid
Lombok	实体类增加工具	1.18.38	https://github.com/rzwitserloot/lombok
Hutool	Java工具类库	5.8.16	https://hutool.cn/docs/#/
Knife4j	API文档增强工具	4.5.0	https://gitee.com/xiaoym/knife4j
Nimbus JOSE JWT	JSON Web Token	10.8	https://bitbucket.org/connect2id/nimbus-jose-jwt/wiki/Home
Spring Boot	Spring快速开发脚手架	3.5.0	https://spring.io/projects/spring-boot
Spring Cloud	微服务框架	2025.0.0	https://spring.io/projects/spring-cloud
Spring Cloud Alibaba	微服务框架	2025.0.0.0	https://sca.aliyun.com/
Spring Authorization Server	认证服务	1.5.6	https://docs.spring.io/spring-authorization-server/reference/
Spring AI	人工智能工程的应用框架	1.1.2	https://spring.io/projects/spring-ai
Spring AI Alibaba	面向Java开发者的代理式人工智能框架	1.1.2.2	https://java2ai.com/
Sentinel	分布式系统的流量防卫兵	1.8.9	https://sentinelguard.io/zh-cn/
Seata	分布式事务解决方案	2.5.0	https://seata.io/zh-cn/
MapStruct	实体类映射代码生成器	1.6.3	https://mapstruct.org/
🔌 后端扩展技术栈
技术	说明	版本	备注
FesodSheet	Excel报表	2.0.1-incubating	https://github.com/apache/fesod
RocketMQ	消息队列中间件	5.3.1	https://github.com/alibaba/spring-cloud-alibaba/wiki/RocketMQ
WebSocket	即时通讯服务	6.2.7	https://docs.spring.io/spring-framework/reference/6.2/web/websocket.html
Elasticsearch	分布式搜索和分析引擎	8.10	https://www.elastic.co/guide/en/elasticsearch/reference/8.10/index.html
LogStash	日志收集工具	8.10	https://www.elastic.co/guide/en/logstash/8.10/index.html
Kibana	日志可视化查看工具	8.10	https://www.elastic.co/guide/en/kibana/8.10/index.html
logstash-logback-encoder	Logstash日志收集插件	9.0	https://github.com/logfellow/logstash-logback-encoder/tree/logstash-logback-encoder-9.0
spring-boot-admin	服务管理和监控面板	3.5.8	https://github.com/codecentric/spring-boot-admin
EasyEs	ES ORM开发框架	3.0.2	https://www.easy-es.cn/
spring-data-mongodb	Spring集成MongoDB	4.5.0	https://docs.spring.io/spring-data/mongodb/reference/4.5/preface.html
tianai-captcha	验证码插件	1.5.5	https://gitee.com/dromara/tianai-captcha
x-easypdf	pdf插件	3.5.5	https://gitee.com/dromara/x-easypdf
🎨 前端技术栈
⚡ 核心技术栈
技术	说明	版本	备注
Vue	前端框架	v3.x	https://v3.vuejs.org/
Vue-Router	路由框架	v5.x	https://next.router.vuejs.org/
Pinia	全局状态管理框架	v3.x	https://pinia.vuejs.org/
Axios	HTTP中间件	latest	https://github.com/axios/axios
Element-Plus	前端UI框架	latest	https://element-plus.gitee.io/zh-CN/
oidc-client-ts	前端授权组件	latest	https://github.com/authts/oidc-client-ts
🧩 扩展技术栈
技术	说明	版本	备注
ECharts	图表框架	latest	Apache ECharts
tianai-captcha	验证码插件	1.5.5	https://gitee.com/dromara/tianai-captcha
SheetJS	电子表格插件	0.20.3	https://docs.sheetjs.com/docs/
https://docs.sheetjs.com/docs/demos/frontend/vue
vue-plugin-hiprint	打印插件	0.0.60	https://gitee.com/CcSimple/vue-plugin-hiprint
wangEditor	富文本编辑器	v5	https://www.wangeditor.com/v5/
pdfobject	pdf预览插件	2.3.1	https://github.com/pipwerks/PDFObject
Vitest	测试框架	latest	https://cn.vitest.dev/
https://cn.vuejs.org/guide/scaling-up/testing.html
pinyin-pro	汉字转拼音库	latest	https://pinyin-pro.cn/
FcDesigner	表单设计器	latest	https://view.form-create.com/
bpmn-js	流程图编辑框架	latest	https://bpmn.io/toolkit/bpmn-js/
https://github.com/bpmn-io/bpmn-js-examples
Tiptap	无头文本编辑器	3.x	https://github.com/ueberdosis/tiptap
https://tiptap.dev/
💻 CPP技术栈
🔧 后端核心技术栈
技术	说明	版本	备注
oat++	Web框架	1.3.0	https://github.com/oatpp/oatpp
MySQL Connector	MySQL连接驱动库	8.4.0	https://dev.mysql.com/downloads/connector/cpp/
https://dev.mysql.com/doc/connector-cpp/1.1/en/connector-cpp-apps.html
jwt-cpp	JSON Web Token	v0.7.2	https://github.com/Thalhammer/jwt-cpp
OpenSSL	开源安全套接层协议	3.x	https://www.openssl.org/
https://www.xolphin.com/support/OpenSSL/OpenSSL_-_Installation_under_Windows
🔌 后端扩展技术栈
技术	说明	版本	备注
xlnt	excel报表	1.5.0	https://github.com/tfussell/xlnt
fastdfs	文件存储客户端	latest	https://gitee.com/fastdfs100
yaml-cpp	解析yaml数据	0.9.0	https://github.com/jbeder/yaml-cpp
nacos	nacos客户端	v1.1.1	https://github.com/nacos-group/nacos-sdk-cpp
redis++	redis连接客户端	1.3.15	https://github.com/sewenew/redis-plus-plus
rocketmq	rocketmq客户端	2.1.0	https://github.com/apache/rocketmq-client-cpp
mongo	mongodb客户端	4.3.0	https://www.mongodb.com/docs/drivers/cxx
libharu	pdf库	2.4.6	https://github.com/libharu/libharu
zxing	用于绘制各种码	2.3.0	https://github.com/zxing-cpp/zxing-cpp
⚙️ 环境要求
🛠️ 开发工具
工具	说明	版本	备注
Navicat	数据库连接工具	latest	https://www.navicat.com.cn/
RDM	Redis可视化管理工具	latest	https://github.com/uglide/RedisDesktopManager
https://gitee.com/qishibo/AnotherRedisDesktopManager
PowerDesigner	数据库设计工具	16.6	http://powerdesigner.de/
Axure	原型设计工具	9	https://www.axure.com/
MindMaster	思维导图设计工具	latest	http://www.edrawsoft.cn/mindmaster
Visio	流程图绘制工具	latest	https://www.microsoft.com/zh-cn/microsoft-365/visio/flowchart-software
Apifox	API接口调试工具	latest	https://apifox.com/
Mock.js	API接口模拟测试	latest	http://mockjs.com/
Git	项目版本管控工具	latest	https://git-scm.com/
Codeup	项目源码托管平台	latest	https://codeup.aliyun.com
Projex	开发过程管控平台	latest	https://devops.aliyun.com/projex
IDEA	Java开发IDE	2022.1.3+	https://www.jetbrains.com/idea/download
Apache Maven	Maven 构建工具	3.9.x	https://maven.apache.org/
Docker Maven	Maven Docker插件	0.40.2	https://dmp.fabric8.io/
https://github.com/fabric8io/docker-maven-plugin
VS	C++开发IDE	2022+	https://learn.microsoft.com/en-us/visualstudio/releases/2022/release-notes
Cmake	C++跨平台编译	latest	https://cmake.org/cmake/help/latest/index.html
gtest	测试框架	1.17.0	https://github.com/google/googletest
VS Code	前端开发IDE	latest	https://code.visualstudio.com/Download
🖥️ 开发环境
依赖环境	版本	备注
Windows	10+	操作系统
JDK	17+	https://www.injdk.cn/
NodeJS	24.15.0	https://nodejs.org/zh-cn/
PNPM	11.1.2	https://pnpm.io/zh/
🖧 服务器环境
依赖环境	版本	备注
Anolis OS	23.3GA	https://openanolis.cn/anolisos
Docker	latest	https://www.docker.com/
MySQL	8.4.9	https://www.mysql.com/cn/
Redis	7.4.8	https://redis.io/
Nacos	3.1.1	https://nacos.io/zh-cn/docs/quick-start-docker.html
Sentinel	1.8.9	https://github.com/alibaba/Sentinel/releases
Seata	2.5.0	https://github.com/seata/seata
RocketMQ	5.3.1	https://rocketmq.apache.org/
Nginx	latest	https://nginx.org/en/
FastDFS	V6.09	https://gitee.com/fastdfs100
ELK	8.19.14	https://www.elastic.co/guide/en/elastic-stack/8.19/index.html
MongoDB	6.0.26	https://www.mongodb.com/try/download/community
Jenkins	latest	https://www.jenkins.io/zh/doc/book/installing/
🙏 特别鸣谢
zero-one-his的诞生离不开开源软件和社区的支持，感谢以下开源项目及项目维护者：

spring：https://github.com/spring-projects
alibaba：https://github.com/alibaba
mybatis：https://github.com/mybatis/mybatis-3.git
mp：https://github.com/baomidou
api：https://gitee.com/xiaoym/knife4j
vue：https://github.com/vuejs
ui：https://github.com/ElemeFE
oatpp：https://github.com/oatpp/oatpp
同时也感谢其他没有明确写出来的开源组件提供给与维护者。
