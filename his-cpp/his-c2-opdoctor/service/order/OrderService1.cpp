// service/order/OrderService1.cpp
#include "stdafx.h"
#include "OrderService1.h"
#include "../../dao/order/OrderDAO1.h"
#include "../../dao/order/OrderAuditDAO1.h"
#include "../../dao/order/EnumDAO.h"
#include "../../service/session/SessionService.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"
#include "domain/do/order/MedicationRequestDO1.h"
#include "domain/do/order/ServiceRequestDO1.h"
#include "domain/do/order/DeviceRequestDO1.h"
#include "domain/do/order/MedicationDefinitionDO1.h"
#include "domain/do/order/ActivityDefinitionDO1.h"
#include "domain/do/order/DeviceDefinitionDO1.h"
#include "RedisClient.h"
#include "MongoClient.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>

// ========== 日期工具函数 ==========
std::string OrderService1::addDaysToDate(const std::string& dateStr, int days)
{
    if (dateStr.empty()) {
        return SimpleDateTimeFormat::format();
    }
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        return SimpleDateTimeFormat::format();
    }
    std::time_t time = std::mktime(&tm);
    time += days * 24 * 3600;
    std::tm* resultTm = std::localtime(&time);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", resultTm);
    return std::string(buffer);
}

// ========== 构造函数 ==========
OrderService1::OrderService1(std::shared_ptr<RedisClient> redisClient,
    std::shared_ptr<MongoClient> mongoClient)
    : m_redisClient(redisClient), m_mongoClient(mongoClient)
{
    m_sessionService = std::make_shared<SessionService>(redisClient);
    m_auditDAO = std::make_shared<OrderAuditDAO1>(mongoClient);
    m_enumDAO = std::make_shared<EnumDAO>(mongoClient);
}

// ========== 枚举校验方法 ==========
bool OrderService1::validateEnumCode(const std::string& enumTypeKey,
    const std::string& enumKey,
    std::string& outDisplay,
    std::string& errorMsg)
{
    if (!m_enumDAO) {
        errorMsg = "MongoDB enum service is unavailable";
        return false;
    }
    if (enumKey.empty()) {
        errorMsg = enumTypeKey + " value cannot be empty";
        return false;
    }
    EnumValue val;
    if (m_enumDAO->getEnumValue(enumTypeKey, enumKey, val)) {
        outDisplay = val.name;
        return true;
    }
    errorMsg = "Invalid " + enumTypeKey + " value: " + enumKey;
    return false;
}

bool OrderService1::validateEnumCode(const std::string& enumTypeKey,
    const std::string& enumKey,
    std::string& errorMsg)
{
    std::string dummy;
    return validateEnumCode(enumTypeKey, enumKey, dummy, errorMsg);
}

std::string OrderService1::getEnumDisplay(const std::string& enumTypeKey,
    const std::string& enumKey)
{
    if (!m_enumDAO || enumKey.empty()) return enumKey;
    EnumValue val;
    if (m_enumDAO->getEnumValue(enumTypeKey, enumKey, val)) {
        return val.name;
    }
    return enumKey;
}

std::vector<EnumValue> OrderService1::getEnumValues(const std::string& enumTypeKey)
{
    if (m_enumDAO) {
        return m_enumDAO->getEnumValues(enumTypeKey);
    }
    return std::vector<EnumValue>();
}

OrderService1::ServiceContext OrderService1::buildContext(const PayloadDTO* payload)
{
    ServiceContext ctx;
    ctx.valid = false;
    if (!payload) return ctx;

    ctx.userId = payload->getId();
    ctx.username = payload->getUsername();
    ctx.practitionerId = payload->getPractitionerId();
    ctx.practitionerName = payload->getPractitionerName();

    auto tenantIdOpt = m_sessionService->getTenantId(ctx.userId);
    ctx.tenantId = tenantIdOpt.has_value() ? tenantIdOpt.value() : "DEFAULT_TENANT";

    auto orgIdOpt = m_sessionService->getOrgId(ctx.userId);
    ctx.orgId = orgIdOpt.has_value() ? orgIdOpt.value() : "DEFAULT_ORG";

    // 从 Redis 获取医院机构ID
    auto hospitalOrgIdOpt = m_sessionService->getHospitalOrganizationId(ctx.userId);
    ctx.hospitalOrgId = hospitalOrgIdOpt.has_value() ? hospitalOrgIdOpt.value() : "";

    // 从 Redis 获取组织单元ID
    auto orgUnitIdOpt = m_sessionService->getOrganizationUnitId(ctx.userId);
    ctx.organizationUnitId = orgUnitIdOpt.has_value() ? orgUnitIdOpt.value() : "";

    ctx.valid = true;
    return ctx;
}

// ========== 审计日志 ==========
void OrderService1::auditLog(
    const ServiceContext& ctx,
    const std::string& orderId,
    const std::string& orderType,
    const std::string& operationType,
    const std::string& beforeData,
    const std::string& afterData,
    const std::list<std::string>& changedFields,
    const std::string& remark)
{
    if (!m_auditDAO) return;
    auto audit = OrderAuditDTO1::createShared();
    audit->orderId = oatpp::String(orderId);
    audit->orderType = oatpp::String(orderType);
    audit->operationType = oatpp::String(operationType);
    audit->operatorId = oatpp::String(ctx.practitionerId);
    audit->operatorName = oatpp::String(ctx.practitionerName);
    audit->operatorOrgId = oatpp::String(ctx.orgId);
    audit->operationTime = oatpp::String(SimpleDateTimeFormat::format());
    audit->remark = oatpp::String(remark);
    if (!beforeData.empty()) audit->beforeData = oatpp::String(beforeData);
    if (!afterData.empty()) audit->afterData = oatpp::String(afterData);
    if (!changedFields.empty()) {
        auto list = oatpp::List<oatpp::String>::createShared();
        for (const auto& field : changedFields) {
            list->push_back(oatpp::String(field));
        }
        audit->changedFields = list;
    }
    m_auditDAO->saveAuditLog(audit);
}

// ========== 从 DO 构建完整 DTO（使用事务共享的 dao） ==========
OrderDetailDTO1::Wrapper OrderService1::buildOrderDetailDTO(
    const std::string& orderId,
    const std::string& orderType,
    const std::string& doctorName,
    OrderDAO1& dao)
{
    if (orderId.empty() || orderType.empty()) {
        return nullptr;
    }

    if (orderType == "medication") {
        auto medOrder = dao.selectMedicationOrderById(orderId);
        if (!medOrder) {
            return nullptr;
        }
        auto def = dao.selectMedicationDefinitionById(medOrder->getMedicationId());
        if (!def) {
            return nullptr;
        }
        auto dto = OrderDetailDTO1::createShared();
        dto->orderId = oatpp::String(medOrder->getId());
        dto->encounterId = oatpp::String(medOrder->getEncounterId());
        dto->patientId = oatpp::String(medOrder->getPatientId());
        dto->doctorId = oatpp::String(medOrder->getRequesterId());
        dto->doctorName = oatpp::String(doctorName);
        dto->catalogId = oatpp::String(def->getId());
        dto->itemCode = oatpp::String(def->getBusNo());
        dto->itemName = oatpp::String(def->getName());
        dto->spec = oatpp::String(def->getTotalVolume());
        dto->orderType = oatpp::String("medication");
        dto->categoryCode = oatpp::String(def->getCategoryCode());
        dto->dose = oatpp::Float64(medOrder->getDose());
        dto->doseUnit = oatpp::String(medOrder->getDoseUnitCode());
        dto->frequency = oatpp::String(medOrder->getRateCode());
        dto->routeCode = oatpp::String(medOrder->getMethodCode());
        dto->quantity = oatpp::Float64(medOrder->getQuantity());
        dto->quantityUnit = oatpp::String(medOrder->getUnitCode());
        dto->isSkinTest = oatpp::Boolean(medOrder->getSkinTestFlag() == 1);
        int days = 0;
        if (!medOrder->getEffectiveDoseStart().empty() && !medOrder->getEffectiveDoseEnd().empty()) {
            std::tm tmStart = {}, tmEnd = {};
            std::istringstream ssStart(medOrder->getEffectiveDoseStart());
            std::istringstream ssEnd(medOrder->getEffectiveDoseEnd());
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
        dto->contentPerUnit = oatpp::String(def->getTotalVolume());
        double unitPrice = dao.getUnitPrice("med_medication_definition", medOrder->getMedicationId());
        dto->unitPrice = oatpp::Float64(unitPrice);
        dto->totalPrice = oatpp::Float64(unitPrice * medOrder->getQuantity());
        dto->status = oatpp::String(medOrder->getStatusEnum());
        dto->groupId = oatpp::String(medOrder->getGroupId());
        dto->orderNo = oatpp::Int32(medOrder->getSortNumber());
        dto->createTime = oatpp::String(medOrder->getCreatedAt());
        dto->updatedAt = oatpp::String(medOrder->getUpdatedAt());
        dto->version = oatpp::Int32(medOrder->getVersion());
        dto->prescriptionNo = oatpp::String(medOrder->getPrescriptionNo());
        dto->remark = oatpp::String(medOrder->getRemark());
        dto->orderTypeDisplay = oatpp::String(getEnumDisplay("ORDER_TYPE", "medication"));
        dto->statusDisplay = oatpp::String(getEnumDisplay("ORDER_STATUS", medOrder->getStatusEnum()));
        dto->frequencyDisplay = oatpp::String(getEnumDisplay("FREQUENCY", medOrder->getRateCode()));
        dto->routeDisplay = oatpp::String(getEnumDisplay("ROUTE_CODE", medOrder->getMethodCode()));
        if (dto->categoryCode) {
            dto->categoryName = oatpp::String(getEnumDisplay("MEDICATION_CATEGORY", dto->categoryCode.getValue("")));
        }
        return dto;
    }
    else if (orderType == "service") {
        auto svcOrder = dao.selectServiceOrderById(orderId);
        if (!svcOrder) return nullptr;
        auto def = dao.selectActivityDefinitionById(svcOrder->getActivityId());
        if (!def) return nullptr;
        auto dto = OrderDetailDTO1::createShared();
        dto->orderId = oatpp::String(svcOrder->getId());
        dto->encounterId = oatpp::String(svcOrder->getEncounterId());
        dto->patientId = oatpp::String(svcOrder->getPatientId());
        dto->doctorId = oatpp::String(svcOrder->getRequesterId());
        dto->doctorName = oatpp::String(doctorName);
        dto->catalogId = oatpp::String(def->getId());
        dto->itemCode = oatpp::String(def->getBusNo());
        dto->itemName = oatpp::String(def->getName());
        dto->spec = oatpp::String(def->getDescriptionText());
        dto->orderType = oatpp::String("service");
        dto->categoryCode = oatpp::String(def->getCategoryCode());
        dto->dose = 0.0;
        dto->doseUnit = oatpp::String("");
        dto->frequency = oatpp::String(svcOrder->getRateCode());
        dto->routeCode = oatpp::String("");
        dto->quantity = oatpp::Float64(svcOrder->getQuantity());
        dto->quantityUnit = oatpp::String(svcOrder->getUnitCode());
        dto->isSkinTest = oatpp::Boolean(false);
        int days = 0;
        if (!svcOrder->getOccurrenceStartTime().empty() && !svcOrder->getOccurrenceEndTime().empty()) {
            std::tm tmStart = {}, tmEnd = {};
            std::istringstream ssStart(svcOrder->getOccurrenceStartTime());
            std::istringstream ssEnd(svcOrder->getOccurrenceEndTime());
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
        dto->contentPerUnit = oatpp::String(def->getDescriptionText());
        double unitPrice = dao.getUnitPrice("wkf_activity_definition", svcOrder->getActivityId());
        dto->unitPrice = oatpp::Float64(unitPrice);
        dto->totalPrice = oatpp::Float64(unitPrice * svcOrder->getQuantity());
        dto->status = oatpp::String(svcOrder->getStatusEnum());
        dto->groupId = oatpp::String(svcOrder->getGroupId());
        dto->orderNo = oatpp::Int32(svcOrder->getSortNumber());
        dto->createTime = oatpp::String(svcOrder->getCreatedAt());
        dto->updatedAt = oatpp::String(svcOrder->getUpdatedAt());
        dto->version = oatpp::Int32(svcOrder->getVersion());
        dto->prescriptionNo = oatpp::String(svcOrder->getPrescriptionNo());
        dto->remark = oatpp::String(svcOrder->getRemark());
        dto->orderTypeDisplay = oatpp::String(getEnumDisplay("ORDER_TYPE", "service"));
        dto->statusDisplay = oatpp::String(getEnumDisplay("ORDER_STATUS", svcOrder->getStatusEnum()));
        dto->frequencyDisplay = oatpp::String(getEnumDisplay("FREQUENCY", svcOrder->getRateCode()));
        dto->routeDisplay = oatpp::String("");
        if (dto->categoryCode) {
            dto->categoryName = oatpp::String(getEnumDisplay("MEDICATION_CATEGORY", dto->categoryCode.getValue("")));
        }
        return dto;
    }
    else if (orderType == "device") {
        auto devOrder = dao.selectDeviceOrderById(orderId);
        if (!devOrder) return nullptr;
        auto def = dao.selectDeviceDefinitionById(devOrder->getDeviceDefId());
        if (!def) return nullptr;
        auto dto = OrderDetailDTO1::createShared();
        dto->orderId = oatpp::String(devOrder->getId());
        dto->encounterId = oatpp::String(devOrder->getEncounterId());
        dto->patientId = oatpp::String(devOrder->getPatientId());
        dto->doctorId = oatpp::String(devOrder->getRequesterId());
        dto->doctorName = oatpp::String(doctorName);
        dto->catalogId = oatpp::String(def->getId());
        dto->itemCode = oatpp::String(def->getBusNo());
        dto->itemName = oatpp::String(def->getName());
        dto->spec = oatpp::String(def->getTotalVolume());
        dto->orderType = oatpp::String("device");
        dto->categoryCode = oatpp::String(def->getCategoryCode());
        dto->dose = 0.0;
        dto->doseUnit = oatpp::String("");
        dto->frequency = oatpp::String(devOrder->getRateCode());
        dto->routeCode = oatpp::String("");
        dto->quantity = oatpp::Float64(devOrder->getQuantity());
        dto->quantityUnit = oatpp::String(devOrder->getUnitCode());
        dto->isSkinTest = oatpp::Boolean(false);
        int days = 0;
        if (!devOrder->getUseStartTime().empty() && !devOrder->getUseEndTime().empty()) {
            std::tm tmStart = {}, tmEnd = {};
            std::istringstream ssStart(devOrder->getUseStartTime());
            std::istringstream ssEnd(devOrder->getUseEndTime());
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
        dto->contentPerUnit = oatpp::String(def->getTotalVolume());
        double unitPrice = dao.getUnitPrice("adm_device_definition", devOrder->getDeviceDefId());
        dto->unitPrice = oatpp::Float64(unitPrice);
        dto->totalPrice = oatpp::Float64(unitPrice * devOrder->getQuantity());
        dto->status = oatpp::String(devOrder->getStatusEnum());
        dto->groupId = oatpp::String("");
        dto->orderNo = oatpp::Int32(devOrder->getSortNumber());
        dto->createTime = oatpp::String(devOrder->getCreatedAt());
        dto->updatedAt = oatpp::String(devOrder->getUpdatedAt());
        dto->version = oatpp::Int32(devOrder->getVersion());
        dto->prescriptionNo = oatpp::String(devOrder->getPrescriptionNo());
        dto->remark = oatpp::String(devOrder->getRemark());
        dto->orderTypeDisplay = oatpp::String(getEnumDisplay("ORDER_TYPE", "device"));
        dto->statusDisplay = oatpp::String(getEnumDisplay("ORDER_STATUS", devOrder->getStatusEnum()));
        dto->frequencyDisplay = oatpp::String(getEnumDisplay("FREQUENCY", devOrder->getRateCode()));
        dto->routeDisplay = oatpp::String("");
        if (dto->categoryCode) {
            dto->categoryName = oatpp::String(getEnumDisplay("MEDICATION_CATEGORY", dto->categoryCode.getValue("")));
        }
        return dto;
    }
    return nullptr;
}

OrderDetailDTO1::Wrapper OrderService1::insertMedicationOrder(
    const OrderAddDTO1::Wrapper& dto,
    const ServiceContext& ctx,
    const std::string& encounterId,
    const std::string& patientId,
    const std::string& medicationId,
    const std::string& orderId,
    const std::string& now,
    int orderNo,
    OrderDAO1& dao,
    std::string& errorMsg)
{
    auto def = dao.selectMedicationDefinitionById(medicationId);
    if (!def) {
        errorMsg = "Medication definition not found: " + medicationId;
        return nullptr;
    }

    double dose = dto->dose ? dto->dose.getValue(0) : 0;
    if (dose <= 0) {
        errorMsg = "dose is required for medication";
        return nullptr;
    }

    double quantity = dto->quantity ? dto->quantity.getValue(0) : 0;
    if (quantity <= 0) {
        errorMsg = "quantity is required for medication";
        return nullptr;
    }

    std::string frequency = dto->frequency.getValue("");
    if (frequency.empty()) frequency = def->getRateCode();

    std::string routeCode = dto->routeCode.getValue("");
    if (routeCode.empty()) routeCode = def->getMethodCode();

    std::string doseUnit = dto->doseUnit.getValue("");
    if (doseUnit.empty()) doseUnit = def->getDoseUnitCode();

    std::string quantityUnit = dto->quantityUnit.getValue("");
    if (quantityUnit.empty()) quantityUnit = def->getPackageUnitCode();

    int useDays = dto->useDays ? dto->useDays.getValue(0) : 0;
    bool isSkinTest = dto->isSkinTest ? dto->isSkinTest.getValue(false) : false;

    MedicationRequestDO1 data;
    data.setId(orderId);
    data.setTenantId(ctx.tenantId);
    data.setRequesterId(ctx.practitionerId);
    data.setOrgId(ctx.orgId);
    data.setCreatedBy(ctx.username);
    data.setUpdatedBy(ctx.username);
    data.setCreatedAt(now);
    data.setUpdatedAt(now);
    data.setStatusEnum("DRAFT");
    data.setEncounterId(encounterId);
    data.setPatientId(patientId);
    data.setMedicationId(medicationId);
    data.setBusNo(def->getBusNo());
    data.setQuantity(quantity);
    data.setUnitCode(quantityUnit);
    data.setMethodCode(routeCode);
    data.setRateCode(frequency);
    data.setDose(dose);
    data.setDoseUnitCode(doseUnit);
    data.setSkinTestFlag(isSkinTest ? 1 : 0);
    data.setRemark(dto->remark.getValue(""));
    data.setGroupId(dto->groupId.getValue(""));
    data.setSortNumber(orderNo);
    data.setTherapyEnum("TESTORDER");
    data.setEffectiveDoseStart(now);
    data.setEffectiveDoseEnd(useDays > 0 ? addDaysToDate(now, useDays) : now);
    data.setStatusChangedTime(now);

    // ===== 设置 performLocation 和 performOrg =====
    // 直接使用 ctx 中的值，确保不为空
    std::string performLocationStr = "1";
    std::string performOrgStr = "1";

    if (!ctx.organizationUnitId.empty()) {
        performLocationStr = ctx.organizationUnitId;
    }
    else if (!ctx.orgId.empty()) {
        performLocationStr = ctx.orgId;
    }

    if (!ctx.hospitalOrgId.empty()) {
        performOrgStr = ctx.hospitalOrgId;
    }
    else if (!ctx.orgId.empty()) {
        performOrgStr = ctx.orgId;
    }


    data.setPerformLocation(performLocationStr);
    data.setPerformOrg(performOrgStr);
    data.setReqAuthoredTime(now);
    data.setCheckTime(now);
    data.setVersion(0);

    if (!dao.insertMedicationOrder(data)) {
        errorMsg = "Failed to save medication order";
        return nullptr;
    }
    auto dtoResult = buildOrderDetailDTO(orderId, "medication", ctx.practitionerName, dao);
    if (!dtoResult) {
        errorMsg = "Order saved but failed to retrieve details";
        return nullptr;
    }
    errorMsg = "";
    return dtoResult;
}

// ========== 插入诊疗医嘱 ==========
OrderDetailDTO1::Wrapper OrderService1::insertServiceOrder(
    const OrderAddDTO1::Wrapper& dto,
    const ServiceContext& ctx,
    const std::string& encounterId,
    const std::string& patientId,
    const std::string& activityId,
    const std::string& orderId,
    const std::string& now,
    int orderNo,
    OrderDAO1& dao,
    std::string& errorMsg)
{
    auto def = dao.selectActivityDefinitionById(activityId);
    if (!def) {
        errorMsg = "Activity definition not found: " + activityId;
        return nullptr;
    }

    double quantity = dto->quantity ? dto->quantity.getValue(0) : 0;
    if (quantity <= 0) {
        errorMsg = "quantity is required for service order";
        return nullptr;
    }

    int useDays = dto->useDays ? dto->useDays.getValue(0) : 0;

    ServiceRequestDO1 data;
    data.setId(orderId);
    data.setTenantId(ctx.tenantId);
    data.setRequesterId(ctx.practitionerId);
    data.setOrgId(ctx.orgId);
    data.setCreatedBy(ctx.username);
    data.setUpdatedBy(ctx.username);
    data.setCreatedAt(now);
    data.setUpdatedAt(now);
    data.setStatusEnum("DRAFT");
    data.setEncounterId(encounterId);
    data.setPatientId(patientId);
    data.setActivityId(activityId);
    data.setBusNo(def->getBusNo());
    data.setQuantity(quantity);
    data.setUnitCode(dto->quantityUnit.getValue(""));
    data.setRateCode(dto->frequency.getValue(""));
    data.setReasonText("");
    data.setRemark(dto->remark.getValue(""));
    data.setGroupId(dto->groupId.getValue(""));
    data.setSortNumber(orderNo);
    data.setOccurrenceStartTime(now);
    data.setOccurrenceEndTime(useDays > 0 ? addDaysToDate(now, useDays) : now);
    data.setVersion(0);
    data.setCategoryEnum(def->getCategoryCode());

    if (!dao.insertServiceOrder(data)) {
        errorMsg = "Failed to save service order";
        return nullptr;
    }
    auto dtoResult = buildOrderDetailDTO(orderId, "service", ctx.practitionerName, dao);
    if (!dtoResult) {
        errorMsg = "Order saved but failed to retrieve details";
        return nullptr;
    }
    errorMsg = "";
    return dtoResult;
}

// ========== 插入耗材医嘱 ==========
OrderDetailDTO1::Wrapper OrderService1::insertDeviceOrder(
    const OrderAddDTO1::Wrapper& dto,
    const ServiceContext& ctx,
    const std::string& encounterId,
    const std::string& patientId,
    const std::string& deviceDefId,
    const std::string& orderId,
    const std::string& now,
    int orderNo,
    OrderDAO1& dao,
    std::string& errorMsg)
{
    auto def = dao.selectDeviceDefinitionById(deviceDefId);
    if (!def) {
        errorMsg = "Device definition not found: " + deviceDefId;
        return nullptr;
    }

    double quantity = dto->quantity ? dto->quantity.getValue(0) : 0;
    if (quantity <= 0) {
        errorMsg = "quantity is required for device order";
        return nullptr;
    }

    int useDays = dto->useDays ? dto->useDays.getValue(0) : 0;

    DeviceRequestDO1 data;
    data.setId(orderId);
    data.setTenantId(ctx.tenantId);
    data.setRequesterId(ctx.practitionerId);
    data.setOrgId(ctx.orgId);
    data.setCreatedBy(ctx.username);
    data.setUpdatedBy(ctx.username);
    data.setCreatedAt(now);
    data.setUpdatedAt(now);
    data.setStatusEnum("DRAFT");
    data.setEncounterId(encounterId);
    data.setPatientId(patientId);
    data.setDeviceDefId(deviceDefId);
    data.setBusNo(def->getBusNo());
    data.setQuantity(quantity);
    data.setUnitCode(dto->quantityUnit.getValue(""));
    data.setRateCode(dto->frequency.getValue(""));
    data.setRemark(dto->remark.getValue(""));
    data.setSortNumber(orderNo);
    data.setUseStartTime(now);
    data.setUseEndTime(useDays > 0 ? addDaysToDate(now, useDays) : now);
    data.setVersion(0);

    if (!dao.insertDeviceOrder(data)) {
        errorMsg = "Failed to save device order";
        return nullptr;
    }
    auto dtoResult = buildOrderDetailDTO(orderId, "device", ctx.practitionerName, dao);
    if (!dtoResult) {
        errorMsg = "Order saved but failed to retrieve details";
        return nullptr;
    }
    errorMsg = "";
    return dtoResult;
}

// ========== 内部新增方法 ==========
OrderDetailDTO1::Wrapper OrderService1::addOrderInternal(
    const OrderAddDTO1::Wrapper& dto,
    const PayloadDTO* payload,
    const ServiceContext& ctx,
    OrderDAO1& dao,
    std::string& errorMsg)
{
    std::string encounterId = dto->encounterId.getValue("");
    if (encounterId.empty()) {
        errorMsg = "encounterId is required";
        return nullptr;
    }

    std::string catalogId = dto->catalogId.getValue("");
    if (catalogId.empty()) {
        errorMsg = "catalogId is required";
        return nullptr;
    }

    std::string orderType = dto->orderType.getValue("");
    if (orderType.empty()) {
        errorMsg = "orderType is required";
        return nullptr;
    }

    int orderNo = dto->orderNo ? dto->orderNo.getValue(0) : 0;
    if (orderNo <= 0) {
        errorMsg = "orderNo is required and must be > 0";
        return nullptr;
    }

    if (!validateEnumCode("ORDER_TYPE", orderType, errorMsg)) return nullptr;

    std::string expenseType = dto->expenseType.getValue("");
    if (!expenseType.empty()) {
        std::string expenseName;
        if (!validateEnumCode("EXPENSE_TYPE", expenseType, expenseName, errorMsg)) return nullptr;
    }

    bool isSkinTest = dto->isSkinTest ? dto->isSkinTest.getValue(false) : false;
    std::string skinTestCode = isSkinTest ? "1" : "0";
    if (!validateEnumCode("SKIN_TEST", skinTestCode, errorMsg)) return nullptr;

    std::string patientId = dao.getPatientIdByEncounterId(encounterId);
    if (patientId.empty()) {
        errorMsg = "Encounter not found or invalid: " + encounterId;
        return nullptr;
    }

    UuidFacade uuid;
    std::string now = SimpleDateTimeFormat::format();
    std::string orderId = uuid.genUuid();

    if (orderType == "medication") {
        std::string medicationId = dao.getMedicationIdByBusNo(catalogId);
        if (medicationId.empty()) {
            errorMsg = "Medication not found: " + catalogId;
            return nullptr;
        }
        double dose = dto->dose ? dto->dose.getValue(0) : 0;
        if (dose <= 0) {
            errorMsg = "dose is required for medication";
            return nullptr;
        }
        if (dto->doseUnit->empty()) {
            errorMsg = "doseUnit is required for medication";
            return nullptr;
        }
        if (dto->frequency->empty()) {
            errorMsg = "frequency is required for medication";
            return nullptr;
        }
        int useDays = dto->useDays ? dto->useDays.getValue(0) : 0;
        if (useDays <= 0) {
            errorMsg = "useDays is required for medication";
            return nullptr;
        }
        double quantity = dto->quantity ? dto->quantity.getValue(0) : 0;
        if (quantity <= 0) {
            errorMsg = "quantity is required for medication";
            return nullptr;
        }
        return insertMedicationOrder(dto, ctx, encounterId, patientId,
            medicationId, orderId, now, orderNo,
            dao, errorMsg);
    }
    else if (orderType == "service") {
        std::string activityId = dao.getActivityIdByBusNo(catalogId);
        if (activityId.empty()) {
            errorMsg = "Service not found: " + catalogId;
            return nullptr;
        }
        return insertServiceOrder(dto, ctx, encounterId, patientId,
            activityId, orderId, now, orderNo,
            dao, errorMsg);
    }
    else if (orderType == "device") {
        std::string deviceDefId = dao.getDeviceDefIdByBusNo(catalogId);
        if (deviceDefId.empty()) {
            errorMsg = "Device not found: " + catalogId;
            return nullptr;
        }
        return insertDeviceOrder(dto, ctx, encounterId, patientId,
            deviceDefId, orderId, now, orderNo,
            dao, errorMsg);
    }
    errorMsg = "Unsupported order type: " + orderType;
    return nullptr;
}

bool OrderService1::updateMedicationOrderInternal(
    const OrderModifyDTO1::Wrapper& dto,
    PtrMedicationRequestDO1& medOrder,
    const ServiceContext& ctx,
    std::string& errorMsg)
{
    std::string beforeData = "{\"dose\":\"" + std::to_string(medOrder->getDose()) +
        "\",\"doseUnit\":\"" + medOrder->getDoseUnitCode() +
        "\",\"frequency\":\"" + medOrder->getRateCode() +
        "\",\"routeCode\":\"" + medOrder->getMethodCode() +
        "\",\"useDays\":\"" + medOrder->getEffectiveDoseEnd() +
        "\",\"quantity\":\"" + std::to_string(medOrder->getQuantity()) +
        "\",\"quantityUnit\":\"" + medOrder->getUnitCode() +
        "\",\"isSkinTest\":\"" + std::to_string(medOrder->getSkinTestFlag()) +
        "\",\"remark\":\"" + medOrder->getRemark() +
        "\",\"groupId\":\"" + medOrder->getGroupId() +
        "\",\"sortNumber\":\"" + std::to_string(medOrder->getSortNumber()) + "\"}";
    std::list<std::string> changedFields;

    // 更新可修改的字段
    if (dto->dose) { medOrder->setDose(dto->dose.getValue(0)); changedFields.push_back("dose"); }
    if (!dto->doseUnit->empty()) { medOrder->setDoseUnitCode(dto->doseUnit.getValue("")); changedFields.push_back("doseUnit"); }
    if (!dto->frequency->empty()) { medOrder->setRateCode(dto->frequency.getValue("")); changedFields.push_back("frequency"); }
    if (!dto->routeCode->empty()) { medOrder->setMethodCode(dto->routeCode.getValue("")); changedFields.push_back("routeCode"); }
    if (dto->useDays) {
        int useDays = dto->useDays.getValue(0);
        if (useDays > 0) {
            medOrder->setEffectiveDoseEnd(addDaysToDate(medOrder->getEffectiveDoseStart(), useDays));
        }
        changedFields.push_back("useDays");
    }
    if (dto->quantity) { medOrder->setQuantity(dto->quantity.getValue(0)); changedFields.push_back("quantity"); }
    if (!dto->quantityUnit->empty()) { medOrder->setUnitCode(dto->quantityUnit.getValue("")); changedFields.push_back("quantityUnit"); }
    if (dto->isSkinTest) { medOrder->setSkinTestFlag(dto->isSkinTest.getValue(false) ? 1 : 0); changedFields.push_back("isSkinTest"); }
    if (!dto->remark->empty()) { medOrder->setRemark(dto->remark.getValue("")); changedFields.push_back("remark"); }
    if (!dto->groupId->empty()) { medOrder->setGroupId(dto->groupId.getValue("")); changedFields.push_back("groupId"); }
    if (dto->orderNo) { medOrder->setSortNumber(dto->orderNo.getValue(0)); changedFields.push_back("orderNo"); }

    // 更新审计字段
    medOrder->setUpdatedBy(ctx.username);
    medOrder->setUpdatedAt(SimpleDateTimeFormat::format());
    medOrder->setStatusChangedTime(SimpleDateTimeFormat::format());
    medOrder->setVersion(medOrder->getVersion() + 1);

    // ===== 修复：确保 req_authored_time 和 check_time 有值 =====
    // 这些字段不应该被修改，但 DO 对象中可能为空，需要保留原有值或设置当前时间
    if (medOrder->getReqAuthoredTime().empty()) {
        medOrder->setReqAuthoredTime(SimpleDateTimeFormat::format());
    }
    if (medOrder->getCheckTime().empty()) {
        medOrder->setCheckTime(SimpleDateTimeFormat::format());
    }

    // ===== 修复：确保 perform_location 和 perform_org 有值 =====
    if (medOrder->getPerformLocation().empty()) {
        medOrder->setPerformLocation(ctx.orgId.empty() ? "1" : ctx.orgId);
    }
    if (medOrder->getPerformOrg().empty()) {
        medOrder->setPerformOrg(ctx.hospitalOrgId.empty() ? ctx.orgId : ctx.hospitalOrgId);
    }
    if (medOrder->getPerformOrg().empty()) {
        medOrder->setPerformOrg("1");
    }

    OrderDAO1 dao;
    if (!dao.updateMedicationOrder(*medOrder)) {
        errorMsg = "Failed to update medication order";
        return false;
    }

    std::string afterData = "{\"dose\":\"" + std::to_string(medOrder->getDose()) +
        "\",\"doseUnit\":\"" + medOrder->getDoseUnitCode() +
        "\",\"frequency\":\"" + medOrder->getRateCode() +
        "\",\"routeCode\":\"" + medOrder->getMethodCode() +
        "\",\"useDays\":\"" + medOrder->getEffectiveDoseEnd() +
        "\",\"quantity\":\"" + std::to_string(medOrder->getQuantity()) +
        "\",\"quantityUnit\":\"" + medOrder->getUnitCode() +
        "\",\"isSkinTest\":\"" + std::to_string(medOrder->getSkinTestFlag()) +
        "\",\"remark\":\"" + medOrder->getRemark() +
        "\",\"groupId\":\"" + medOrder->getGroupId() +
        "\",\"sortNumber\":\"" + std::to_string(medOrder->getSortNumber()) + "\"}";

    auditLog(ctx, medOrder->getId(), "medication", "MODIFY",
        beforeData, afterData, changedFields, "Modify medication order");
    errorMsg = "";
    return true;
}
bool OrderService1::updateServiceOrderInternal(
    const OrderModifyDTO1::Wrapper& dto,
    PtrServiceRequestDO1& svcOrder,
    const ServiceContext& ctx,
    std::string& errorMsg)
{
    std::string beforeData = "{\"frequency\":\"" + svcOrder->getRateCode() +
        "\",\"quantity\":\"" + std::to_string(svcOrder->getQuantity()) +
        "\",\"remark\":\"" + svcOrder->getRemark() +
        "\",\"groupId\":\"" + svcOrder->getGroupId() +
        "\",\"sortNumber\":\"" + std::to_string(svcOrder->getSortNumber()) + "\"}";
    std::list<std::string> changedFields;

    // 更新可修改的字段
    if (!dto->frequency->empty()) { svcOrder->setRateCode(dto->frequency.getValue("")); changedFields.push_back("frequency"); }
    if (dto->quantity) { svcOrder->setQuantity(dto->quantity.getValue(0)); changedFields.push_back("quantity"); }
    if (!dto->remark->empty()) { svcOrder->setRemark(dto->remark.getValue("")); changedFields.push_back("remark"); }
    if (!dto->groupId->empty()) { svcOrder->setGroupId(dto->groupId.getValue("")); changedFields.push_back("groupId"); }
    if (dto->orderNo) { svcOrder->setSortNumber(dto->orderNo.getValue(0)); changedFields.push_back("orderNo"); }
    if (dto->useDays) {
        int useDays = dto->useDays.getValue(0);
        if (useDays > 0) {
            svcOrder->setOccurrenceEndTime(addDaysToDate(svcOrder->getOccurrenceStartTime(), useDays));
        }
        changedFields.push_back("useDays");
    }

    // 更新审计字段
    svcOrder->setUpdatedBy(ctx.username);
    svcOrder->setUpdatedAt(SimpleDateTimeFormat::format());
    svcOrder->setVersion(svcOrder->getVersion() + 1);

    // ===== 修复：确保 authored_time 和 check_time 有值 =====
    if (svcOrder->getAuthoredTime().empty()) {
        svcOrder->setAuthoredTime(SimpleDateTimeFormat::format());
    }
    if (svcOrder->getCheckTime().empty()) {
        svcOrder->setCheckTime(SimpleDateTimeFormat::format());
    }

    // ===== 修复：确保 orgId 有值 =====
    if (svcOrder->getOrgId().empty()) {
        svcOrder->setOrgId(ctx.orgId.empty() ? "1" : ctx.orgId);
    }

    OrderDAO1 dao;
    if (!dao.updateServiceOrder(*svcOrder)) {
        errorMsg = "Failed to update service order";
        return false;
    }

    std::string afterData = "{\"frequency\":\"" + svcOrder->getRateCode() +
        "\",\"quantity\":\"" + std::to_string(svcOrder->getQuantity()) +
        "\",\"remark\":\"" + svcOrder->getRemark() +
        "\",\"groupId\":\"" + svcOrder->getGroupId() +
        "\",\"sortNumber\":\"" + std::to_string(svcOrder->getSortNumber()) + "\"}";

    auditLog(ctx, svcOrder->getId(), "service", "MODIFY",
        beforeData, afterData, changedFields, "Modify service order");
    errorMsg = "";
    return true;
}
bool OrderService1::updateDeviceOrderInternal(
    const OrderModifyDTO1::Wrapper& dto,
    PtrDeviceRequestDO1& devOrder,
    const ServiceContext& ctx,
    std::string& errorMsg)
{
    std::string beforeData = "{\"frequency\":\"" + devOrder->getRateCode() +
        "\",\"quantity\":\"" + std::to_string(devOrder->getQuantity()) +
        "\",\"remark\":\"" + devOrder->getRemark() +
        "\",\"sortNumber\":\"" + std::to_string(devOrder->getSortNumber()) + "\"}";
    std::list<std::string> changedFields;

    // 更新可修改的字段
    if (!dto->frequency->empty()) { devOrder->setRateCode(dto->frequency.getValue("")); changedFields.push_back("frequency"); }
    if (dto->quantity) { devOrder->setQuantity(dto->quantity.getValue(0)); changedFields.push_back("quantity"); }
    if (!dto->remark->empty()) { devOrder->setRemark(dto->remark.getValue("")); changedFields.push_back("remark"); }
    if (dto->orderNo) { devOrder->setSortNumber(dto->orderNo.getValue(0)); changedFields.push_back("orderNo"); }
    if (dto->useDays) {
        int useDays = dto->useDays.getValue(0);
        if (useDays > 0) {
            devOrder->setUseEndTime(addDaysToDate(devOrder->getUseStartTime(), useDays));
        }
        changedFields.push_back("useDays");
    }

    // 更新审计字段
    devOrder->setUpdatedBy(ctx.username);
    devOrder->setUpdatedAt(SimpleDateTimeFormat::format());
    devOrder->setVersion(devOrder->getVersion() + 1);

    // ===== 修复：确保 req_authored_time 有值 =====
    if (devOrder->getReqAuthoredTime().empty()) {
        devOrder->setReqAuthoredTime(SimpleDateTimeFormat::format());
    }

    // ===== 修复：确保 orgId 有值 =====
    if (devOrder->getOrgId().empty()) {
        devOrder->setOrgId(ctx.orgId.empty() ? "1" : ctx.orgId);
    }

    OrderDAO1 dao;
    if (!dao.updateDeviceOrder(*devOrder)) {
        errorMsg = "Failed to update device order";
        return false;
    }

    std::string afterData = "{\"frequency\":\"" + devOrder->getRateCode() +
        "\",\"quantity\":\"" + std::to_string(devOrder->getQuantity()) +
        "\",\"remark\":\"" + devOrder->getRemark() +
        "\",\"sortNumber\":\"" + std::to_string(devOrder->getSortNumber()) + "\"}";

    auditLog(ctx, devOrder->getId(), "device", "MODIFY",
        beforeData, afterData, changedFields, "Modify device order");
    errorMsg = "";
    return true;
}
// ========== 查询医嘱列表 ==========
OrderDetailPageDTO1::Wrapper OrderService1::queryOrderList(
    const OrderQuery1::Wrapper& query,
    const PayloadDTO* payload)
{
    auto pageDto = OrderDetailPageDTO1::createShared();
    pageDto->pageIndex = query->pageIndex;
    pageDto->pageSize = query->pageSize;

    std::string encounterId = query->encounterId.getValue("");

    std::string keyword = query->keyword.getValue("");
    std::string orderType = query->orderType.getValue("");

    std::list<std::string> statusList;
    if (query->statusList) {
        for (const auto& status : *query->statusList) {
            statusList.push_back(status.getValue(""));
        }
    }

    std::string doctorName = payload ? payload->getPractitionerName() : "";

    OrderDAO1 dao;
    uint64_t total = 0;
    auto resultList = dao.queryOrderList(
        encounterId, keyword, orderType, statusList,
        query->pageIndex, query->pageSize, total, doctorName);

    // 枚举转换填充显示字段
    std::list<std::string> orderTypes, statuses, frequencies, routes;
    for (auto& item : resultList) {
        if (item->orderType) orderTypes.push_back(item->orderType.getValue(""));
        if (item->status) statuses.push_back(item->status.getValue(""));
        if (item->frequency) frequencies.push_back(item->frequency.getValue(""));
        if (item->routeCode) routes.push_back(item->routeCode.getValue(""));
    }

    std::map<std::string, std::string> typeNames, statusNames, freqNames, routeNames;
    if (m_enumDAO) {
        typeNames = m_enumDAO->getEnumNamesMap("ORDER_TYPE", orderTypes);
        statusNames = m_enumDAO->getEnumNamesMap("ORDER_STATUS", statuses);
        freqNames = m_enumDAO->getEnumNamesMap("FREQUENCY", frequencies);
        routeNames = m_enumDAO->getEnumNamesMap("ROUTE_CODE", routes);
    }

    for (auto& item : resultList) {
        std::string orderTypeVal = item->orderType.getValue("");
        std::string statusVal = item->status.getValue("");
        std::string freqVal = item->frequency.getValue("");
        std::string routeVal = item->routeCode.getValue("");

        auto itType = typeNames.find(orderTypeVal);
        item->orderTypeDisplay = oatpp::String(itType != typeNames.end() ? itType->second : orderTypeVal);
        auto itStatus = statusNames.find(statusVal);
        item->statusDisplay = oatpp::String(itStatus != statusNames.end() ? itStatus->second : statusVal);
        auto itFreq = freqNames.find(freqVal);
        item->frequencyDisplay = oatpp::String(itFreq != freqNames.end() ? itFreq->second : freqVal);
        auto itRoute = routeNames.find(routeVal);
        item->routeDisplay = oatpp::String(itRoute != routeNames.end() ? itRoute->second : routeVal);

        if (item->categoryCode) {
            item->categoryName = oatpp::String(getEnumDisplay("MEDICATION_CATEGORY", item->categoryCode.getValue("")));
        }
    }

    pageDto->total = total;
    pageDto->calcPages();
    for (auto& item : resultList) {
        pageDto->addData(item);
    }
    return pageDto;
}

// ========== 新增单条医嘱 ==========
OrderDetailDTO1::Wrapper OrderService1::addOrder(
    const OrderAddDTO1::Wrapper& dto,
    const PayloadDTO* payload,
    std::string& errorMsg)
{
    auto ctx = buildContext(payload);
    if (!ctx.valid) {
        errorMsg = "User context is invalid, please login again";
        return nullptr;
    }
    OrderDAO1 dao;
    return addOrderInternal(dto, payload, ctx, dao, errorMsg);
}

// ========== 修改单条医嘱 ==========
OrderDetailDTO1::Wrapper OrderService1::modifyOrder(
    const OrderModifyDTO1::Wrapper& dto,
    const PayloadDTO* payload,
    std::string& errorMsg)
{
    auto ctx = buildContext(payload);
    if (!ctx.valid) {
        errorMsg = "User context is invalid, please login again";
        return nullptr;
    }

    std::string orderId = dto->orderId.getValue("");
    if (orderId.empty()) {
        errorMsg = "orderId is required";
        return nullptr;
    }

    // 允许 version 为 0（新增时初始值为 0）
    int clientVersion = dto->version ? dto->version.getValue(0) : -1;
    if (clientVersion < 0) {
        errorMsg = "version is required for optimistic lock";
        return nullptr;
    }

    OrderDAO1 dao;

    auto medOrder = dao.selectMedicationOrderById(orderId);
    if (medOrder) {
        if (medOrder->getStatusEnum() != "DRAFT") {
            errorMsg = "Order status is not DRAFT, modification not allowed";
            return nullptr;
        }
        if (medOrder->getRequesterId() != ctx.practitionerId) {
            errorMsg = "You can only modify orders created by yourself";
            return nullptr;
        }
        if (medOrder->getVersion() != clientVersion) {
            errorMsg = "Data has been modified by another user, please refresh and try again";
            return nullptr;
        }
        if (!updateMedicationOrderInternal(dto, medOrder, ctx, errorMsg)) {
            return nullptr;
        }
        auto result = buildOrderDetailDTO(orderId, "medication", ctx.practitionerName, dao);
        if (!result) {
            errorMsg = "Order updated but failed to retrieve details";
            return nullptr;
        }
        return result;
    }

    auto svcOrder = dao.selectServiceOrderById(orderId);
    if (svcOrder) {
        if (svcOrder->getStatusEnum() != "DRAFT") {
            errorMsg = "Order status is not DRAFT, modification not allowed";
            return nullptr;
        }
        if (svcOrder->getRequesterId() != ctx.practitionerId) {
            errorMsg = "You can only modify orders created by yourself";
            return nullptr;
        }
        if (svcOrder->getVersion() != clientVersion) {
            errorMsg = "Data has been modified by another user, please refresh and try again";
            return nullptr;
        }
        if (!updateServiceOrderInternal(dto, svcOrder, ctx, errorMsg)) {
            return nullptr;
        }
        auto result = buildOrderDetailDTO(orderId, "service", ctx.practitionerName, dao);
        if (!result) {
            errorMsg = "Order updated but failed to retrieve details";
            return nullptr;
        }
        return result;
    }

    auto devOrder = dao.selectDeviceOrderById(orderId);
    if (devOrder) {
        if (devOrder->getStatusEnum() != "DRAFT") {
            errorMsg = "Order status is not DRAFT, modification not allowed";
            return nullptr;
        }
        if (devOrder->getRequesterId() != ctx.practitionerId) {
            errorMsg = "You can only modify orders created by yourself";
            return nullptr;
        }
        if (devOrder->getVersion() != clientVersion) {
            errorMsg = "Data has been modified by another user, please refresh and try again";
            return nullptr;
        }
        if (!updateDeviceOrderInternal(dto, devOrder, ctx, errorMsg)) {
            return nullptr;
        }
        auto result = buildOrderDetailDTO(orderId, "device", ctx.practitionerName, dao);
        if (!result) {
            errorMsg = "Order updated but failed to retrieve details";
            return nullptr;
        }
        return result;
    }

    errorMsg = "Order not found: " + orderId;
    return nullptr;
}

// ========== 批量新增医嘱 ==========
std::list<OrderDetailDTO1::Wrapper> OrderService1::batchAddOrder(
    const oatpp::List<OrderAddDTO1::Wrapper>& orderList,
    const PayloadDTO* payload,
    std::list<std::string>& errorList)
{
    std::list<OrderDetailDTO1::Wrapper> resultList;
    errorList.clear();

    if (!orderList || orderList->empty()) {
        errorList.push_back("Order list is empty");
        return resultList;
    }

    auto ctx = buildContext(payload);
    if (!ctx.valid) {
        errorList.push_back("User context is invalid, please login again");
        return resultList;
    }

    OrderDAO1 dao;
    SqlSession* session = dao.getSqlSession();
    session->beginTransaction();

    try {
        int index = 0;
        for (const auto& dto : *orderList) {
            index++;
            std::string errorMsg;
            auto result = addOrderInternal(dto, payload, ctx, dao, errorMsg);
            if (result) {
                resultList.push_back(result);
            }
            else {
                errorList.push_back("Order #" + std::to_string(index) + ": " + errorMsg);
                session->rollbackTransaction();
                resultList.clear();
                return resultList;
            }
        }
        session->commitTransaction();
    }
    catch (const std::exception& e) {
        errorList.push_back(std::string("Transaction failed: ") + e.what());
        session->rollbackTransaction();
        resultList.clear();
    }
    return resultList;
}