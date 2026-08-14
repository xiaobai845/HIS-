#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/23
*/
#ifndef _PRINT_DATA_DTO_
#define _PRINT_DATA_DTO_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class PrintDataDTO : public oatpp::DTO
{
	DTO_INIT(PrintDataDTO, DTO);
	// common
	DTO_FIELD(String, patientName);
	DTO_FIELD_INFO(patientName) { info->description = ZH_WORDS_GETTER("opnurse3.field.patientName"); }
	DTO_FIELD(String, doctorName);
	DTO_FIELD_INFO(doctorName) { info->description = ZH_WORDS_GETTER("opnurse3.field.doctorName"); }
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) { info->description = ZH_WORDS_GETTER("opnurse3.field.remark"); }
	// treatment
	DTO_FIELD(String, treatmentItem);
	DTO_FIELD_INFO(treatmentItem) { info->description = ZH_WORDS_GETTER("opnurse3.field.treatmentItem"); }
	DTO_FIELD(String, execDept);
	DTO_FIELD_INFO(execDept) { info->description = ZH_WORDS_GETTER("opnurse3.field.execDept"); }
	DTO_FIELD(String, orderTime);
	DTO_FIELD_INFO(orderTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.orderTime"); }
	DTO_FIELD(String, execTime);
	DTO_FIELD_INFO(execTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.execTime"); }
	DTO_FIELD(String, executor);
	DTO_FIELD_INFO(executor) { info->description = ZH_WORDS_GETTER("opnurse3.field.executor"); }
	// prescription
	DTO_FIELD(String, drugName);
	DTO_FIELD_INFO(drugName) { info->description = ZH_WORDS_GETTER("opnurse3.field.drugName"); }
	DTO_FIELD(String, specification);
	DTO_FIELD_INFO(specification) { info->description = ZH_WORDS_GETTER("opnurse3.field.specification"); }
	DTO_FIELD(String, quantity);
	DTO_FIELD_INFO(quantity) { info->description = ZH_WORDS_GETTER("opnurse3.field.quantity"); }
	DTO_FIELD(String, usage);
	DTO_FIELD_INFO(usage) { info->description = ZH_WORDS_GETTER("opnurse3.field.usage"); }
	DTO_FIELD(String, frequency);
	DTO_FIELD_INFO(frequency) { info->description = ZH_WORDS_GETTER("opnurse3.field.frequency"); }
	// charge_receipt
	DTO_FIELD(String, receiptNo);
	DTO_FIELD_INFO(receiptNo) { info->description = ZH_WORDS_GETTER("opnurse3.field.receiptNo"); }
	DTO_FIELD(String, chargeTime);
	DTO_FIELD_INFO(chargeTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.chargeTime"); }
	DTO_FIELD(String, itemName);
	DTO_FIELD_INFO(itemName) { info->description = ZH_WORDS_GETTER("opnurse3.field.itemName"); }
	DTO_FIELD(String, unitPrice);
	DTO_FIELD_INFO(unitPrice) { info->description = ZH_WORDS_GETTER("opnurse3.field.unitPrice"); }
	DTO_FIELD(String, amount);
	DTO_FIELD_INFO(amount) { info->description = ZH_WORDS_GETTER("opnurse3.field.amount"); }
	DTO_FIELD(String, totalAmount);
	DTO_FIELD_INFO(totalAmount) { info->description = ZH_WORDS_GETTER("opnurse3.field.totalAmount"); }
	// reg_receipt
	DTO_FIELD(String, deptName);
	DTO_FIELD_INFO(deptName) { info->description = ZH_WORDS_GETTER("opnurse3.field.deptName"); }
	DTO_FIELD(String, regTime);
	DTO_FIELD_INFO(regTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.regTime"); }
	DTO_FIELD(String, regType);
	DTO_FIELD_INFO(regType) { info->description = ZH_WORDS_GETTER("opnurse3.field.regType"); }
	DTO_FIELD(String, regLevel);
	DTO_FIELD_INFO(regLevel) { info->description = ZH_WORDS_GETTER("opnurse3.field.regLevel"); }
	DTO_FIELD(String, queueNo);
	DTO_FIELD_INFO(queueNo) { info->description = ZH_WORDS_GETTER("opnurse3.field.queueNo"); }
	DTO_FIELD(String, regFee);
	DTO_FIELD_INFO(regFee) { info->description = ZH_WORDS_GETTER("opnurse3.field.regFee"); }
	// infusion_label
	DTO_FIELD(String, bedNo);
	DTO_FIELD_INFO(bedNo) { info->description = ZH_WORDS_GETTER("opnurse3.field.bedNo"); }
	DTO_FIELD(String, admissionNo);
	DTO_FIELD_INFO(admissionNo) { info->description = ZH_WORDS_GETTER("opnurse3.field.admissionNo"); }
	DTO_FIELD(String, dosage);
	DTO_FIELD_INFO(dosage) { info->description = ZH_WORDS_GETTER("opnurse3.field.dosage"); }
	DTO_FIELD(String, dripRate);
	DTO_FIELD_INFO(dripRate) { info->description = ZH_WORDS_GETTER("opnurse3.field.dripRate"); }
	// daily_settlement
	DTO_FIELD(String, settleDate);
	DTO_FIELD_INFO(settleDate) { info->description = ZH_WORDS_GETTER("opnurse3.field.settleDate"); }
	DTO_FIELD(String, operatorName);
	DTO_FIELD_INFO(operatorName) { info->description = ZH_WORDS_GETTER("opnurse3.field.operator"); }
	DTO_FIELD(String, regTotal);
	DTO_FIELD_INFO(regTotal) { info->description = ZH_WORDS_GETTER("opnurse3.field.regTotal"); }
	DTO_FIELD(String, drugTotal);
	DTO_FIELD_INFO(drugTotal) { info->description = ZH_WORDS_GETTER("opnurse3.field.drugTotal"); }
	DTO_FIELD(String, examTotal);
	DTO_FIELD_INFO(examTotal) { info->description = ZH_WORDS_GETTER("opnurse3.field.examTotal"); }
	DTO_FIELD(String, labTotal);
	DTO_FIELD_INFO(labTotal) { info->description = ZH_WORDS_GETTER("opnurse3.field.labTotal"); }
	DTO_FIELD(String, treatmentTotal);
	DTO_FIELD_INFO(treatmentTotal) { info->description = ZH_WORDS_GETTER("opnurse3.field.treatmentTotal"); }
	// exam_request / lab_request
	DTO_FIELD(String, applyDept);
	DTO_FIELD_INFO(applyDept) { info->description = ZH_WORDS_GETTER("opnurse3.field.applyDept"); }
	DTO_FIELD(String, examItem);
	DTO_FIELD_INFO(examItem) { info->description = ZH_WORDS_GETTER("opnurse3.field.examItem"); }
	DTO_FIELD(String, examBodyPart);
	DTO_FIELD_INFO(examBodyPart) { info->description = ZH_WORDS_GETTER("opnurse3.field.examBodyPart"); }
	DTO_FIELD(String, examMethod);
	DTO_FIELD_INFO(examMethod) { info->description = ZH_WORDS_GETTER("opnurse3.field.examMethod"); }
	DTO_FIELD(String, labItem);
	DTO_FIELD_INFO(labItem) { info->description = ZH_WORDS_GETTER("opnurse3.field.labItem"); }
	DTO_FIELD(String, specimenType);
	DTO_FIELD_INFO(specimenType) { info->description = ZH_WORDS_GETTER("opnurse3.field.specimenType"); }
	DTO_FIELD(String, sampleTime);
	DTO_FIELD_INFO(sampleTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.sampleTime"); }
	DTO_FIELD(String, diagnosis);
	DTO_FIELD_INFO(diagnosis) { info->description = ZH_WORDS_GETTER("opnurse3.field.diagnosis"); }
	// system
	DTO_FIELD(String, printTime);
	DTO_FIELD_INFO(printTime) { info->description = ZH_WORDS_GETTER("opnurse3.field.printTime"); }
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_PRINT_DATA_DTO_
