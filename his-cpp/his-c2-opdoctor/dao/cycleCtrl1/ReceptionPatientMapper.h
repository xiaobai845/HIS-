#pragma once
#include "Mapper.h"
#include "domain/do/cycleCtrl1/AdmEncounterDO.h"
#include "domain/do/cycleCtrl1/AdmPatientDO.h"
#include "domain/do/cycleCtrl1/AdmEncounterParticipantDO.h"
#include "domain/do/cycleCtrl1/AdmEncounterLocationDO.h"
#include "domain/do/cycleCtrl1/AdmHealthcareServiceDO.h"
#include "domain/do/cycleCtrl1/AdmAccountDO.h"
#include "domain/do/cycleCtrl1/ClnAllergyIntoleranceDO.h"
#include "domain/do/cycleCtrl1/AdmOrganizationDO.h"


class CurrentReceptionCombineDO
{
public:
    CC_SYNTHESIZE(PtrAdmEncounterDO, encounterDO, EncounterDO);
    CC_SYNTHESIZE(PtrAdmPatientDO, patientDO, PatientDO);
    CC_SYNTHESIZE(PtrAdmEncounterLocationDO, locationDO, LocationDO);
    CC_SYNTHESIZE(PtrAdmHealthcareServiceDO, serviceDO, ServiceDO);
    CC_SYNTHESIZE(PtrAdmAccountDO, accountDO, AccountDO);
    CC_SYNTHESIZE(PtrAdmOrganizationDO, orgDO, OrgDO);    
    CC_SYNTHESIZE(PtrClnAllergyIntoleranceDO, allergyDO, AllergyDO);

    CurrentReceptionCombineDO() = default;
};
typedef std::shared_ptr<CurrentReceptionCombineDO> PtrCurrentReceptionCombineDO;

class ReceptionPatientMapper : public Mapper<PtrCurrentReceptionCombineDO>
{
public:
    PtrCurrentReceptionCombineDO mapper(ResultSet* resultSet) const override
    {
        PtrCurrentReceptionCombineDO item = std::make_shared<CurrentReceptionCombineDO>();

        // 就诊主表
        PtrAdmEncounterDO encDO = std::make_shared<AdmEncounterDO>();
        encDO->setId(resultSet->getString("enc_id"));
        encDO->setTenantId(resultSet->getString("tenant_id"));
        encDO->setPatientId(resultSet->getString("patient_id"));
        encDO->setBusNo(resultSet->getString("bus_no"));
        encDO->setStatusEnum(resultSet->getString("status_enum"));
        encDO->setReceptionTime(resultSet->getInt64("reception_time"));
        encDO->setServiceTypeId(resultSet->getString("service_type_id"));
        item->setEncounterDO(encDO);

        // 患者表
        PtrAdmPatientDO patDO = std::make_shared<AdmPatientDO>();
        patDO->setId(resultSet->getString("patient_id"));
        patDO->setName(resultSet->getString("patient_name"));
        patDO->setGenderEnum(resultSet->getString("gender_enum"));
        patDO->setBirthDate(resultSet->getString("birth_date"));
        patDO->setPhone(resultSet->getString("phone_num"));
        item->setPatientDO(patDO);

        // 号源服务（便民号/专家号）
        PtrAdmHealthcareServiceDO serviceDO = std::make_shared<AdmHealthcareServiceDO>();
        serviceDO->setName(resultSet->getString("service_name"));
        item->setServiceDO(serviceDO);

        // 挂号科室
        PtrAdmOrganizationDO orgDO = std::make_shared<AdmOrganizationDO>();
        orgDO->setName(resultSet->getString("org_name"));
        item->setOrgDO(orgDO);

        // 费用账户（费用性质）
        PtrAdmAccountDO accountDO = std::make_shared<AdmAccountDO>();
        accountDO->setTypeCode(resultSet->getString("pay_type"));
        item->setAccountDO(accountDO);

        // 过敏史
        PtrClnAllergyIntoleranceDO allergyDO = std::make_shared<ClnAllergyIntoleranceDO>();
        allergyDO->setAllergyText(resultSet->getString("allergy_content"));
        item->setAllergyDO(allergyDO);

        return item;
    }
};