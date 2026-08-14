#ifndef _chinapres3CONTROLLER_H_
#define _chinapres3CONTROLLER_H_

// VO、DTO 数据结构头文件引入
#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/chinapres3/chinapres3IssueDTO.h"
#include "../../domain/vo/chinapres3/chinapres3IssueResultVO.h"
// 撤回处方相关结构体头文件
#include "../../domain/dto/chinapres3/chinapres3RevokeDTO.h"
#include "../../domain/vo/chinapres3/chinapres3RevokeResultVO.h"
#include "../../service/chinapres3/chinapres3Service.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

// Swagger接口分组标签多语言词条
#define API_TAG ZH_WORDS_GETTER("chinapres3.tags.tag")

/**
 * 中医处方控制器
 *
 * 提供中医处方签发、撤回对外API接口
 * 所有接口均携带JWT身份鉴权
 * 内部依赖 chinapres3Service 处理业务逻辑
 * 入参DTO、出参VO统一封装请求与返回数据
 */
class chinapres3Controller : public oatpp::web::server::api::ApiController
{
	// 声明JWT权限拦截器
	API_ACCESS_DECLARE(chinapres3Controller);

public:
	// 处方签发接口Swagger文档定义（带鉴权）
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("chinapres3.issue.summary"),
		issuechinapres3,                              // 接口内部函数标识
		chinapres3IssueResultVO::Wrapper,              // 接口返回VO包装类型
		API_TAG);

	// POST /chinapres3/issue 处方签发路由绑定
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,                                   // 请求方法 POST
		"/chinapres3/issue",                          // 接口路径
		issuechinapres3,                              // 关联文档定义标识
		BODY_DTO(chinapres3IssueDTO::Wrapper, dto),   // 接收JSON请求体并绑定dto变量
		execIssuechinapres3(dto, authObject->getPayload()));

	// ---- 处方撤回接口文档定义 ----
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("chinapres3.recall.summary"),
		revokechinapres3,
		chinapres3RevokeResultVO::Wrapper,
		API_TAG);

	// POST /chinapres3/revoke 处方撤回路由绑定
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/chinapres3/revoke",
		revokechinapres3,
		BODY_DTO(chinapres3RevokeDTO::Wrapper, dto),
		execRevokechinapres3(dto, authObject->getPayload()));

private:
	// 处方业务服务实例
	chinapres3Service service;

	/**
	 * 处方签发执行函数
	 *
	 * 接收前端传入的签发DTO与JWT身份载荷
	 * 调用service.issue完成处方签发全业务流程
	 *
	 * @param dto 签发请求DTO，包含就诊ID、患者ID、待签署处方列表
	 * @param payload JWT载荷，存储当前操作医生、科室、医院身份信息
	 * @return chinapres3IssueResultVO 签发结果封装对象，返回成功/失败状态与回执
	 */
	chinapres3IssueResultVO::Wrapper execIssuechinapres3(
		const chinapres3IssueDTO::Wrapper& dto,
		const PayloadDTO& payload);

	// ---- 处方撤回执行函数 ----
	/**
	 * 处方撤回执行函数
	 *
	 * 调用service.revoke执行处方撤回、数据库状态变更逻辑
	 *
	 * @param dto 撤回请求DTO，包含需要撤销的处方编号数组
	 * @param payload JWT身份载荷，用于校验操作权限
	 * @return chinapres3RevokeResultVO 撤回结果VO，标记每条处方撤回执行结果
	 */
	chinapres3RevokeResultVO::Wrapper execRevokechinapres3(
		const chinapres3RevokeDTO::Wrapper& dto,
		const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif // !_chinapres3CONTROLLER_H_