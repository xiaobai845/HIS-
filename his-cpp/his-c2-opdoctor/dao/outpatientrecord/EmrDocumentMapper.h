#pragma once
#ifndef _EMRDOCUMENTMAPPER_H_
#define _EMRDOCUMENTMAPPER_H_

#include "Mapper.h"
#include "domain/do/outpatientrecord/EmrDocumentDO.h"

class EmrDocumentMapper : public Mapper<PtrEmrDocumentDO>
{
public:
	PtrEmrDocumentDO mapper(ResultSet* resultSet) const override
	{
		PtrEmrDocumentDO docDO = std::make_shared<EmrDocumentDO>();
		docDO->setId(resultSet->getString("id"));
		docDO->setTenantId(resultSet->getString("tenant_id"));
		docDO->setPatientId(resultSet->getString("patient_id"));
		docDO->setEncounterId(resultSet->getString("encounter_id"));
		docDO->setDocumentTypeCode(resultSet->getString("document_type_code"));
		docDO->setTitle(resultSet->getString("title"));
		docDO->setStatus(resultSet->getString("status"));
		docDO->setSourceTemplateId(resultSet->getString("source_template_id"));
		docDO->setCreatedAt(resultSet->getString("created_at"));
		docDO->setUpdatedAt(resultSet->getString("updated_at"));
		docDO->setCreatedBy(resultSet->getString("created_by"));
		docDO->setUpdatedBy(resultSet->getString("updated_by"));
		docDO->setIsDeleted(resultSet->getInt("is_deleted"));
		docDO->setDeletedAt(resultSet->getString("deleted_at"));
		docDO->setDeletedBy(resultSet->getString("deleted_by"));
		return docDO;
	}
};

#endif // !_EMRDOCUMENTMAPPER_H_