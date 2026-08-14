#pragma once

#ifndef _chinapres3Service_H_
#define _chinapres3Service_H_

// 处方签发、撤回DTO与VO头文件
#include "../../domain/dto/chinapres3/chinapres3IssueDTO.h"
#include "../../domain/vo/chinapres3/chinapres3IssueResultVO.h"
// 撤回接口相关头文件
#include "../../domain/dto/chinapres3/chinapres3RevokeDTO.h"
#include "../../domain/vo/chinapres3/chinapres3RevokeResultVO.h"
// DAO数据访问层头文件：处方主表、发药记录表、收费项表
#include "../../dao/chinapres3/chinapres3MedicationRequestDAO.h"
#include "../../dao/chinapres3/chinapres3MedicationDispenseDAO.h"
#include "../../dao/chinapres3/chinapres3ChargeItemDAO.h"

/**
 * 中医处方业务服务层
 *
 * 签发处方核心流程：
 *   1. 校验入参就诊ID、患者ID、待签发处方列表非空
 *   2. 查询待签发处方主表数据，校验处方状态为草稿DRAFT、就诊/患者身份匹配
 *   3. 开启数据库事务，执行多表更新/插入操作
 *   4. 更新处方主表状态为已签发ACTIVE、生成发药记录、同步更新收费项
 *   5. 事务统一提交，出现任意异常全部回滚
 *   6. 封装签发结果VO，返回成功条数、处方编号列表等统计信息
 *
 * 依赖组件说明：
 *   - chinapres3MedicationRequestDAO    : 处方主表查询与更新
 *   - chinapres3MedicationDispenseDAO   : 处方发药记录新增
 *   - chinapres3ChargeItemDAO           : 门诊收费项同步更新
 *   - TransactionManager                : 数据库事务管理器
 *   - SnowFlake                         : 分布式雪花ID生成器
 *   - SimpleDateTimeFormat              : 统一时间格式化工具
 */
class chinapres3Service
{
	// 处方主表DAO：查询处方草稿、更新签发状态
	chinapres3MedicationRequestDAO medReqDAO;
	// 处方发药记录DAO：每张签发处方生成一条发药记录
	chinapres3MedicationDispenseDAO medDispDAO;
	// 收费项DAO：同步更新门诊收费单据，支持新增/修改
	chinapres3ChargeItemDAO chargeDAO;

public:
	/**
	 * 执行中医处方签发业务逻辑
	 *
	 * 完整业务步骤：
	 *   1. 入参校验：就诊encounterId、患者patientId、待签发列表signTargets不能为空
	 *   2. 遍历signTargets内每条medicationRequestId查询处方主表
	 *      - 校验处方记录是否存在
	 *      - 校验处方状态为草稿DRAFT，仅草稿处方允许签发
	 *      - 校验处方归属就诊ID、患者ID和入参一致
	 *   3. 通过事务管理器获取SqlSession，开启事务
	 *   4. 更新med_medication_request处方主表：状态改为ACTIVE、更新操作人/时间
	 *   5. 向med_medication_dispense插入发药记录：雪花ID、当前时间、发药状态PREPARATION
	 *   6. 同步操作adm_charge_item收费表，匹配业务单据执行新增/更新
	 *   7. 全部操作无异常则统一commit，出现任意异常执行rollback事务回滚
	 *   8. 统计成功签发数量、处方编号集合，封装返回数据
	 *   9. 通过OATPP共享指针构造返回VO，统一返回成功响应体
	 *
	 * @param dto 签发请求入参DTO，携带就诊ID、患者ID、待签发处方ID数组
	 * @param payload JWT载荷对象，获取操作医生用户名、账号ID
	 * @return chinapres3IssueResultVO::Wrapper 签发结果VO，包含成功/失败状态、统计信息
	 */
	chinapres3IssueResultVO::Wrapper issue(
		const chinapres3IssueDTO::Wrapper& dto,
		const PayloadDTO& payload);

	// ---- 处方撤回业务方法 ----
	/**
	 * 撤回已签发的中医处方
	 *
	 * 单张处方独立事务撤回流程：
	 *   1. 校验入参处方编号列表prescriptionNos不为空
	 *   2. 循环处理每一条处方号：
	 *      a. 查询medication_request处方主表，仅状态ACTIVE已签发处方允许撤回
	 *      b. 校验对应发药记录状态为待调配PREPARATION且未逻辑删除
	 *      c. 更新处方主表状态回退至DRAFT，更新操作人、操作时间
	 *      d. 发药记录执行逻辑删除is_deleted=1，更新操作信息
	 *      e. 同步收费项adm_charge_item逻辑删除is_deleted=1
	 *      f. 单张处方操作完成后独立提交事务，互不影响
	 *   3. 收集全部撤回成功数量、失败处方号及失败原因
	 *
	 * @param dto 撤回请求DTO，携带需要撤销的处方编号数组
	 * @param payload JWT载荷，提供当前操作人账号信息
	 * @return chinapres3RevokeResultVO::Wrapper 撤回结果，包含撤回计数、失败明细
	 */
	chinapres3RevokeResultVO::Wrapper revoke(
		const chinapres3RevokeDTO::Wrapper& dto,
		const PayloadDTO& payload);
};

#endif // !_chinapres3Service_H_