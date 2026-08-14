#include "stdafx.h"
#include "PatientQueueDAO.h"

std::list<PtrPatientQueueCombineDO> PatientQueueDAO::queryPatientQueue(
    const PatientQueueQuery::Wrapper& query,
    const std::string& tenantId,
    const std::string& practitionerId)
{
    std::string sql = R"(
                    SELECT
                    enc.id AS enc_id,
                    enc.tenant_id AS tenant_id,
                    pat.id AS patient_id,
                    pat.name AS patient_name,
                    pat.gender_enum,
                    pat.birth_date,
                    enc.bus_no,
                    enc.status_enum,
                    (DATE(enc.reception_time)) AS reception_time,
                    enc.service_type_id,
                    serv.name AS service_name,
                    acc.type_code
                    FROM adm_encounter enc
                    INNER JOIN adm_patient pat ON enc.patient_id = pat.id
                    INNER JOIN adm_encounter_location enc_loc ON enc.id = enc_loc.encounter_id
                    LEFT JOIN adm_encounter_participant part ON enc.id = part.encounter_id
                    LEFT JOIN adm_account acc ON enc.id = acc.encounter_id AND acc.default_flag = 1
                    LEFT JOIN adm_healthcare_service serv ON enc.service_type_id = serv.id
                    WHERE enc.is_deleted = 0
                    )";

    SqlParams params;

    // 可选的 tenantId / practitionerId：只有非空才加入过滤条件和参数
    if (!tenantId.empty())
    {
        sql += " AND enc.tenant_id = ? ";
        SQLPARAMS_PUSH(params, "s", std::string, tenantId);
    }

    if (!practitionerId.empty())
    {
        sql += " AND part.practitioner_id = ? ";
        SQLPARAMS_PUSH(params, "s", std::string, practitionerId);
    }

    // 日期是必须的（你说只传日期），把它加入条件
    sql += " AND DATE(enc.reception_time) = ? ";
    SQLPARAMS_PUSH(params, "s", std::string, query->date->c_str());

    // 患者姓名模糊查询
    if (query->patientName && !query->patientName->empty())
    {
        sql += " AND pat.name LIKE CONCAT('%', ?, '%') ";
        SQLPARAMS_PUSH(params, "s", std::string, query->patientName->c_str());
    }

    // allStatus=false 才进行状态筛选
    
        if (query->visitStatus && !query->visitStatus->empty())
        {
            sql += " AND enc.status_enum = ? ";
            SQLPARAMS_PUSH(params, "s", std::string, query->visitStatus->c_str());
        }
    
    PatientQueueMapper mapper;
    return sqlSession->executeQuery<PtrPatientQueueCombineDO>(sql, mapper, params);
}

