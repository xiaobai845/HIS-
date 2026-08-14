-- print_log table: print execution history
CREATE TABLE IF NOT EXISTS `print_log` (
    `id` varchar(32) NOT NULL COMMENT 'Primary key',
    `print_job_id` varchar(32) NOT NULL COMMENT 'Associated order id',
    `doc_type` varchar(32) DEFAULT NULL COMMENT 'Document type',
    `patient_name` varchar(64) DEFAULT NULL COMMENT 'Patient name',
    `print_time` datetime DEFAULT NULL COMMENT 'Print execution time',
    `printer_name` varchar(128) DEFAULT NULL COMMENT 'Printer device name',
    `is_reprint` int DEFAULT 0 COMMENT '0=first print, 1=reprint',
    `status` int DEFAULT 1 COMMENT 'Print result: 0=fail, 1=success',
    `operator` varchar(64) DEFAULT NULL COMMENT 'Operator who triggered print',
    `remark` varchar(256) DEFAULT NULL COMMENT 'Fail reason or extra info',
    `create_time` datetime DEFAULT NULL COMMENT 'Record create time',
    PRIMARY KEY (`id`),
    INDEX `idx_print_job_id` (`print_job_id`),
    INDEX `idx_print_time` (`print_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Print execution log';

-- Test data: 12 records across different doc types, dates, and statuses
INSERT INTO `print_log` VALUES
('log001', 'order_001', 'treatment', '张三', '2026-07-21 08:30:00', 'HP-LaserJet-3F-A', 0, 1, '王护士', '处置单打印成功', '2026-07-21 08:30:00'),
('log002', 'order_002', 'treatment', '李四', '2026-07-21 09:15:00', 'HP-LaserJet-3F-A', 0, 1, '王护士', '处置单打印成功', '2026-07-21 09:15:00'),
('log003', 'order_003', 'prescription', '王五', '2026-07-21 10:00:00', 'HP-LaserJet-3F-B', 0, 1, '赵护士', '处方打印成功', '2026-07-21 10:00:00'),
('log004', 'order_004', 'lab_request', '赵六', '2026-07-21 11:20:00', 'HP-LaserJet-3F-A', 0, 0, '王护士', '打印机卡纸', '2026-07-21 11:20:00'),
('log005', 'order_001', 'treatment', '张三', '2026-07-22 08:10:00', 'HP-LaserJet-3F-A', 1, 1, '钱护士', '患者要求补打处置单', '2026-07-22 08:10:00'),
('log006', 'order_005', 'treatment', '孙七', '2026-07-22 10:45:00', 'HP-LaserJet-3F-C', 0, 1, '钱护士', '处置单打印成功', '2026-07-22 10:45:00'),
('log007', 'order_006', 'exam_request', '周八', '2026-07-22 13:30:00', 'HP-LaserJet-3F-A', 0, 1, '王护士', '检查申请单打印成功', '2026-07-22 13:30:00'),
('log008', 'order_002', 'treatment', '李四', '2026-07-23 08:00:00', 'HP-LaserJet-3F-B', 1, 1, '赵护士', '补打：复核用', '2026-07-23 08:00:00'),
('log009', 'order_007', 'treatment', '吴九', '2026-07-23 09:30:00', 'HP-LaserJet-3F-A', 0, 1, '王护士', '处置单打印成功', '2026-07-23 09:30:00'),
('log010', 'order_008', 'prescription', '郑十', '2026-07-23 10:15:00', 'HP-LaserJet-3F-C', 0, 0, '钱护士', '打印机离线', '2026-07-23 10:15:00'),
('log011', 'order_009', 'lab_request', '陈一', '2026-07-23 14:00:00', 'HP-LaserJet-3F-A', 0, 1, '赵护士', '检验申请单打印成功', '2026-07-23 14:00:00'),
('log012', 'order_001', 'treatment', '张三', '2026-07-23 15:45:00', 'HP-LaserJet-3F-A', 1, 1, '王护士', '再次补打', '2026-07-23 15:45:00');
