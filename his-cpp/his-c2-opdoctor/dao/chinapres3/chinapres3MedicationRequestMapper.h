#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: his-c2-opdoctor
 @Date: 2025/07/26

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _chinapres3MedicationRequestMapper_H_
#define _chinapres3MedicationRequestMapper_H_

#include "Mapper.h"
#include "../../domain/do/chinapres3/chinapres3MedicationRequestDO.h"

/**
 * 中国医保3代处方药品申请单映射器
 *
 * 功能：数据库查询结果集 ResultSet 转换为 chinapres3MedicationRequestDO 持久化对象
 * 对应数据库物理表：med_medication_request 药品处方明细表
 * 业务场景：第三方医保3.0处方流转，读取门诊/住院开立药品处方数据
 * 继承基类：Mapper 通用数据库结果集映射模板基类
 * 泛型约束：Ptrchinapres3MedicationRequestDO 处方DO智能指针类型
 */
class chinapres3MedicationRequestMapper : public Mapper<Ptrchinapres3MedicationRequestDO>
{
public:
	/**
	 * 数据库结果集映射核心方法
	 * @param resultSet 数据库查询单行结果集对象，包含SQL查询返回的所有字段
	 * @return Ptrchinapres3MedicationRequestDO 封装完成的处方DO智能指针对象
	 * @override 重写父类Mapper纯虚映射方法，实现表字段与DO实体属性绑定
	 */
	Ptrchinapres3MedicationRequestDO mapper(ResultSet* resultSet) const override
	{
		// 1. 创建处方DO持久化对象智能指针实例
		auto data = std::make_shared<chinapres3MedicationRequestDO>();

		// ========== 主键字段 ==========
		// id：处方明细主键ID，med_medication_request表唯一标识
		data->setId(resultSet->getString("id"));

		// ========== 业务核心关键字段（处方业务标识） ==========
		// prescription_no：处方单号，同一张处方所有药品行共享同一个处方号
		data->setPrescriptionNo(resultSet->getString("prescription_no"));
		// patient_id：患者唯一ID，关联患者主表patient
		data->setPatientId(resultSet->getString("patient_id"));
		// encounter_id：就诊ID，关联门诊/住院就诊记录encounter
		data->setEncounterId(resultSet->getString("encounter_id"));
		// status_enum：处方状态枚举（开立/审核/发药/作废/撤回等）
		data->setStatusEnum(resultSet->getString("status_enum"));

		// ========== 药品明细业务字段 ==========
		// rx_type_code：处方类型编码（西药/中药/外用药/检查等分类）
		data->setRxTypeCode(resultSet->getString("rx_type_code"));
		// medication_id：药品基础档案ID，关联药品基础数据表medication
		data->setMedicationId(resultSet->getString("medication_id"));
		// quantity：药品开具数量，浮点型支持小数剂量（如0.5片）
		data->setQuantity(resultSet->getDouble("quantity"));
		// unit_code：药品单位编码（片、袋、支、瓶、克等）
		data->setUnitCode(resultSet->getString("unit_code"));
		// location_id：药房/科室机构ID，区分取药药房、开立科室
		data->setLocationId(resultSet->getString("location_id"));

		// ========== 通用审计字段（数据操作日志） ==========
		// created_by：数据创建人账号/工号
		data->setCreatedBy(resultSet->getString("created_by"));
		// created_at：数据创建时间戳
		data->setCreatedAt(resultSet->getString("created_at"));
		// updated_by：最后修改人账号/工号
		data->setUpdatedBy(resultSet->getString("updated_by"));
		// updated_at：最后修改时间戳
		data->setUpdatedAt(resultSet->getString("updated_at"));

		// 返回封装完成的处方DO对象，供上层Service业务层使用
		return data;
	}
};

#endif // !_chinapres3MedicationRequestMapper_H_