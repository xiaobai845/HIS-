/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2022/12/03 11:01:02
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
#include "AdmissionService.h"
#include "BaseDAO.h"
#include "Mapper.h"
#include "domain/do/AdmEncounterDO.h"
#include "id/UuidFacade.h"
#include "SimpleDateTimeFormat.h"

namespace {
	struct ScalarStr { std::string val; };
	class ScalarStrMapper : public Mapper<ScalarStr>
	{
	public:
		ScalarStr mapper(ResultSet* rs) const override
		{
			ScalarStr s; s.val = rs->getString(1); return s;
		}
	};
}

std::string AdmissionService::applyAdmission(const Admission2Query::Wrapper& query, const std::string& patientId,
	const std::string& operatorId)
{
	BaseDAO dao;
	auto* ss = dao.getSqlSession();

	std::string pid = ss->executeQueryOne<ScalarStr>(
		"SELECT id FROM adm_patient WHERE bus_no = ? AND is_deleted = 0 LIMIT 1",
		ScalarStrMapper(), "%s", patientId).val;
	if (pid.empty()) return "";

	std::string wardName = query->admissionWard.getValue("");
	std::string deptName = query->admissionDepartment.getValue("");
	std::string orgId;
	if (!wardName.empty())
		orgId = ss->executeQueryOne<ScalarStr>(
			"SELECT id FROM adm_organization WHERE name = ? AND is_deleted = 0 LIMIT 1",
			ScalarStrMapper(), "%s", wardName).val;
	if (orgId.empty() && !deptName.empty())
		orgId = ss->executeQueryOne<ScalarStr>(
			"SELECT id FROM adm_organization WHERE name = ? AND is_deleted = 0 LIMIT 1",
			ScalarStrMapper(), "%s", deptName).val;

	std::string encId = ss->executeQueryOne<ScalarStr>(
		"SELECT id FROM adm_encounter "
		"WHERE patient_id = ? AND class_enum = 'AMB' AND status_enum = 'arrived' "
		"AND is_deleted = 0 ORDER BY start_time DESC LIMIT 1",
		ScalarStrMapper(), "%s", pid).val;

	std::string now = SimpleDateTimeFormat::format();
	UuidFacade uf;
	std::string newId;

	if (!encId.empty())
	{
		std::string sql =
			"UPDATE adm_encounter SET class_enum = ?, organization_id = ?, "
			"admit_source_code = ?, in_way_code = ?, priority_enum = ?, "
			"status_enum = 'arrived', updated_at = NOW() "
			"WHERE id = ? AND is_deleted = 0";
		int rows = ss->executeUpdate(sql,
			"%s%s%s%s%s%s", std::string("IMP"), orgId,
			query->admissionType.getValue(""), query->admissionMethod.getValue(""),
			query->priority.getValue(""), encId);
		if (rows <= 0) return "";
		newId = encId;
	}
	else
	{
		newId = uf.genUuid();
		AdmEncounterDO enc;
		enc.setId(newId);
		enc.setPatient_id(pid);
		enc.setClass_enum("IMP");
		enc.setStatus_enum("arrived");
		enc.setOrganization_id(orgId);
		enc.setAdmit_source_code(query->admissionType.getValue(""));
		enc.setIn_way_code(query->admissionMethod.getValue(""));
		enc.setPriority_enum(query->priority.getValue(""));
		enc.setStart_time(now);
		enc.setCreated_by(operatorId);
		if (dao.insert(enc) != 1) return "";
	}

	std::string diagnosis = query->admissionDiagnosis.getValue("");
	if (!diagnosis.empty())
	{
		std::string diagType = query->diagnosisType.getValue("WESTERN");
		std::string syndrome = query->diagnosisSyndrome.getValue("");
		std::string desc = query->diagnosisDesc.getValue("");
		if (desc.empty()) desc = diagnosis;

		std::string diagId = uf.genUuid();
		int tcmFlag = (diagType == "CHINESE") ? 1 : 0;
		std::string sql =
			"INSERT INTO adm_encounter_diagnosis "
			"(id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version, "
			"encounter_id, condition_id, primary_flag, `rank`, description, "
			"diag_type_code, condition_code, tcm_syndrome_group, tcm_flag) "
			"VALUES (?, '1', ?, ?, ?, 1, 0, 0, ?, ?, 1, 1, ?, ?, 11, ?, ?)";
		ss->executeUpdate(sql, "%s%s%s%s%s%s%s%s%s%i",
			diagId, now, now, operatorId, newId, diagId,
			desc, diagType, syndrome, tcmFlag);
	}

	return newId;
}
