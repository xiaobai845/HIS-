/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2022/12/03 11:01:02
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
#include "stdafx.h"
#include "RefundService.h"
#include "BaseDAO.h"
#include "Mapper.h"
#include "domain/do/AdmChargeItemDO.h"
#include "domain/do/AdmInvoiceDO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

namespace {
	struct ScalarStr { std::string val; };
	class ScalarStrMapper : public Mapper<ScalarStr>
	{
	public:
		ScalarStr mapper(ResultSet* rs) const override
		{
			ScalarStr s; s.val = rs->getString(1); return s;
		}
	};

	class ChargeItemMapper : public Mapper<AdmChargeItemDO>
	{
	public:
		AdmChargeItemDO mapper(ResultSet* rs) const override
		{
			AdmChargeItemDO d;
			d.setId(rs->getString(1));
			d.setBus_no(rs->getString(2));
			d.setDefinition_id(rs->getString(3));
			d.setQuantity_value(rs->getDouble(4));
			d.setTotal_price(rs->getDouble(5));
			d.setStatus_enum(rs->getString(6));
			d.setRefund_id(rs->getString(7));
			return d;
		}
	};
}

oatpp::List<oatpp::Object<Refund2DetailDTO>> RefundService::queryRefundList(const Refund2Query::Wrapper& query)
{
	auto resultList = oatpp::List<oatpp::Object<Refund2DetailDTO>>::createShared();
	std::string patientNo = query->num.getValue("");
	if (patientNo.empty()) return resultList;

	BaseDAO dao;
	auto* ss = dao.getSqlSession();

	// 1. 病历号 → 患者ID + 姓名
	std::string pid = ss->executeQueryOne<ScalarStr>(
		"SELECT id FROM adm_patient WHERE bus_no = ? AND is_deleted = 0 LIMIT 1",
		ScalarStrMapper(), "%s", patientNo).val;
	if (pid.empty()) return resultList;

	std::string patientName = ss->executeQueryOne<ScalarStr>(
		"SELECT name FROM adm_patient WHERE id = ?", ScalarStrMapper(), "%s", pid).val;

	// 2. 收费项列表 — 单表查询
	auto items = ss->executeQuery<AdmChargeItemDO>(
		"SELECT id, bus_no, definition_id, quantity_value, total_price, status_enum, refund_id "
		"FROM adm_charge_item "
		"WHERE patient_id = ? AND is_deleted = 0 "
		"ORDER BY created_at DESC",
		ChargeItemMapper(), "%s", pid);

	// 3. 组装 DTO
	for (auto& item : items)
	{
		auto dto = Refund2DetailDTO::createShared();
		dto->patientName = patientName;
		dto->paymentNo = item.getId();
		dto->itemName = item.getDefinition_id();
		dto->quantity = std::to_string(item.getQuantity_value());
		dto->amount = std::to_string(item.getTotal_price());
		dto->chargeStatus = item.getStatus_enum();
		dto->refundStatus = item.getRefund_id().empty() ? "" : "refunded";
		resultList->push_back(dto);
	}
	return resultList;
}

bool RefundService::applyRefund(const Refund2ApplyDTO::Wrapper& dto, const std::string& operatorId)
{
	UuidFacade uf;
	std::string refundId = uf.genUuid();
	std::string now = SimpleDateTimeFormat::format();

	AdmInvoiceDO invoice;
	invoice.setId(refundId);
	invoice.setTenant_id("1");
	invoice.setCreated_at(now);
	invoice.setPatient_id(dto->patientNo.getValue(""));
	invoice.setBus_no(dto->patientNo.getValue(""));
	invoice.setAmount(dto->applySum.getValue(0.0));
	invoice.setStatus_enum("refund");
	invoice.setIssued_at(now);
	invoice.setCreated_by(operatorId);

	std::list<std::string> itemIds;
	if (dto->apply)
	{
		for (auto& item : *dto->apply)
		{
			if (item->paymentNo)
				itemIds.push_back(item->paymentNo.getValue(""));
		}
	}

	BaseDAO dao;
	if (dao.insert(invoice) != 1) return false;

	if (!itemIds.empty())
	{
		auto* ss = dao.getSqlSession();
		std::string sql = "UPDATE adm_charge_item SET refund_id = ?, status_enum = 'refunded', updated_at = NOW() WHERE id IN (";
		SqlParams params;
		SQLPARAMS_PUSH(params, "s", std::string, refundId);
		for (size_t i = 0; i < itemIds.size(); ++i)
		{
			if (i > 0) sql += ",";
			sql += "?";
		}
		for (auto& id : itemIds)
			SQLPARAMS_PUSH(params, "s", std::string, id);
		sql += ") AND is_deleted = 0";
		ss->executeUpdate(sql, params);
	}
	return true;
}
