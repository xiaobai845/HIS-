#include "stdafx.h"
#include "MedicationDAO.h"
#include "MedicationMapper.h"

PtrMedicationDO MedicationDAO::selectById(const std::string& id) {

    std::string sql = "SELECT id, name, spec, unit_code, price FROM med_medication WHERE id = ?";
    auto result = sqlSession->executeQueryOne<PtrMedicationDO>(sql, PtrMedicationMapper(), "%s", id);

    return result;
}