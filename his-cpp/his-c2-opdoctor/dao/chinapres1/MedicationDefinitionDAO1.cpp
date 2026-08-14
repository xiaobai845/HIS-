#include "MedicationDefinitionDAO1.h"
#include "MedicationDefinitionMapper1.h"

PtrMedicationDefinitionDO MedicationDefinitionDAO1::selectById(const string& id)
{
	string sql = "SELECT id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version, bus_no, name, domain_enum, name_en, py_str, wb_str, category_code, merchandise_name, merchandise_py_str, merchandise_wb_str, purchase_unit_code, split_unit_code, dose_unit_code, package_unit_code, stock_unit_code, total_volume, dose, max_unit, usage_limit, method_code, rate_code, manufacturer_id, manufacturer_text, supply_id, active_flag, status_enum, org_id, rx_flag, skin_test_flag, inject_flag, antibiotic_flag, basic_flag, def_encounter_unit_code, def_inhospital_unit_code FROM med_medication_definition WHERE id = ?";
	return sqlSession->executeQueryOne<PtrMedicationDefinitionDO>(sql, MedicationDefinitionMapper1(), "%s", id);
}