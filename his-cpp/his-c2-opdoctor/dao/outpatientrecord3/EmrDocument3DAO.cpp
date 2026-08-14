#include "stdafx.h"
#include "EmrDocument3DAO.h"
#include "EmrDocument3Mapper.h"
#include "SqlSession.h"
#include <sstream>

#define QUERY_HEAD "SELECT id,patient_id,encounter_id,document_type_code,title,content,status," \
                    "source_template_id,created_at,updated_at,created_by,updated_by," \
                    "is_deleted,tenant_id FROM emr_document "

PtrEmrDocument3DO EmrDocument3DAO::selectById(const std::string& id)
{
	std::ostringstream sql;
	sql << QUERY_HEAD;
	sql << "WHERE id=? AND is_deleted=0";
	EmrDocument3Mapper mapper;
	SqlParams params = { SqlParam("s", std::make_shared<std::string>(id)) };
	auto list = sqlSession->executeQuery<PtrEmrDocument3DO>(sql.str(), mapper, params);
	if (list.empty())
		return nullptr;
	return list.front();
}

PtrEmrDocument3DO EmrDocument3DAO::selectByEncounterId(const std::string& encounterId)
{
	std::ostringstream sql;
	sql << QUERY_HEAD;
	sql << "WHERE encounter_id=? AND document_type_code='OUTPATIENT_RECORD' AND is_deleted=0";
	EmrDocument3Mapper mapper;
	SqlParams params = { SqlParam("s", std::make_shared<std::string>(encounterId)) };
	auto list = sqlSession->executeQuery<PtrEmrDocument3DO>(sql.str(), mapper, params);
	if (list.empty())
		return nullptr;
	return list.front();
}
