#pragma once
#ifndef _PRACTITIONER_DO_1_H_
#define _PRACTITIONER_DO_1_H_
#include "../DoInclude.h"

/**
 * 医务人员实体类
 * 对应表: adm_practitioner
 */
class PractitionerDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, nameJson, NameJson);
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);
    MYSQL_SYNTHESIZE(string, genderEnum, GenderEnum);
    MYSQL_SYNTHESIZE(string, birthDate, BirthDate);
    MYSQL_SYNTHESIZE(string, deceasedDate, DeceasedDate);
    MYSQL_SYNTHESIZE(string, phone, Phone);
    MYSQL_SYNTHESIZE(string, addressProvince, AddressProvince);
    MYSQL_SYNTHESIZE(string, addressCity, AddressCity);
    MYSQL_SYNTHESIZE(string, addressDistrict, AddressDistrict);
    MYSQL_SYNTHESIZE(string, addressStreet, AddressStreet);
    MYSQL_SYNTHESIZE(string, addressJson, AddressJson);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(int, activeFlag, ActiveFlag);
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, ybNo, YbNo);
    MYSQL_SYNTHESIZE(string, userId, UserId);
    MYSQL_SYNTHESIZE(string, orgId, OrgId);
    MYSQL_SYNTHESIZE(int, drProfttlCode, DrProfttlCode);
    MYSQL_SYNTHESIZE(string, pharPracCertNo, PharPracCertNo);
    MYSQL_SYNTHESIZE(string, prscDrCertCode, PrscDrCertCode);
    MYSQL_SYNTHESIZE(string, signature, Signature);
    MYSQL_SYNTHESIZE(string, kpdCode, KpdCode);
    MYSQL_SYNTHESIZE(string, posNo, PosNo);

public:
    PractitionerDO1() : BaseDO("adm_practitioner")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("name_json", "s", nameJson);
        MYSQL_ADD_FIELD("py_str", "s", pyStr);
        MYSQL_ADD_FIELD("wb_str", "s", wbStr);
        MYSQL_ADD_FIELD("gender_enum", "s", genderEnum);
        MYSQL_ADD_FIELD("birth_date", "s", birthDate);
        MYSQL_ADD_FIELD("deceased_date", "s", deceasedDate);
        MYSQL_ADD_FIELD("phone", "s", phone);
        MYSQL_ADD_FIELD("address_province", "s", addressProvince);
        MYSQL_ADD_FIELD("address_city", "s", addressCity);
        MYSQL_ADD_FIELD("address_district", "s", addressDistrict);
        MYSQL_ADD_FIELD("address_street", "s", addressStreet);
        MYSQL_ADD_FIELD("address_json", "s", addressJson);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("active_flag", "i", activeFlag);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("yb_no", "s", ybNo);
        MYSQL_ADD_FIELD("user_id", "s", userId);
        MYSQL_ADD_FIELD("org_id", "s", orgId);
        MYSQL_ADD_FIELD("dr_profttl_code", "i", drProfttlCode);
        MYSQL_ADD_FIELD("phar_prac_cert_no", "s", pharPracCertNo);
        MYSQL_ADD_FIELD("prsc_dr_cert_code", "s", prscDrCertCode);
        MYSQL_ADD_FIELD("signature", "s", signature);
        MYSQL_ADD_FIELD("kpd_code", "s", kpdCode);
        MYSQL_ADD_FIELD("pos_no", "s", posNo);
    }
};

typedef std::shared_ptr<PractitionerDO1> PtrPractitionerDO1;
#endif // !_PRACTITIONER_DO_1_H_