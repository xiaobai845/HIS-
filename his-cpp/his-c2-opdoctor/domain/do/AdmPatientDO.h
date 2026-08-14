#pragma once

#ifndef _ADM_PATIENT_DO_H_
#define _ADM_PATIENT_DO_H_
#include "../DoInclude.h"

/**
 * 患者主数据 DO
 * 对应表：adm_patient
 */
class AdmPatientDO : public BaseDO
{
    // ===== 按表字段顺序 =====
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, tenant_id, Tenant_id);
    MYSQL_SYNTHESIZE(string, created_at, Created_at);
    MYSQL_SYNTHESIZE(string, updated_at, Updated_at);
    MYSQL_SYNTHESIZE(string, created_by, Created_by);
    MYSQL_SYNTHESIZE(string, updated_by, Updated_by);
    MYSQL_SYNTHESIZE(bool, is_deleted, Is_deleted);
    MYSQL_SYNTHESIZE(string, deleted_at, Deleted_at);
    MYSQL_SYNTHESIZE(string, deleted_by, Deleted_by);
    MYSQL_SYNTHESIZE(int, version, Version);
    MYSQL_SYNTHESIZE(string, bus_no, Bus_no);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, name_json, Name_json);
    MYSQL_SYNTHESIZE(string, gender_enum, Gender_enum);
    MYSQL_SYNTHESIZE(string, birth_date, Birth_date);
    MYSQL_SYNTHESIZE(string, status_enum, Status_enum);
    MYSQL_SYNTHESIZE(bool, active_flag, Active_flag);
    MYSQL_SYNTHESIZE(bool, temp_flag, Temp_flag);
    MYSQL_SYNTHESIZE(string, id_card, Id_card);
    MYSQL_SYNTHESIZE(string, marital_status_enum, Marital_status_enum);
    MYSQL_SYNTHESIZE(string, prfs_enum, Prfs_enum);
    MYSQL_SYNTHESIZE(string, phone, Phone);
    MYSQL_SYNTHESIZE(string, address, Address);
    MYSQL_SYNTHESIZE(string, address_province, Address_province);
    MYSQL_SYNTHESIZE(string, address_city, Address_city);
    MYSQL_SYNTHESIZE(string, address_district, Address_district);
    MYSQL_SYNTHESIZE(string, address_street, Address_street);
    MYSQL_SYNTHESIZE(string, address_extend_json, Address_extend_json);
    MYSQL_SYNTHESIZE(string, nationality_code, Nationality_code);
    MYSQL_SYNTHESIZE(string, py_str, Py_str);
    MYSQL_SYNTHESIZE(string, wb_str, Wb_str);
    MYSQL_SYNTHESIZE(string, blood_type_abo, Blood_type_abo);
    MYSQL_SYNTHESIZE(string, blood_type_rh, Blood_type_rh);
    MYSQL_SYNTHESIZE(string, work_company, Work_company);
    MYSQL_SYNTHESIZE(string, native_place, Native_place);
    MYSQL_SYNTHESIZE(string, country_code, Country_code);
    MYSQL_SYNTHESIZE(string, link_name, Link_name);
    MYSQL_SYNTHESIZE(string, link_relation_code, Link_relation_code);
    MYSQL_SYNTHESIZE(string, link_telcom, Link_telcom);
    MYSQL_SYNTHESIZE(string, link_jsons, Link_jsons);
    MYSQL_SYNTHESIZE(string, deceased_date, Deceased_date);
    MYSQL_SYNTHESIZE(string, deceased_reason, Deceased_reason);
    MYSQL_SYNTHESIZE(string, organization_id, Organization_id);
    MYSQL_SYNTHESIZE(string, merged_target_patient, Merged_target_patient);
    MYSQL_SYNTHESIZE(string, merged_at, Merged_at);

public:
    AdmPatientDO() : BaseDO("adm_patient")
    {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("tenant_id", "s", tenant_id);
        MYSQL_ADD_FIELD("created_at", "s", created_at);
        MYSQL_ADD_FIELD("updated_at", "s", updated_at);
        MYSQL_ADD_FIELD("created_by", "s", created_by);
        MYSQL_ADD_FIELD("updated_by", "s", updated_by);
        MYSQL_ADD_FIELD("is_deleted", "b", is_deleted);
        MYSQL_ADD_FIELD("deleted_at", "s", deleted_at);
        MYSQL_ADD_FIELD("deleted_by", "s", deleted_by);
        MYSQL_ADD_FIELD("version", "i", version);
        MYSQL_ADD_FIELD("bus_no", "s", bus_no);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD("name_json", "s", name_json);
        MYSQL_ADD_FIELD("gender_enum", "s", gender_enum);
        MYSQL_ADD_FIELD("birth_date", "s", birth_date);
        MYSQL_ADD_FIELD("status_enum", "s", status_enum);
        MYSQL_ADD_FIELD("active_flag", "b", active_flag);
        MYSQL_ADD_FIELD("temp_flag", "b", temp_flag);
        MYSQL_ADD_FIELD("id_card", "s", id_card);
        MYSQL_ADD_FIELD("marital_status_enum", "s", marital_status_enum);
        MYSQL_ADD_FIELD("prfs_enum", "s", prfs_enum);
        MYSQL_ADD_FIELD("phone", "s", phone);
        MYSQL_ADD_FIELD("address", "s", address);
        MYSQL_ADD_FIELD("address_province", "s", address_province);
        MYSQL_ADD_FIELD("address_city", "s", address_city);
        MYSQL_ADD_FIELD("address_district", "s", address_district);
        MYSQL_ADD_FIELD("address_street", "s", address_street);
        MYSQL_ADD_FIELD("address_extend_json", "s", address_extend_json);
        MYSQL_ADD_FIELD("nationality_cod e", "s", nationality_code);
        MYSQL_ADD_FIELD("py_str", "s", py_str );
        MYSQL_ADD_FIELD("wb_str", "s", wb_str);
        MYSQL_ADD_FIELD("blood_type_abo", "s", blood_type_abo);
        MYSQL_ADD_FIELD("blood_type_rh", "s", blood_type_rh);
        MYSQL_ADD_FIELD("work_company", "s", work_company);
        MYSQL_ADD_FIELD("native_place", "s", native_place);
        MYSQL_ADD_FIELD("country_code", "s", country_code);
        MYSQL_ADD_FIELD("link_name", "s", link_name);
        MYSQL_ADD_FIELD("link_relation_code", "s", link_relation_code);
        MYSQL_ADD_FIELD("link_telcom", "s", link_telcom);
        MYSQL_ADD_FIELD("link_jsons", "s", link_jsons);
        MYSQL_ADD_FIELD("deceased_date", "s", deceased_date);
        MYSQL_ADD_FIELD("deceased_reason", "s", deceased_reason);
        MYSQL_ADD_FIELD("organization_id", "s", organization_id);
        MYSQL_ADD_FIELD("merged_target_patient", "s", merged_target_patient);
        MYSQL_ADD_FIELD("merged_at", "s", merged_at);
    }
};

#endif

typedef std::shared_ptr<AdmPatientDO> adm_pDO;