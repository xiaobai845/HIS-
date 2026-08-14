#pragma once
#ifndef _CHINAPRESDETAILDTO1_H_
#define _CHINAPRESDETAILDTO1_H_

#include "../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)

class ChinapresHerbDTO : public oatpp::DTO
{
	DTO_INIT(ChinapresHerbDTO, DTO);
	// 药品定义ID
	API_DTO_FIELD_REQUIRE(String, medicineId, ZH_WORDS_GETTER("chinapres1.field.medicineid"), true);
	// 药材编码
	API_DTO_FIELD_REQUIRE(String, medicineCode, ZH_WORDS_GETTER("chinapres1.field.medicinecode"), true);
	// 药材名称
	API_DTO_FIELD_REQUIRE(String, name, ZH_WORDS_GETTER("chinapres1.field.name"), true);
	// 数量
	API_DTO_FIELD_REQUIRE(Float64, quantity, ZH_WORDS_GETTER("chinapres1.field.quantity"), true);
	// 单位
	API_DTO_FIELD_REQUIRE(String, unit, ZH_WORDS_GETTER("chinapres1.field.unit"), true);
	// 单剂量
	API_DTO_FIELD_REQUIRE(Float64, dose, ZH_WORDS_GETTER("chinapres1.field.dose"), true);
	// 剂量单位
	API_DTO_FIELD_REQUIRE(String, doseUnit, ZH_WORDS_GETTER("chinapres1.field.doseunit"), true);
	// 排序号
	API_DTO_FIELD_REQUIRE(Int32, sortNumber, ZH_WORDS_GETTER("chinapres1.field.sortnumber"), true);
	// 单价
	API_DTO_FIELD_REQUIRE(Float64, unitPrice, ZH_WORDS_GETTER("chinapres1.field.unitprice"), true);
	// 小计
	API_DTO_FIELD_REQUIRE(Float64, subtotal, ZH_WORDS_GETTER("chinapres1.field.subtotal"), true);
};

class ChinapresDetailDTO1 : public oatpp::DTO
{
	DTO_INIT(ChinapresDetailDTO1, DTO);
	// 处方记录ID（处方号）
	API_DTO_FIELD_REQUIRE(String, prescriptionId, ZH_WORDS_GETTER("chinapres1.field.prescriptionid"), true);
	// 就诊ID
	API_DTO_FIELD_REQUIRE(String, encounterId, ZH_WORDS_GETTER("chinapres1.field.encounterid"), true);
	// 患者ID
	API_DTO_FIELD_REQUIRE(String, patientId, ZH_WORDS_GETTER("chinapres1.field.patientid"), true);
	// 处方状态码
	API_DTO_FIELD_REQUIRE(String, status, ZH_WORDS_GETTER("chinapres1.field.status"), true);
	// 处方状态名称（中文，MongoDB翻译）
	API_DTO_FIELD_REQUIRE(String, statusName, ZH_WORDS_GETTER("chinapres1.field.statusname"), true);
	// 用法编码
	API_DTO_FIELD_REQUIRE(String, usage, ZH_WORDS_GETTER("chinapres1.field.usage"), true);
	// 频次编码
	API_DTO_FIELD_REQUIRE(String, frequency, ZH_WORDS_GETTER("chinapres1.field.frequency"), true);
	// 天数
	API_DTO_FIELD_REQUIRE(Int32, days, ZH_WORDS_GETTER("chinapres1.field.days"), true);
	// 付数
	API_DTO_FIELD_REQUIRE(Int32, copies, ZH_WORDS_GETTER("chinapres1.field.copies"), true);
	// 代煎
	API_DTO_FIELD_REQUIRE(Boolean, decoction, ZH_WORDS_GETTER("chinapres1.field.decoction"), true);
	// 诊断
	API_DTO_FIELD_REQUIRE(String, diagnosis, ZH_WORDS_GETTER("chinapres1.field.diagnosis"), false);
	// 备注
	API_DTO_FIELD_REQUIRE(String, remark, ZH_WORDS_GETTER("chinapres1.field.remark"), false);
	// 版本号
	API_DTO_FIELD_REQUIRE(Int32, version, ZH_WORDS_GETTER("chinapres1.field.version"), true);
	// 创建时间
	API_DTO_FIELD_REQUIRE(String, createdAt, ZH_WORDS_GETTER("chinapres1.field.createdat"), true);
	// 状态变更时间
	API_DTO_FIELD_REQUIRE(String, statusChangedAt, ZH_WORDS_GETTER("chinapres1.field.statuschangedat"), false);
	// 共几味
	API_DTO_FIELD_REQUIRE(Int32, totalCount, ZH_WORDS_GETTER("chinapres1.field.totalcount"), true);
	// 单剂金额
	API_DTO_FIELD_REQUIRE(Float64, doseAmount, ZH_WORDS_GETTER("chinapres1.field.doseamount"), true);
	// 总计金额
	API_DTO_FIELD_REQUIRE(Float64, totalAmount, ZH_WORDS_GETTER("chinapres1.field.totalamount"), true);
	// 药材列表
	API_DTO_FIELD_REQUIRE(List<Object<ChinapresHerbDTO>>, details, ZH_WORDS_GETTER("chinapres1.field.details"), true);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_CHINAPRESDETAILDTO1_H_