/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/29
*/
#include "stdafx.h"
#include "ExecutionDAO.h"
#include "ExecutionMapper.h"

std::list<ExecutionDO> ExecutionDAO::selectByIds(const std::list<std::string>& ids)
{
	if (ids.empty()) return {};
	SqlParams params;
	stringstream sql;
	sql << "SELECT id,encounter_id,document_type,patient_name,doctor_name,remark,"
		"treatment_item,exec_dept,order_time,exec_time,executor,"
		"drug_name,specification,quantity,`usage`,frequency,"
		"receipt_no,charge_time,item_name,unit_price,amount,total_amount,"
		"dept_name,reg_time,reg_type,reg_level,queue_no,reg_fee,"
		"bed_no,admission_no,dosage,drip_rate,"
		"settle_date,operator_name,reg_total,drug_total,exam_total,lab_total,treatment_total,"
		"apply_dept,exam_item,exam_body_part,exam_method,"
		"lab_item,specimen_type,sample_time,diagnosis "
		"FROM opnurse_execution WHERE id IN (";
	bool first = true;
	for (auto& id : ids) {
		if (!first) sql << ",";
		first = false;
		sql << "?";
		SQLPARAMS_PUSH(params, "s", std::string, id);
	}
	sql << ")";
	return sqlSession->executeQuery<ExecutionDO>(sql.str(), ExecutionMapper(), params);
}

ExecutionDO ExecutionDAO::selectOne(const std::string& id)
{
	std::list<std::string> ids{ id };
	auto list = selectByIds(ids);
	if (!list.empty()) return std::move(list.front());
	return ExecutionDO();
}
