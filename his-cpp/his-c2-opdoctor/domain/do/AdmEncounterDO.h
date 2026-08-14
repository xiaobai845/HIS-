#pragma once

#ifndef _ADM_ENCOUNTER_DO_H_
#define _ADM_ENCOUNTER_DO_H_

#include "../DoInclude.h"

class AdmEncounterDO : public BaseDO
{
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
    MYSQL_SYNTHESIZE(string, patient_id, Patient_id);
    MYSQL_SYNTHESIZE(string, group_id, Group_id);
    MYSQL_SYNTHESIZE(string, bus_no, Bus_no);
    MYSQL_SYNTHESIZE(string, status_enum, Status_enum);
    MYSQL_SYNTHESIZE(string, class_enum, Class_enum);
    MYSQL_SYNTHESIZE(string, yb_class_enum, Yb_class_enum);
    MYSQL_SYNTHESIZE(string, yb_class_text, Yb_class_text);
    MYSQL_SYNTHESIZE(string, class_json, Class_json);
    MYSQL_SYNTHESIZE(string, priority_enum, Priority_enum);
    MYSQL_SYNTHESIZE(string, type_enum, Type_enum);
    MYSQL_SYNTHESIZE(string, service_type_id, Service_type_id);
    MYSQL_SYNTHESIZE(string, subject_status_enum, Subject_status_enum);
    MYSQL_SYNTHESIZE(string, start_time, Start_time);
    MYSQL_SYNTHESIZE(string, end_time, End_time);
    MYSQL_SYNTHESIZE(string, organization_id, Organization_id);
    MYSQL_SYNTHESIZE(int, display_order, Display_order);
    MYSQL_SYNTHESIZE(string, first_enum, First_enum);
    MYSQL_SYNTHESIZE(string, admit_source_code, Admit_source_code);
    MYSQL_SYNTHESIZE(string, in_way_code, In_way_code);
    MYSQL_SYNTHESIZE(string, reception_time, Reception_time);
    MYSQL_SYNTHESIZE(string, registrar_id, Registrar_id);
    MYSQL_SYNTHESIZE(string, amb_encounter_id, Amb_encounter_id);
    MYSQL_SYNTHESIZE(string, out_way_code, Out_way_code);

public:
    AdmEncounterDO() : BaseDO("adm_encounter")
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
        MYSQL_ADD_FIELD("patient_id", "s", patient_id);
        MYSQL_ADD_FIELD("group_id", "s", group_id);
        MYSQL_ADD_FIELD("bus_no", "s", bus_no);
        MYSQL_ADD_FIELD("status_enum", "s", status_enum);
        MYSQL_ADD_FIELD("class_enum", "s", class_enum);
        MYSQL_ADD_FIELD("yb_class_enum", "s", yb_class_enum);
        MYSQL_ADD_FIELD("yb_class_text", "s", yb_class_text);
        MYSQL_ADD_FIELD("class_json", "s", class_json);
        MYSQL_ADD_FIELD("priority_enum", "s", priority_enum);
        MYSQL_ADD_FIELD("type_enum", "s", type_enum);
        MYSQL_ADD_FIELD("service_type_id", "s", service_type_id);
        MYSQL_ADD_FIELD("subject_status_enum", "s", subject_status_enum);
        MYSQL_ADD_FIELD("start_time", "s", start_time);
        MYSQL_ADD_FIELD("end_time", "s", end_time);
        MYSQL_ADD_FIELD("organization_id", "s", organization_id);
        MYSQL_ADD_FIELD("display_order", "i", display_order);
        MYSQL_ADD_FIELD("first_enum", "s", first_enum);
        MYSQL_ADD_FIELD("admit_source_code", "s", admit_source_code);
        MYSQL_ADD_FIELD("in_way_code", "s", in_way_code);
        MYSQL_ADD_FIELD("reception_time", "s", reception_time);
        MYSQL_ADD_FIELD("registrar_id", "s", registrar_id);
        MYSQL_ADD_FIELD("amb_encounter_id", "s", amb_encounter_id);
        MYSQL_ADD_FIELD("out_way_code", "s", out_way_code);
    }
};

typedef std::shared_ptr<AdmEncounterDO> AdmEncounterDOPtr;

#endif