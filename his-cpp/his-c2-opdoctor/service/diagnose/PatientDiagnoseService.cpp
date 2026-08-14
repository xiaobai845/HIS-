#include "stdafx.h"

#include "PatientDiagnoseService.h"
#include "dao/diagnose/PatientDiagnoseDAO.h"

PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper
PatientDiagnoseService::queryPatientDiagnose(const PatientDiagnoseQuery::Wrapper& query)
{
	// 1. Resolve pagination parameters
	uint64_t pageIndex = query->pageIndex.getValue(1);
	uint64_t pageSize = query->pageSize.getValue(10);

	// 2. Resolve filter values
	std::string patientId = query->patientId.getValue("");
	std::string keyword = query->keyword.getValue("");
	std::string diagTypeCode = query->diagTypeCode.getValue("");
	std::string startDate = query->startDate.getValue("");
	std::string endDate = query->endDate.getValue("");

	// 3. Query with in-database JOIN — single SQL per count/select
	PatientDiagnoseDAO dao;

	// Get total count for pagination metadata (JOIN query)
	uint64_t total = dao.countDiagnosesByPatientId(
		patientId, keyword, diagTypeCode, startDate, endDate);

	// 4. If no matching records, return empty page
	PageDTO<DiagnoseUsageDTO::Wrapper>::Wrapper pageDTO =
		PageDTO<DiagnoseUsageDTO::Wrapper>::createShared();
	if (total == 0)
	{
		pageDTO->pageIndex = v_uint64(pageIndex);
		pageDTO->pageSize = v_uint64(pageSize);
		pageDTO->total = v_int64(0);
		pageDTO->pages = v_int64(0);
		pageDTO->rows = {};
		return pageDTO;
	}

	// 5. Calculate offset and query paginated data (JOIN query)
	uint64_t offset = (pageIndex - 1) * pageSize;
	std::list<PtrAdmEncounterDiagnosisDO> diagnosisList =
		dao.selectDiagnosesByPatientId(
			patientId, keyword, diagTypeCode, startDate, endDate,
			offset, pageSize);

	// 6. Convert DO list to DTO list
	auto rows = oatpp::List<oatpp::Object<DiagnoseUsageDTO>>::createShared();
	for (const auto& doItem : diagnosisList)
	{
		auto dto = DiagnoseUsageDTO::createShared();
		dto->id = doItem->getId();
		dto->encounterId = doItem->getEncounterId();
		dto->conditionId = doItem->getConditionId();
		dto->description = doItem->getDescription();
		dto->diagTypeCode = doItem->getDiagTypeCode();
		dto->diagCode = doItem->getDiagCode();
		dto->rank = doItem->getRank();
		dto->primaryFlag = doItem->getPrimaryFlag();
		dto->highestDiagFlag = doItem->getHighestDiagFlag();
		dto->tcmFlag = doItem->getTcmFlag();
		dto->tcmSyndromeGroup = doItem->getTcmSyndromeGroup();
		dto->medType = doItem->getMedType();
		dto->conditionCode = doItem->getConditionCode();
		dto->createdAt = doItem->getCreatedAt();
		rows->push_back(dto);
	}

	// 7. Assemble PageDTO
	pageDTO->pageIndex = v_uint64(pageIndex);
	pageDTO->pageSize = v_uint64(pageSize);
	pageDTO->total = v_int64(static_cast<int64_t>(total));
	pageDTO->calcPages();
	pageDTO->rows = rows;

	return pageDTO;
}
