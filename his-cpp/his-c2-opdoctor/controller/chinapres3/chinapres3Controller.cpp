#include "stdafx.h"
#include "chinapres3Controller.h"

/**
 * 签发处方接口执行逻辑
 *
 * 接收前端传入的处方签发DTO与当前登录用户JWT载荷信息
 * 调用 chinapres3Service.issue 完成处方签发业务逻辑
 * Service层内部处理处方数据校验、数据库写入、处方签名流程
 *
 * @param dto 签发入参DTO，包含就诊ID、患者ID、待签发处方数组
 * @param payload JWT载荷对象，携带当前操作医生、科室、医院身份信息
 * @return chinapres3IssueResultVO 签发结果VO，包含签发成功/失败状态、处方回执信息
 */
chinapres3IssueResultVO::Wrapper chinapres3Controller::execIssuechinapres3(
	const chinapres3IssueDTO::Wrapper& dto,
	const PayloadDTO& payload)
{
	// 调用业务服务层执行处方签发逻辑
	return service.issue(dto, payload);
}

// ---- 处方撤回相关执行函数 ----
/**
 * 撤回处方接口执行逻辑
 *
 * 接收前端传入的撤回DTO与登录用户JWT载荷
 * 调用 service.revoke 执行处方撤回、数据库状态更新
 *
 * @param dto 撤回入参DTO，包含需要撤销的处方编号数组
 * @param payload JWT载荷对象，校验操作医生权限
 * @return chinapres3RevokeResultVO 撤回结果VO，标记每条处方撤回成功/失败
 */
chinapres3RevokeResultVO::Wrapper chinapres3Controller::execRevokechinapres3(
	const chinapres3RevokeDTO::Wrapper& dto,
	const PayloadDTO& payload)
{
	return service.revoke(dto, payload);
}