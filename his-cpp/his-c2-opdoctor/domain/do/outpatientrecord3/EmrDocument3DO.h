#pragma once
#ifndef _EmrDocument3DO_H_
#define _EmrDocument3DO_H_

#include "../DoInclude.h"

/**
 * 电子病历文档数据库实体类
 *
 * 对应数据库物理表：emr_document（门诊电子病历主表）
 *
 * 映射电子病历完整业务实体字段。
 * 门诊病历保存/更新业务时使用该实体与数据库交互，
 * 存储前端Tiptap富文本编辑器产出的JSON病历正文。
 */
class EmrDocument3DO : public BaseDO
{
	// =============================
	// 主键字段区
	// =============================
	// 病历唯一ID，雪花算法分布式全局唯一标识
	MYSQL_SYNTHESIZE(string, id, Id);

	// =============================
	// 核心业务字段区
	// =============================
	// 患者ID，关联患者基础信息表，标识病历归属就诊人
	MYSQL_SYNTHESIZE(string, patientId, PatientId);
	// 就诊流水ID，单次门诊挂号就诊唯一标识
	MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
	// 病历文档类型编码，固定值示例：OUTPATIENT_RECORD 门诊病历
	MYSQL_SYNTHESIZE(string, documentTypeCode, DocumentTypeCode);
	// 病历标题，前端不传参时后端自动生成默认标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 病历正文内容，存储格式为 Tiptap/ProseMirror 富文本结构化JSON字符串
	MYSQL_SYNTHESIZE(string, content, Content);
	// 病历状态枚举值：
	// DRAFT 草稿 / SUBMITTED 已提交 / LOCKED 锁定 / ARCHIVED 归档
	MYSQL_SYNTHESIZE(string, status, Status);
	// 病历模板ID，关联emr_template模板表，记录创建病历使用的模板
	MYSQL_SYNTHESIZE(string, sourceTemplateId, SourceTemplateId);

	// =============================
	// 系统审计字段区（自动填充，前端无需传入）
	// =============================
	// 病历创建时间戳
	MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);
	// 病历最后更新时间戳
	MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
	// 创建人账号/操作员ID
	MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);
	// 最后更新人账号/操作员ID
	MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
	// 逻辑删除标识：0=正常有效数据，1=已软删除
	MYSQL_SYNTHESIZE(int, isDeleted, IsDeleted);
	// 租户ID，SaaS多医院隔离字段，区分不同医疗机构数据
	MYSQL_SYNTHESIZE(string, tenantId, TenantId);

public:
	/**
	 * 构造函数：绑定实体与数据库表名，映射C++成员变量与MySQL字段
	 */
	EmrDocument3DO() : BaseDO("emr_document")
	{
		// 绑定主键字段 id
		MYSQL_ADD_FIELD_PK("id", "s", id);

		// 绑定核心业务字段（数据库字段名 <-> 实体成员变量）
		MYSQL_ADD_FIELD("patient_id", "s", patientId);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
		MYSQL_ADD_FIELD("document_type_code", "s", documentTypeCode);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("content", "s", content);
		MYSQL_ADD_FIELD("status", "s", status);
		MYSQL_ADD_FIELD("source_template_id", "s", sourceTemplateId);

		// 绑定审计通用字段
		MYSQL_ADD_FIELD("created_at", "s", createdAt);
		MYSQL_ADD_FIELD("updated_at", "s", updatedAt);
		MYSQL_ADD_FIELD("created_by", "s", createdBy);
		MYSQL_ADD_FIELD("updated_by", "s", updatedBy);
		MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
	}
};

// 类型别名：简化std::shared_ptr<EmrDocument3DO>书写，全项目统一使用PtrEmrDocument3DO
typedef std::shared_ptr<EmrDocument3DO> PtrEmrDocument3DO;

#endif // !_EmrDocument3DO_H_