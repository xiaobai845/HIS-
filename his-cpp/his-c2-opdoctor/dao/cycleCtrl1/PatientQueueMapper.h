#pragma once
#include "Mapper.h"
#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "domain/do/cycleCtrl1/AdmPatientDO.h"
#include "domain/do/cycleCtrl1/AdmHealthcareServiceDO.h"
#include "domain/do/cycleCtrl1/AdmAccountDO.h"

// 患者队列组合映射对象，多表JOIN时可以用于不同字段查询
class PatientQueueCombineDO
{
public:
    CC_SYNTHESIZE(PtrAdmEncounterDO, encounterDO, EncounterDO);
    CC_SYNTHESIZE(PtrAdmPatientDO, patientDO, PatientDO);
    CC_SYNTHESIZE(PtrAdmHealthcareServiceDO, serviceDO, ServiceDO);
    CC_SYNTHESIZE(PtrAdmAccountDO, accountDO, AccountDO);
public:
    PatientQueueCombineDO() = default;
};
typedef std::shared_ptr<PatientQueueCombineDO> PtrPatientQueueCombineDO;

class PatientQueueMapper : public Mapper<PtrPatientQueueCombineDO>
{
public:
    PtrPatientQueueCombineDO mapper(ResultSet* resultSet) const override
    {
        PtrPatientQueueCombineDO item = std::make_shared<PatientQueueCombineDO>();

        PtrAdmEncounterDO encDO = std::make_shared<AdmEncounterDO>();
        encDO->setId(resultSet->getString("enc_id"));
        encDO->setTenantId(resultSet->getString("tenant_id"));
        encDO->setPatientId(resultSet->getString("patient_id"));
        encDO->setBusNo(resultSet->getString("bus_no"));
        encDO->setStatusEnum(resultSet->getString("status_enum"));
        encDO->setReceptionTime(resultSet->getInt64("reception_time"));
        encDO->setServiceTypeId(resultSet->getString("service_type_id"));
        item->setEncounterDO(encDO);

        PtrAdmPatientDO patDO = std::make_shared<AdmPatientDO>();
        patDO->setId(resultSet->getString("patient_id"));
        patDO->setName(resultSet->getString("patient_name"));
        patDO->setGenderEnum(resultSet->getString("gender_enum"));
        patDO->setBirthDate(resultSet->getString("birth_date"));
        item->setPatientDO(patDO);

        PtrAdmHealthcareServiceDO servDO = std::make_shared<AdmHealthcareServiceDO>();
        servDO->setName(resultSet->getString("service_name"));
        item->setServiceDO(servDO);

        PtrAdmAccountDO accDO = std::make_shared<AdmAccountDO>();
        accDO->setTypeCode(resultSet->getString("type_code"));
        item->setAccountDO(accDO);

        return item;
    }
};