/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/25
*/
#include "stdafx.h"
#include "Chinapres2Service.h"
#include "../../dao/chinapres2/MedicationDAO.h"  // 药品查询
#include <chrono>
#include <iomanip>
#include <sstream>
/*
// ========== 私有方法：DO → DTO 转换 ==========
oatpp::List<Chinapres2DetailDTO::Wrapper> Chinapres2Service::convertToDTOList(const std::list<PtrChinapres2ViewDO>& doList)
{
    auto dtoList = oatpp::List<Chinapres2DetailDTO::Wrapper>::createShared();

    for (auto& doItem : doList) {
        auto dto = Chinapres2DetailDTO::createShared();

        // 主表字段映射
        dto->id = doItem->getId();
        dto->usage = doItem->getMethodCode();
        dto->frequency = doItem->getRateCode();
        dto->days = doItem->getExecuteNum();
        dto->copies = (int)doItem->getChineseHerbsDoseQuantity();
        dto->decoction = doItem->getSufferingFlag();
        dto->diagnosis = doItem->getDosageInstruction();
        dto->remark = doItem->getRemark();

        // 视图扩展字段（如果 DTO 有这些字段，可以赋值）
        // dto->diagnosisName = doItem->getDiagnosisName();
        // dto->requesterName = doItem->getRequesterName();
        // dto->medicationNames = doItem->getMedicationNames();
        // dto->totalPrice = doItem->getTotalPrice();

        dtoList->push_back(dto);
    }

    return dtoList;
}

// ========== 查询历史处方 ==========
Chinapres2DetailPageDTO::Wrapper Chinapres2Service::listAll(const Chinapres2Query::Wrapper& query)
{
    // 1. 调用 DAO 查询数据
    auto doList = dao.selectWithPage(query);
    auto total = dao.count(query);

    // 2. DO → DTO 转换
    auto dtoList = convertToDTOList(doList);

    // 3. 组装分页结果
    auto pageDto = Chinapres2DetailPageDTO::createShared();
    pageDto->rows = dtoList;
    pageDto->total = total;
    pageDto->pageIndex = query->pageIndex ? query->pageIndex.getValue(1) : 1;
    pageDto->pageSize = query->pageSize ? query->pageSize.getValue(10) : 10;
    pageDto->pages = (total + pageDto->pageSize - 1) / pageDto->pageSize;

    return pageDto;
}
*/

// ========== 新增处方 ==========
// 辅助函数：获取当前时间字符串
static std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}



Chinapres2AddRespDTO::Wrapper Chinapres2Service::saveData(
    const Chinapres2AddDTO::Wrapper& dto,
    const PayloadDTO& payload)
{
    auto resp = Chinapres2AddRespDTO::createShared();

    // ========== 1. 基础校验 ==========
    if (!dto) {
        throw std::runtime_error("dto is null");
    }
    if (!dto->details || dto->details->empty()) {
        throw std::runtime_error("details list is null or empty");
    }

    // 就诊可编辑校验
    if (!dao.isEncounterEditable(dto->encounterId->c_str())) {
        throw std::runtime_error("Encounter does not exist or has been deleted");
    }

    // ========== 2. 生成主键 ==========
    auto now = std::chrono::system_clock::now();
    auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    std::string mainId = "PRES_" + std::to_string(ts);
    std::string busNo = "BUS_" + std::to_string(ts);
    std::string timeStr = getCurrentTime();

    // ========== 3. 构造主表 DO ==========
    Chinapres2MainDO mainDO;
    mainDO.setId(mainId);
    mainDO.setBusNo(busNo);
    mainDO.setPrescriptionNo("PRESNO_" + std::to_string(ts));
    mainDO.setStatusEnum("UNSIGNED");
    mainDO.setIsDeleted(0);

    // 硬编码测试数据（可根据 payload 替换）
    mainDO.setPatientId("325580322788872192");
    mainDO.setEncounterId("329874660147597312");
    mainDO.setRequesterId("308791351298756608");
    mainDO.setOrgId("322663105141149696");

    // 从 DTO 安全取值
    mainDO.setMethodCode(dto->usage ? dto->usage->c_str() : "");
    mainDO.setRateCode(dto->frequency ? dto->frequency->c_str() : "");
    mainDO.setExecuteNum(dto->days ? *dto->days : 0);
    mainDO.setChineseHerbsDoseQuantity(dto->copies ? (double)*dto->copies : 0.0);
    mainDO.setSufferingFlag(dto->decoction ? *dto->decoction : 0);
    mainDO.setEncounterDiagnosisId(dto->encounterDiagnosisId ? dto->encounterDiagnosisId->c_str() : "");
    mainDO.setConditionDefinitionId("");
    mainDO.setDosageInstruction("");
    mainDO.setRemark(dto->remark ? dto->remark->c_str() : "");
    mainDO.setCreatedAt(timeStr);
    mainDO.setStatusReason("");

    // ========== 4. 处理明细 ==========
    MedicationDAO medDao;
    double totalAmount = 0.0;
    double singleDoseTotal = 0.0;
    std::list<PtrChinapres2DetailDO> detailList;
    int sort = 0;

    for (auto& item : *(dto->details)) {
        if (!item) continue;

        // 药品有效性校验
        if (!item->medicineId || item->medicineId->empty()) {
            throw std::runtime_error("medicineId is required.");
        }
        auto med = medDao.selectById(item->medicineId->c_str());
        if (!med) {
            throw std::runtime_error("药品ID不存在: " + std::string(item->medicineId->c_str()));
        }

        // 单位合法性校验
        if (item->unit && !item->unit->empty() && !dao.isUnitValid(item->unit->c_str())) {
            throw std::runtime_error("单位不合法: " + std::string(item->unit->c_str()));
        }

        auto detail = std::make_shared<Chinapres2DetailDO>();
        detail->setId("DETAIL_" + std::to_string(ts) + "_" + std::to_string(sort));
        detail->setRequestId(mainId);
        detail->setMedicationId(item->medicineId->c_str());
        detail->setQuantity(item->quantity ? *item->quantity : 0.0);
        detail->setUnitCode(item->unit ? item->unit->c_str() : med->getUnitCode().c_str());
        detail->setDose(item->dose ? *item->dose : 0.0);
        detail->setDoseUnitCode(item->doseUnit ? item->doseUnit->c_str() : med->getUnitCode().c_str());
        detail->setSortNo(sort++);
        detail->setCreateTime(timeStr);

        double itemAmount = detail->getQuantity() * med->getPrice();
        totalAmount += itemAmount;
        singleDoseTotal += itemAmount;
        detailList.push_back(detail);
    }

    // ========== 5. 插入数据库 ==========
    if (!dao.insertMain(mainDO)) {
        throw std::runtime_error("保存主表失败");
    }
    if (!dao.insertDetailsPtr(detailList)) {
        throw std::runtime_error("保存明细失败");
    }

    // ========== 6. 组装响应 ==========
    resp->id = mainId;
    resp->prescriptionNo = mainDO.getPrescriptionNo();
    resp->status = mainDO.getStatusEnum();
    resp->version = (int64_t)0;
    resp->createdAt = timeStr;
    resp->herbCount = (int32_t)detailList.size();
    resp->singleDoseAmount = singleDoseTotal;
    resp->totalAmount = totalAmount * (dto->copies ? *dto->copies : 1);

    return resp;
}
// ========== 删除（软删除） ==========
bool Chinapres2Service::removeData(const std::string& id)
{
    if (id.empty()) {
        return false;
    }

    return dao.softDeleteById(id);
}

Chinapres2RemoveRespDTO::Wrapper Chinapres2Service::removeDataEnhanced(const std::string& id, const std::string& encounterId, int64_t version, const PayloadDTO& payload) {
    auto resp = Chinapres2RemoveRespDTO::createShared();
    if (id.empty() || encounterId.empty()) {
        throw std::runtime_error("id and encounterId are required");
    }
    std::string operatorId = payload.getPractitionerId();
    if (operatorId.empty()) {
        operatorId = "308791351298756608";  // 测试医生ID
    }
    std::string newVersion, updatedAt;
    bool success = dao.removeWithCondition(id, encounterId, version, operatorId, newVersion, updatedAt);
    if (!success) {
        // 检查具体原因：可调用 getPresenceStatus 获取状态并抛出具体错误
        std::string status;
        int64_t currentVersion;
        std::string currentEncounter;
        if (dao.getPresenceStatus(id, status, currentVersion, currentEncounter)) {
            if (currentEncounter != encounterId) {
                throw std::runtime_error("Encounter ID mismatch");
            }
            if (status != "UNSIGNED") {
                throw std::runtime_error("Prescription status is not UNSIGNED, cannot delete");
            }
            if (currentVersion != version) {
                throw std::runtime_error("Version mismatch, please refresh and retry");
            }
            // 如果已删除但未在 removeWithCondition 中处理，这里再判断
            // 但 removeWithCondition 已处理幂等，若返回 false 但已删除，我们已经处理了
        }
        else {
            throw std::runtime_error("Prescription not found");
        }
        throw std::runtime_error("Delete failed for unknown reason");
    }
    resp->id = id;
    resp->version = std::stoll(newVersion);
    resp->updatedAt = updatedAt;
    return resp;
}