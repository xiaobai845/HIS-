#pragma once

#ifndef CHINAPRESMAPPER1
#define CHINAPRESMAPPER1

#include "Mapper.h"
#include "domain/do/chinapres1/ChinapresDO1.h"

class ChinapresMapper1 : public Mapper<PtrChinapresDO>
{
public:
	PtrChinapresDO mapper(ResultSet* resultSet) const override
	{
		PtrChinapresDO chinapresDO = std::make_shared<ChinapresDO1>();

		// 通用字段
		chinapresDO->setId(resultSet->getString("id"));
		chinapresDO->setTenantId(resultSet->getString("tenant_id"));
		chinapresDO->setCreatedAt(resultSet->getString("created_at"));
		chinapresDO->setUpdatedAt(resultSet->getString("updated_at"));
		chinapresDO->setCreatedBy(resultSet->getString("created_by"));
		chinapresDO->setUpdatedBy(resultSet->getString("updated_by"));
		chinapresDO->setIsDeleted(resultSet->getInt("is_deleted"));
		chinapresDO->setDeletedAt(resultSet->getString("deleted_at"));
		chinapresDO->setDeletedBy(resultSet->getString("deleted_by"));
		chinapresDO->setVersion(resultSet->getInt("version"));

		// 处方业务标识
		chinapresDO->setBusNo(resultSet->getString("bus_no"));
		chinapresDO->setPrescriptionNo(resultSet->getString("prescription_no"));
		chinapresDO->setGroupId(resultSet->getString("group_id"));
		chinapresDO->setPackageId(resultSet->getString("package_id"));

		// 状态与意图
		chinapresDO->setStatusEnum(resultSet->getString("status_enum"));
		chinapresDO->setStatusReason(resultSet->getInt("status_reason"));
		chinapresDO->setStatusChangedTime(resultSet->getString("status_changed_time"));
		chinapresDO->setIntentEnum(resultSet->getString("intent_enum"));
		chinapresDO->setCategoryEnum(resultSet->getString("category_enum"));
		chinapresDO->setPriorityEnum(resultSet->getString("priority_enum"));
		chinapresDO->setPerformFlag(resultSet->getInt("perform_flag"));

		// 关联对象
		chinapresDO->setMedicationId(resultSet->getString("medication_id"));
		chinapresDO->setPatientId(resultSet->getString("patient_id"));
		chinapresDO->setEncounterId(resultSet->getString("encounter_id"));

		// 开方与执行位置
		chinapresDO->setRequesterId(resultSet->getString("requester_id"));
		chinapresDO->setLocationId(resultSet->getString("location_id"));
		chinapresDO->setOrgId(resultSet->getString("org_id"));
		chinapresDO->setPerformLocation(resultSet->getInt64("perform_location"));
		chinapresDO->setPerformOrg(resultSet->getInt64("perform_org"));

		// 执行人与记录人
		chinapresDO->setPerformerEnum(resultSet->getString("performer_enum"));
		chinapresDO->setPerformerId(resultSet->getString("performer_id"));
		chinapresDO->setDeviceDefId(resultSet->getString("device_def_id"));
		chinapresDO->setRecorderId(resultSet->getString("recorder_id"));

		// 时间与标志
		chinapresDO->setReqAuthoredTime(resultSet->getString("req_authored_time"));
		chinapresDO->setReportFlag(resultSet->getInt("report_flag"));
		chinapresDO->setSupportInfo(resultSet->getString("support_info"));
		chinapresDO->setReasonJson(resultSet->getString("reason_json"));

		// 治疗类型
		chinapresDO->setTherapyEnum(resultSet->getString("therapy_enum"));
		chinapresDO->setEffectiveDoseStart(resultSet->getString("effective_dose_start"));

		// 数量与单位
		chinapresDO->setQuantity(resultSet->getDouble("quantity"));
		chinapresDO->setExecuteNum(resultSet->getInt("execute_num"));
		chinapresDO->setUnitCode(resultSet->getString("unit_code"));

		// 用法、频次、剂量
		chinapresDO->setMethodCode(resultSet->getString("method_code"));
		chinapresDO->setRateCode(resultSet->getString("rate_code"));
		chinapresDO->setDose(resultSet->getDouble("dose"));
		chinapresDO->setDoseUnitCode(resultSet->getString("dose_unit_code"));
		chinapresDO->setMaxDose(resultSet->getDouble("max_dose"));
		chinapresDO->setFirstDose(resultSet->getDouble("first_dose"));
		chinapresDO->setFirstDoseUnitCode(resultSet->getString("first_dose_unit_code"));
		chinapresDO->setFirstDuration(resultSet->getString("first_duration"));

		// 发药相关
		chinapresDO->setDispenseInterval(resultSet->getString("dispense_interval"));
		chinapresDO->setDispensePerQuantity(resultSet->getInt("dispense_per_quantity"));
		chinapresDO->setDispensePerDuration(resultSet->getInt("dispense_per_duration"));

		// 批号与追溯
		chinapresDO->setLotNumber(resultSet->getString("lot_number"));
		chinapresDO->setTraceNo(resultSet->getString("trace_no"));

		// 特殊标志
		chinapresDO->setSkinTestFlag(resultSet->getInt("skin_test_flag"));
		chinapresDO->setInfusionFlag(resultSet->getInt("infusion_flag"));
		chinapresDO->setSpeedCode(resultSet->getString("speed_code"));

		// 合同与诊断
		chinapresDO->setContractId(resultSet->getString("contract_id"));
		chinapresDO->setConditionDefinitionId(resultSet->getString("condition_definition_id"));
		chinapresDO->setEncounterDiagnosisId(resultSet->getString("encounter_diagnosis_id"));

		// 核对与退费
		chinapresDO->setPerformerCheckId(resultSet->getString("performer_check_id"));
		chinapresDO->setCheckTime(resultSet->getString("check_time"));
		chinapresDO->setEffectiveDoseEnd(resultSet->getString("effective_dose_end"));
		chinapresDO->setRefundMedicineId(resultSet->getString("refund_medicine_id"));

		// 处方类型与医保
		chinapresDO->setRxTypeCode(resultSet->getString("rx_type_code"));
		chinapresDO->setYbClassEnum(resultSet->getString("yb_class_enum"));
		chinapresDO->setDosageInstruction(resultSet->getString("dosage_instruction"));

		// 来源与中医
		chinapresDO->setBasedOnTable(resultSet->getString("based_on_table"));
		chinapresDO->setBasedOnId(resultSet->getString("based_on_id"));
		chinapresDO->setTcmFlag(resultSet->getInt("tcm_flag"));
		chinapresDO->setContentJson(resultSet->getString("content_json"));

		// 中药特有
		chinapresDO->setChineseHerbsDoseQuantity(resultSet->getDouble("chinese_herbs_dose_quantity"));
		chinapresDO->setSufferingFlag(resultSet->getInt("suffering_flag"));
		chinapresDO->setSortNumber(resultSet->getInt("sort_number"));
		chinapresDO->setGenerateSourceEnum(resultSet->getString("generate_source_enum"));
		chinapresDO->setRemark(resultSet->getString("remark"));

		return chinapresDO;
	}
};

#endif// !_CHINAPRESMAPPER1_H_