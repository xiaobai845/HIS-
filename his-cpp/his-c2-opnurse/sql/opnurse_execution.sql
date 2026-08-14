-- Mock table: simulates teammate 1's nurse execution items
DROP TABLE IF EXISTS `opnurse_execution`;
CREATE TABLE `opnurse_execution` (
    `id` varchar(32) NOT NULL COMMENT 'Primary key (documentId)',
    `encounter_id` varchar(32) NOT NULL COMMENT 'Encounter ID',
    `document_type` varchar(32) NOT NULL COMMENT 'Document type',
    `patient_name` varchar(64) DEFAULT NULL,
    `doctor_name` varchar(64) DEFAULT NULL,
    `remark` varchar(256) DEFAULT NULL,
    `treatment_item` varchar(128) DEFAULT NULL,
    `exec_dept` varchar(64) DEFAULT NULL,
    `order_time` varchar(32) DEFAULT NULL,
    `exec_time` varchar(32) DEFAULT NULL,
    `executor` varchar(64) DEFAULT NULL,
    `drug_name` varchar(128) DEFAULT NULL,
    `specification` varchar(64) DEFAULT NULL,
    `quantity` varchar(32) DEFAULT NULL,
    `usage` varchar(64) DEFAULT NULL,
    `frequency` varchar(64) DEFAULT NULL,
    `receipt_no` varchar(64) DEFAULT NULL,
    `charge_time` varchar(32) DEFAULT NULL,
    `item_name` varchar(128) DEFAULT NULL,
    `unit_price` varchar(32) DEFAULT NULL,
    `amount` varchar(32) DEFAULT NULL,
    `total_amount` varchar(32) DEFAULT NULL,
    `dept_name` varchar(64) DEFAULT NULL,
    `reg_time` varchar(32) DEFAULT NULL,
    `reg_type` varchar(32) DEFAULT NULL,
    `reg_level` varchar(32) DEFAULT NULL,
    `queue_no` varchar(32) DEFAULT NULL,
    `reg_fee` varchar(32) DEFAULT NULL,
    `bed_no` varchar(32) DEFAULT NULL,
    `admission_no` varchar(64) DEFAULT NULL,
    `dosage` varchar(64) DEFAULT NULL,
    `drip_rate` varchar(64) DEFAULT NULL,
    `settle_date` varchar(32) DEFAULT NULL,
    `operator_name` varchar(64) DEFAULT NULL,
    `reg_total` varchar(32) DEFAULT NULL,
    `drug_total` varchar(32) DEFAULT NULL,
    `exam_total` varchar(32) DEFAULT NULL,
    `lab_total` varchar(32) DEFAULT NULL,
    `treatment_total` varchar(32) DEFAULT NULL,
    `apply_dept` varchar(64) DEFAULT NULL,
    `exam_item` varchar(128) DEFAULT NULL,
    `exam_body_part` varchar(64) DEFAULT NULL,
    `exam_method` varchar(64) DEFAULT NULL,
    `lab_item` varchar(128) DEFAULT NULL,
    `specimen_type` varchar(64) DEFAULT NULL,
    `sample_time` varchar(32) DEFAULT NULL,
    `diagnosis` varchar(256) DEFAULT NULL,
    PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 1. treatment
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,doctor_name,remark,
  treatment_item,exec_dept,order_time,exec_time,executor) VALUES
('exec_001','enc_001','treatment','张三','王医生','青霉素过敏史，注意观察',
 '青霉素皮试','急诊科','2026-07-29 08:00:00','2026-07-29 09:30:00','李护士');

-- 2. prescription
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,doctor_name,remark,
  drug_name,specification,quantity,`usage`,frequency) VALUES
('exec_002','enc_001','prescription','李四','赵医生','饭后服用，忌酒',
 '阿莫西林胶囊','0.5g×24粒/盒','2盒','口服','tid 每次1粒');

-- 3. charge_receipt
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,
  receipt_no,charge_time,item_name,unit_price,quantity,amount,total_amount) VALUES
('exec_003','enc_002','charge_receipt','王五',
 'SF20260729001','2026-07-29 10:15:00','血常规检查','35.00','1','35.00','35.00');

-- 4. reg_receipt
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,
  dept_name,reg_time,reg_type,reg_level,queue_no,reg_fee) VALUES
('exec_004','enc_003','reg_receipt','赵六',
 '内科','2026-07-29 07:30:00','普通号','主治医师','A015','15.00');

-- 5. infusion_label
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,
  bed_no,admission_no,drug_name,dosage,`usage`,frequency,drip_rate,remark) VALUES
('exec_005','enc_004','infusion_label','孙七',
 '12','ZY20260715003','0.9%氯化钠注射液','250ml','静脉滴注','bid','40滴/分','注意滴速');

-- 6. daily_settlement
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,
  settle_date,dept_name,operator_name,
  reg_total,drug_total,exam_total,lab_total,treatment_total,total_amount) VALUES
('exec_006','enc_005','daily_settlement',
 '2026-07-29','急诊科','王护士',
 '1250.00','3820.50','960.00','1480.00','650.00','8160.50');

-- 7. exam_request
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,doctor_name,remark,
  apply_dept,exam_item,exam_body_part,exam_method,diagnosis) VALUES
('exec_007','enc_006','exam_request','周八','王医生','',
 '急诊科','胸部CT平扫','胸部','CT平扫','疑似肺炎');

-- 8. lab_request
INSERT INTO `opnurse_execution` (id,encounter_id,document_type,patient_name,doctor_name,remark,
  apply_dept,lab_item,specimen_type,sample_time,diagnosis) VALUES
('exec_008','enc_006','lab_request','吴九','赵医生','空腹采血',
 '内科','血常规+肝功能','静脉血','2026-07-29 08:00:00','肝功能异常待查');
