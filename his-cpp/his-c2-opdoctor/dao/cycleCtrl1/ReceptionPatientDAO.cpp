#include "stdafx.h"
#include "ReceptionPatientDAO.h"
#include <iostream>

PtrCurrentReceptionCombineDO ReceptionPatientDAO::queryReceptionPatient(
    const RecePatientQuery::Wrapper& query,
    const std::string& tenantId,
    const std::string& practitionerId)
{
    std::string sql = R"(
       SELECT
            e.id AS enc_id,
            e.tenant_id,
            e.bus_no,
            e.status_enum,
            e.class_enum,
            e.yb_class_text,
            UNIX_TIMESTAMP(e.reception_time) AS reception_time,

            p.id AS patient_id,
            p.name AS patient_name,
            p.gender_enum,
            p.birth_date,
            p.phone AS phone_num,

            org.name AS org_name,
            ai.description AS allergy_content,

            serv.name AS service_name,
            acc.type_code AS pay_type,
            e.service_type_id AS service_type_id

        FROM adm_encounter e
        INNER JOIN adm_patient p
            ON e.patient_id = p.id AND p.is_deleted = 0
        LEFT JOIN adm_encounter_location enc_loc
            ON e.id = enc_loc.encounter_id AND enc_loc.is_deleted = 0
        LEFT JOIN adm_organization org
            ON enc_loc.location_id = org.id AND org.is_deleted = 0
        LEFT JOIN adm_encounter_participant part
            ON e.id = part.encounter_id 
            AND part.is_deleted = 0
            AND part.practitioner_id = ?
        LEFT JOIN cln_allergy_intolerance ai
            ON ai.patient_id = p.id AND ai.is_deleted = 0
        LEFT JOIN adm_account acc
            ON e.id = acc.encounter_id AND acc.default_flag = 1
        LEFT JOIN adm_healthcare_service serv
            ON e.service_type_id = serv.id AND serv.is_deleted = 0

        WHERE e.is_deleted = 0
          AND e.tenant_id = ?
          AND DATE(e.reception_time) = ?
          AND e.status_enum = ?
        ORDER BY e.reception_time ASC;
    )";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, practitionerId);
    SQLPARAMS_PUSH(params, "s", std::string, tenantId);
    SQLPARAMS_PUSH(params, "s", std::string, query->date->c_str());
    SQLPARAMS_PUSH(params, "s", std::string, std::string("in-progress"));

    ReceptionPatientMapper mapper;

    auto result = sqlSession->executeQuery<PtrCurrentReceptionCombineDO>(sql, mapper, params);

    std::cout << "查询结果数量：" << result.size() << std::endl;
    return result.empty() ? nullptr : result.front();
}