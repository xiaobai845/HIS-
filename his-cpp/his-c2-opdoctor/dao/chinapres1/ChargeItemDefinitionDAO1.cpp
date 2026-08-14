#include "ChargeItemDefinitionDAO1.h"
#include "ChargeItemDefinitionMapper1.h"

PtrChargeItemDefinitionDO ChargeItemDefinitionDAO1::selectByInstanceId(const string& instanceId)
{
	string sql = "SELECT id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version, instance_table, instance_id, charge_name, status_enum, org_id, type_code, price_type_code, price_value, lot_no, priority, yb_type FROM adm_charge_item_definition WHERE instance_id = ? AND status_enum = 'ACTIVE' LIMIT 1";
	return sqlSession->executeQueryOne<PtrChargeItemDefinitionDO>(sql, ChargeItemDefinitionMapper1(), "%s", instanceId);
}