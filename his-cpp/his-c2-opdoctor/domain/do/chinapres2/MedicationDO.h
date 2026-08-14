#pragma once
#ifndef _MEDICATION_DO_
#define _MEDICATION_DO_
#include "../DoInclude.h"

class MedicationDO : public BaseDO {
    MYSQL_SYNTHESIZE(string, id, Id);
    MYSQL_SYNTHESIZE(string, name, Name);
    MYSQL_SYNTHESIZE(string, spec, Spec);
    MYSQL_SYNTHESIZE(string, unitCode, UnitCode);
    MYSQL_SYNTHESIZE(double, price, Price);

public:
    MedicationDO() : BaseDO("med_medication") {
        MYSQL_ADD_FIELD_PK("id", "s", id);
        MYSQL_ADD_FIELD("name", "s", name);
        MYSQL_ADD_FIELD_NULLABLE("spec", "s", spec, false);
        MYSQL_ADD_FIELD_NULLABLE("unit_code", "s", unitCode, false);
        MYSQL_ADD_FIELD("price", "d", price);
    }
};

typedef std::shared_ptr<MedicationDO> PtrMedicationDO;
#endif