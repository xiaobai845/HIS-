#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/29
*/
#ifndef _EXECUTION_DO_
#define _EXECUTION_DO_

#include "../DoInclude.h"

class ExecutionDO : public BaseDO
{
	MYSQL_SYNTHESIZE(string, id, Id);
	MYSQL_SYNTHESIZE(string, encounterId, EncounterId);
	MYSQL_SYNTHESIZE(string, documentType, DocumentType);
	MYSQL_SYNTHESIZE(string, patientName, PatientName);
	MYSQL_SYNTHESIZE(string, doctorName, DoctorName);
	MYSQL_SYNTHESIZE(string, remark, Remark);
	MYSQL_SYNTHESIZE(string, treatmentItem, TreatmentItem);
	MYSQL_SYNTHESIZE(string, execDept, ExecDept);
	MYSQL_SYNTHESIZE(string, orderTime, OrderTime);
	MYSQL_SYNTHESIZE(string, execTime, ExecTime);
	MYSQL_SYNTHESIZE(string, executor, Executor);
	MYSQL_SYNTHESIZE(string, drugName, DrugName);
	MYSQL_SYNTHESIZE(string, specification, Specification);
	MYSQL_SYNTHESIZE(string, quantity, Quantity);
	MYSQL_SYNTHESIZE(string, usage, Usage);
	MYSQL_SYNTHESIZE(string, frequency, Frequency);
	MYSQL_SYNTHESIZE(string, receiptNo, ReceiptNo);
	MYSQL_SYNTHESIZE(string, chargeTime, ChargeTime);
	MYSQL_SYNTHESIZE(string, itemName, ItemName);
	MYSQL_SYNTHESIZE(string, unitPrice, UnitPrice);
	MYSQL_SYNTHESIZE(string, amount, Amount);
	MYSQL_SYNTHESIZE(string, totalAmount, TotalAmount);
	MYSQL_SYNTHESIZE(string, deptName, DeptName);
	MYSQL_SYNTHESIZE(string, regTime, RegTime);
	MYSQL_SYNTHESIZE(string, regType, RegType);
	MYSQL_SYNTHESIZE(string, regLevel, RegLevel);
	MYSQL_SYNTHESIZE(string, queueNo, QueueNo);
	MYSQL_SYNTHESIZE(string, regFee, RegFee);
	MYSQL_SYNTHESIZE(string, bedNo, BedNo);
	MYSQL_SYNTHESIZE(string, admissionNo, AdmissionNo);
	MYSQL_SYNTHESIZE(string, dosage, Dosage);
	MYSQL_SYNTHESIZE(string, dripRate, DripRate);
	MYSQL_SYNTHESIZE(string, settleDate, SettleDate);
	MYSQL_SYNTHESIZE(string, operatorName, OperatorName);
	MYSQL_SYNTHESIZE(string, regTotal, RegTotal);
	MYSQL_SYNTHESIZE(string, drugTotal, DrugTotal);
	MYSQL_SYNTHESIZE(string, examTotal, ExamTotal);
	MYSQL_SYNTHESIZE(string, labTotal, LabTotal);
	MYSQL_SYNTHESIZE(string, treatmentTotal, TreatmentTotal);
	MYSQL_SYNTHESIZE(string, applyDept, ApplyDept);
	MYSQL_SYNTHESIZE(string, examItem, ExamItem);
	MYSQL_SYNTHESIZE(string, examBodyPart, ExamBodyPart);
	MYSQL_SYNTHESIZE(string, examMethod, ExamMethod);
	MYSQL_SYNTHESIZE(string, labItem, LabItem);
	MYSQL_SYNTHESIZE(string, specimenType, SpecimenType);
	MYSQL_SYNTHESIZE(string, sampleTime, SampleTime);
	MYSQL_SYNTHESIZE(string, diagnosis, Diagnosis);

public:
	ExecutionDO() : BaseDO("opnurse_execution")
	{
		MYSQL_ADD_FIELD_PK("id", "s", id);
		MYSQL_ADD_FIELD("encounter_id", "s", encounterId);
		MYSQL_ADD_FIELD("document_type", "s", documentType);
		MYSQL_ADD_FIELD("patient_name", "s", patientName);
		MYSQL_ADD_FIELD("doctor_name", "s", doctorName);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("treatment_item", "s", treatmentItem);
		MYSQL_ADD_FIELD("exec_dept", "s", execDept);
		MYSQL_ADD_FIELD("order_time", "s", orderTime);
		MYSQL_ADD_FIELD("exec_time", "s", execTime);
		MYSQL_ADD_FIELD("executor", "s", executor);
		MYSQL_ADD_FIELD("drug_name", "s", drugName);
		MYSQL_ADD_FIELD("specification", "s", specification);
		MYSQL_ADD_FIELD("quantity", "s", quantity);
		MYSQL_ADD_FIELD("usage", "s", usage);
		MYSQL_ADD_FIELD("frequency", "s", frequency);
		MYSQL_ADD_FIELD("receipt_no", "s", receiptNo);
		MYSQL_ADD_FIELD("charge_time", "s", chargeTime);
		MYSQL_ADD_FIELD("item_name", "s", itemName);
		MYSQL_ADD_FIELD("unit_price", "s", unitPrice);
		MYSQL_ADD_FIELD("amount", "s", amount);
		MYSQL_ADD_FIELD("total_amount", "s", totalAmount);
		MYSQL_ADD_FIELD("dept_name", "s", deptName);
		MYSQL_ADD_FIELD("reg_time", "s", regTime);
		MYSQL_ADD_FIELD("reg_type", "s", regType);
		MYSQL_ADD_FIELD("reg_level", "s", regLevel);
		MYSQL_ADD_FIELD("queue_no", "s", queueNo);
		MYSQL_ADD_FIELD("reg_fee", "s", regFee);
		MYSQL_ADD_FIELD("bed_no", "s", bedNo);
		MYSQL_ADD_FIELD("admission_no", "s", admissionNo);
		MYSQL_ADD_FIELD("dosage", "s", dosage);
		MYSQL_ADD_FIELD("drip_rate", "s", dripRate);
		MYSQL_ADD_FIELD("settle_date", "s", settleDate);
		MYSQL_ADD_FIELD("operator_name", "s", operatorName);
		MYSQL_ADD_FIELD("reg_total", "s", regTotal);
		MYSQL_ADD_FIELD("drug_total", "s", drugTotal);
		MYSQL_ADD_FIELD("exam_total", "s", examTotal);
		MYSQL_ADD_FIELD("lab_total", "s", labTotal);
		MYSQL_ADD_FIELD("treatment_total", "s", treatmentTotal);
		MYSQL_ADD_FIELD("apply_dept", "s", applyDept);
		MYSQL_ADD_FIELD("exam_item", "s", examItem);
		MYSQL_ADD_FIELD("exam_body_part", "s", examBodyPart);
		MYSQL_ADD_FIELD("exam_method", "s", examMethod);
		MYSQL_ADD_FIELD("lab_item", "s", labItem);
		MYSQL_ADD_FIELD("specimen_type", "s", specimenType);
		MYSQL_ADD_FIELD("sample_time", "s", sampleTime);
		MYSQL_ADD_FIELD("diagnosis", "s", diagnosis);
	}
};

typedef std::shared_ptr<ExecutionDO> PtrExecutionDO;
#endif // !_EXECUTION_DO_
