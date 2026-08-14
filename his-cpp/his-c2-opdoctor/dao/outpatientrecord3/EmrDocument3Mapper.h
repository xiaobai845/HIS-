#pragma once
/*
版权所有 Zero One Star，保留所有权利。

 @作者: his-c2-opdoctor
 @日期: 2026/07/28

 本文件遵循 Apache 2.0 开源许可证协议；
 你仅可在完全遵守许可证条款的前提下使用本文件。
 你可通过以下地址获取完整许可证原文：

	  https://www.apache.org/licenses/LICENSE-2.0

 除非现行法律要求或双方书面达成一致，本软件以“现有状态”分发，
 不附带任何明示或暗示的担保（包括适销性、适配特定用途等担保）。
 请查阅许可证，了解权限范围、使用约束与免责条款。
*/
#ifndef _EmrDocument3Mapper_H_
#define _EmrDocument3Mapper_H_

#include "Mapper.h"
#include "../../domain/do/outpatientrecord3/EmrDocument3DO.h"

/**
 * 电子病历数据库结果集映射器
 *
 * 作用：将数据库查询返回的单行结果集（ResultSet）转换为 EmrDocument3DO 实体对象
 * 完整映射 emr_document 数据表全部字段，一一赋值给DO实体对应的属性
 */
class EmrDocument3Mapper : public Mapper<PtrEmrDocument3DO>
{
public:
	/**
	 * 重写父类映射方法，执行数据库行→C++实体的转换逻辑
	 * @param resultSet 数据库查询返回的单行数据集
	 * @return 填充完字段的电子病历DO智能指针对象
	 */
	PtrEmrDocument3DO mapper(ResultSet* resultSet) const override
	{
		// 创建空的电子病历DO共享指针对象
		auto data = std::make_shared<EmrDocument3DO>();

		// ========== 主键字段赋值 ==========
		// 读取数据库id字段，赋值给DO主键
		data->setId(resultSet->getString("id"));

		// ========== 核心业务字段赋值 ==========
		// 患者ID
		data->setPatientId(resultSet->getString("patient_id"));
		// 门诊就诊流水ID
		data->setEncounterId(resultSet->getString("encounter_id"));
		// 病历类型编码
		data->setDocumentTypeCode(resultSet->getString("document_type_code"));
		// 病历标题
		data->setTitle(resultSet->getString("title"));
		// 病历富文本JSON内容
		data->setContent(resultSet->getString("content"));
		// 病历状态（草稿/提交/归档等）
		data->setStatus(resultSet->getString("status"));
		// 病历模板ID
		data->setSourceTemplateId(resultSet->getString("source_template_id"));

		// ========== 系统审计字段赋值 ==========
		// 创建时间
		data->setCreatedAt(resultSet->getString("created_at"));
		// 更新时间
		data->setUpdatedAt(resultSet->getString("updated_at"));
		// 创建操作人
		data->setCreatedBy(resultSet->getString("created_by"));
		// 最后更新操作人
		data->setUpdatedBy(resultSet->getString("updated_by"));
		// 逻辑删除标记（int类型，0正常，1删除）
		data->setIsDeleted(resultSet->getInt("is_deleted"));
		// 多租户机构ID
		data->setTenantId(resultSet->getString("tenant_id"));

		// 返回填充完成的病历实体
		return data;
	}
};

#endif // !_EmrDocument3Mapper_H_