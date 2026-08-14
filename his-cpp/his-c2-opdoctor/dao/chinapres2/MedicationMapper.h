#pragma once

#ifndef _MEDICATION_MAPPER_
#define _MEDICATION_MAPPER_
#include "Mapper.h"
#include "../../domain/do/chinapres2/MedicationDO.h"

class PtrMedicationMapper : public Mapper<PtrMedicationDO> {
public:
    PtrMedicationDO mapper(ResultSet* resultSet) const override {
        auto data = std::make_shared<MedicationDO>();
        data->setId(resultSet->getString("id"));
        data->setName(resultSet->getString("name"));
        data->setSpec(resultSet->getString("spec"));
        data->setUnitCode(resultSet->getString("unit_code"));
        data->setPrice(resultSet->getDouble("price"));
        return data;
    }
};
#endif