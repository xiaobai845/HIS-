#include "stdafx.h"
#include "MedicalRecordService.h"
#include "dao/outpatientrecord/EmrDocumentDAO.h"
#include "dao/mongo/MongoDictDAO.h"

MedicalRecordPageDTO::Wrapper MedicalRecordService::queryList(const MedicalRecordQuery::Wrapper& query)
{
	auto page = MedicalRecordPageDTO::createShared();
	page->pageIndex = query->pageIndex;
	page->pageSize = query->pageSize;

	EmrDocumentDAO dao;
	auto total = dao.count(query);
	if (total <= 0) {
		return page;
	}
	page->total = total;
	page->calcPages();

	auto list = dao.selectList(query);
	MongoDictDAO mongoDao;
	for (auto& record : list) {
		auto dto = MedicalRecordDTO::createShared();
		dto->recordId = record->getId();
		dto->recordName = record->getTitle();
		dto->status = record->getStatus();
		dto->updatedTime = record->getUpdatedAt();
		dto->statusName = mongoDao.getDictName("emr_document_status", record->getStatus());
		page->addData(dto);
	}
	return page;
}