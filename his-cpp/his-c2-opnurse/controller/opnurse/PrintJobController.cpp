/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/20
*/
#include "stdafx.h"
#include "PrintJobController.h"
#include "../../service/opnurse/PrintTplRender.h"
#include "../../dao/opnurse/PrintLogDAO.h"
#include "../../dao/opnurse/ExecutionDAO.h"
#include "domain/do/opnurse/PrintLogDO.h"
#include "domain/do/opnurse/ExecutionDO.h"
#include "PdfComponent.h"
#include "domain/bo/PdfReportBO.h"
#include "SimpleDateTimeFormat.h"
#include "id/UuidFacade.h"
#include "jwt-cpp/base.h"

PrintResultJsonVO::Wrapper PrintJobController::executePrint(const PrintRequestDTO::Wrapper& req)
{
	auto jvo = PrintResultJsonVO::createShared();
	auto result = PrintResultDTO::createShared();

	if (!req->documentIds || req->documentIds->size() == 0)
	{
		result->success = false;
		result->message = "documentIds is empty";
		jvo->fail(result);
		return jvo;
	}

	std::string docType = req->documentType ? req->documentType.getValue("") : "treatment";

	PrintTplRender::registerAll();

	// Lookup print data from opnurse_execution (mock teammate 1 table)
	ExecutionDAO execDao;
	auto idsList = std::list<std::string>();
	for (auto& id : *req->documentIds) { idsList.push_back(id); }
	auto execRows = execDao.selectByIds(idsList);
	if (execRows.empty())
	{
		result->success = false;
		result->message = "No execution data found for given documentIds";
		jvo->fail(result);
		return jvo;
	}
	auto& exec = execRows.front(); // Take first row as print data source

	auto printData = PrintDataDTO::createShared();
	printData->printTime = SimpleDateTimeFormat::format();
	// Map ExecutionDO → PrintDataDTO (1:1)
	printData->patientName = exec.getPatientName();
	printData->doctorName = exec.getDoctorName();
	printData->remark = exec.getRemark();
	printData->treatmentItem = exec.getTreatmentItem();
	printData->execDept = exec.getExecDept();
	printData->orderTime = exec.getOrderTime();
	printData->execTime = exec.getExecTime();
	printData->executor = exec.getExecutor();
	printData->drugName = exec.getDrugName();
	printData->specification = exec.getSpecification();
	printData->quantity = exec.getQuantity();
	printData->usage = exec.getUsage();
	printData->frequency = exec.getFrequency();
	printData->receiptNo = exec.getReceiptNo();
	printData->chargeTime = exec.getChargeTime();
	printData->itemName = exec.getItemName();
	printData->unitPrice = exec.getUnitPrice();
	printData->amount = exec.getAmount();
	printData->totalAmount = exec.getTotalAmount();
	printData->deptName = exec.getDeptName();
	printData->regTime = exec.getRegTime();
	printData->regType = exec.getRegType();
	printData->regLevel = exec.getRegLevel();
	printData->queueNo = exec.getQueueNo();
	printData->regFee = exec.getRegFee();
	printData->bedNo = exec.getBedNo();
	printData->admissionNo = exec.getAdmissionNo();
	printData->dosage = exec.getDosage();
	printData->dripRate = exec.getDripRate();
	printData->settleDate = exec.getSettleDate();
	printData->operatorName = exec.getOperatorName();
	printData->regTotal = exec.getRegTotal();
	printData->drugTotal = exec.getDrugTotal();
	printData->examTotal = exec.getExamTotal();
	printData->labTotal = exec.getLabTotal();
	printData->treatmentTotal = exec.getTreatmentTotal();
	printData->applyDept = exec.getApplyDept();
	printData->examItem = exec.getExamItem();
	printData->examBodyPart = exec.getExamBodyPart();
	printData->examMethod = exec.getExamMethod();
	printData->labItem = exec.getLabItem();
	printData->specimenType = exec.getSpecimenType();
	printData->sampleTime = exec.getSampleTime();
	printData->diagnosis = exec.getDiagnosis();

	auto dataList = oatpp::List<PrintDataDTO::Wrapper>::createShared();
	dataList->push_back(printData);
	OatppAccessor<PrintDataDTO::Wrapper> accessor(dataList);

	try
	{
		PdfComponent pdf;
		pdf.drawWithTemplate("tpl/" + docType + ".yml", docType, &accessor);

		auto pdfData = pdf.saveDocToMem();
		auto base64Str = jwt::base::encode<jwt::alphabet::base64>(
			std::string(pdfData.begin(), pdfData.end()));

		result->success = true;
		result->message = "PDF generated";
		result->pdfBase64 = base64Str;
	}
	catch (const std::exception& e)
	{
		result->success = false;
		result->message = std::string("PDF generation failed: ") + e.what();
	}

	// Write print_log record
	{
		PrintLogDO log;
		log.setId(UuidFacade().genUuid());
		log.setPrintJobId(req->documentIds->front());
		log.setDocType(docType);
		log.setPatientName(printData->patientName ? printData->patientName.getValue("") : "");
		log.setPrintTime(printData->printTime.getValue(""));
		log.setPrinterName("HP-LaserJet-3F-A");
		log.setIsReprint(req->reprint ? (req->reprint.getValue(false) ? 1 : 0) : 0);
		log.setStatus(result->success ? 1 : 0);
		log.setOperatorName("护士");
		log.setRemark(result->success ? "" : result->message.getValue(""));
		log.setCreateTime(SimpleDateTimeFormat::format());
		PrintLogDAO dao;
		dao.insert(log);
	}

	// TODO: call OpenHIS plugin at localhost:5000

	if (result->success)
		jvo->success(result);
	else
		jvo->fail(result);
	return jvo;
}
