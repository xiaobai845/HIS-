#pragma once
#ifndef _ENCOUNTER_MAPPER_1_H_
#define _ENCOUNTER_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/EncounterDO1.h"

/**
 * ¾ÍÕï±í×Ö¶ÎÆ¥ÅäÓ³Éä
 */
class EncounterMapper1 : public Mapper<EncounterDO1>
{
public:
    EncounterDO1 mapper(ResultSet* resultSet) const override
    {
        EncounterDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setCreatedAt(resultSet->getString("created_at"));
        data.setUpdatedAt(resultSet->getString("updated_at"));
        data.setCreatedBy(resultSet->getString("created_by"));
        data.setUpdatedBy(resultSet->getString("updated_by"));
        data.setIsDeleted(resultSet->getInt("is_deleted"));
        data.setVersion(resultSet->getInt("version"));
        data.setPatientId(resultSet->getString("patient_id"));
        data.setGroupId(resultSet->getString("group_id"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setClassEnum(resultSet->getString("class_enum"));
        data.setYbClassEnum(resultSet->getString("yb_class_enum"));
        data.setYbClassText(resultSet->getString("yb_class_text"));
        data.setClassJson(resultSet->getString("class_json"));
        data.setPriorityEnum(resultSet->getString("priority_enum"));
        data.setTypeEnum(resultSet->getString("type_enum"));
        data.setServiceTypeId(resultSet->getString("service_type_id"));
        data.setSubjectStatusEnum(resultSet->getString("subject_status_enum"));
        data.setStartTime(resultSet->getString("start_time"));
        data.setEndTime(resultSet->getString("end_time"));
        data.setOrganizationId(resultSet->getString("organization_id"));
        data.setDisplayOrder(resultSet->getInt("display_order"));
        data.setFirstEnum(resultSet->getString("first_enum"));
        data.setAdmitSourceCode(resultSet->getString("admit_source_code"));
        data.setInWayCode(resultSet->getString("in_way_code"));
        data.setReceptionTime(resultSet->getString("reception_time"));
        data.setRegistrarId(resultSet->getString("registrar_id"));
        data.setAmbEncounterId(resultSet->getString("amb_encounter_id"));
        data.setOutWayCode(resultSet->getString("out_way_code"));
        return data;
    }
};

/**
 * ¾ÍÕï±í×Ö¶ÎÆ¥ÅäÓ³Éä-ÖÇÄÜÖ¸Õë°æ±¾
 */
class PtrEncounterMapper1 : public Mapper<PtrEncounterDO1>
{
public:
    PtrEncounterDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<EncounterDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setCreatedAt(resultSet->getString("created_at"));
        data->setUpdatedAt(resultSet->getString("updated_at"));
        data->setCreatedBy(resultSet->getString("created_by"));
        data->setUpdatedBy(resultSet->getString("updated_by"));
        data->setIsDeleted(resultSet->getInt("is_deleted"));
        data->setVersion(resultSet->getInt("version"));
        data->setPatientId(resultSet->getString("patient_id"));
        data->setGroupId(resultSet->getString("group_id"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setClassEnum(resultSet->getString("class_enum"));
        data->setYbClassEnum(resultSet->getString("yb_class_enum"));
        data->setYbClassText(resultSet->getString("yb_class_text"));
        data->setClassJson(resultSet->getString("class_json"));
        data->setPriorityEnum(resultSet->getString("priority_enum"));
        data->setTypeEnum(resultSet->getString("type_enum"));
        data->setServiceTypeId(resultSet->getString("service_type_id"));
        data->setSubjectStatusEnum(resultSet->getString("subject_status_enum"));
        data->setStartTime(resultSet->getString("start_time"));
        data->setEndTime(resultSet->getString("end_time"));
        data->setOrganizationId(resultSet->getString("organization_id"));
        data->setDisplayOrder(resultSet->getInt("display_order"));
        data->setFirstEnum(resultSet->getString("first_enum"));
        data->setAdmitSourceCode(resultSet->getString("admit_source_code"));
        data->setInWayCode(resultSet->getString("in_way_code"));
        data->setReceptionTime(resultSet->getString("reception_time"));
        data->setRegistrarId(resultSet->getString("registrar_id"));
        data->setAmbEncounterId(resultSet->getString("amb_encounter_id"));
        data->setOutWayCode(resultSet->getString("out_way_code"));
        return data;
    }
};

#endif // !_ENCOUNTER_MAPPER_1_H_