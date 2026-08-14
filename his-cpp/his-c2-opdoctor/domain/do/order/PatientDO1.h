#pragma once
#ifndef _PATIENT_DO_1_H_
#define _PATIENT_DO_1_H_
#include "../DoInclude.h"

/**
 * 患者实体类
 * 对应表: adm_patient
 */
class PatientDO1 : public BaseDO
{
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenantId, TenantId);
    MYSQL_SYNTHESIZE(string, busNo, BusNo);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, nameJson, NameJson);
    MYSQL_SYNTHESIZE(string, genderEnum, GenderEnum);
    MYSQL_SYNTHESIZE(string, birthDate, BirthDate);
    MYSQL_SYNTHESIZE(string, statusEnum, StatusEnum);
    MYSQL_SYNTHESIZE(int, activeFlag, ActiveFlag);
    MYSQL_SYNTHESIZE(int, tempFlag, TempFlag);
    MYSQL_SYNTHESIZE(string, idCard, IdCard);
    MYSQL_SYNTHESIZE(string, maritalStatusEnum, MaritalStatusEnum);
    MYSQL_SYNTHESIZE(string, prfsEnum, PrfsEnum);
    MYSQL_SYNTHESIZE(string, phone, Phone);
    MYSQL_SYNTHESIZE(string, address, Address);
    MYSQL_SYNTHESIZE(string, addressProvince, AddressProvince);
    MYSQL_SYNTHESIZE(string, addressCity, AddressCity);
    MYSQL_SYNTHESIZE(string, addressDistrict, AddressDistrict);
    MYSQL_SYNTHESIZE(string, addressStreet, AddressStreet);
    MYSQL_SYNTHESIZE(string, addressExtendJson, AddressExtendJson);
    MYSQL_SYNTHESIZE(string, nationalityCode, NationalityCode);
    MYSQL_SYNTHESIZE(string, pyStr, PyStr);
    MYSQL_SYNTHESIZE(string, wbStr, WbStr);
    MYSQL_SYNTHESIZE(int, bloodTypeAbo, BloodTypeAbo);
    MYSQL_SYNTHESIZE(int, bloodTypeRh, BloodTypeRh);
    MYSQL_SYNTHESIZE(string, workCompany, WorkCompany);
    MYSQL_SYNTHESIZE(string, nativePlace, NativePlace);
    MYSQL_SYNTHESIZE(string, countryCode, CountryCode);
    MYSQL_SYNTHESIZE(string, linkName, LinkName);
    MYSQL_SYNTHESIZE(int, linkRelationCode, LinkRelationCode);
    MYSQL_SYNTHESIZE(string, linkTelcom, LinkTelcom);
    MYSQL_SYNTHESIZE(string, linkJsons, LinkJsons);
    MYSQL_SYNTHESIZE(string, deceasedDate, DeceasedDate);
    MYSQL_SYNTHESIZE(string, deceasedReason, DeceasedReason);
    MYSQL_SYNTHESIZE(string, organizationId, OrganizationId);
    MYSQL_SYNTHESIZE(string, mergedTargetPatientId, MergedTargetPatientId);
    MYSQL_SYNTHESIZE(string, mergedAt, MergedAt);

public:
    PatientDO1() : BaseDO("adm_patient")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenantId);
        MYSQL_ADD_FIELD("bus_no", "s", busNo);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("name_json", "s", nameJson);
        MYSQL_ADD_FIELD("gender_enum", "s", genderEnum);
        MYSQL_ADD_FIELD("birth_date", "s", birthDate);
        MYSQL_ADD_FIELD("status_enum", "s", statusEnum);
        MYSQL_ADD_FIELD("active_flag", "i", activeFlag);
        MYSQL_ADD_FIELD("temp_flag", "i", tempFlag);
        MYSQL_ADD_FIELD("id_card", "s", idCard);
        MYSQL_ADD_FIELD("marital_status_enum", "s", maritalStatusEnum);
        MYSQL_ADD_FIELD("prfs_enum", "s", prfsEnum);
        MYSQL_ADD_FIELD("phone", "s", phone);
        MYSQL_ADD_FIELD("address", "s", address);
        MYSQL_ADD_FIELD("address_province", "s", addressProvince);
        MYSQL_ADD_FIELD("address_city", "s", addressCity);
        MYSQL_ADD_FIELD("address_district", "s", addressDistrict);
        MYSQL_ADD_FIELD("address_street", "s", addressStreet);
        MYSQL_ADD_FIELD("address_extend_json", "s", addressExtendJson);
        MYSQL_ADD_FIELD("nationality_code", "s", nationalityCode);
        MYSQL_ADD_FIELD("py_str", "s", pyStr);
        MYSQL_ADD_FIELD("wb_str", "s", wbStr);
        MYSQL_ADD_FIELD("blood_type_abo", "i", bloodTypeAbo);
        MYSQL_ADD_FIELD("blood_type_rh", "i", bloodTypeRh);
        MYSQL_ADD_FIELD("work_company", "s", workCompany);
        MYSQL_ADD_FIELD("native_place", "s", nativePlace);
        MYSQL_ADD_FIELD("country_code", "s", countryCode);
        MYSQL_ADD_FIELD("link_name", "s", linkName);
        MYSQL_ADD_FIELD("link_relation_code", "i", linkRelationCode);
        MYSQL_ADD_FIELD("link_telcom", "s", linkTelcom);
        MYSQL_ADD_FIELD("link_jsons", "s", linkJsons);
        MYSQL_ADD_FIELD("deceased_date", "s", deceasedDate);
        MYSQL_ADD_FIELD("deceased_reason", "s", deceasedReason);
        MYSQL_ADD_FIELD("organization_id", "s", organizationId);
        MYSQL_ADD_FIELD("merged_target_patient_id", "s", mergedTargetPatientId);
        MYSQL_ADD_FIELD("merged_at", "s", mergedAt);
    }
};

typedef std::shared_ptr<PatientDO1> PtrPatientDO1;
#endif // !_PATIENT_DO_1_H_