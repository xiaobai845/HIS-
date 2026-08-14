#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/29
*/
#ifndef _EXECUTION_MAPPER_
#define _EXECUTION_MAPPER_

#include "Mapper.h"
#include "../../domain/do/opnurse/ExecutionDO.h"

class ExecutionMapper : public Mapper<ExecutionDO>
{
public:
	ExecutionDO mapper(ResultSet* rs) const override
	{
		ExecutionDO data;
		data.setId(rs->getString(1));
		data.setEncounterId(rs->getString(2));
		data.setDocumentType(rs->getString(3));
		data.setPatientName(rs->getString(4));
		data.setDoctorName(rs->getString(5));
		data.setRemark(rs->getString(6));
		data.setTreatmentItem(rs->getString(7));
		data.setExecDept(rs->getString(8));
		data.setOrderTime(rs->getString(9));
		data.setExecTime(rs->getString(10));
		data.setExecutor(rs->getString(11));
		data.setDrugName(rs->getString(12));
		data.setSpecification(rs->getString(13));
		data.setQuantity(rs->getString(14));
		data.setUsage(rs->getString(15));
		data.setFrequency(rs->getString(16));
		data.setReceiptNo(rs->getString(17));
		data.setChargeTime(rs->getString(18));
		data.setItemName(rs->getString(19));
		data.setUnitPrice(rs->getString(20));
		data.setAmount(rs->getString(21));
		data.setTotalAmount(rs->getString(22));
		data.setDeptName(rs->getString(23));
		data.setRegTime(rs->getString(24));
		data.setRegType(rs->getString(25));
		data.setRegLevel(rs->getString(26));
		data.setQueueNo(rs->getString(27));
		data.setRegFee(rs->getString(28));
		data.setBedNo(rs->getString(29));
		data.setAdmissionNo(rs->getString(30));
		data.setDosage(rs->getString(31));
		data.setDripRate(rs->getString(32));
		data.setSettleDate(rs->getString(33));
		data.setOperatorName(rs->getString(34));
		data.setRegTotal(rs->getString(35));
		data.setDrugTotal(rs->getString(36));
		data.setExamTotal(rs->getString(37));
		data.setLabTotal(rs->getString(38));
		data.setTreatmentTotal(rs->getString(39));
		data.setApplyDept(rs->getString(40));
		data.setExamItem(rs->getString(41));
		data.setExamBodyPart(rs->getString(42));
		data.setExamMethod(rs->getString(43));
		data.setLabItem(rs->getString(44));
		data.setSpecimenType(rs->getString(45));
		data.setSampleTime(rs->getString(46));
		data.setDiagnosis(rs->getString(47));
		return data;
	}
};

#endif // !_EXECUTION_MAPPER_
