#include "EmrDocumentDAO.h"
#include "EmrDocumentMapper.h"

uint64_t EmrDocumentDAO::count(const MedicalRecordQuery::Wrapper& query)
{
	string sql = "SELECT COUNT(*) FROM emr_document WHERE patient_id = ? AND is_deleted = 0";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, query->patientId.getValue(""));

	if (query->encounterId && !query->encounterId->empty()) {
		sql += " AND encounter_id != ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->encounterId.getValue(""));
	}
	if (query->keyWord) {
		sql += " AND (title LIKE CONCAT('%',?,'%') OR document_type_code LIKE CONCAT('%',?,'%'))";
		SQLPARAMS_PUSH(params, "s", std::string, query->keyWord.getValue(""));
		SQLPARAMS_PUSH(params, "s", std::string, query->keyWord.getValue(""));
	}
	return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrEmrDocumentDO> EmrDocumentDAO::selectList(const MedicalRecordQuery::Wrapper& query)
{
	string sql = "SELECT id, tenant_id, patient_id, encounter_id, document_type_code, title, status, source_template_id, created_at, updated_at, created_by, updated_by, is_deleted, deleted_at, deleted_by FROM emr_document WHERE patient_id = ? AND is_deleted = 0";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, query->patientId.getValue(""));
	if (query->encounterId && !query->encounterId->empty()) {
		sql += " AND encounter_id != ?";
		SQLPARAMS_PUSH(params, "s", std::string, query->encounterId.getValue(""));
	}
	if (query->keyWord) {
		sql += " AND (title LIKE CONCAT('%',?,'%') OR document_type_code LIKE CONCAT('%',?,'%'))";
		SQLPARAMS_PUSH(params, "s", std::string, query->keyWord.getValue(""));
		SQLPARAMS_PUSH(params, "s", std::string, query->keyWord.getValue(""));
	}
	sql += " ORDER BY updated_at DESC";
	sql += " LIMIT ?,?";
	SQLPARAMS_PUSH(params, "ull", uint64_t, (query->pageIndex.getValue(1) - 1) * query->pageSize.getValue(10));
	SQLPARAMS_PUSH(params, "ull", uint64_t, query->pageSize.getValue(10));

	return sqlSession->executeQuery<PtrEmrDocumentDO>(sql, EmrDocumentMapper(), params);
}