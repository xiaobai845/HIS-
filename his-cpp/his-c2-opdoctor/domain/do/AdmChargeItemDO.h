#pragma once

#ifndef _ADM_CHARGE_ITEM_DO_H_
#define _ADM_CHARGE_ITEM_DO_H_

#include "../DoInclude.h"

class AdmChargeItemDO : public BaseDO
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
    MYSQL_SYNTHESIZE(string, generate_source_enum, Generate_source_enum);
    MYSQL_SYNTHESIZE(string, context_enum, Context_enum);
    MYSQL_SYNTHESIZE(string, bus_no, Bus_no);
    MYSQL_SYNTHESIZE(string, parent_id, Parent_id);
    MYSQL_SYNTHESIZE(string, prescription_no, Prescription_no);
    MYSQL_SYNTHESIZE(string, patient_id, Patient_id);
    MYSQL_SYNTHESIZE(string, encounter_id, Encounter_id);
    MYSQL_SYNTHESIZE(string, service_table, Service_table);
    MYSQL_SYNTHESIZE(string, service_id, Service_id);
    MYSQL_SYNTHESIZE(string, account_id, Account_id);
    MYSQL_SYNTHESIZE(string, definition_id, Definition_id);
    MYSQL_SYNTHESIZE(string, status_enum, Status_enum);
    MYSQL_SYNTHESIZE(double, total_price, Total_price);
    MYSQL_SYNTHESIZE(string, occurrence_time, Occurrence_time);
    MYSQL_SYNTHESIZE(string, performer_id, Performer_id);
    MYSQL_SYNTHESIZE(string, performing_org_id, Performing_org_id);
    MYSQL_SYNTHESIZE(string, requesting_org_id, Requesting_org_id);
    MYSQL_SYNTHESIZE(string, cost_org_id, Cost_org_id);
    MYSQL_SYNTHESIZE(double, quantity_value, Quantity_value);
    MYSQL_SYNTHESIZE(string, quantity_unit, Quantity_unit);
    MYSQL_SYNTHESIZE(double, unit_price, Unit_price);
    MYSQL_SYNTHESIZE(string, def_detail_id, Def_detail_id);
    MYSQL_SYNTHESIZE(double, base_amount, Base_amount);
    MYSQL_SYNTHESIZE(double, discount_amount, Discount_amount);
    MYSQL_SYNTHESIZE(double, surcharge_amount, Surcharge_amount);
    MYSQL_SYNTHESIZE(double, system_discount_price, System_discount_price);
    MYSQL_SYNTHESIZE(double, manual_adjusted_price, Manual_adjusted_price);
    MYSQL_SYNTHESIZE(string, override_reason_code, Override_reason_code);
    MYSQL_SYNTHESIZE(string, override_reason_text, Override_reason_text);
    MYSQL_SYNTHESIZE(string, enterer_id, Enterer_id);
    MYSQL_SYNTHESIZE(string, entered_date, Entered_date);
    MYSQL_SYNTHESIZE(string, product_table, Product_table);
    MYSQL_SYNTHESIZE(string, product_id, Product_id);
    MYSQL_SYNTHESIZE(string, procedure_id, Procedure_id);
    MYSQL_SYNTHESIZE(string, dispense_table, Dispense_table);
    MYSQL_SYNTHESIZE(string, dispense_id, Dispense_id);
    MYSQL_SYNTHESIZE(int, claim_state_enum, Claim_state_enum);
    MYSQL_SYNTHESIZE(int, print_count, Print_count);
    MYSQL_SYNTHESIZE(string, org_id, Org_id);
    MYSQL_SYNTHESIZE(string, refund_id, Refund_id);
    MYSQL_SYNTHESIZE(string, condition_id, Condition_id);
    MYSQL_SYNTHESIZE(string, encounter_diagnosis_id, Encounter_diagnosis_id);
    MYSQL_SYNTHESIZE(bool, tcm_flag, Tcm_flag);

public:
    AdmChargeItemDO() : BaseDO("adm_charge_item")
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
        MYSQL_ADD_FIELD("generate_source_enum", "s", generate_source_enum);
        MYSQL_ADD_FIELD("context_enum", "s", context_enum);
        MYSQL_ADD_FIELD("bus_no", "s", bus_no);
        MYSQL_ADD_FIELD("parent_id", "s", parent_id);
        MYSQL_ADD_FIELD("prescription_no", "s", prescription_no);
        MYSQL_ADD_FIELD("patient_id", "s", patient_id);
        MYSQL_ADD_FIELD("encounter_id", "s", encounter_id);
        MYSQL_ADD_FIELD("service_table", "s", service_table);
        MYSQL_ADD_FIELD("service_id", "s", service_id);
        MYSQL_ADD_FIELD("account_id", "s", account_id);
        MYSQL_ADD_FIELD("definition_id", "s", definition_id);
        MYSQL_ADD_FIELD("status_enum", "s", status_enum);
        MYSQL_ADD_FIELD("total_price", "d", total_price);
        MYSQL_ADD_FIELD("occurrence_time", "s", occurrence_time);
        MYSQL_ADD_FIELD("performer_id", "s", performer_id);
        MYSQL_ADD_FIELD("performing_org_id", "s", performing_org_id);
        MYSQL_ADD_FIELD("requesting_org_id", "s", requesting_org_id);
        MYSQL_ADD_FIELD("cost_org_id", "s", cost_org_id);
        MYSQL_ADD_FIELD("quantity_value", "d", quantity_value);
        MYSQL_ADD_FIELD("quantity_unit", "s", quantity_unit);
        MYSQL_ADD_FIELD("unit_price", "d", unit_price);
        MYSQL_ADD_FIELD("def_detail_id", "s", def_detail_id);
        MYSQL_ADD_FIELD("base_amount", "d", base_amount);
        MYSQL_ADD_FIELD("discount_amount", "d", discount_amount);
        MYSQL_ADD_FIELD("surcharge_amount", "d", surcharge_amount);
        MYSQL_ADD_FIELD("system_discount_price", "d", system_discount_price);
        MYSQL_ADD_FIELD("manual_adjusted_price", "d", manual_adjusted_price);
        MYSQL_ADD_FIELD("override_reason_code", "s", override_reason_code);
        MYSQL_ADD_FIELD("override_reason_text", "s", override_reason_text);
        MYSQL_ADD_FIELD("enterer_id", "s", enterer_id);
        MYSQL_ADD_FIELD("entered_date", "s", entered_date);
        MYSQL_ADD_FIELD("product_table", "s", product_table);
        MYSQL_ADD_FIELD("product_id", "s", product_id);
        MYSQL_ADD_FIELD("procedure_id", "s", procedure_id);
        MYSQL_ADD_FIELD("dispense_table", "s", dispense_table);
        MYSQL_ADD_FIELD("dispense_id", "s", dispense_id);
        MYSQL_ADD_FIELD("claim_state_enum", "i", claim_state_enum);
        MYSQL_ADD_FIELD("print_count", "i", print_count);
        MYSQL_ADD_FIELD("org_id", "s", org_id);
        MYSQL_ADD_FIELD("refund_id", "s", refund_id);
        MYSQL_ADD_FIELD("condition_id", "s", condition_id);
        MYSQL_ADD_FIELD("encounter_diagnosis_id", "s", encounter_diagnosis_id);
        MYSQL_ADD_FIELD("tcm_flag", "b", tcm_flag);
    }
};

typedef std::shared_ptr<AdmChargeItemDO> AdmChargeItemDOPtr;

#endif