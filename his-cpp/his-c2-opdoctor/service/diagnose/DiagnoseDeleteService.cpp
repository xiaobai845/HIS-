#include "stdafx.h"

#include "DiagnoseDeleteService.h"
#include "dao/diagnose/DiagnoseDAO.h"
#include "domain/do/diagnose/AdmEncounterDiagnosisDO.h"

DiagnoseDeleteVO::Wrapper
DiagnoseDeleteService::deleteDiagnose(const std::string& id)
{
	return deleteDiagnose(id, "system");
}

DiagnoseDeleteVO::Wrapper
DiagnoseDeleteService::deleteDiagnose(const std::string& id, const std::string& deletedBy)
{
	DiagnoseDAO dao;
	int affectedRows = dao.deleteById(id, deletedBy);
	if (affectedRows <= 0)
	{
		return {};
	}

	PtrAdmEncounterDiagnosisDO ptrDiagnoseDo = dao.selectById(id);

	DiagnoseDeleteVO::Wrapper vo = DiagnoseDeleteVO::createShared();
	vo->id = id;
	vo->encounterId = ptrDiagnoseDo->getEncounterId();
	vo->conditionId = ptrDiagnoseDo->getConditionId();
	vo->deletedAt = ptrDiagnoseDo->getDeletedAt();
	vo->deletedBy = ptrDiagnoseDo->getDeletedBy();

	return vo;
}
