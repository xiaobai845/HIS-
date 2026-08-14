
#pragma once
#ifndef _MEDICATION_DAO_
#define _MEDICATION_DAO_
#include "BaseDAO.h"
#include "../../domain/do/chinapres2/MedicationDO.h"

class MedicationDAO : public BaseDAO {
public:
    PtrMedicationDO selectById(const std::string& id);
};
#endif