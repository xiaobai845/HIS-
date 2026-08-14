-- 可重复执行：先删后插
USE zo_his;

DELETE FROM adm_charge_item          WHERE id LIKE '9999%';
DELETE FROM adm_encounter_diagnosis  WHERE id LIKE '9999%';
DELETE FROM med_medication_request   WHERE id LIKE '9999%';
DELETE FROM adm_encounter            WHERE id LIKE '9999%';

-- 1. 门诊就诊（PA0005=周女士）
INSERT INTO adm_encounter (id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version,
  patient_id, bus_no, status_enum, class_enum, organization_id, start_time)
VALUES
('999900010000000001', 1, NOW(), NOW(), 1, 1, 0, 0,
 '326940849401761792', 'EN-TEST-001', 'arrived', 'AMB', '322663218269917184', NOW()),
('999900010000000002', 1, NOW(), NOW(), 1, 1, 0, 0,
 '326940849401761792', 'EN-TEST-002', 'arrived', 'AMB', '322663218269917184', NOW());

-- 2. 处方
INSERT INTO med_medication_request (id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version,
  bus_no, prescription_no, status_enum, category_enum, therapy_enum,
  medication_id, patient_id, encounter_id, requester_id, org_id,
  quantity, unit_code, method_code, rate_code, content_json, sort_number, generate_source_enum)
VALUES
('999900020000000001', 1, NOW(), NOW(), '308791351298756608', 1, 0, 0,
 'MR-TEST-001', 'CP-TEST-001', 'COMPLETED', 'WESTERN', 'TEMPORARY',
 '322997883812974592', '326940849401761792', '999900010000000001', '322963602326687744', '322663218269917184',
 2, '盒', 'PO', 'BID',
 '{"items":[{"name":"阿莫西林胶囊","spec":"0.25g*24","qty":2,"price":15.50},{"name":"布洛芬缓释胶囊","spec":"0.3g*20","qty":1,"price":22.00}]}',
 1, 'doctor-prescription'),
('999900020000000002', 1, NOW(), NOW(), '308791351298756608', 1, 0, 0,
 'MR-TEST-002', 'CP-TEST-002', 'COMPLETED', 'CHINESE', 'TEMPORARY',
 '322996998399594496', '326940849401761792', '999900010000000002', '322963602326687744', '322663218269917184',
 3, '瓶', 'PO', 'TID',
 '{"items":[{"name":"六味地黄丸","spec":"360丸","qty":3,"price":18.00}]}',
 2, 'doctor-prescription');

-- 3. 诊断
INSERT INTO adm_encounter_diagnosis (id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version,
  encounter_id, condition_id, primary_flag, `rank`, description, diag_type_code, condition_code)
VALUES
('999900030000000001', 1, NOW(), NOW(), '308791351298756608', '308791351298756608', 0, 0,
 '999900010000000001', '999900030000000001', 1, 1, '急性上呼吸道感染', '2', 11),
('999900030000000002', 1, NOW(), NOW(), '308791351298756608', '308791351298756608', 0, 0,
 '999900010000000002', '999900030000000002', 1, 1, '肾阴虚证', '2', 11);

-- 4. 收费项
INSERT INTO adm_charge_item (id, tenant_id, created_at, updated_at, created_by, updated_by, is_deleted, version,
  generate_source_enum, context_enum, bus_no, prescription_no, patient_id, encounter_id,
  service_table, service_id, definition_id, status_enum, total_price,
  quantity_value, quantity_unit, unit_price, performer_id, org_id)
VALUES
('999900040000000001', 1, NOW(), NOW(), 1, 1, 0, 0,
 'doctor-prescription', '1', 'CI-TEST-001', 'CP-TEST-001', '326940849401761792', '999900010000000001',
 'med_medication_request', '999900020000000001', '322957264586018817', 'SETTLED', 31.00,
 2, '盒', 15.50, '322963602326687744', '322663218269917184'),
('999900040000000002', 1, NOW(), NOW(), 1, 1, 0, 0,
 'doctor-prescription', '1', 'CI-TEST-002', 'CP-TEST-001', '326940849401761792', '999900010000000001',
 'med_medication_request', '999900020000000001', '322957296852799489', 'SETTLED', 22.00,
 1, '盒', 22.00, '322963602326687744', '322663218269917184'),
('999900040000000003', 1, NOW(), NOW(), 1, 1, 0, 0,
 'doctor-prescription', '2', 'CI-TEST-003', 'CP-TEST-002', '326940849401761792', '999900010000000002',
 'med_medication_request', '999900020000000002', '322957264586018817', 'SETTLED', 54.00,
 3, '瓶', 18.00, '322963602326687744', '322663218269917184'),
('999900040000000004', 1, NOW(), NOW(), 1, 1, 0, 0,
 'doctor-prescription', '1', 'CI-TEST-004', 'CP-TEST-001', '326940849401761792', '999900010000000001',
 'wkf_service_request', '999900050000000001', '323001764538224641', 'DRAFT', 6.00,
 1, '次', 6.00, '322963602326687744', '322663218269917184');
