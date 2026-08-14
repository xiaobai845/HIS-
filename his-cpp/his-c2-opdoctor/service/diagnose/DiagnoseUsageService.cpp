#include "stdafx.h"

#include "DiagnoseUsageService.h"
#include "dao/diagnose/DiagnoseDAO.h"
#include "domain/do/diagnose/AdmEncounterDiagnosisDO.h"

PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper
DiagnoseUsageService::queryDiagnoseUsage(const DiagnoseUsageQuery::Wrapper& query)
{
	DiagnoseDAO diagnoseDao;

	// 1. Count total matching records
	uint64_t total = diagnoseDao.countDiagnoseUsageHistory(query);

	// 2. Assemble PageDTO
	PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper pageDto =
		PageDTO<DiagnoseUsageDTO::Wrapper>::createShared();

	if (total == 0)
	{
		pageDto->pageIndex = v_uint64(query->pageIndex.getValue(1));
		pageDto->pageSize = v_uint64(query->pageSize.getValue(10));
		pageDto->total = v_int64(0);
		pageDto->pages = v_int64(0);
		pageDto->rows = {};
		return pageDto;
	}

	// 3. Query paginated data
	std::list<PtrAdmEncounterDiagnosisDO> diagnoseUsageHistory =
		diagnoseDao.selectDiagnoseUsageHistory(query);

	// 4. Convert DO list to DTO list
	auto rows = oatpp::List<oatpp::Object<DiagnoseUsageDTO>>::createShared();
	for (const PtrAdmEncounterDiagnosisDO& diagnoseDo : diagnoseUsageHistory)
	{
		DiagnoseUsageDTO::Wrapper dto = DiagnoseUsageDTO::createShared();

		dto->id = diagnoseDo->getId();
		dto->encounterId = diagnoseDo->getEncounterId();
		dto->conditionId = diagnoseDo->getConditionId();
		dto->description = diagnoseDo->getDescription();
		dto->diagTypeCode = diagnoseDo->getDiagTypeCode();
		dto->diagCode = diagnoseDo->getDiagCode();
		dto->rank = diagnoseDo->getRank();
		dto->primaryFlag = diagnoseDo->getPrimaryFlag();
		dto->highestDiagFlag = diagnoseDo->getHighestDiagFlag();
		dto->tcmFlag = diagnoseDo->getTcmFlag();
		dto->tcmSyndromeGroup = diagnoseDo->getTcmSyndromeGroup();
		dto->medType = diagnoseDo->getMedType();
		dto->conditionCode = diagnoseDo->getConditionCode();
		dto->createdAt = diagnoseDo->getCreatedAt();

		pageDto->addData(dto);
	}

	// 5. Set pagination metadata
	pageDto->pageIndex = v_uint64(query->pageIndex.getValue(1));
	pageDto->pageSize = v_uint64(query->pageSize.getValue(10));
	pageDto->total = v_int64(static_cast<int64_t>(total));
	pageDto->calcPages();

	return pageDto;
}
