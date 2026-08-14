#pragma once
#ifndef _OUTPATIENTRECORD_VIEW_DO_
#define _OUTPATIENTRECORD_VIEW_DO_

#include "OutpatientRecordMainDO.h"

/**
 * 视图 DO：继承主表，扩展联查的患者、诊断、医生、科室信息
 */
class OutpatientRecordViewDO : public OutpatientRecordMainDO
{
    // 患者姓名 (adm_patient.name)
    MYSQL_SYNTHESIZE(string, patientName, PatientName);
    // 性别 (adm_patient.gender_enum)
    MYSQL_SYNTHESIZE(string, gender, Gender);
    // 诊断描述 (主诊断 cln_condition.description)
    MYSQL_SYNTHESIZE(string, diagnosis, Diagnosis);
    // 医生姓名 (adm_practitioner.name)
    MYSQL_SYNTHESIZE(string, doctorName, DoctorName);
    // 科室名称 (adm_organization.name)
    MYSQL_SYNTHESIZE(string, deptName, DeptName);
    // 备注（暂缺，留空）
    MYSQL_SYNTHESIZE(string, remark, Remark);

public:
    OutpatientRecordViewDO() : OutpatientRecordMainDO() {}
};

typedef std::shared_ptr<OutpatientRecordViewDO> PtrOutpatientRecordViewDO;

#endif // !_OUTPATIENTRECORD_VIEW_DO_