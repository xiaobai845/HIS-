#pragma once

#ifndef _ADM_INVOICE_DO_H_
#define _ADM_INVOICE_DO_H_

#include "../DoInclude.h"

class AdmInvoiceDO : public BaseDO
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
    MYSQL_SYNTHESIZE(string, reconciliation_id, Reconciliation_id);
    MYSQL_SYNTHESIZE(string, payment_id, Payment_id);
    MYSQL_SYNTHESIZE(string, bus_no, Bus_no);
    MYSQL_SYNTHESIZE(string, bill_no, Bill_no);
    MYSQL_SYNTHESIZE(string, type_code, Type_code);
    MYSQL_SYNTHESIZE(string, cancelled_reason, Cancelled_reason);
    MYSQL_SYNTHESIZE(string, charge_item_ids, Charge_item_ids);
    MYSQL_SYNTHESIZE(string, payment_terms, Payment_terms);
    MYSQL_SYNTHESIZE(double, amount, Amount);
    MYSQL_SYNTHESIZE(string, status_enum, Status_enum);
    MYSQL_SYNTHESIZE(string, issued_at, Issued_at);

public:
    AdmInvoiceDO() : BaseDO("adm_invoice")
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
        MYSQL_ADD_FIELD("reconciliation_id", "s", reconciliation_id);
        MYSQL_ADD_FIELD("payment_id", "s", payment_id);
        MYSQL_ADD_FIELD("bus_no", "s", bus_no);
        MYSQL_ADD_FIELD("bill_no", "s", bill_no);
        MYSQL_ADD_FIELD("type_code", "s", type_code);
        MYSQL_ADD_FIELD("cancelled_reason", "s", cancelled_reason);
        MYSQL_ADD_FIELD("charge_item_ids", "s", charge_item_ids);
        MYSQL_ADD_FIELD("payment_terms", "s", payment_terms);
        MYSQL_ADD_FIELD("amount", "d", amount);
        MYSQL_ADD_FIELD("status_enum", "s", status_enum);
        MYSQL_ADD_FIELD("issued_at", "s", issued_at);
    }
};

typedef std::shared_ptr<AdmInvoiceDO> AdmInvoiceDOPtr;

#endif