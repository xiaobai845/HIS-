/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/07/27

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
#include "historyOrderListDAO.h"
#include "historyOrderListMapper.h"

// Build query WHERE condition
std::string HistoryOrderListDAO::queryConditionBuilder(const HistoryOrderListQuery::Wrapper& query, SqlParams& params)
{
    std::stringstream sqlCondition;
    sqlCondition << " WHERE e.is_deleted = 0 AND e.patient_id = ?";
    SQLPARAMS_PUSH(params, "s", std::string, query->patientId.getValue(""));

    if (query->visitType && !query->visitType->empty()) {
        sqlCondition << " AND e.class_enum = ?";
        SQLPARAMS_PUSH(params, "s", std::string, query->visitType.getValue(""));
    }

    if (query->keyword && !query->keyword->empty()) {
        sqlCondition << " AND ("
            << "EXISTS (SELECT 1 FROM adm_encounter_diagnosis ed "
            << "LEFT JOIN cln_condition c ON ed.condition_id = c.id "
            << "WHERE ed.encounter_id = e.id AND ed.primary_flag = 1 "
            << "AND c.description LIKE CONCAT('%', ?, '%')) "
            << "OR EXISTS (SELECT 1 FROM adm_encounter_participant ep "
            << "LEFT JOIN adm_practitioner p ON ep.practitioner_id = p.id "
            << "WHERE ep.encounter_id = e.id AND ep.role_code = 'primary' "
            << "AND p.name LIKE CONCAT('%', ?, '%'))"
            << ")";
        SQLPARAMS_PUSH(params, "s", std::string, query->keyword.getValue(""));
        SQLPARAMS_PUSH(params, "s", std::string, query->keyword.getValue(""));
    }

    return sqlCondition.str();
}

uint64_t HistoryOrderListDAO::count(const HistoryOrderListQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = "SELECT COUNT(*) FROM adm_encounter e";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrHistoryOrderListDO> HistoryOrderListDAO::selectWithPage(const HistoryOrderListQuery::Wrapper& query)
{
    SqlParams params;

    std::string sql =
        "SELECT "
        "e.id AS visit_id, "
        "DATE_FORMAT(COALESCE(e.start_time, e.created_at), '%Y-%m-%d %H:%i') AS visit_time, "
        "e.class_enum AS visit_type, "
        "c.description AS main_diagnosis, "
        "p.name AS doctor_name, "
        "COALESCE(drug.cnt, 0) AS drug_count, "
        "COALESCE(exam.cnt, 0) AS exam_count, "
        "COALESCE(material.cnt, 0) AS material_count "
        "FROM adm_encounter e "
        "LEFT JOIN adm_encounter_diagnosis ed ON e.id = ed.encounter_id AND ed.primary_flag = 1 "
        "LEFT JOIN cln_condition c ON ed.condition_id = c.id "
        "LEFT JOIN adm_encounter_participant ep ON e.id = ep.encounter_id AND ep.role_code = 'primary' "
        "LEFT JOIN adm_practitioner p ON ep.practitioner_id = p.id "
        "LEFT JOIN (SELECT encounter_id, COUNT(*) AS cnt FROM med_medication_request WHERE is_deleted = 0 GROUP BY encounter_id) drug ON e.id = drug.encounter_id "
        "LEFT JOIN (SELECT encounter_id, COUNT(*) AS cnt FROM wkf_service_request WHERE is_deleted = 0 GROUP BY encounter_id) exam ON e.id = exam.encounter_id "
        "LEFT JOIN (SELECT encounter_id, COUNT(*) AS cnt FROM wkf_device_request WHERE is_deleted = 0 GROUP BY encounter_id) material ON e.id = material.encounter_id";

    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY COALESCE(e.start_time, e.created_at) DESC, e.id DESC ";

    uint64_t pageIndex = static_cast<uint64_t>(query->pageIndex.getValue(1));
    uint64_t pageSize = static_cast<uint64_t>(query->pageSize.getValue(10));
    uint64_t offset = (pageIndex > 0 ? pageIndex - 1 : 0) * pageSize;
    sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(pageSize);

    return sqlSession->executeQuery<PtrHistoryOrderListDO>(sql, PtrHistoryOrderListMapper(), params);
}
