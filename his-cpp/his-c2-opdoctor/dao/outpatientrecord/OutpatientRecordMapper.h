#pragma once
#ifndef _OUTPATIENTRECORD_MAPPER_
#define _OUTPATIENTRECORD_MAPPER_

#include "Mapper.h"
#include "../../domain/do/outpatientrecord/OutpatientRecordMainDO.h"
#include "../../domain/do/outpatientrecord/OutpatientRecordViewDO.h"

class OutpatientRecordViewMapper : public Mapper<PtrOutpatientRecordViewDO>
{
public:
    PtrOutpatientRecordViewDO mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<OutpatientRecordViewDO>();

        // 主表字段
        data->setId(resultSet->getString("id"));
        data->setPatientId(resultSet->getString("patient_id"));
        data->setOrganizationId(resultSet->getString("organization_id"));
        data->setStartTime(resultSet->getString("start_time"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setClassEnum(resultSet->getString("class_enum"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));

        // 扩展字段
        data->setPatientName(resultSet->getString("patient_name"));
        data->setGender(resultSet->getString("gender"));
        data->setDiagnosis(resultSet->getString("diagnosis"));
        data->setDoctorName(resultSet->getString("doctor_name"));
        data->setDeptName(resultSet->getString("dept_name"));
        data->setRemark(resultSet->getString("remark"));   // 可能为NULL

        return data;
    }
};

#endif // !_OUTPATIENTRECORD_MAPPER_