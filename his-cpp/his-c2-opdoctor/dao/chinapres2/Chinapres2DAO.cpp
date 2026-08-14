/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/25
*/
#include "stdafx.h"
#include "Chinapres2DAO.h"
#include "Chinapres2Mapper.h"
#include "Chinapres2DetailMapper.h"
#include <iomanip>
#include <ctime>

// 用于 getPresenceStatus 查询结果映射（仅包含查询的三个字段）
struct PresenceInfo {
    std::string status;
    int64_t version;
    std::string encounterId;
};

class PresenceInfoMapper : public Mapper<PresenceInfo> {
public:
    PresenceInfo mapper(ResultSet* resultSet) const override {
        PresenceInfo info;
        info.status = resultSet->getString("status_enum");
        info.version = resultSet->getInt64("version");
        info.encounterId = resultSet->getString("encounter_id");
        return info;
    }
};


// 用于查询删除状态的信息
struct DeletedInfo {
    int isDeleted;
    int64_t version;
    std::string deletedAt;
};

class DeletedInfoMapper : public Mapper<DeletedInfo> {
public:
    DeletedInfo mapper(ResultSet* resultSet) const override {
        DeletedInfo info;
        info.isDeleted = resultSet->getInt("is_deleted");
        info.version = resultSet->getInt64("version");
        info.deletedAt = resultSet->getString("deleted_at");
        return info;
    }
};



bool Chinapres2DAO::isEncounterEditable(const std::string& encounterId) {
    if (encounterId.empty()) return false;
    try {
        std::string sql = "SELECT COUNT(*) FROM adm_encounter WHERE id = ? AND is_deleted = 0";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        uint64_t count = sqlSession->executeQueryNumerical(sql, params);
        return count > 0;
    }
    catch (...) {
        return false;
    }
}

bool Chinapres2DAO::isUnitValid(const std::string& unitCode) {
    if (unitCode.empty()) return false;
    try {
        std::string sql = "SELECT COUNT(*) FROM ter_code_system WHERE name = ? AND status = 'ACTIVE'";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, unitCode);
        uint64_t count = sqlSession->executeQueryNumerical(sql, params);
        return count > 0;
    }
    catch (...) {
        return false;
    }
}
/*
// ========== 查询条件构建器 ==========
std::string Chinapres2DAO::queryConditionBuilder(const Chinapres2Query::Wrapper& query, SqlParams& params)
{
    std::stringstream sqlCondition;
    sqlCondition << " WHERE m.is_deleted = 0";

    if (query->preNum) {
        sqlCondition << " AND m.execute_num = ?";
        SQLPARAMS_PUSH(params, "i", int, query->preNum.getValue(0));
    }

    if (query->medicine && !query->medicine->empty()) {
        sqlCondition << " AND EXISTS (SELECT 1 FROM med_medication_request_detail d WHERE d.request_id = m.id AND d.medication_id LIKE CONCAT('%', ?, '%'))";
        SQLPARAMS_PUSH(params, "s", std::string, query->medicine.getValue(""));
    }

    return sqlCondition.str();
}

// ========== 统计总数 ==========
uint64_t Chinapres2DAO::count(const Chinapres2Query::Wrapper& query)
{
    SqlParams params;
    std::string sql = "SELECT COUNT(*) FROM med_medication_request m";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

// ========== 分页查询（联查） ==========
std::list<PtrChinapres2ViewDO> Chinapres2DAO::selectWithPage(const Chinapres2Query::Wrapper& query)
{
    SqlParams params;

    std::string sql =
        "SELECT "
        "m.id, "
        "m.bus_no, "
        "m.prescription_no, "
        "m.group_id, "
        "m.status_enum, "
        "m.is_deleted, "
        "m.patient_id, "
        "m.encounter_id, "
        "m.requester_id, "
        "m.org_id, "
        "m.method_code, "
        "m.rate_code, "
        "m.execute_num, "
        "m.chinese_herbs_dose_quantity, "
        "m.suffering_flag, "
        "m.encounter_diagnosis_id, "
        "m.condition_definition_id, "
        "m.dosage_instruction, "
        "m.remark, "
        "m.created_at, "
        "m.status_reason, "
        "c.description AS diagnosis_name, "
        "p.name AS requester_name, "
        "(SELECT GROUP_CONCAT(CONCAT(d.quantity, d.unit_code) SEPARATOR ', ') "
        "FROM med_medication_request_detail d WHERE d.request_id = m.id) AS medication_names, "
        "0 AS total_price "
        "FROM med_medication_request m "
        "LEFT JOIN adm_encounter_diagnosis ed ON m.encounter_diagnosis_id = ed.id "
        "LEFT JOIN cln_condition c ON ed.condition_id = c.id "
        "LEFT JOIN adm_practitioner p ON m.requester_id = p.id";

    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY m.created_at DESC, m.id DESC ";

    int pageIndex = query->pageIndex ? query->pageIndex.getValue(1) : 1;
    int pageSize = query->pageSize ? query->pageSize.getValue(10) : 10;
    sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

    return sqlSession->executeQuery<PtrChinapres2ViewDO>(sql, Chinapres2ViewMapper(), params);
}
*/
// ========== 根据 ID 查询主表 ==========
PtrChinapres2MainDO Chinapres2DAO::selectById(const std::string& id)
{
    std::string sql =
        "SELECT "
        "id, bus_no, prescription_no, group_id, status_enum, is_deleted, "
        "patient_id, encounter_id, requester_id, org_id, "
        "method_code, rate_code, execute_num, chinese_herbs_dose_quantity, "
        "suffering_flag, encounter_diagnosis_id, condition_definition_id, "
        "dosage_instruction, remark, created_at, status_reason "
        "FROM med_medication_request "
        "WHERE id = ? AND is_deleted = 0";
    return sqlSession->executeQueryOne<PtrChinapres2MainDO>(sql, PtrChinapres2Mapper(), "%s", id);
}

// ========== 根据主表 ID 查询明细列表 ==========
std::list<PtrChinapres2DetailDO> Chinapres2DAO::selectDetailsByRequestIdPtr(const std::string& requestId)
{
    std::string sql =
        "SELECT "
        "id, request_id, medication_id, quantity, unit_code, "
        "dose, dose_unit_code, sort_no, "
        "create_by, create_time, update_by, update_time "
        "FROM med_medication_request_detail "
        "WHERE request_id = ? "
        "ORDER BY sort_no ASC, id ASC";
    return sqlSession->executeQuery<PtrChinapres2DetailDO>(sql, PtrChinapres2DetailMapper(), "%s", requestId);
}

bool Chinapres2DAO::insertMain(const Chinapres2MainDO& data) {
    try {
        std::string sql =
            "INSERT INTO med_medication_request ("
            "id, bus_no, prescription_no, group_id, status_enum, is_deleted, "
            "patient_id, encounter_id, requester_id, org_id, "
            "method_code, rate_code, execute_num, chinese_herbs_dose_quantity, "
            "suffering_flag, encounter_diagnosis_id, condition_definition_id, "
            "dosage_instruction, remark, created_at, status_reason"
            ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

        // ===== 所有字段值均先从 data 中安全提取，再 push =====
        // 但对于可能为空的字段，给予默认值
        std::string idVal = data.getId();
        std::string busNoVal = data.getBusNo();
        std::string presNoVal = data.getPrescriptionNo();
        // groupId 直接从 data 获取可能崩溃，我们硬编码一个默认值
        std::string groupIdVal = "DEFAULT_GROUP";   // <-- 关键：直接硬编码
        std::string statusVal = data.getStatusEnum();
        int isDeletedVal = data.getIsDeleted();
        std::string patientIdVal = data.getPatientId();
        std::string encounterIdVal = data.getEncounterId();
        std::string requesterIdVal = data.getRequesterId();
        std::string orgIdVal = data.getOrgId();
        std::string methodCodeVal = data.getMethodCode();
        std::string rateCodeVal = data.getRateCode();
        int executeNumVal = data.getExecuteNum();
        double doseQuantityVal = data.getChineseHerbsDoseQuantity();
        int sufferingFlagVal = data.getSufferingFlag();
        std::string diagIdVal = data.getEncounterDiagnosisId();
        std::string conditionIdVal = data.getConditionDefinitionId();
        std::string dosageInstVal = data.getDosageInstruction();
        std::string remarkVal = data.getRemark();
        std::string createdAtVal = data.getCreatedAt();
        std::string statusReasonVal = data.getStatusReason();

        // 如果某些字段为空，也设为默认值，以防万一
        if (idVal.empty()) idVal = "DEFAULT_ID";
        if (busNoVal.empty()) busNoVal = "DEFAULT_BUS";
        if (presNoVal.empty()) presNoVal = "DEFAULT_PRES";
        if (statusVal.empty()) statusVal = "UNSIGNED";
        // groupId 已经硬编码，无需再检查
        if (patientIdVal.empty()) patientIdVal = "DEFAULT_PATIENT";
        if (encounterIdVal.empty()) encounterIdVal = "DEFAULT_ENCOUNTER";
        if (requesterIdVal.empty()) requesterIdVal = "DEFAULT_REQUESTER";
        if (orgIdVal.empty()) orgIdVal = "DEFAULT_ORG";
        if (methodCodeVal.empty()) methodCodeVal = "DEFAULT_METHOD";
        if (rateCodeVal.empty()) rateCodeVal = "DEFAULT_RATE";
        if (diagIdVal.empty()) diagIdVal = "DEFAULT_DIAG";
        if (conditionIdVal.empty()) conditionIdVal = "DEFAULT_COND";
        if (dosageInstVal.empty()) dosageInstVal = "";
        if (remarkVal.empty()) remarkVal = "";
        if (createdAtVal.empty()) createdAtVal = "2020-01-01 00:00:00";
        if (statusReasonVal.empty()) statusReasonVal = "";

        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, idVal);
        SQLPARAMS_PUSH(params, "s", std::string, busNoVal);
        SQLPARAMS_PUSH(params, "s", std::string, presNoVal);
        SQLPARAMS_PUSH(params, "s", std::string, groupIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, statusVal);
        SQLPARAMS_PUSH(params, "i", int, isDeletedVal);
        SQLPARAMS_PUSH(params, "s", std::string, patientIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, encounterIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, requesterIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, orgIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, methodCodeVal);
        SQLPARAMS_PUSH(params, "s", std::string, rateCodeVal);
        SQLPARAMS_PUSH(params, "i", int, executeNumVal);
        SQLPARAMS_PUSH(params, "d", double, doseQuantityVal);
        SQLPARAMS_PUSH(params, "i", int, sufferingFlagVal);
        SQLPARAMS_PUSH(params, "s", std::string, diagIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, conditionIdVal);
        SQLPARAMS_PUSH(params, "s", std::string, dosageInstVal);
        SQLPARAMS_PUSH(params, "s", std::string, remarkVal);
        SQLPARAMS_PUSH(params, "s", std::string, createdAtVal);
        SQLPARAMS_PUSH(params, "s", std::string, statusReasonVal);

        int affected = sqlSession->executeUpdate(sql, params);
        return affected > 0;
    }
    catch (...) {
        return false;
    }
}// ========== 批量插入明细表（参数化+异常捕获） ==========
bool Chinapres2DAO::insertDetailsPtr(const std::list<PtrChinapres2DetailDO>& details) {
    if (details.empty()) return true;
    try {
        for (auto& data : details) {
            std::string sql =
                "INSERT INTO med_medication_request_detail ("
                "id, request_id, medication_id, quantity, unit_code, dose, dose_unit_code, sort_no, created_at"
                ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

            SqlParams params;
            SQLPARAMS_PUSH(params, "s", std::string, data->getId());
            SQLPARAMS_PUSH(params, "s", std::string, data->getRequestId());
            SQLPARAMS_PUSH(params, "s", std::string, data->getMedicationId());
            SQLPARAMS_PUSH(params, "d", double, data->getQuantity());
            SQLPARAMS_PUSH(params, "s", std::string, data->getUnitCode());
            SQLPARAMS_PUSH(params, "d", double, data->getDose());
            SQLPARAMS_PUSH(params, "s", std::string, data->getDoseUnitCode());
            SQLPARAMS_PUSH(params, "i", int, data->getSortNo());
            SQLPARAMS_PUSH(params, "s", std::string, data->getCreateTime());

            int affected = sqlSession->executeUpdate(sql, params);
            if (affected <= 0) {
                std::cerr << "[insertDetailsPtr] Failed to insert detail id: " << data->getId()
                    << ", affected=" << affected << std::endl;
                return false;
            }
        }
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "[insertDetailsPtr] SQL Exception: " << e.what() << std::endl;
        return false;
    }
    catch (...) {
        std::cerr << "[insertDetailsPtr] Unknown exception occurred." << std::endl;
        return false;
    }
}

// ========== 更新主表 ==========
bool Chinapres2DAO::updateMain(const Chinapres2MainDO& data)
{
    std::string sql =
        "UPDATE med_medication_request SET "
        "bus_no = ?, "
        "prescription_no = ?, "
        "group_id = ?, "
        "status_enum = ?, "
        "is_deleted = ?, "
        "patient_id = ?, "
        "encounter_id = ?, "
        "requester_id = ?, "
        "org_id = ?, "
        "method_code = ?, "
        "rate_code = ?, "
        "execute_num = ?, "
        "chinese_herbs_dose_quantity = ?, "
        "suffering_flag = ?, "
        "encounter_diagnosis_id = ?, "
        "condition_definition_id = ?, "
        "dosage_instruction = ?, "
        "remark = ?, "
        "status_reason = ? "
        "WHERE id = ?";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, data.getBusNo());
    SQLPARAMS_PUSH(params, "s", std::string, data.getPrescriptionNo());
    SQLPARAMS_PUSH(params, "s", std::string, data.getGroupId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getStatusEnum());
    SQLPARAMS_PUSH(params, "i", int, data.getIsDeleted());
    SQLPARAMS_PUSH(params, "s", std::string, data.getPatientId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getEncounterId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getRequesterId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getOrgId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getMethodCode());
    SQLPARAMS_PUSH(params, "s", std::string, data.getRateCode());
    SQLPARAMS_PUSH(params, "i", int, data.getExecuteNum());
    SQLPARAMS_PUSH(params, "d", double, data.getChineseHerbsDoseQuantity());
    SQLPARAMS_PUSH(params, "i", int, data.getSufferingFlag());
    SQLPARAMS_PUSH(params, "s", std::string, data.getEncounterDiagnosisId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getConditionDefinitionId());
    SQLPARAMS_PUSH(params, "s", std::string, data.getDosageInstruction());
    SQLPARAMS_PUSH(params, "s", std::string, data.getRemark());
    SQLPARAMS_PUSH(params, "s", std::string, data.getStatusReason());
    SQLPARAMS_PUSH(params, "s", std::string, data.getId());

    return sqlSession->executeUpdate(sql, params) > 0;
}

// ========== 根据 ID 软删除（主表 + 明细表） ==========
bool Chinapres2DAO::softDeleteById(const std::string& id)
{
    std::string detailSql = "UPDATE med_medication_request_detail SET is_deleted = 1 WHERE request_id = ?";
    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id);
    sqlSession->executeUpdate(detailSql, params);

    std::string mainSql = "UPDATE med_medication_request SET is_deleted = 1 WHERE id = ?";
    SqlParams mainParams;
    SQLPARAMS_PUSH(mainParams, "s", std::string, id);
    return sqlSession->executeUpdate(mainSql, mainParams) > 0;
}

// ========== 批量软删除 ==========
bool Chinapres2DAO::softDeleteBatch(const std::list<std::string>& ids)
{
    if (ids.empty()) return true;

    std::string placeholders;
    SqlParams params;
    for (auto& id : ids) {
        if (!placeholders.empty()) placeholders += ", ";
        placeholders += "?";
        SQLPARAMS_PUSH(params, "s", std::string, id);
    }

    std::string detailSql = "UPDATE med_medication_request_detail SET is_deleted = 1 WHERE request_id IN (" + placeholders + ")";
    sqlSession->executeUpdate(detailSql, params);

    std::string mainSql = "UPDATE med_medication_request SET is_deleted = 1 WHERE id IN (" + placeholders + ")";
    return sqlSession->executeUpdate(mainSql, params) > 0;
}

static std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool Chinapres2DAO::getPresenceStatus(const std::string& id, std::string& status, int64_t& version, std::string& encounterId) {
    if (id.empty()) return false;
    try {
        std::string sql = "SELECT status_enum, version, encounter_id FROM med_medication_request WHERE id = ?";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, id);
        auto results = sqlSession->executeQuery<PresenceInfo>(sql, PresenceInfoMapper(), params);
        if (!results.empty()) {
            const auto& info = results.front();
            status = info.status;
            version = info.version;
            encounterId = info.encounterId;
            return true;
        }
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] getPresenceStatus: " << e.what() << std::endl;
        return false;
    }
    catch (...) {
        std::cerr << "[ERROR] getPresenceStatus unknown exception" << std::endl;
        return false;
    }
}



bool Chinapres2DAO::removeWithCondition(const std::string& id, const std::string& encounterId, int64_t version, const std::string& operatorId, std::string& newVersion, std::string& updatedAt) {
    // 1. 获取当前记录信息
    std::string status;
    int64_t currentVersion;
    std::string currentEncounter;
    if (!getPresenceStatus(id, status, currentVersion, currentEncounter)) {
        return false; // 不存在
    }

    // 2. 校验就诊
    if (currentEncounter != encounterId) {
        return false;
    }

    // 3. 幂等：如果已删除，视为成功
    try {
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, id);
        auto results = sqlSession->executeQuery<DeletedInfo>("SELECT is_deleted, version, deleted_at FROM med_medication_request WHERE id = ?", DeletedInfoMapper(), params);        if (!results.empty()) {
            const auto& info = results.front();
            if (info.isDeleted == 1) {
                newVersion = std::to_string(info.version);
                updatedAt = info.deletedAt.empty() ? getCurrentTime() : info.deletedAt;
                return true;
            }
        }
    }
    catch (...) {
        // 忽略异常，继续执行更新
    }

    // 4. 校验状态
    if (status != "UNSIGNED") {
        return false;
    }

    // 5. 校验版本
    if (currentVersion != version) {
        return false;
    }

    // 6. 执行软删除
    try {
        std::string now = getCurrentTime();
        std::string sql =
            "UPDATE med_medication_request SET is_deleted = 1, deleted_at = ?, deleted_by = ?, version = version + 1, updated_at = ? "
            "WHERE id = ? AND encounter_id = ? AND version = ? AND status_enum = 'UNSIGNED' AND is_deleted = 0";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, now);
        SQLPARAMS_PUSH(params, "s", std::string, operatorId);
        SQLPARAMS_PUSH(params, "s", std::string, now);
        SQLPARAMS_PUSH(params, "s", std::string, id);
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        SQLPARAMS_PUSH(params, "i", int64_t, version);
        int affected = sqlSession->executeUpdate(sql, params);
        if (affected > 0) {
            newVersion = std::to_string(version + 1);
            updatedAt = now;
            return true;
        }
        else {
            // 更新失败，检查是否已被其他操作删除
            auto results2 = sqlSession->executeQuery<DeletedInfo>("SELECT is_deleted, version, deleted_at FROM med_medication_request WHERE id = ?", DeletedInfoMapper(), "%s", id.c_str());
            if (!results2.empty()) {
                const auto& info = results2.front();
                if (info.isDeleted == 1) {
                    newVersion = std::to_string(info.version);
                    updatedAt = info.deletedAt.empty() ? getCurrentTime() : info.deletedAt;
                    return true;
                }
            }
            return false;
        }
    }
    catch (...) {
        return false;
    }
}