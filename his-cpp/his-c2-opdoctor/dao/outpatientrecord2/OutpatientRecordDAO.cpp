#include "stdafx.h"
#include "OutpatientRecordDAO.h"
#include "OutpatientRecordMapper.h"
#include "../../domain/do/outpatientrecord2/OutpatientRecordDetailDO.h"

// 用于 checkAccessPermission 查询就诊信息
struct EncounterPermissionInfo {
    std::string patientId;
    std::string organizationId;
    std::string practitionerId;  // 主诊医生ID
};

class EncounterPermissionMapper : public Mapper<EncounterPermissionInfo> {
public:
    EncounterPermissionInfo mapper(ResultSet* resultSet) const override {
        EncounterPermissionInfo info;
        info.patientId = resultSet->getString("patient_id");
        info.organizationId = resultSet->getString("organization_id");
        info.practitionerId = resultSet->getString("practitioner_id");
        return info;
    }
};

// 用于查询医生的科室
struct PractitionerDeptInfo {
    std::string organizationId;
};

class PractitionerDeptMapper : public Mapper<PractitionerDeptInfo> {
public:
    PractitionerDeptInfo mapper(ResultSet* resultSet) const override {
        PractitionerDeptInfo info;
        info.organizationId = resultSet->getString("organization_id");
        return info;
    }
};

// 用于 selectDetailByEncounterId 结果映射
struct DetailResult {
    std::string id;
    std::string encounterId;
    std::string content;
    // int64_t version;  // 注释或删除
    std::string updatedAt;
};

class DetailResultMapper : public Mapper<DetailResult> {
public:
    DetailResult mapper(ResultSet* resultSet) const override {
        DetailResult info;
        info.id = resultSet->getString("id");
        info.encounterId = resultSet->getString("encounter_id");
        info.content = resultSet->getString("content");
        // info.version = resultSet->getInt64("version");  // 注释或删除
        info.updatedAt = resultSet->getString("updated_at");
        return info;
    }
};

// 用于 getEncounterSummary 结果映射
struct SummaryResult {
    std::string patientName;
    std::string diagnosis;
    std::string doctorName;
    std::string deptName;
    std::string visitDate;
    std::string status;
};

class SummaryResultMapper : public Mapper<SummaryResult> {
public:
    SummaryResult mapper(ResultSet* resultSet) const override {
        SummaryResult info;
        info.patientName = resultSet->getString("patient_name");
        info.diagnosis = resultSet->getString("diagnosis");
        info.doctorName = resultSet->getString("doctor_name");
        info.deptName = resultSet->getString("dept_name");
        info.visitDate = resultSet->getString("visit_date");
        info.status = resultSet->getString("status");
        return info;
    }
};


std::string OutpatientRecordDAO::queryConditionBuilder(const OutpatientRecordQuery::Wrapper& query, SqlParams& params)
{
    std::stringstream sql;
    sql << " WHERE e.is_deleted = 0";

    if (query->patientName && !query->patientName->empty()) {
        sql << " AND p.name LIKE CONCAT('%', ?, '%')";
        SQLPARAMS_PUSH(params, "s", std::string, query->patientName.getValue(""));
    }
    if (query->startDate && !query->startDate->empty()) {
        sql << " AND DATE(e.start_time) >= ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->startDate.getValue(""));
    }
    if (query->endDate && !query->endDate->empty()) {
        sql << " AND DATE(e.start_time) <= ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->endDate.getValue(""));
    }
    if (query->diagnosis && !query->diagnosis->empty()) {
        sql << " AND c.description LIKE CONCAT('%', ?, '%')";
        SQLPARAMS_PUSH(params, "s", std::string, query->diagnosis.getValue(""));
    }
    return sql.str();
}

uint64_t OutpatientRecordDAO::count(const OutpatientRecordQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql =
        "SELECT COUNT(*) "
        "FROM adm_encounter e "
        "LEFT JOIN adm_patient p ON e.patient_id = p.id "
        "LEFT JOIN adm_encounter_diagnosis ed ON e.id = ed.encounter_id AND ed.primary_flag = 1 "
        "LEFT JOIN cln_condition c ON ed.condition_id = c.id";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

// ========== 关键实现：分页查询 ==========
std::list<PtrOutpatientRecordViewDO> OutpatientRecordDAO::selectWithPage(const OutpatientRecordQuery::Wrapper& query)
{
    SqlParams params;

    std::string sql =
        "SELECT "
        "e.id, "
        "e.patient_id, "
        "e.organization_id, "
        "e.start_time, "
        "e.created_at, "
        "e.status_enum, "
        "e.class_enum, "
        "e.bus_no, "
        "e.is_deleted, "
        "p.name AS patient_name, "
        "p.gender_enum AS gender, "
        "c.description AS diagnosis, "
        "pr.name AS doctor_name, "
        "org.name AS dept_name, "
        "NULL AS remark "
        "FROM adm_encounter e "
        "LEFT JOIN adm_patient p ON e.patient_id = p.id "
        "LEFT JOIN adm_encounter_diagnosis ed ON e.id = ed.encounter_id AND ed.primary_flag = 1 "
        "LEFT JOIN cln_condition c ON ed.condition_id = c.id "
        "LEFT JOIN adm_encounter_participant ep ON e.id = ep.encounter_id AND ep.role_code = 'ATTENDING_DOCTOR' AND ep.status_enum = 'ACTIVE' "
        "LEFT JOIN adm_practitioner pr ON ep.practitioner_id = pr.id "
        "LEFT JOIN adm_organization org ON e.organization_id = org.id";

    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY e.start_time DESC, e.created_at DESC ";

    int pageIndex = query->pageIndex ? query->pageIndex.getValue(1) : 1;
    int pageSize = query->pageSize ? query->pageSize.getValue(10) : 10;
    sql += " LIMIT " + std::to_string((pageIndex - 1) * pageSize) + "," + std::to_string(pageSize);

    return sqlSession->executeQuery<PtrOutpatientRecordViewDO>(sql, OutpatientRecordViewMapper(), params);
}

// ========== 实现 selectDetailByEncounterId ==========
PtrOutpatientRecordDetailDO OutpatientRecordDAO::selectDetailByEncounterId(const std::string& encounterId)
{
    if (encounterId.empty()) return nullptr;
    try {
        std::string sql = "SELECT id, encounter_id, content, updated_at FROM emr_document WHERE encounter_id = ?";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        auto results = sqlSession->executeQuery<DetailResult>(sql, DetailResultMapper(), params);
        if (!results.empty()) {
            const auto& info = results.front();
            auto detail = std::make_shared<OutpatientRecordDetailDO>();
            detail->setId(info.id);
            detail->setEncounterId(info.encounterId);
            detail->setContent(info.content);
            detail->setVersion(0);  // 设置默认值 0
            detail->setUpdatedAt(info.updatedAt);
            return detail;
        }
        return nullptr;
    }
    catch (...) {
        return nullptr;
    }
}
// ========== 实现 getEncounterSummary ==========
bool OutpatientRecordDAO::getEncounterSummary(const std::string& encounterId,
    std::string& patientName,
    std::string& diagnosis,
    std::string& doctorName,
    std::string& deptName,
    std::string& visitDate,
    std::string& status)
{
    if (encounterId.empty()) return false;
    try {
        std::string sql =
            "SELECT "
            "p.name AS patient_name, "
            "c.description AS diagnosis, "
            "pr.name AS doctor_name, "
            "org.name AS dept_name, "
            "e.start_time AS visit_date, "
            "e.status_enum AS status "
            "FROM adm_encounter e "
            "LEFT JOIN adm_patient p ON e.patient_id = p.id "
            "LEFT JOIN adm_encounter_diagnosis ed ON e.id = ed.encounter_id AND ed.primary_flag = 1 "
            "LEFT JOIN cln_condition c ON ed.condition_id = c.id "
            "LEFT JOIN adm_encounter_participant ep ON e.id = ep.encounter_id AND ep.role_code = 'ATTENDING_DOCTOR' AND ep.status_enum = 'ACTIVE' "
            "LEFT JOIN adm_practitioner pr ON ep.practitioner_id = pr.id "
            "LEFT JOIN adm_organization org ON e.organization_id = org.id "
            "WHERE e.id = ? AND e.is_deleted = 0";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        auto results = sqlSession->executeQuery<SummaryResult>(sql, SummaryResultMapper(), params);
        if (!results.empty()) {
            const auto& info = results.front();
            patientName = info.patientName;
            diagnosis = info.diagnosis;
            doctorName = info.doctorName;
            deptName = info.deptName;
            visitDate = info.visitDate;
            status = info.status;
            return true;
        }
        return false;
    }
    catch (...) {
        return false;
    }
}

bool OutpatientRecordDAO::checkAccessPermission(const std::string& encounterId, const std::string& practitionerId)
{
    if (encounterId.empty() || practitionerId.empty()) return false;
    try {
        std::string sql =
            "SELECT e.patient_id, e.organization_id, ep.practitioner_id "
            "FROM adm_encounter e "
            "LEFT JOIN adm_encounter_participant ep ON e.id = ep.encounter_id AND ep.role_code = 'ATTENDING_DOCTOR' AND ep.status_enum = 'ACTIVE' "
            "WHERE e.id = ? AND e.is_deleted = 0";
        SqlParams params;
        SQLPARAMS_PUSH(params, "s", std::string, encounterId);
        auto results = sqlSession->executeQuery<EncounterPermissionInfo>(sql, EncounterPermissionMapper(), params);

        if (results.empty()) {
            return false;
        }

        const auto& info = results.front();

        // 规则1：如果当前医生是该就诊的主诊医生，有权限
        if (info.practitionerId == practitionerId) {
            return true;
        }

        // 规则2：同一科室校验（由于 adm_practitioner 没有 organization_id，暂时禁用）
        // 如需启用，请先确认表结构
        // ... 已禁用 ...

        return false;
    }
    catch (...) {
        return false;
    }
}