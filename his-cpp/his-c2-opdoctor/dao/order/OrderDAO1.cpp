// dao/order/OrderDAO1.cpp
#include "stdafx.h"
#include "../../dao/order/OrderDAO1.h"
#include "Mapper/MedicationDefinitionMapper1.h"
#include "Mapper/ActivityDefinitionMapper1.h"
#include "Mapper/DeviceDefinitionMapper1.h"
#include "Mapper/MedicationRequestMapper1.h"
#include "Mapper/ServiceRequestMapper1.h"
#include "Mapper/DeviceRequestMapper1.h"
#include "Mapper/ChargeItemDefinitionMapper1.h"
#include "Mapper/EncounterMapper1.h"

#include "SimpleDateTimeFormat.h"
#include <sstream>
#include <iomanip>
#include <ctime>

// ========== 辅助查询 ==========

std::string OrderDAO1::getMedicationIdByBusNo(const std::string& busNo)
{
    if (busNo.empty()) return "";
    std::string sql = "SELECT * FROM med_medication_definition WHERE bus_no = ? AND status_enum = 'ACTIVE' AND is_deleted = 0 LIMIT 1";
    auto result = sqlSession->executeQueryOne<PtrMedicationDefinitionDO1>(sql, PtrMedicationDefinitionMapper1(), "%s", busNo);
    if (result) {
        return result->getId();
    }
    return "";
}

std::string OrderDAO1::getActivityIdByBusNo(const std::string& busNo)
{
    if (busNo.empty()) return "";
    std::string sql = "SELECT * FROM wkf_activity_definition WHERE bus_no = ? AND status_enum = 'ACTIVE' AND is_deleted = 0 LIMIT 1";
    auto result = sqlSession->executeQueryOne<PtrActivityDefinitionDO1>(sql, PtrActivityDefinitionMapper1(), "%s", busNo);
    if (result) {
        return result->getId();
    }
    return "";
}

std::string OrderDAO1::getDeviceDefIdByBusNo(const std::string& busNo)
{
    if (busNo.empty()) return "";
    std::string sql = "SELECT * FROM adm_device_definition WHERE bus_no = ? AND status_enum = 'ACTIVE' AND is_deleted = 0 LIMIT 1";
    auto result = sqlSession->executeQueryOne<PtrDeviceDefinitionDO1>(sql, PtrDeviceDefinitionMapper1(), "%s", busNo);
    if (result) {
        return result->getId();
    }
    return "";
}

uint64_t OrderDAO1::getUnitPrice(const std::string& instanceTable, const std::string& instanceId)
{
    if (instanceTable.empty() || instanceId.empty()) {
        return 0.0;
    }
    std::string sql = "SELECT price_value FROM adm_charge_item_definition "
        "WHERE instance_table = ? AND instance_id = ? AND status_enum = 'ACTIVE' "
        "ORDER BY priority ASC, created_at DESC LIMIT 1";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, instanceTable);
    SQLPARAMS_PUSH(params, "s", std::string, instanceId);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::string OrderDAO1::getPatientIdByEncounterId(const std::string& encounterId)
{
    if (encounterId.empty()) return "";
    
    std::string sql = "SELECT * FROM adm_encounter WHERE id = ? AND is_deleted = 0";
    auto encounter = sqlSession->executeQueryOne<PtrEncounterDO1>(sql, PtrEncounterMapper1(), "%s", encounterId);
    
    if (encounter) {
        return encounter->getPatientId();
    }
    return "";
}

// ========== 构建关键词 EXISTS 子查询 ==========
std::string OrderDAO1::buildKeywordCondition(const std::string& keyword,
    const std::string& defTable,
    const std::string& idField,
    const std::string& idColumn)
{
    if (keyword.empty()) return "";

    std::ostringstream cond;
    cond << " AND EXISTS (";
    cond << "SELECT 1 FROM " << defTable << " d ";
    cond << "WHERE d." << idField << " = " << idColumn;
    cond << " AND d.is_deleted = 0";
    cond << " AND (";
    cond << "d.bus_no LIKE '%" << keyword << "%'";
    cond << " OR d.name LIKE '%" << keyword << "%'";
    cond << " OR d.py_str LIKE '%" << keyword << "%'";
    cond << " OR d.wb_str LIKE '%" << keyword << "%'";
    cond << " OR d.merchandise_name LIKE '%" << keyword << "%'";
    cond << " OR d.merchandise_py_str LIKE '%" << keyword << "%'";
    cond << " OR d.merchandise_wb_str LIKE '%" << keyword << "%'";
    cond << ")";
    cond << ")";
    return cond.str();
}

// ========== 构建状态 IN 子句 ==========
std::string OrderDAO1::buildStatusCondition(const std::list<std::string>& statusList)
{
    if (statusList.empty()) return "";

    std::ostringstream cond;
    cond << " AND status_enum IN (";
    bool first = true;
    for (const auto& s : statusList) {
        if (!first) cond << ",";
        first = false;
        cond << "'" << s << "'";
    }
    cond << ")";
    return cond.str();
}

// ========== 从 DO 构建 DTO ==========

OrderDetailDTO1::Wrapper OrderDAO1::buildMedicationDTO(
    const MedicationRequestDO1& item,
    const MedicationDefinitionDO1& def,
    const std::string& doctorName)
{
    auto dto = OrderDetailDTO1::createShared();

    // 基础信息
    dto->orderId = oatpp::String(item.getId());
    dto->encounterId = oatpp::String(item.getEncounterId());
    dto->patientId = oatpp::String(item.getPatientId());
    dto->doctorId = oatpp::String(item.getRequesterId());
    dto->doctorName = oatpp::String(doctorName);

    // 目录信息
    dto->catalogId = oatpp::String(def.getId());
    dto->itemCode = oatpp::String(def.getBusNo());
    dto->itemName = oatpp::String(def.getName());
    dto->spec = oatpp::String(def.getTotalVolume());
    dto->orderType = oatpp::String("medication");

    // 分类信息
    dto->categoryCode = oatpp::String(def.getCategoryCode());
    // categoryName 由 Service 层通过枚举转换填充

    // 临床决策字段
    dto->dose = oatpp::Float64(item.getDose());
    dto->doseUnit = oatpp::String(item.getDoseUnitCode());
    dto->frequency = oatpp::String(item.getRateCode());
    dto->routeCode = oatpp::String(item.getMethodCode());
    dto->quantity = oatpp::Float64(item.getQuantity());
    dto->quantityUnit = oatpp::String(item.getUnitCode());
    dto->isSkinTest = oatpp::Boolean(item.getSkinTestFlag() == 1);

    // 使用天数计算
    int days = 0;
    if (!item.getEffectiveDoseStart().empty() && !item.getEffectiveDoseEnd().empty()) {
        std::tm tmStart = {}, tmEnd = {};
        std::istringstream ssStart(item.getEffectiveDoseStart());
        std::istringstream ssEnd(item.getEffectiveDoseEnd());
        ssStart >> std::get_time(&tmStart, "%Y-%m-%d %H:%M:%S");
        ssEnd >> std::get_time(&tmEnd, "%Y-%m-%d %H:%M:%S");
        if (!ssStart.fail() && !ssEnd.fail()) {
            std::time_t timeStart = std::mktime(&tmStart);
            std::time_t timeEnd = std::mktime(&tmEnd);
            days = (int)((timeEnd - timeStart) / (24 * 3600));
            if (days < 0) days = 0;
        }
    }
    dto->useDays = oatpp::Int32(days);

    // 每单位含量（从规格中提取，或直接使用总规格）
    dto->contentPerUnit = oatpp::String(def.getTotalVolume());

    // 单价和总价
    double unitPrice = getUnitPrice("med_medication_definition", item.getMedicationId());
    dto->unitPrice = oatpp::Float64(unitPrice);
    dto->totalPrice = oatpp::Float64(unitPrice * item.getQuantity());

    // 状态
    dto->status = oatpp::String(item.getStatusEnum());

    // 分组与排序
    dto->groupId = oatpp::String(item.getGroupId());
    dto->orderNo = oatpp::Int32(item.getSortNumber());

    // 时间与版本
    dto->createTime = oatpp::String(item.getCreatedAt());
    dto->updatedAt = oatpp::String(item.getUpdatedAt());
    dto->version = oatpp::Int32(item.getVersion());

    // 其他
    dto->prescriptionNo = oatpp::String(item.getPrescriptionNo());
    dto->remark = oatpp::String(item.getRemark());

    return dto;
}

OrderDetailDTO1::Wrapper OrderDAO1::buildServiceDTO(
    const ServiceRequestDO1& item,
    const ActivityDefinitionDO1& def,
    const std::string& doctorName)
{
    auto dto = OrderDetailDTO1::createShared();

    // 基础信息
    dto->orderId = oatpp::String(item.getId());
    dto->encounterId = oatpp::String(item.getEncounterId());
    dto->patientId = oatpp::String(item.getPatientId());
    dto->doctorId = oatpp::String(item.getRequesterId());
    dto->doctorName = oatpp::String(doctorName);

    // 目录信息
    dto->catalogId = oatpp::String(def.getId());
    dto->itemCode = oatpp::String(def.getBusNo());
    dto->itemName = oatpp::String(def.getName());
    dto->spec = oatpp::String(def.getDescriptionText());
    dto->orderType = oatpp::String("service");

    // 分类信息
    dto->categoryCode = oatpp::String(def.getCategoryCode());

    // 临床决策字段（诊疗部分字段为空）
    dto->dose = oatpp::Float64(0.0);
    dto->doseUnit = oatpp::String("");
    dto->frequency = oatpp::String(item.getRateCode());
    dto->routeCode = oatpp::String("");
    dto->quantity = oatpp::Float64(item.getQuantity());
    dto->quantityUnit = oatpp::String(item.getUnitCode());
    dto->isSkinTest = oatpp::Boolean(false);

    // 使用天数计算
    int days = 0;
    if (!item.getOccurrenceStartTime().empty() && !item.getOccurrenceEndTime().empty()) {
        std::tm tmStart = {}, tmEnd = {};
        std::istringstream ssStart(item.getOccurrenceStartTime());
        std::istringstream ssEnd(item.getOccurrenceEndTime());
        ssStart >> std::get_time(&tmStart, "%Y-%m-%d %H:%M:%S");
        ssEnd >> std::get_time(&tmEnd, "%Y-%m-%d %H:%M:%S");
        if (!ssStart.fail() && !ssEnd.fail()) {
            std::time_t timeStart = std::mktime(&tmStart);
            std::time_t timeEnd = std::mktime(&tmEnd);
            days = (int)((timeEnd - timeStart) / (24 * 3600));
            if (days < 0) days = 0;
        }
    }
    dto->useDays = oatpp::Int32(days);

    dto->contentPerUnit = oatpp::String(def.getDescriptionText());

    // 单价和总价
    double unitPrice = getUnitPrice("wkf_activity_definition", item.getActivityId());
    dto->unitPrice = oatpp::Float64(unitPrice);
    dto->totalPrice = oatpp::Float64(unitPrice * item.getQuantity());

    // 状态
    dto->status = oatpp::String(item.getStatusEnum());

    // 分组与排序
    dto->groupId = oatpp::String(item.getGroupId());
    dto->orderNo = oatpp::Int32(item.getSortNumber());

    // 时间与版本
    dto->createTime = oatpp::String(item.getCreatedAt());
    dto->updatedAt = oatpp::String(item.getUpdatedAt());
    dto->version = oatpp::Int32(item.getVersion());

    // 其他
    dto->prescriptionNo = oatpp::String(item.getPrescriptionNo());
    dto->remark = oatpp::String(item.getRemark());

    return dto;
}

OrderDetailDTO1::Wrapper OrderDAO1::buildDeviceDTO(
    const DeviceRequestDO1& item,
    const DeviceDefinitionDO1& def,
    const std::string& doctorName)
{
    auto dto = OrderDetailDTO1::createShared();

    // 基础信息
    dto->orderId = oatpp::String(item.getId());
    dto->encounterId = oatpp::String(item.getEncounterId());
    dto->patientId = oatpp::String(item.getPatientId());
    dto->doctorId = oatpp::String(item.getRequesterId());
    dto->doctorName = oatpp::String(doctorName);

    // 目录信息
    dto->catalogId = oatpp::String(def.getId());
    dto->itemCode = oatpp::String(def.getBusNo());
    dto->itemName = oatpp::String(def.getName());
    dto->spec = oatpp::String(def.getTotalVolume());
    dto->orderType = oatpp::String("device");

    // 分类信息
    dto->categoryCode = oatpp::String(def.getCategoryCode());

    // 临床决策字段
    dto->dose = oatpp::Float64(0.0);
    dto->doseUnit = oatpp::String("");
    dto->frequency = oatpp::String(item.getRateCode());
    dto->routeCode = oatpp::String("");
    dto->quantity = oatpp::Float64(item.getQuantity());
    dto->quantityUnit = oatpp::String(item.getUnitCode());
    dto->isSkinTest = oatpp::Boolean(false);

    // 使用天数计算
    int days = 0;
    if (!item.getUseStartTime().empty() && !item.getUseEndTime().empty()) {
        std::tm tmStart = {}, tmEnd = {};
        std::istringstream ssStart(item.getUseStartTime());
        std::istringstream ssEnd(item.getUseEndTime());
        ssStart >> std::get_time(&tmStart, "%Y-%m-%d %H:%M:%S");
        ssEnd >> std::get_time(&tmEnd, "%Y-%m-%d %H:%M:%S");
        if (!ssStart.fail() && !ssEnd.fail()) {
            std::time_t timeStart = std::mktime(&tmStart);
            std::time_t timeEnd = std::mktime(&tmEnd);
            days = (int)((timeEnd - timeStart) / (24 * 3600));
            if (days < 0) days = 0;
        }
    }
    dto->useDays = oatpp::Int32(days);

    dto->contentPerUnit = oatpp::String(def.getTotalVolume());

    // 单价和总价
    double unitPrice = getUnitPrice("adm_device_definition", item.getDeviceDefId());
    dto->unitPrice = oatpp::Float64(unitPrice);
    dto->totalPrice = oatpp::Float64(unitPrice * item.getQuantity());

    // 状态
    dto->status = oatpp::String(item.getStatusEnum());

    // 分组与排序
    dto->groupId = oatpp::String("");
    dto->orderNo = oatpp::Int32(item.getSortNumber());

    // 时间与版本
    dto->createTime = oatpp::String(item.getCreatedAt());
    dto->updatedAt = oatpp::String(item.getUpdatedAt());
    dto->version = oatpp::Int32(item.getVersion());

    // 其他
    dto->prescriptionNo = oatpp::String(item.getPrescriptionNo());
    dto->remark = oatpp::String(item.getRemark());

    return dto;
}

// ========== 查询定义表 ==========

PtrMedicationDefinitionDO1 OrderDAO1::selectMedicationDefinitionById(const std::string& id)
{
    if (id.empty()) return nullptr;
    std::string sql = "SELECT * FROM med_medication_definition WHERE id = ? AND status_enum = 'ACTIVE' AND is_deleted = 0 LIMIT 1";
    return sqlSession->executeQueryOne<PtrMedicationDefinitionDO1>(sql, PtrMedicationDefinitionMapper1(), "%s", id);
}

PtrActivityDefinitionDO1 OrderDAO1::selectActivityDefinitionById(const std::string& id)
{
    if (id.empty()) return nullptr;
    std::string sql = "SELECT * FROM wkf_activity_definition WHERE id = ? AND status_enum = 'ACTIVE' AND is_deleted = 0 LIMIT 1";
    return sqlSession->executeQueryOne<PtrActivityDefinitionDO1>(sql, PtrActivityDefinitionMapper1(), "%s", id);
}

PtrDeviceDefinitionDO1 OrderDAO1::selectDeviceDefinitionById(const std::string& id)
{
    if (id.empty()) return nullptr;
    std::string sql = "SELECT * FROM adm_device_definition WHERE id = ? AND status_enum = 'ACTIVE' AND is_deleted = 0 LIMIT 1";
    return sqlSession->executeQueryOne<PtrDeviceDefinitionDO1>(sql, PtrDeviceDefinitionMapper1(), "%s", id);
}

// ========== 查询医嘱列表（核心方法） ==========

std::list<OrderDetailDTO1::Wrapper> OrderDAO1::queryOrderList(
    const std::string& encounterId,
    const std::string& keyword,
    const std::string& orderType,
    const std::list<std::string>& statusList,
    uint64_t pageIndex,
    uint64_t pageSize,
    uint64_t& total,
    const std::string& doctorName)
{
    std::list<OrderDetailDTO1::Wrapper> resultList;

    if (pageIndex < 1) pageIndex = 1;
    if (pageSize < 1) pageSize = 10;

    // 构建状态条件
    std::string statusCond = buildStatusCondition(statusList);

    // 决定查询哪些表
    bool queryMedication = (orderType.empty() || orderType == "medication");
    bool queryService = (orderType.empty() || orderType == "service");
    bool queryDevice = (orderType.empty() || orderType == "device");

    // 合并列表：<创建时间, DTO>
    std::list<std::pair<std::string, OrderDetailDTO1::Wrapper>> mergedList;

    // 1. 查询药品医嘱
    if (queryMedication) {
        std::string keywordCond = buildKeywordCondition(keyword, "med_medication_definition", "id", "medication_id");
        std::string sql = "SELECT * FROM med_medication_request "
            "WHERE encounter_id = ? AND is_deleted = 0" +
            keywordCond + statusCond +
            " ORDER BY sort_number ASC, created_at DESC";

        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        auto orders = sqlSession->executeQuery<MedicationRequestDO1>(sql, MedicationRequestMapper1(), params);

        for (const auto& item : orders) {
            auto def = selectMedicationDefinitionById(item.getMedicationId());
            if (def) {
                auto dto = buildMedicationDTO(item, *def, doctorName);
                mergedList.push_back({ item.getCreatedAt(), dto });
            }
        }
    }

    // 2. 查询诊疗医嘱
    if (queryService) {
        std::string keywordCond = buildKeywordCondition(keyword, "wkf_activity_definition", "id", "activity_id");
        std::string sql = "SELECT * FROM wkf_service_request "
            "WHERE encounter_id = ? AND is_deleted = 0" +
            keywordCond + statusCond +
            " ORDER BY sort_number ASC, created_at DESC";

        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        auto orders = sqlSession->executeQuery<ServiceRequestDO1>(sql, ServiceRequestMapper1(), params);

        for (const auto& item : orders) {
            auto def = selectActivityDefinitionById(item.getActivityId());
            if (def) {
                auto dto = buildServiceDTO(item, *def, doctorName);
                mergedList.push_back({ item.getCreatedAt(), dto });
            }
        }
    }

    // 3. 查询耗材医嘱
    if (queryDevice) {
        std::string keywordCond = buildKeywordCondition(keyword, "adm_device_definition", "id", "device_def_id");
        std::string sql = "SELECT * FROM wkf_device_request "
            "WHERE encounter_id = ? AND is_deleted = 0" +
            keywordCond + statusCond +
            " ORDER BY sort_number ASC, created_at DESC";

        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        auto orders = sqlSession->executeQuery<DeviceRequestDO1>(sql, DeviceRequestMapper1(), params);

        for (const auto& item : orders) {
            auto def = selectDeviceDefinitionById(item.getDeviceDefId());
            if (def) {
                auto dto = buildDeviceDTO(item, *def, doctorName);
                mergedList.push_back({ item.getCreatedAt(), dto });
            }
        }
    }

    // 排序：先按 sortNumber（orderNo）升序，再按创建时间降序
    mergedList.sort([](const auto& a, const auto& b) {
        int sortA = a.second->orderNo ? a.second->orderNo.getValue(0) : 0;
        int sortB = b.second->orderNo ? b.second->orderNo.getValue(0) : 0;
        if (sortA != sortB) return sortA < sortB;
        return a.first > b.first;
        });

    total = mergedList.size();

    // 分页截取
    uint64_t start = (pageIndex - 1) * pageSize;
    uint64_t end = std::min(start + pageSize, total);

    uint64_t idx = 0;
    for (auto it = mergedList.begin(); it != mergedList.end() && idx < end; ++it, ++idx) {
        if (idx >= start) {
            resultList.push_back(it->second);
        }
    }

    return resultList;
}

// ========== 插入 ==========

bool OrderDAO1::insertMedicationOrder(const MedicationRequestDO1& data)
{
    return insert(data) == 1;
}

bool OrderDAO1::insertServiceOrder(const ServiceRequestDO1& data)
{
    return insert(data) == 1;
}

bool OrderDAO1::insertDeviceOrder(const DeviceRequestDO1& data)
{
    return insert(data) == 1;
}

// ========== 更新 ==========

bool OrderDAO1::updateMedicationOrder(const MedicationRequestDO1& data)
{
    return update(data) == 1;
}

bool OrderDAO1::updateServiceOrder(const ServiceRequestDO1& data)
{
    return update(data) == 1;
}

bool OrderDAO1::updateDeviceOrder(const DeviceRequestDO1& data)
{
    return update(data) == 1;
}

// ========== 查询单条 ==========

PtrMedicationRequestDO1 OrderDAO1::selectMedicationOrderById(const std::string& id)
{
    std::string sql = "SELECT * FROM med_medication_request WHERE id = ? AND is_deleted = 0";
    return sqlSession->executeQueryOne<PtrMedicationRequestDO1>(sql, PtrMedicationRequestMapper1(), "%s", id);
}

PtrServiceRequestDO1 OrderDAO1::selectServiceOrderById(const std::string& id)
{
    std::string sql = "SELECT * FROM wkf_service_request WHERE id = ? AND is_deleted = 0";
    return sqlSession->executeQueryOne<PtrServiceRequestDO1>(sql, PtrServiceRequestMapper1(), "%s", id);
}

PtrDeviceRequestDO1 OrderDAO1::selectDeviceOrderById(const std::string& id)
{
    std::string sql = "SELECT * FROM wkf_device_request WHERE id = ? AND is_deleted = 0";
    return sqlSession->executeQueryOne<PtrDeviceRequestDO1>(sql, PtrDeviceRequestMapper1(), "%s", id);
}