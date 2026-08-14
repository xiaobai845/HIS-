#include "stdafx.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "dao/diagnose/DiagnoseDAO.h"
#include "DiagnoseAddService.h"
#include "domain/do/diagnose/AdmEncounterDiagnosisDO.h"


namespace
{
	std::string currentDateTime()
	{
		auto now = std::chrono::system_clock::now();
		auto timeT = std::chrono::system_clock::to_time_t(now);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			now.time_since_epoch()) % 1000;
		std::tm tmBuf;
#ifdef _WIN32
		localtime_s(&tmBuf, &timeT);
#else
		localtime_r(&timeT, &tmBuf);
#endif
		std::ostringstream oss;
		oss << std::put_time(&tmBuf, "%Y-%m-%d %H:%M:%S")
			<< "." << std::setfill('0') << std::setw(3) << ms.count();
		return oss.str();
	}
}

DiagnoseAddVO::Wrapper
DiagnoseAddService::DiagnoseAdd(const DiagnoseAddDTO::Wrapper& dto)
{
	UuidFacade uf;
	std::string uuid = uf.genUuid();
	if (uuid.empty())
	{
		return {};
	}

	AdmEncounterDiagnosisDO diagnoseDo;
	diagnoseDo.setId(uuid);
	diagnoseDo.setCreatedAt(currentDateTime());

	ZO_STAR_DOMAIN_DTO_TO_DO(diagnoseDo, dto,
		EncounterId, encounterId,
		ConditionId, conditionId,
		Description, description,
		DiagTypeCode, diagTypeCode,
		DiagCode, diagCode,
		Rank, rank,
		PrimaryFlag, primaryFlag,
		HighestDiagFlag, highestDiagFlag,
		TcmFlag, tcmFlag,
		TcmSyndromeGroup, tcmSyndromeGroup,
		MedType, medType,
		ConditionCode, conditionCode
	);

	DiagnoseDAO diagnoseDao;
	int affectedRows = diagnoseDao.insertDiagnose(diagnoseDo);
	if (affectedRows <= 0)
	{
		return {};
	}

	PtrAdmEncounterDiagnosisDO ptrDiagnoseDo = diagnoseDao.getCreatedAtById(uuid);

	DiagnoseAddVO::Wrapper vo = DiagnoseAddVO::createShared();
	vo->id = uuid;
	vo->encounterId = dto->encounterId;
	vo->description = dto->description;
	vo->primaryFlag = dto->primaryFlag;
	vo->createdAt = ptrDiagnoseDo->getCreatedAt();

	return vo;
}
