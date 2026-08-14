#pragma once
#ifndef _EMRDOCUMENTDO_H_
#define _EMRDOCUMENTDO_H_

#include "../DoInclude.h"

class EmrDocumentDO : public BaseDO
{
    // 主键与租户
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    // 关联对象
    MYSQL_SYNTHESIZE(string, patientId, PatientId);
    MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
    // 页面上显示的核心信息
    MYSQL_SYNTHESIZE(string, documentTypeCode, DocumentTypeCode); // 文书类型编码
    MYSQL_SYNTHESIZE(string, title, Title);                       // 标题（如"门诊病历（标准）"）
    MYSQL_SYNTHESIZE(string, status, Status);                     // 状态（草稿）
    // 模板来源
    MYSQL_SYNTHESIZE(string, sourceTemplateId, SourceTemplateId);
    // 审计字段
    MYSQL_SYNTHESIZE(string, createdAt, CreatedAt);             // 创建时间 
    MYSQL_SYNTHESIZE(string, updatedAt, UpdatedAt);
    MYSQL_SYNTHESIZE(string, createdBy, CreatedBy);             // 创建人（医生ID）
    MYSQL_SYNTHESIZE(string, updatedBy, UpdatedBy);
    MYSQL_SYNTHESIZE(bool, isDeleted, IsDeleted);
    MYSQL_SYNTHESIZE(string, deletedAt, DeletedAt);
    MYSQL_SYNTHESIZE(string, deletedBy, DeletedBy);
public:
    EmrDocumentDO() : BaseDO("emr_document")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD_NULLABLE("tenant_id", "s", tenantId, false);
        MYSQL_ADD_FIELD_NULLABLE("patient_id", "s", patientId, false);
        MYSQL_ADD_FIELD_NULLABLE("encounter_id", "s", encounterId, false);
        MYSQL_ADD_FIELD_NULLABLE("document_type_code", "s", documentTypeCode, false);
        MYSQL_ADD_FIELD_NULLABLE("title", "s", title, false);
        MYSQL_ADD_FIELD_NULLABLE("status", "s", status, false);
        MYSQL_ADD_FIELD_NULLABLE("source_template_id", "s", sourceTemplateId, false);
        MYSQL_ADD_FIELD("created_at", "dt", createdAt);
        MYSQL_ADD_FIELD_NULLABLE("updated_at", "dt", updatedAt, false);
        MYSQL_ADD_FIELD_NULLABLE("created_by", "s", createdBy, false);
        MYSQL_ADD_FIELD_NULLABLE("updated_by", "s", updatedBy, false);
        MYSQL_ADD_FIELD("is_deleted", "b", isDeleted);
        MYSQL_ADD_FIELD_NULLABLE("deleted_at", "dt", deletedAt, false);
        MYSQL_ADD_FIELD_NULLABLE("deleted_by", "s", deletedBy, false);
    }
};

typedef std::shared_ptr<EmrDocumentDO> PtrEmrDocumentDO;

#endif // !_EMRDOCUMENTDO_H_