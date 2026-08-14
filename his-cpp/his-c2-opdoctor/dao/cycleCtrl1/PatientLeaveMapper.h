#pragma once
#ifndef PATIENTLEAVEMAPPER_H_
#define PATIENTLEAVEMAPPER_H_

#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "Mapper.h"

class PatientLeaveMapper : public Mapper<PtrAdmEncounterDO>
{
public:
    PtrAdmEncounterDO mapper(ResultSet* resultSet) const override
    {
        PtrAdmEncounterDO encDO = std::make_shared<AdmEncounterDO>();
        encDO->setId(resultSet->getString("id"));
        encDO->setTenantId(resultSet->getString("tenant_id"));
        encDO->setStatusEnum(resultSet->getString("status_enum"));
        encDO->setIsDeleted(resultSet->getInt64("is_deleted"));
        return encDO;
    }
};

#endif // !PATIENTLEAVEMAPPER_H_