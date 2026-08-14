#include "stdafx.h"
#include "MedicalAdviceService.h"
#include "dao/prescription2/MedicationRequestDAO.h"
#include "dao/prescription2/ServiceRequestDAO.h"
#include "SimpleDateTimeFormat.h"
#include "TransactionManager.h"
#include <set>

namespace
{
// 医嘱记录签发前必须具备的状态
const std::string MEDICAL_ADVICE_DRAFT_STATUS = "DRAFT";
// 签发成功后设置的状态
const std::string MEDICAL_ADVICE_ACTIVE_STATUS = "ACTIVE";
// 撤回成功后设置的状态
const std::string MEDICAL_ADVICE_CANCELLED_STATUS = "CANCELLED";
// 检查同一医嘱组的所有记录是否被一起选中
bool containsWholeGroup(MedicationRequestDAO& dao, const std::string& encounterId,
    const std::string& groupId,
    const std::set<std::string>& selectedIds,
    std::set<std::string>& checkedGroupIds)
{
    // 空医嘱组标识表示该医嘱记录独立存在
    if (groupId.empty() || !checkedGroupIds.insert(groupId).second)
    {
        return true;
    }

    const auto groupMemberIds = dao.selectIdsByGroupForUpdate(encounterId, groupId);
    if (groupMemberIds.empty())
    {
        return false;
    }

    for (const auto& memberId : groupMemberIds)
    {
        if (selectedIds.find(memberId) == selectedIds.end())
        {
            return false;
        }
    }
    return true;
}

}

std::list<std::string> MedicalAdviceService::normalizeAdviceIds(
    const oatpp::List<oatpp::String>& adviceIds) const
{
    std::list<std::string> ids;
    std::set<std::string> uniqueIds;
    if (!adviceIds)
    {
        return ids;
    }

    for (const auto& adviceId : *adviceIds)
    {
        const std::string id = adviceId.getValue("");
        if (!id.empty() && uniqueIds.insert(id).second)
        {
            ids.emplace_back(id);
        }
    }
    return ids;
}

std::list<std::string> MedicalAdviceService::signMedicalAdvice(
    const SignMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload)
{
    if (!dto)
    {
        return {};
    }

    const std::string encounterId = dto->encounterId.getValue("");
    const int expectedVersion = dto->version.getValue(-1);
    const auto ids = normalizeAdviceIds(dto->adviceIds);
    if (encounterId.empty() || expectedVersion < 0 || ids.empty())
    {
        return {};
    }

    // 使用集合高效校验完整的医嘱组
    const std::set<std::string> selectedIds(ids.begin(), ids.end());
    MedicationRequestDAO dao;
    TransactionManager transaction(&dao);
    const std::string currentTime = SimpleDateTimeFormat::format();
    std::set<std::string> checkedGroupIds;
    std::list<std::string> signedIds;
    try
    {
        for (const auto& id : ids)
        {
            // 校验并变更状态前先锁定当前记录
            auto medicalAdvice = dao.selectByIdForUpdate(id, encounterId);
            if (!medicalAdvice ||
                medicalAdvice->getStatusEnum() != MEDICAL_ADVICE_DRAFT_STATUS ||
                medicalAdvice->getVersion() != expectedVersion ||
                !containsWholeGroup(dao, encounterId, medicalAdvice->getGroupId(),
                    selectedIds, checkedGroupIds))
            {
                transaction.rollback();
                return {};
            }

            // 构建更新数据，不修改签发范围之外的字段
            MedicationRequestDO updateData;
            updateData.setId(id);
            updateData.setEncounterId(encounterId);
            updateData.setVersion(medicalAdvice->getVersion() + 1);
            updateData.setStatusEnum(MEDICAL_ADVICE_ACTIVE_STATUS);
            updateData.setStatusChangedTime(currentTime);
            updateData.setPerformerCheckId(payload.getId());
            updateData.setCheckTime(currentTime);
            updateData.setUpdatedBy(payload.getUsername());
            updateData.setUpdatedAt(currentTime);
            if (dao.updateStatus(updateData, MEDICAL_ADVICE_DRAFT_STATUS,
                medicalAdvice->getVersion(), true) != 1)
            {
                transaction.rollback();
                return {};
            }
            signedIds.emplace_back(id);
        }
    }
    catch (...)
    {
        transaction.rollback();
        return {};
    }

    transaction.commit();
    return signedIds;
}

std::list<std::string> MedicalAdviceService::withdrawMedicalAdvice(
    const WithdrawMedicalAdviceDTO::Wrapper& dto, const PayloadDTO& payload)
{
    if (!dto)
    {
        return {};
    }

    const std::string encounterId = dto->encounterId.getValue("");
    const int expectedVersion = dto->version.getValue(-1);
    const auto ids = normalizeAdviceIds(dto->adviceIds);
    if (encounterId.empty() || expectedVersion < 0 || ids.empty())
    {
        return {};
    }

    // 使用集合高效校验完整的医嘱组
    const std::set<std::string> selectedIds(ids.begin(), ids.end());
    MedicationRequestDAO dao;
    TransactionManager transaction(&dao);
    const std::string currentTime = SimpleDateTimeFormat::format();
    std::set<std::string> checkedGroupIds;
    std::list<std::string> withdrawnIds;
    try
    {
        for (const auto& id : ids)
        {
            // 校验并变更状态前先锁定当前记录
            auto medicalAdvice = dao.selectByIdForUpdate(id, encounterId);
            if (!medicalAdvice ||
                medicalAdvice->getStatusEnum() != MEDICAL_ADVICE_ACTIVE_STATUS ||
                medicalAdvice->getVersion() != expectedVersion ||
                medicalAdvice->getExecuteNum() > 0 ||
                !containsWholeGroup(dao, encounterId, medicalAdvice->getGroupId(),
                    selectedIds, checkedGroupIds))
            {
                transaction.rollback();
                return {};
            }

            // 构建更新数据，不修改撤回范围之外的字段
            MedicationRequestDO updateData;
            updateData.setId(id);
            updateData.setEncounterId(encounterId);
            updateData.setVersion(medicalAdvice->getVersion() + 1);
            updateData.setStatusEnum(MEDICAL_ADVICE_CANCELLED_STATUS);
            updateData.setStatusChangedTime(currentTime);
            updateData.setUpdatedBy(payload.getUsername());
            updateData.setUpdatedAt(currentTime);
            if (dao.updateStatus(updateData, MEDICAL_ADVICE_ACTIVE_STATUS,
                medicalAdvice->getVersion(), false) != 1)
            {
                transaction.rollback();
                return {};
            }
            withdrawnIds.emplace_back(id);
        }
    }
    catch (...)
    {
        transaction.rollback();
        return {};
    }

    transaction.commit();
    return withdrawnIds;
}

std::string MedicalAdviceService::printApplicationForm(
    const PrintApplicationFormDTO::Wrapper& dto, const PayloadDTO& payload)
{
    if (!dto)
    {
        return "";
    }

    const std::string serviceRequestId = dto->serviceRequestId.getValue("");
    if (serviceRequestId.empty())
    {
        return "";
    }

    ServiceRequestDAO dao;
    TransactionManager transaction(&dao);
    try
    {
        // 锁定申请单，避免并发更新打印次数时发生数据丢失
        auto serviceRequest = dao.selectByIdForUpdate(serviceRequestId);
        if (!serviceRequest)
        {
            transaction.rollback();
            return "";
        }

        // 仅更新打印次数和审计字段
        ServiceRequestDO updateData;
        updateData.setId(serviceRequestId);
        updateData.setPrintCount(serviceRequest->getPrintCount() + 1);
        updateData.setUpdatedBy(payload.getUsername());
        updateData.setUpdatedAt(SimpleDateTimeFormat::format());
        updateData.setVersion(serviceRequest->getVersion() + 1);
        if (dao.incrementPrintCount(updateData, serviceRequest->getVersion()) != 1)
        {
            transaction.rollback();
            return "";
        }
    }
    catch (...)
    {
        transaction.rollback();
        return "";
    }

    transaction.commit();
    return serviceRequestId;
}
