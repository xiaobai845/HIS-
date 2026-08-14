#include "stdafx.h"
#include "OutpatientRecordDAO.h"
#include "OutpatientRecordMapper.h"

inline std::string OutpatientRecordDAO::queryConditionBuilder(const OutpatientRecordQuery::Wrapper& query, SqlParams& params)
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

inline uint64_t OutpatientRecordDAO::count(const OutpatientRecordQuery::Wrapper& query)
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

inline std::list<PtrOutpatientRecordViewDO> OutpatientRecordDAO::selectWithPage(const OutpatientRecordQuery::Wrapper& query)
{
    SqlParams params;

    // 联查：患者、主诊断、主诊医生（角色 ATTENDING_DOCTOR）、科室
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
        "NULL AS remark "   // 暂缺
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