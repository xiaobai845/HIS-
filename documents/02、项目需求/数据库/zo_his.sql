-- Create DataBase
DROP DATABASE IF EXISTS `zo_his`;
CREATE DATABASE `zo_his`;

-- Change DataBase
USE `zo_his`;
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for adm_account
-- ----------------------------
CREATE TABLE `adm_account` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '就诊账户聚合根：与单次就诊关联的分账账户（如自费/医保等）',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊 标识',
  `type_code` VARCHAR(255) NOT NULL COMMENT 'type 代码',
  `bus_no` VARCHAR(255) COMMENT '业务流水号（新建必填）',
  `name` VARCHAR(255) COMMENT '名称',
  `balance` DECIMAL(19,6) COMMENT '余额',
  `billing_status_enum` VARCHAR(255) COMMENT '结账状态（{ com.openhis.health.domain.share.enums.AccountBillingStatus#getCode()}）',
  `contract_no` VARCHAR(255) COMMENT '合同 编号',
  `yb_area_no` VARCHAR(255) COMMENT 'ybArea 编号',
  `encounter_flag` TINYINT(1) COMMENT '就诊 标志位',
  `insutype` VARCHAR(255) COMMENT '险种类型',
  `default_flag` TINYINT(1) COMMENT '默认 标志位',
  `status_enum` VARCHAR(255) COMMENT '账户主状态（有效/无效，{ com.openhis.health.domain.share.enums.PublicationStatus#getCode()}）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 账号';
-- ----------------------------
-- Table structure for adm_charge_item
-- ----------------------------
CREATE TABLE `adm_charge_item` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `generate_source_enum` VARCHAR(255) COMMENT '生成来源存储码（DM generate_source_enum）',
  `context_enum` VARCHAR(255) COMMENT '收费上下文存储码（DM context_enum）',
  `bus_no` VARCHAR(255) COMMENT '业务流水号（DM bus_no）',
  `parent_id` VARCHAR(64) COMMENT '父收费明细主键（拆分/关联场景，DM parent_id）',
  `prescription_no` VARCHAR(255) COMMENT '处方号展示/追溯（DM prescription_no）',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者主键（DM 患者_id）',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊主键（DM 就诊_id）',
  `service_table` VARCHAR(255) COMMENT '上游业务表名锚点（BR-CHG-001，DM service_table）',
  `service_id` VARCHAR(64) COMMENT '上游业务主键锚点（DM service_id）',
  `account_id` VARCHAR(64) COMMENT '账户主键（DM 账号_id）',
  `definition_id` VARCHAR(64) COMMENT '收费项目定义主键（DM 定义_id）',
  `status_enum` VARCHAR(255) COMMENT '收费明细聚合根（DM-ADM-011 §3.1，表 adm_charge_item）',
  `total_price` DECIMAL(19,6) COMMENT '总价（DM total_price）',
  `occurrence_time` DATETIME(6) COMMENT '费用发生时刻（DM occurrence_time）',
  `performer_id` VARCHAR(64) COMMENT '执行人主键（DM performer_id）',
  `performing_org_id` VARCHAR(64) COMMENT '执行机构主键（DM performing_org_id）',
  `requesting_org_id` VARCHAR(64) COMMENT '申请机构主键（DM requesting_org_id）',
  `cost_org_id` VARCHAR(64) COMMENT '成本归属机构主键（DM cost_org_id）',
  `quantity_value` DECIMAL(18,4) COMMENT '数量值（DM quantity_value）',
  `quantity_unit` VARCHAR(255) COMMENT '数量单位（DM quantity_unit）',
  `unit_price` DECIMAL(19,6) COMMENT '单价（DM unit_price）',
  `def_detail_id` VARCHAR(64) COMMENT '定义明细主键（DM def_detail_id）',
  `base_amount` DECIMAL(19,6) COMMENT '基准金额（DM base_amount）',
  `discount_amount` DECIMAL(19,6) COMMENT '折扣金额（DM discount_amount）',
  `surcharge_amount` DECIMAL(19,6) COMMENT '附加费金额（DM surcharge_amount）',
  `system_discount_price` DECIMAL(19,6) COMMENT '系统折后价（DM system_discount_price）',
  `manual_adjusted_price` DECIMAL(19,6) COMMENT '手工调价后金额（DM manual_adjusted_price）',
  `override_reason_code` VARCHAR(255) COMMENT '改价原因码（DM override_reason_code）',
  `override_reason_text` VARCHAR(255) COMMENT '改价原因说明（DM override_reason_text）',
  `enterer_id` VARCHAR(64) COMMENT '录入人主键（DM enterer_id）',
  `entered_date` DATETIME(6) COMMENT '录入时间（DM entered_date）',
  `product_table` VARCHAR(255) COMMENT '产品来源表名（DM product_table）',
  `product_id` VARCHAR(64) COMMENT '产品主键（DM product_id）',
  `procedure_id` VARCHAR(64) COMMENT '处置/手术类关联主键（DM 手术/操作_id）',
  `dispense_table` VARCHAR(255) COMMENT '发药来源表名（DM dispense_table）',
  `dispense_id` VARCHAR(64) COMMENT '发药主键（DM dispense_id）',
  `claim_state_enum` INT COMMENT '理赔状态枚举（DM claim_state_enum）',
  `print_count` INT COMMENT '打印次数（DM print_count）',
  `org_id` VARCHAR(64) COMMENT '开立机构主键（DM org_id）',
  `refund_id` VARCHAR(64) COMMENT '退费关联主键（DM refund_id）',
  `condition_id` VARCHAR(64) COMMENT '病情/诊断条件关联（DM 病情_id）',
  `encounter_diagnosis_id` VARCHAR(64) COMMENT '就诊诊断关联主键（DM 就诊_diagnosis_id）',
  `tcm_flag` TINYINT(1) COMMENT '是否中医相关标记（DM tcm_flag）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 收费项目';
-- ----------------------------
-- Table structure for adm_charge_item_definition
-- ----------------------------
CREATE TABLE `adm_charge_item_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `instance_table` VARCHAR(255) COMMENT '收费项目定义实体：描述某业务实例在特定价类/批次下的可计费项与价格',
  `instance_id` VARCHAR(64) NOT NULL COMMENT '业务实例主键',
  `charge_name` VARCHAR(255) COMMENT '收费展示名称',
  `status_enum` VARCHAR(255) NOT NULL DEFAULT 'ACTIVE' COMMENT '状态枚举编码（PublicationStatus，默认 ACTIVE）',
  `org_id` VARCHAR(64) COMMENT '所属机构主键（可空表示全局）',
  `type_code` VARCHAR(255) NOT NULL COMMENT '收费类型编码（fin_type_code，必填；号源落诊察费 1012）',
  `yb_type` VARCHAR(255) COMMENT '医保类别或对照编码',
  `price_type_code` VARCHAR(255) NOT NULL COMMENT '价格类型编码（必填）',
  `lot_no` VARCHAR(255) COMMENT '批次或效期批次号',
  `price_value` DECIMAL(19,6) NOT NULL COMMENT '价格数值（元，与 { adm_charge_item} 金额列同口径）',
  `priority` INT COMMENT '同实例多价时的优先级（数值越小越优先，由产品约定）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 收费项目定义';
-- ----------------------------
-- Table structure for adm_device_definition
-- ----------------------------
CREATE TABLE `adm_device_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '器材定义聚合根（DM-ADM-008 §3.1，SDD §4.2）',
  `bus_no` VARCHAR(255) COMMENT '器材业务编码（院内唯一）',
  `py_str` VARCHAR(255) COMMENT '拼音码（用于检索）',
  `wb_str` VARCHAR(255) COMMENT '五笔码（用于检索）',
  `category_code` VARCHAR(255) COMMENT '器材分类编码',
  `type_code` VARCHAR(255) COMMENT '器材种类编码',
  `purchase_unit_code` VARCHAR(255) COMMENT '采购单位（5类单位之一）',
  `total_volume` VARCHAR(255) COMMENT '包装规格描述（与药品 total_volume 语义对齐）',
  `item_min_quantity` DECIMAL(18,2) COMMENT '最小库存警戒量',
  `item_max_quantity` DECIMAL(18,2) COMMENT '最大库存警戒量',
  `split_unit_code` VARCHAR(255) COMMENT '拆零单位（5类单位之一）',
  `merchandise_name` VARCHAR(255) COMMENT '商品名称',
  `merchandise_py_str` VARCHAR(255) COMMENT '商品名拼音检索码',
  `merchandise_wb_str` VARCHAR(255) COMMENT '商品名五笔检索码',
  `def_encounter_unit_code` VARCHAR(255) COMMENT '默认门诊/就诊单位编码',
  `def_inhospital_unit_code` VARCHAR(255) COMMENT '默认住院单位编码',
  `org_id` VARCHAR(64) COMMENT '所属科室标识',
  `location_id` VARCHAR(64) COMMENT '所在位置标识',
  `model_number` VARCHAR(255) COMMENT '产品型号',
  `hvcm_flag` TINYINT(1) COMMENT '高值器材标志',
  `dose_unit_code` VARCHAR(255) COMMENT '剂量单位（5类单位之一）',
  `package_unit_code` VARCHAR(255) COMMENT '销售单位（5类单位之一）',
  `stock_unit_code` VARCHAR(255) COMMENT '库存单位（5类单位之一）',
  `approval_number` VARCHAR(255) COMMENT '批准文号',
  `manufacturer_id` VARCHAR(64) COMMENT '生产厂家标识',
  `manufacturer_text` VARCHAR(255) COMMENT '生产厂家名称',
  `supply_id` VARCHAR(64) COMMENT '供应商标识',
  `description` VARCHAR(255) COMMENT '器材说明',
  `jurisdiction` VARCHAR(255) COMMENT '适用范围描述',
  `device_version` VARCHAR(255) COMMENT '器材版本',
  `substance_text` VARCHAR(255) COMMENT '主要成分描述',
  `allergen_flag` TINYINT(1) COMMENT '过敏标记',
  `rx_flag` TINYINT(1) COMMENT '处方标志',
  `yb_flag` TINYINT(1) COMMENT '医保标记',
  `yb_no` VARCHAR(255) COMMENT '医保编码',
  `yb_org_no` VARCHAR(255) COMMENT '医药机构目录编码',
  `yb_match_flag` TINYINT(1) COMMENT '医保对码标记',
  `chrgitm_lv` INT COMMENT '医保等级',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '发布状态（存储为整数码）',
  `active_flag` TINYINT(1) NOT NULL COMMENT '是否启用标记',
  `yb_mapping_code` VARCHAR(255) COMMENT '医保对码标识',
  `dose_unit_ratio` DECIMAL(18,6) COMMENT '剂量单位→拆零单位换算倍数（拆零单位为1）',
  `purchase_unit_ratio` DECIMAL(18,6) COMMENT '采购单位→拆零单位换算倍数（拆零单位为1）',
  `stock_unit_ratio` DECIMAL(18,6) COMMENT '库存单位→拆零单位换算倍数（拆零单位为1）',
  `package_unit_ratio` DECIMAL(18,6) COMMENT '销售单位→拆零单位换算倍数（拆零单位为1）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 设备定义';
-- ----------------------------
-- Table structure for adm_encounter
-- ----------------------------
CREATE TABLE `adm_encounter` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '就诊聚合根实体',
  `group_id` VARCHAR(64) COMMENT 'group 标识',
  `bus_no` VARCHAR(255) NOT NULL COMMENT 'bus 编号',
  `status_enum` VARCHAR(255) NOT NULL COMMENT 'status 枚举值',
  `class_enum` VARCHAR(255) NOT NULL COMMENT 'class 枚举值',
  `yb_class_enum` VARCHAR(255) COMMENT 'ybClass 枚举值',
  `yb_class_text` VARCHAR(255) COMMENT '医保class文本',
  `class_json` VARCHAR(255) COMMENT 'class JSON 快照',
  `priority_enum` VARCHAR(255) COMMENT 'priority 枚举值',
  `type_enum` VARCHAR(255) COMMENT 'type 枚举值',
  `service_type_id` VARCHAR(64) COMMENT 'serviceType 标识',
  `subject_status_enum` VARCHAR(255) COMMENT 'subjectStatus 枚举值',
  `start_time` DATETIME(6) COMMENT 'start 时间',
  `end_time` DATETIME(6) COMMENT 'end 时间',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构 标识',
  `display_order` INT COMMENT '显示顺序',
  `first_enum` VARCHAR(255) COMMENT 'first 枚举值',
  `admit_source_code` VARCHAR(255) COMMENT 'admitSource 代码',
  `in_way_code` VARCHAR(255) COMMENT 'inWay 代码',
  `reception_time` DATETIME(6) COMMENT 'reception 时间',
  `registrar_id` VARCHAR(64) COMMENT 'registrar 标识',
  `amb_encounter_id` VARCHAR(64) COMMENT 'ambEncounter 标识',
  `out_way_code` VARCHAR(255) COMMENT 'outWay 代码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 就诊';
-- ----------------------------
-- Table structure for adm_encounter_diagnosis
-- ----------------------------
CREATE TABLE `adm_encounter_diagnosis` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊诊断关联子实体：持久化就诊与病情（Condition）的多对多事实及诊断扩展字段',
  `condition_id` VARCHAR(64) NOT NULL COMMENT '病情/诊断条件主键',
  `primary_flag` TINYINT(1) COMMENT '是否主诊断',
  `rank` INT COMMENT '排序序号',
  `description` VARCHAR(255) COMMENT '诊断描述',
  `diag_type_code` VARCHAR(32) COMMENT '诊断类型码（术语 code 字符串，与 ipt_dise_type_code 对齐，不做整型转换）',
  `diag_code` INT COMMENT '诊断编码',
  `condition_code` INT COMMENT '病情编码',
  `med_type` VARCHAR(255) COMMENT '医保或诊疗类别',
  `highest_diag_flag` TINYINT(1) COMMENT '是否最高诊断',
  `tcm_syndrome_group` VARCHAR(255) COMMENT '中医证候组',
  `tcm_flag` TINYINT(1) COMMENT '是否中医诊断'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 就诊诊断';
-- ----------------------------
-- Table structure for adm_encounter_location
-- ----------------------------
CREATE TABLE `adm_encounter_location` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `location_id` VARCHAR(64) NOT NULL COMMENT '位置/科室标识',
  `form_enum` VARCHAR(255) COMMENT 'form枚举值',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `start_time` DATETIME(6) COMMENT '开始时间',
  `end_time` DATETIME(6) COMMENT '结束时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 就诊地点';
-- ----------------------------
-- Table structure for adm_encounter_participant
-- ----------------------------
CREATE TABLE `adm_encounter_participant` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `role_code` VARCHAR(255) NOT NULL COMMENT '角色编码',
  `practitioner_id` VARCHAR(64) NOT NULL COMMENT '医护人员标识',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `start_time` DATETIME(6) COMMENT '开始时间',
  `end_time` DATETIME(6) COMMENT '结束时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 就诊参与者';
-- ----------------------------
-- Table structure for adm_encounter_reason
-- ----------------------------
CREATE TABLE `adm_encounter_reason` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊原因子实体：记录就诊事由的来源表与业务主键及用途编码',
  `use_code` VARCHAR(255) NOT NULL COMMENT '用途编码（如挂号原因类型）',
  `reason_table` VARCHAR(255) COMMENT '原因实体所在逻辑表名',
  `reason_id` VARCHAR(64) COMMENT '原因业务主键',
  `description` VARCHAR(255) COMMENT '原因描述'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 就诊原因';
-- ----------------------------
-- Table structure for adm_episode_of_care
-- ----------------------------
CREATE TABLE `adm_episode_of_care` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者 标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构 标识',
  `bus_no` VARCHAR(255) NOT NULL COMMENT 'bus 编号',
  `care_team_id` VARCHAR(64) COMMENT 'careTeam 标识',
  `care_type` VARCHAR(255) COMMENT 'care类型',
  `care_goal` VARCHAR(255) COMMENT '照护目标',
  `status_enum` VARCHAR(255) NOT NULL COMMENT 'status 枚举值',
  `active_flag` TINYINT(1) NOT NULL COMMENT 'active 标志位',
  `start_time` DATETIME(6) COMMENT 'start 时间',
  `end_time` DATETIME(6) COMMENT 'end 时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 诊疗周期';
-- ----------------------------
-- Table structure for adm_episode_of_care_encounter
-- ----------------------------
CREATE TABLE `adm_episode_of_care_encounter` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `episode_of_care_id` VARCHAR(64) NOT NULL COMMENT '疗程-就诊关联实体：记录某次就诊加入/离开疗程的时间',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊主键',
  `join_time` DATETIME(6) NOT NULL COMMENT '纳入疗程时间',
  `leave_time` DATETIME(6) COMMENT '离开疗程时间（未离开时为空）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 诊疗周期就诊';
-- ----------------------------
-- Table structure for adm_healthcare_service
-- ----------------------------
CREATE TABLE `adm_healthcare_service` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '医疗服务聚合根，对应表 { adm_healthcare_service}',
  `type_code` VARCHAR(255) NOT NULL COMMENT '服务类型编码（type_code），区分普通门诊、专家门诊等服务类型',
  `category_code` VARCHAR(255) COMMENT '服务类别编码（category_code），区分门诊、住院等服务大类',
  `offered_org_id` VARCHAR(64) COMMENT '提供该服务的机构主键（offered_org_id），关联 { adm_机构}',
  `specialty_code` VARCHAR(255) COMMENT '专科码（specialty_code），如"CARDIOLOGY""SURGERY"，可为空',
  `location_id` VARCHAR(64) COMMENT '服务所在地点主键，关联 { adm_地点}，可为空',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '服务状态码（status_enum，String code）',
  `active_flag` TINYINT(1) NOT NULL COMMENT '服务是否处于激活可用状态，与 statusEnum=ACTIVE 联动维护',
  `appointment_required_flag` TINYINT(1) COMMENT '预约是否必填标志，true 表示患者必须预约后才可就诊',
  `yb_no` VARCHAR(255) COMMENT '医保编号（yb_no），对接医保结算使用，可为空',
  `bus_no` VARCHAR(255) COMMENT '业务编号（bus_no），系统内唯一标识医疗服务的人读编码，可为空',
  `comment` VARCHAR(255) COMMENT '备注说明，对外展示的补充描述，可为空',
  `extra_details` VARCHAR(255) COMMENT '扩展详情（JSON 字符串），存储结构化附加信息，可为空',
  `contact` VARCHAR(255) COMMENT '联系方式（JSON 字符串），医疗服务对外联系信息，可为空'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 医疗服务';
-- ----------------------------
-- Table structure for adm_invoice
-- ----------------------------
CREATE TABLE `adm_invoice` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `patient_id` VARCHAR(64) COMMENT '票据聚合根：草稿开具等写侧由 { com.openhis.health.domain.administration.发票.service.InvoiceDomainService} 编排',
  `reconciliation_id` VARCHAR(64) COMMENT 'reconciliation 标识',
  `payment_id` VARCHAR(64) COMMENT 'payment 标识',
  `bus_no` VARCHAR(255) COMMENT '业务流水号（新建必填）',
  `bill_no` VARCHAR(255) COMMENT 'bill 编号',
  `type_code` VARCHAR(255) COMMENT 'type 代码',
  `cancelled_reason` VARCHAR(255) COMMENT 'cancelled原因',
  `charge_item_ids` TEXT COMMENT '收费项ids',
  `payment_terms` VARCHAR(255) COMMENT '支付terms',
  `amount` DECIMAL(19,6) COMMENT '金额',
  `status_enum` VARCHAR(255) COMMENT 'status 枚举值',
  `issued_at` DATETIME(6) COMMENT 'issued 时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 发票';
-- ----------------------------
-- Table structure for adm_location
-- ----------------------------
CREATE TABLE `adm_location` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '位置聚合根实体',
  `bus_no` VARCHAR(255) NOT NULL COMMENT 'bus 编号',
  `status_enum` VARCHAR(255) NOT NULL COMMENT 'status 枚举值',
  `operational_enum` VARCHAR(255) COMMENT 'operational 枚举值',
  `form_enum` VARCHAR(255) NOT NULL COMMENT 'form 枚举值',
  `mode_enum` VARCHAR(255) NOT NULL COMMENT 'mode 枚举值',
  `type_json` VARCHAR(255) COMMENT 'type JSON 快照',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构 标识',
  `display_order` INT COMMENT '显示顺序',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `parent_id` VARCHAR(64) COMMENT 'parent 标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 地点';
-- ----------------------------
-- Table structure for adm_organization
-- ----------------------------
CREATE TABLE `adm_organization` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '机构聚合根实体',
  `bus_no` VARCHAR(255) NOT NULL COMMENT 'bus 编号',
  `parent_id` VARCHAR(64) COMMENT 'parent 标识',
  `type_enum` VARCHAR(255) NOT NULL COMMENT 'type 枚举值',
  `class_enum` VARCHAR(255) COMMENT 'class 枚举值',
  `status_enum` VARCHAR(255) NOT NULL COMMENT 'status 枚举值（{ PublicationStatus#getCode()}）',
  `active_flag` TINYINT(1) NOT NULL COMMENT 'active 标志位',
  `display_order` INT COMMENT '显示顺序',
  `def_doctor_id` VARCHAR(64) COMMENT 'defDoctor 标识',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `yb_no` VARCHAR(255) COMMENT 'yb 编号',
  `yb_name` VARCHAR(255) COMMENT 'yb 名称',
  `medins_id` VARCHAR(255) COMMENT 'medins 标识',
  `medins_admdvs` VARCHAR(255) COMMENT '医疗机构医保区划',
  `medins_type` VARCHAR(255) COMMENT 'medins类型',
  `medins_lv` VARCHAR(255) COMMENT '医疗机构等级',
  `caty` VARCHAR(255) COMMENT '科别'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 机构';
-- ----------------------------
-- Table structure for adm_patient
-- ----------------------------
CREATE TABLE `adm_patient` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '患者聚合根实体',
  `name` VARCHAR(255) NOT NULL COMMENT '患者姓名',
  `name_json` VARCHAR(255) COMMENT '姓名扩展 JSON',
  `gender_enum` VARCHAR(255) NOT NULL COMMENT '性别编码',
  `birth_date` DATE COMMENT '出生日期',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '患者状态编码',
  `active_flag` TINYINT(1) NOT NULL COMMENT '启用标记',
  `temp_flag` TINYINT(1) NOT NULL COMMENT '临时建档标记',
  `id_card` VARCHAR(255) COMMENT '身份证号',
  `marital_status_enum` VARCHAR(255) COMMENT '婚姻状态编码',
  `prfs_enum` VARCHAR(255) COMMENT '职业编码',
  `phone` VARCHAR(255) COMMENT '联系电话',
  `address` VARCHAR(255) COMMENT '地址',
  `address_province` VARCHAR(255) COMMENT '地址province',
  `address_city` VARCHAR(255) COMMENT '地址city',
  `address_district` VARCHAR(255) COMMENT '地址district',
  `address_street` VARCHAR(255) COMMENT '地址street',
  `address_extend_json` VARCHAR(255) COMMENT '主要地址',
  `nationality_code` VARCHAR(255) COMMENT '民族编码',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `blood_type_abo` INT COMMENT 'blood类型abo',
  `blood_type_rh` INT COMMENT 'blood类型rh',
  `work_company` VARCHAR(255) COMMENT '血型',
  `native_place` VARCHAR(255) COMMENT '籍贯',
  `country_code` VARCHAR(255) COMMENT '国家地区编码',
  `link_name` VARCHAR(255) COMMENT 'link名称',
  `link_relation_code` INT COMMENT 'linkrelation编码',
  `link_telcom` VARCHAR(255) COMMENT '联系电话',
  `link_jsons` VARCHAR(255) COMMENT '主要联系人',
  `deceased_date` DATETIME(6) COMMENT '死亡时间',
  `deceased_reason` VARCHAR(255) COMMENT '死亡原因',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '建档机构标识',
  `merged_target_patient_id` VARCHAR(64) COMMENT '合并目标患者标识',
  `merged_at` DATETIME(6) COMMENT '合并时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 患者';
-- ----------------------------
-- Table structure for adm_patient_identifier
-- ----------------------------
CREATE TABLE `adm_patient_identifier` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `type_code` VARCHAR(255) NOT NULL COMMENT '患者非身份证标识子实体',
  `identifier_no` VARCHAR(255) NOT NULL COMMENT '标识号码',
  `state_enum` VARCHAR(255) COMMENT '标识状态编码',
  `start_time` DATETIME(6) COMMENT '有效开始时间',
  `end_time` DATETIME(6) COMMENT '有效结束时间',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '所属患者标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 患者标识';
-- ----------------------------
-- Table structure for adm_patient_student
-- ----------------------------
CREATE TABLE `adm_patient_student` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '公费学生资质子实体',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `gender_enum` VARCHAR(255) COMMENT '性别编码',
  `age` INT COMMENT '年龄',
  `student_no` VARCHAR(255) NOT NULL COMMENT '学号',
  `id_card` VARCHAR(255) COMMENT '身份证号',
  `phone` VARCHAR(255) COMMENT '联系电话',
  `college` VARCHAR(255) COMMENT '学院',
  `major` VARCHAR(255) COMMENT '专业',
  `edu_level` INT COMMENT '学历层次',
  `enroll_time` DATETIME(6) COMMENT '入校时间',
  `leave_time` DATETIME(6) COMMENT '离校时间',
  `grade` VARCHAR(255) COMMENT '年级',
  `study_type` INT COMMENT '学习形式',
  `school_status` INT COMMENT '在校状态',
  `physical_exam_result` INT COMMENT '体检结果',
  `counselor` VARCHAR(255) COMMENT '辅导员',
  `counselor_phone` VARCHAR(255) COMMENT '辅导员电话',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '所属患者标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 患者学员';
-- ----------------------------
-- Table structure for adm_pr_assign
-- ----------------------------
CREATE TABLE `adm_pr_assign` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) COMMENT '名称',
  `active_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `practitioner_id` VARCHAR(64) NOT NULL COMMENT '医护人员标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `specialty_code` VARCHAR(64) COMMENT 'specialty编码',
  `type_code` INT COMMENT '类型编码',
  `role_id` VARCHAR(64) NOT NULL COMMENT '岗位分配聚合根（{ adm_pr_assign}）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 PR分配';
-- ----------------------------
-- Table structure for adm_pr_assign_schedule
-- ----------------------------
CREATE TABLE `adm_pr_assign_schedule` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `assignment_id` VARCHAR(64) NOT NULL COMMENT '岗位排班项子实体，对应表 { adm_pr_assign_排班}',
  `availability_json` TEXT NOT NULL COMMENT '可用时间 JSON'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 PR分配排班';
-- ----------------------------
-- Table structure for adm_pr_assign_service
-- ----------------------------
CREATE TABLE `adm_pr_assign_service` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `assignment_id` VARCHAR(64) NOT NULL COMMENT '岗位服务项子实体，对应表 { adm_pr_assign_service}',
  `healthcare_service_id` VARCHAR(64) NOT NULL COMMENT '医疗服务标识，关联 { adm_healthcare_service.id}'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 PR分配服务';
-- ----------------------------
-- Table structure for adm_practitioner
-- ----------------------------
CREATE TABLE `adm_practitioner` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` BIGINT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '人员姓名',
  `name_json` VARCHAR(2000) COMMENT '其他名称 JSON（曾用名、英文名等）',
  `py_str` VARCHAR(255) COMMENT '姓名拼音检索码',
  `wb_str` VARCHAR(255) COMMENT '姓名五笔检索码',
  `gender_enum` VARCHAR(255) NOT NULL COMMENT '行政性别编码',
  `birth_date` DATE COMMENT '出生日期',
  `deceased_date` DATETIME(6) COMMENT '死亡时间',
  `phone` VARCHAR(50) COMMENT '联系电话',
  `address_province` VARCHAR(64) COMMENT '地址-省',
  `address_city` VARCHAR(64) COMMENT '地址-市',
  `address_district` VARCHAR(64) COMMENT '地址-区/县',
  `address_street` VARCHAR(255) COMMENT '地址-街道/详细地址',
  `address_json` VARCHAR(2000) COMMENT '地址扩展 JSON',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '人员状态（ACTIVE / INACTIVE / DISCARDED）',
  `active_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用（status_enum == ACTIVE 时为 true）',
  `bus_no` VARCHAR(64) COMMENT '院内工号/业务编号',
  `yb_no` VARCHAR(64) COMMENT '医保人员编码',
  `user_id` VARCHAR(64) NOT NULL COMMENT '关联平台用户主键（与 id 独立，无库表外键）',
  `org_id` VARCHAR(64) COMMENT '默认登录科室/当前工作科室（Organization 主键）',
  `dr_profttl_code` INT COMMENT '职称编码',
  `phar_prac_cert_no` VARCHAR(64) COMMENT '医师/药师执业资格证编号',
  `prsc_dr_cert_code` VARCHAR(64) COMMENT '执业证件类型编码',
  `signature` TEXT COMMENT '医生签名图片 Base64（可含 data:image/*;base64, 前缀）',
  `kpd_code` VARCHAR(64) COMMENT '开票点编码',
  `pos_no` VARCHAR(64) COMMENT 'POS 机终端编号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医务人员主数据';
-- ----------------------------
-- Table structure for adm_specimen_definition
-- ----------------------------
CREATE TABLE `adm_specimen_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '样本定义聚合根（{ adm_specimen_定义}，DM-ADM-014）',
  `name` VARCHAR(255) NOT NULL COMMENT '面向临床与维护页的显示名称',
  `py_str` VARCHAR(255) COMMENT '拼音检索码',
  `wb_str` VARCHAR(255) COMMENT '五笔检索码',
  `type_enum` VARCHAR(255) NOT NULL COMMENT '标本种类（存 { SpecimenType#getCode()}）',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '发布状态（存 { PublicationStatus#getCode()}）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='管理域 标本定义';
-- ----------------------------
-- Table structure for bkg_bed_reservation_ext
-- ----------------------------
CREATE TABLE `bkg_bed_reservation_ext` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `appointment_id` VARCHAR(64) NOT NULL COMMENT '关联预约主键（wkf_预约_queue）',
  `location_id` VARCHAR(64) NOT NULL COMMENT '床位/房间 Location 主键',
  `patient_id` VARCHAR(64) COMMENT '患者主键',
  `ward_location_id` VARCHAR(64) COMMENT '病区 Location 主键',
  `intended_admission_date` DATE COMMENT '拟入院日期',
  `remark` VARCHAR(512) COMMENT '备注',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='床位预约扩展：关联 预约，不占用 时段';
-- ----------------------------
-- Table structure for bkg_calendar_exception
-- ----------------------------
CREATE TABLE `bkg_calendar_exception` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构/科室；空=全院',
  `exception_date` DATE NOT NULL COMMENT '例外日期或区间起点',
  `range_end` DATE COMMENT '区间终点；空=单日',
  `exception_type` VARCHAR(16) NOT NULL COMMENT '类型：CLOSED / REDUCED / OVERRIDE / EXTRA',
  `override_schedule_template_id` VARCHAR(64) COMMENT 'REDUCED/OVERRIDE/EXTRA 时关联 T2',
  `reason` VARCHAR(255) COMMENT '原因说明',
  `auto_apply_on_generate` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '从模板生成 排班 时是否自动应用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='T3 日历例外（07 §5.4）';
-- ----------------------------
-- Table structure for bkg_channel_config
-- ----------------------------
CREATE TABLE `bkg_channel_config` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识；空=租户默认',
  `channel_code` VARCHAR(32) NOT NULL COMMENT '渠道编码：WINDOW / APP / WECHAT 等',
  `channel_name` VARCHAR(64) NOT NULL COMMENT '渠道名称',
  `enabled_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `quota_percent` INT NOT NULL DEFAULT 100 COMMENT '号源配额百分比（0-100）',
  `notify_template_code` VARCHAR(64) COMMENT '通知模板编码',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='预约渠道：窗口、APP、第三方等配额与通知模板';
-- ----------------------------
-- Table structure for bkg_diagnostic_resource_map
-- ----------------------------
CREATE TABLE `bkg_diagnostic_resource_map` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `activity_definition_id` VARCHAR(64) COMMENT '检查项目（ActivityDefinition）主键',
  `service_category_code` VARCHAR(64) COMMENT '服务类别编码',
  `schedule_id` VARCHAR(64) COMMENT '关联号源日程主键',
  `location_id` VARCHAR(64) COMMENT '执行地点主键',
  `device_id` VARCHAR(64) COMMENT '设备主键',
  `resource_name` VARCHAR(128) COMMENT '展示名称',
  `active_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医技预约：检查项目与 排班/设备/诊室映射';
-- ----------------------------
-- Table structure for bkg_group_checkup_batch
-- ----------------------------
CREATE TABLE `bkg_group_checkup_batch` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) NOT NULL COMMENT '团检单位主键',
  `batch_name` VARCHAR(128) NOT NULL COMMENT '批次名称',
  `package_id` VARCHAR(64) COMMENT '默认套餐主键',
  `schedule_id` VARCHAR(64) COMMENT '关联号源日程',
  `booking_date` DATE NOT NULL COMMENT '体检日期',
  `start_time` time(6) COMMENT '时段开始',
  `end_time` time(6) COMMENT '时段结束',
  `capacity_limit` INT NOT NULL DEFAULT 0 COMMENT '容量上限',
  `booked_count` INT NOT NULL DEFAULT 0 COMMENT '已预约人数',
  `status_code` VARCHAR(32) NOT NULL DEFAULT 'DRAFT' COMMENT '状态：DRAFT / OPEN / CLOSED 等',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='团检批次：日期、容量、关联 排班';
-- ----------------------------
-- Table structure for bkg_group_checkup_org
-- ----------------------------
CREATE TABLE `bkg_group_checkup_org` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_code` VARCHAR(64) NOT NULL COMMENT '单位编码',
  `org_name` VARCHAR(128) NOT NULL COMMENT '单位名称',
  `contact_name` VARCHAR(64) COMMENT '联系人',
  `contact_phone` VARCHAR(32) COMMENT '联系电话',
  `settlement_mode` VARCHAR(32) COMMENT '结算方式',
  `contract_year` VARCHAR(16) COMMENT '合同年度',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='团检签约单位';
-- ----------------------------
-- Table structure for bkg_group_checkup_roster
-- ----------------------------
CREATE TABLE `bkg_group_checkup_roster` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `batch_id` VARCHAR(64) NOT NULL COMMENT '所属批次主键',
  `patient_id` VARCHAR(64) COMMENT '患者主键（建档后回填）',
  `full_name` VARCHAR(64) NOT NULL COMMENT '姓名',
  `id_card_no` VARCHAR(32) COMMENT '身份证号',
  `student_no` VARCHAR(32) COMMENT '学号/工号',
  `mobile_phone` VARCHAR(32) COMMENT '手机号',
  `appointment_id` VARCHAR(64) COMMENT '关联预约主键',
  `booking_status_code` VARCHAR(32) NOT NULL DEFAULT 'PENDING' COMMENT '预约状态：PENDING / BOOKED / CANCELLED 等',
  `import_status_code` VARCHAR(32) NOT NULL DEFAULT 'IMPORTED' COMMENT '导入状态',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='团检人员名单及预约状态';
-- ----------------------------
-- Table structure for bkg_health_check_booking_ext
-- ----------------------------
CREATE TABLE `bkg_health_check_booking_ext` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `appointment_id` VARCHAR(64) NOT NULL COMMENT '关联预约主键',
  `package_id` VARCHAR(64) COMMENT '套餐主键',
  `batch_id` VARCHAR(64) COMMENT '团检批次主键（个检为空）',
  `package_snapshot_json` TEXT COMMENT '下单时套餐快照 JSON',
  `estimated_amount` DECIMAL(12,2) COMMENT '参考金额',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='体检预约扩展：套餐快照、金额';
-- ----------------------------
-- Table structure for bkg_health_check_package
-- ----------------------------
CREATE TABLE `bkg_health_check_package` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识',
  `package_code` VARCHAR(64) NOT NULL COMMENT '套餐编码',
  `package_name` VARCHAR(128) NOT NULL COMMENT '套餐名称',
  `applicable_gender` VARCHAR(16) COMMENT '适用性别：M/F/ALL',
  `applicable_age_min` INT COMMENT '适用年龄下限',
  `applicable_age_max` INT COMMENT '适用年龄上限',
  `estimated_amount` DECIMAL(12,2) COMMENT '参考金额',
  `active_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='体检套餐定义（个检/团检共用）';
-- ----------------------------
-- Table structure for bkg_health_check_package_item
-- ----------------------------
CREATE TABLE `bkg_health_check_package_item` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `package_id` VARCHAR(64) NOT NULL COMMENT '所属套餐主键',
  `activity_definition_id` VARCHAR(64) COMMENT '检查项目主键',
  `item_name` VARCHAR(128) COMMENT '项目名称（冗余展示）',
  `required_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否必检',
  `sort_order` INT NOT NULL DEFAULT 0 COMMENT '排序号',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='体检套餐检查项目明细';
-- ----------------------------
-- Table structure for bkg_queue_display_config
-- ----------------------------
CREATE TABLE `bkg_queue_display_config` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `location_id` VARCHAR(64) COMMENT '候诊区 Location 主键',
  `display_title` VARCHAR(128) COMMENT '大屏标题',
  `refresh_seconds` INT NOT NULL DEFAULT 5 COMMENT '数据刷新间隔（秒）',
  `voice_enabled_flag` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否启用语音叫号',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='候诊叫号大屏：刷新间隔、语音播报';
-- ----------------------------
-- Table structure for bkg_registration_policy
-- ----------------------------
CREATE TABLE `bkg_registration_policy` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识；空=租户默认',
  `walk_in_slot_mode` VARCHAR(32) NOT NULL DEFAULT 'APPOINTMENT_FIRST' COMMENT '现场取号模式：APPOINTMENT_FIRST / SLOT_FIRST 等',
  `auto_check_in_on_register` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '挂号时是否自动签到',
  `on_cancel_policy` VARCHAR(32) NOT NULL DEFAULT 'RELEASE_SLOT_ONLY' COMMENT '取消预约处置：RELEASE_SLOT_ONLY / KEEP_SLOT 等',
  `allow_edit_practitioner_from_appointment` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否允许从预约修改接诊医师',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='挂号衔接策略：现场取号、取消处置、医师变更等';
-- ----------------------------
-- Table structure for bkg_release_policy
-- ----------------------------
CREATE TABLE `bkg_release_policy` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识；空=租户默认',
  `policy_code` VARCHAR(64) NOT NULL COMMENT '策略编码（机构内唯一）',
  `policy_name` VARCHAR(128) NOT NULL COMMENT '策略名称',
  `advance_days` INT NOT NULL DEFAULT 7 COMMENT '可预约提前天数',
  `slot_minutes` INT NOT NULL DEFAULT 30 COMMENT '默认时段粒度（分钟）',
  `capacity_per_slot` INT NOT NULL DEFAULT 10 COMMENT '默认每时段容量',
  `channel_quota_json` TEXT COMMENT '渠道配额 JSON，如 {"WINDOW":60,"APP":40}',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='放号策略：提前天数、时段粒度、每段容量、渠道配额';
-- ----------------------------
-- Table structure for bkg_resource_profile
-- ----------------------------
CREATE TABLE `bkg_resource_profile` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `resource_type_code` VARCHAR(32) NOT NULL COMMENT '资源类型：PRACTITIONER / DEVICE / LOCATION 等',
  `resource_id` VARCHAR(64) NOT NULL COMMENT '资源主键',
  `profile_name` VARCHAR(128) COMMENT '画像名称',
  `profile_json` TEXT COMMENT '扩展属性 JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='预约资源扩展画像（医师/设备/诊室等 JSON 属性）';
-- ----------------------------
-- Table structure for bkg_schedule_change_policy
-- ----------------------------
CREATE TABLE `bkg_schedule_change_policy` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识；空=租户默认',
  `on_practitioner_stop_mode` VARCHAR(32) NOT NULL DEFAULT 'MANUAL' COMMENT '停诊默认处置：TRANSFER / RESCHEDULE / CANCEL / MANUAL',
  `transfer_match_rule` VARCHAR(32) NOT NULL DEFAULT 'SAME_SERVICE_SAME_SLOT' COMMENT '转交匹配规则',
  `transfer_require_same_service` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '转交是否要求同号源类型',
  `transfer_allow_cross_practitioner` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否允许跨医师转交',
  `transfer_patient_confirm_mode` VARCHAR(32) NOT NULL DEFAULT 'NONE' COMMENT '转交患者确认：NONE / SMS_CONFIRM / WINDOW_CONFIRM',
  `block_deactivate_if_unhandled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '存在未处置预约时禁止完成停诊',
  `notify_on_transfer` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '转交后是否通知患者',
  `notify_on_cancel_stop` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '停诊取消预约时是否通知',
  `freeze_source_slot_on_preview` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '停诊预览后冻结源号源，防并发新约',
  `freeze_ttl_minutes` INT NOT NULL DEFAULT 15 COMMENT '冻结超时分钟数（TTL 自动释放）',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='停诊与预约处置院点策略（07 §4.2）';
-- ----------------------------
-- Table structure for bkg_schedule_template
-- ----------------------------
CREATE TABLE `bkg_schedule_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构/科室；空=全院',
  `template_code` VARCHAR(64) NOT NULL COMMENT '模板编码',
  `template_name` VARCHAR(128) NOT NULL COMMENT '模板名称',
  `schedule_mode` VARCHAR(16) NOT NULL DEFAULT 'MODE-A' COMMENT '排班模式：MODE-A / MODE-B / MODE-C',
  `practitioner_id` VARCHAR(64) COMMENT '默认医师主键（可选）',
  `location_id` VARCHAR(64) COMMENT '默认诊室主键（可选）',
  `healthcare_service_id` VARCHAR(64) COMMENT '号源类型主键',
  `slot_provision_template_id` VARCHAR(64) COMMENT '关联 T1 放号时段模板',
  `default_release_policy_id` VARCHAR(64) COMMENT '默认放号策略主键',
  `effective_start` DATE COMMENT '生效日期起',
  `effective_end` DATE COMMENT '生效日期止',
  `priority` INT NOT NULL DEFAULT 0 COMMENT '匹配优先级（数值越大越优先）',
  `source_practitioner_role_id` VARCHAR(64) COMMENT '来源岗位主键（导入追溯）',
  `enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='T2 排班日模板（07 §5.3）';
-- ----------------------------
-- Table structure for bkg_slot_provision_template
-- ----------------------------
CREATE TABLE `bkg_slot_provision_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构/科室；空=全院',
  `template_code` VARCHAR(64) NOT NULL COMMENT '模板编码',
  `template_name` VARCHAR(128) NOT NULL COMMENT '模板名称',
  `slot_templates_json` TEXT NOT NULL COMMENT '时段 JSON：[{startTime,endTime,capacity}]',
  `enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='T1 放号时段模板（07 §5.2）';
-- ----------------------------
-- Table structure for bkg_stop_clinic_slot_freeze
-- ----------------------------
CREATE TABLE `bkg_stop_clinic_slot_freeze` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `schedule_id` VARCHAR(64) NOT NULL COMMENT '被停诊日程主键',
  `slot_id` VARCHAR(64) NOT NULL COMMENT '被冻结的源号源主键',
  `expires_at` DATETIME(6) NOT NULL COMMENT '冻结过期时间（TTL 自动释放）',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='停诊预览期间源号源冻结（防并发新约）';
-- ----------------------------
-- Table structure for bkg_waitlist_entry
-- ----------------------------
CREATE TABLE `bkg_waitlist_entry` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者主键',
  `slot_id` VARCHAR(64) NOT NULL COMMENT '候补号源主键',
  `schedule_id` VARCHAR(64) NOT NULL COMMENT '所属日程主键',
  `queue_position` INT NOT NULL COMMENT '同 时段 下排队序号，从 1 递增',
  `status` VARCHAR(32) NOT NULL DEFAULT 'WAITING' COMMENT '状态',
  `promoted_appointment_id` VARCHAR(64) COMMENT '提升为正式预约后关联 预约Id',
  `cancel_reason` VARCHAR(255) COMMENT '取消原因',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='号源候补队列：满号时不占 时段，释放后按序号提升';
-- ----------------------------
-- Table structure for bkg_week_schedule_template
-- ----------------------------
CREATE TABLE `bkg_week_schedule_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构/科室；空=全院',
  `template_code` VARCHAR(64) NOT NULL COMMENT '模板编码',
  `template_name` VARCHAR(128) NOT NULL COMMENT '模板名称',
  `fallback_bookable` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '无 排班 时模板态是否允许预约（虚拟可约）',
  `is_default` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '科室默认周模板（同科室仅一条 is_默认=true）',
  `enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `effective_start` DATE COMMENT '生效日期起',
  `effective_end` DATE COMMENT '生效日期止',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='TW 周排班模板（07 §5.3b / §5.7）';
-- ----------------------------
-- Table structure for bkg_week_schedule_template_item
-- ----------------------------
CREATE TABLE `bkg_week_schedule_template_item` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `week_schedule_template_id` VARCHAR(64) NOT NULL COMMENT '所属 TW 主键',
  `weekday` INT NOT NULL COMMENT '星期：1=周一 … 7=周日（ISO）',
  `day_schedule_template_id` VARCHAR(64) NOT NULL COMMENT '关联 bkg_排班_template（T2）',
  `sort_no` INT NOT NULL DEFAULT 0 COMMENT '同 星期 多行时的排序',
  `enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='TW 明细：星期 → T2 日模板';
-- ----------------------------
-- Table structure for cln_allergy_intolerance
-- ----------------------------
CREATE TABLE `cln_allergy_intolerance` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `request_id` VARCHAR(64) NOT NULL COMMENT '申请标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `medication_id` VARCHAR(64) COMMENT '药品标识',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `clinical_status_enum` VARCHAR(255) NOT NULL COMMENT 'clinical状态枚举值',
  `verification_status_enum` VARCHAR(255) NOT NULL COMMENT 'verification状态枚举值',
  `type_enum` VARCHAR(255) COMMENT '类型枚举值',
  `category_code` VARCHAR(255) COMMENT 'category编码',
  `criticality_enum` VARCHAR(255) COMMENT 'criticality枚举值',
  `code` VARCHAR(255) COMMENT '编码',
  `description` VARCHAR(255) COMMENT '描述',
  `severity_enum` VARCHAR(255) COMMENT 'severity枚举值',
  `onset_date_time` DATETIME(6) COMMENT 'onset日期时间',
  `recorded_date` DATETIME(6) COMMENT '记录日期',
  `last_reaction_occurrence` DATETIME(6) COMMENT '末次反应发生时间',
  `exposure_route` VARCHAR(255) COMMENT '暴露途径',
  `practitioner_id` VARCHAR(64) COMMENT '医护人员标识',
  `check_practitioner_id` VARCHAR(64) COMMENT 'check医护人员标识',
  `note` VARCHAR(255) COMMENT '备注说明'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床 过敏不耐受';
-- ----------------------------
-- Table structure for cln_condition
-- ----------------------------
CREATE TABLE `cln_condition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `verification_status_enum` VARCHAR(255) COMMENT 'verification状态枚举值',
  `clinical_status_enum` VARCHAR(255) COMMENT 'clinical状态枚举值',
  `category_enum` VARCHAR(255) COMMENT 'category枚举值',
  `severity_enum` VARCHAR(255) COMMENT 'severity枚举值',
  `bus_no` VARCHAR(255) COMMENT '业务编号',
  `body_site_json` VARCHAR(255) COMMENT '身体siteJSON',
  `body_structure_id` VARCHAR(64) COMMENT '身体结构标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `description` VARCHAR(255) COMMENT '描述',
  `onset_datetime` DATETIME(6) COMMENT '发病时间',
  `onset_age` INT COMMENT '发病年龄',
  `onset_text` VARCHAR(255) COMMENT 'onset文本',
  `abatement_datetime` DATETIME(6) COMMENT '缓解时间',
  `abatement_age` INT COMMENT '缓解年龄',
  `abatement_string` VARCHAR(255) COMMENT '缓解描述',
  `recorded_datetime` DATETIME(6) COMMENT '记录datetime',
  `recorder_id` VARCHAR(64) COMMENT '记录人标识',
  `stage_summary_text` VARCHAR(255) COMMENT 'stagesummary文本',
  `evidence` VARCHAR(255) COMMENT '临床证据',
  `yb_no` VARCHAR(255) COMMENT '医保编号',
  `definition_id` VARCHAR(64) COMMENT '定义标识',
  `tcm_flag` TINYINT(1) COMMENT 'tcm标志位',
  `encounter_id` VARCHAR(64) COMMENT '诊断记录聚合根'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床 病情';
-- ----------------------------
-- Table structure for cln_condition_definition
-- ----------------------------
CREATE TABLE `cln_condition_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `source_enum` VARCHAR(255) NOT NULL COMMENT '来源枚举值',
  `condition_code` VARCHAR(255) NOT NULL COMMENT '病情编码',
  `name` VARCHAR(255) NOT NULL COMMENT '名称',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `type_code` VARCHAR(255) COMMENT '类型编码',
  `description` VARCHAR(255) COMMENT '描述',
  `yb_flag` TINYINT(1) COMMENT '医保标志位',
  `disease_code` VARCHAR(255) COMMENT 'disease编码',
  `yb_no` VARCHAR(255) COMMENT '医保编号',
  `yb_match_flag` TINYINT(1) COMMENT '医保match标志位',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床 病情定义';
-- ----------------------------
-- Table structure for cln_diagnostic_report
-- ----------------------------
CREATE TABLE `cln_diagnostic_report` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `status_enum` VARCHAR(64) NOT NULL DEFAULT 'preliminary' COMMENT '状态枚举',
  `summary_text` TEXT COMMENT '摘要文本',
  `conclusion_text` TEXT COMMENT '结论文本',
  `result_refs_json` TEXT COMMENT '结果引用 JSON',
  `pdf_storage_key` VARCHAR(512) COMMENT 'PDF 存储键',
  `finalized_at` DATETIME(6) COMMENT '定稿时间',
  `finalized_by` VARCHAR(64) COMMENT '定稿人标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='PEIS/临床总检 DiagnosticReport 事实（非 LIS/PACS 报告）';
-- ----------------------------
-- Table structure for cln_diagnostic_report_index
-- ----------------------------
CREATE TABLE `cln_diagnostic_report_index` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `module_enum` VARCHAR(32) NOT NULL COMMENT '来源模块枚举',
  `source_report_id` VARCHAR(64) NOT NULL COMMENT '源报告标识',
  `encounter_id` VARCHAR(64) COMMENT '就诊标识',
  `service_request_id` VARCHAR(64) COMMENT '服务请求标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `status_enum` VARCHAR(64) NOT NULL COMMENT '状态枚举',
  `published_at` DATETIME(6) COMMENT '发布时间',
  `title` VARCHAR(512) COMMENT '报告标题',
  `category_code` VARCHAR(64) COMMENT '分类编码',
  `pdf_storage_key` VARCHAR(512) COMMENT 'PDF 存储键',
  `external_view_url` VARCHAR(1024) COMMENT '外部查看 URL',
  `amended_from_id` VARCHAR(64) COMMENT '修正来源报告标识',
  `unique_key` VARCHAR(255) NOT NULL COMMENT '唯一索引键'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='多模块 DiagnosticReport 读侧索引';
-- ----------------------------
-- Table structure for cln_observation
-- ----------------------------
CREATE TABLE `cln_observation` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `service_request_id` VARCHAR(64) COMMENT '服务请求标识',
  `definition_id` VARCHAR(64) NOT NULL COMMENT '观察项定义标识',
  `code` VARCHAR(255) COMMENT '观察项编码',
  `value_quantity` DECIMAL(18,6) COMMENT '数值结果',
  `value_string` TEXT COMMENT '文本结果',
  `value_codeable_concept` VARCHAR(512) COMMENT '编码概念结果',
  `interpretation_code` VARCHAR(64) COMMENT '解读编码',
  `status_enum` VARCHAR(64) NOT NULL COMMENT '状态枚举',
  `effective_time` DATETIME(6) COMMENT '有效时间',
  `source_observation_id` VARCHAR(64) COMMENT '来源观察实例标识（LIS 投影时指向 lis_observation.id）',
  `source_module_enum` VARCHAR(32) COMMENT '来源模块枚举',
  `performer_id` VARCHAR(64) COMMENT '执行人标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床观察实例（体检小项/分科结论/LIS 投影）';
-- ----------------------------
-- Table structure for cln_observation_definition
-- ----------------------------
CREATE TABLE `cln_observation_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `code` VARCHAR(255) NOT NULL COMMENT '观察项编码',
  `display` VARCHAR(512) NOT NULL COMMENT '展示名称',
  `value_type_enum` VARCHAR(64) NOT NULL COMMENT '值类型枚举',
  `unit_code` VARCHAR(64) COMMENT '单位编码',
  `category_code` VARCHAR(64) NOT NULL COMMENT '分类编码',
  `status_enum` VARCHAR(64) NOT NULL DEFAULT 'active' COMMENT '状态枚举'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床观察项目录（体检小项/分科结论 OD）';
-- ----------------------------
-- Table structure for cln_procedure
-- ----------------------------
CREATE TABLE `cln_procedure` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `request_id` VARCHAR(64) NOT NULL COMMENT '申请标识',
  `request_table` VARCHAR(255) NOT NULL COMMENT '申请table',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `status_reason_text` VARCHAR(255) COMMENT '状态原因文本',
  `category_enum` VARCHAR(255) NOT NULL COMMENT 'category枚举值',
  `procedure_code` VARCHAR(255) COMMENT '处置编码',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `occurrence_time` DATETIME(6) COMMENT 'occurrence时间',
  `occurrence_period` VARCHAR(255) COMMENT '发生时段',
  `occurrence_age` VARCHAR(255) COMMENT '发生年龄',
  `occurrence_text` VARCHAR(255) COMMENT 'occurrence文本',
  `recorded_time` DATETIME(6) COMMENT '记录时间',
  `recorder_id` VARCHAR(64) COMMENT '记录人标识',
  `report_flag` TINYINT(1) COMMENT '报表标志位',
  `reported_patient_id` VARCHAR(64) COMMENT 'reported患者标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `reason_text` VARCHAR(255) COMMENT '原因文本',
  `body_site_json` VARCHAR(255) COMMENT '身体siteJSON',
  `body_structure_id` VARCHAR(64) COMMENT '身体结构标识',
  `result_text` VARCHAR(255) COMMENT 'result文本',
  `report_json` VARCHAR(255) COMMENT '报表JSON',
  `complication_json` VARCHAR(255) COMMENT '并发症JSON',
  `follow_up_json` VARCHAR(255) COMMENT '随访JSON',
  `group_id` VARCHAR(64) COMMENT '分组标识',
  `refund_id` VARCHAR(64) COMMENT 'refund标识',
  `occurrence_slot_active` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '计划点占用标记；CANCEL 对冲后释放，允许同 occurrence 再执行'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床 手术/操作';
-- ----------------------------
-- Table structure for cln_procedure_performer
-- ----------------------------
CREATE TABLE `cln_procedure_performer` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `procedure_id` VARCHAR(64) NOT NULL COMMENT '处置标识',
  `function_code` VARCHAR(255) COMMENT 'function编码',
  `start_time` DATETIME(6) NOT NULL COMMENT '开始时间',
  `end_time` DATETIME(6) COMMENT '结束时间',
  `practitioner_id` VARCHAR(64) NOT NULL COMMENT '医护人员标识',
  `org_from_id` VARCHAR(255) COMMENT 'orgfrom标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='临床 操作执行者';
-- ----------------------------
-- Table structure for cus_activity_execution_location
-- ----------------------------
CREATE TABLE `cus_activity_execution_location` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `activity_definition_id` VARCHAR(64) COMMENT '执行科室规则聚合根',
  `activity_category_code` VARCHAR(255) NOT NULL COMMENT '活动类别编码',
  `execution_org_id` VARCHAR(64) NOT NULL COMMENT '执行科室标识',
  `execution_location_id` VARCHAR(64) COMMENT '执行位置标识',
  `start_time` time(6) COMMENT '生效开始时间',
  `end_time` time(6) COMMENT '生效结束时间',
  `priority` INT NOT NULL COMMENT '优先级（数值越小越优先，1 最优先；与取药科室一致）',
  `display_order` INT COMMENT '展示顺序',
  `remark` VARCHAR(255) COMMENT '备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 活动执行地点';
-- ----------------------------
-- Table structure for cus_activity_observation_link
-- ----------------------------
CREATE TABLE `cus_activity_observation_link` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `activity_definition_id` VARCHAR(64) NOT NULL COMMENT '活动定义标识',
  `observation_definition_id` VARCHAR(64) NOT NULL COMMENT '观察项定义标识',
  `sort_num` INT NOT NULL DEFAULT 0 COMMENT '排序号',
  `required_flag` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否必填'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='体检项目 AD ↔ 小项 OD 绑定';
-- ----------------------------
-- Table structure for cus_charge_item_auto_gen
-- ----------------------------
CREATE TABLE `cus_charge_item_auto_gen` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `rule_name` VARCHAR(255) NOT NULL COMMENT '收费明细自动生成规则聚合根',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举（发布状态）',
  `trigger_source_table` VARCHAR(255) NOT NULL COMMENT '触发来源表名（落库字符串须与来源聚合主表表名一致）',
  `trigger_source_id` VARCHAR(64) NOT NULL COMMENT '触发来源主键',
  `charge_definition_id` VARCHAR(64) NOT NULL COMMENT '收费项定价标识（adm_charge_item_定义.id）',
  `performing_org_id` VARCHAR(64) COMMENT '执行科室标识（为空表示全局规则）',
  `quantity_value` DECIMAL(18,2) NOT NULL COMMENT '默认数量（大于 0）',
  `priority` INT NOT NULL COMMENT '优先级（数值越小越靠前）',
  `remark` VARCHAR(255) COMMENT '备注',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '住院就诊标识（adm_就诊.id）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 收费项目自动生成';
-- ----------------------------
-- Table structure for cus_condition_template
-- ----------------------------
CREATE TABLE `cus_condition_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `object_id` VARCHAR(64) NOT NULL COMMENT '诊断常用模板聚合根',
  `definition_id` VARCHAR(64) NOT NULL COMMENT '诊断定义标识',
  `binding_enum` VARCHAR(255) NOT NULL COMMENT '绑定类型枚举',
  `sort_weight` INT COMMENT '排序权重',
  `remark` VARCHAR(255) COMMENT '备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 病情模板';
-- ----------------------------
-- Table structure for cus_encounter_history
-- ----------------------------
CREATE TABLE `cus_encounter_history` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(255) NOT NULL COMMENT '就诊历史里程碑聚合根',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `request_id` VARCHAR(64) COMMENT '请求标识（如 ServiceRequest）',
  `request_table_name` VARCHAR(255) COMMENT '请求表名（与 requestId 成对出现）',
  `original_organization_id` VARCHAR(64) COMMENT '原科室标识',
  `target_organization_id` VARCHAR(64) COMMENT '目标科室标识',
  `original_location_id` VARCHAR(64) COMMENT '原位置标识（病区/床位等）',
  `target_location_id` VARCHAR(64) COMMENT '目标位置标识（病区/床位等）',
  `out_way_code` VARCHAR(255) COMMENT '出院方式编码（仅离院类里程碑使用）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 就诊历史';
-- ----------------------------
-- Table structure for cus_frequency
-- ----------------------------
CREATE TABLE `cus_frequency` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `rate_code` VARCHAR(255) COMMENT '频次聚合根实体',
  `name` VARCHAR(255) NOT NULL COMMENT '频次名称',
  `cycle_type` VARCHAR(32) NOT NULL COMMENT '周期类型（{ com.openhis.health.domain.share.enums.FrequencyCycleType#getCode()}）',
  `day_count` INT COMMENT '日计数',
  `day_interval` INT COMMENT '日间隔',
  `day_times` VARCHAR(255) COMMENT '日执行时点串',
  `week_cycle_flag` TINYINT(1) COMMENT '周周期标记',
  `total_execution_count` INT COMMENT '总执行次数',
  `execution_period` INT COMMENT '执行周期',
  `execution_period_unit` VARCHAR(255) COMMENT '执行周期单位',
  `applicable_scenes` VARCHAR(255) COMMENT '适用场景',
  `allow_cross_day` VARCHAR(32) COMMENT '允许跨日（{ com.openhis.health.domain.share.enums.FrequencyAllowCrossDay#getCode()}）',
  `active_flag` TINYINT(1) NOT NULL COMMENT '启用标记',
  `sort_no` INT COMMENT '排序号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 频次';
-- ----------------------------
-- Table structure for cus_order_template
-- ----------------------------
CREATE TABLE `cus_order_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `object_id` VARCHAR(64) NOT NULL COMMENT '组套模板头聚合根',
  `binding_enum` VARCHAR(255) NOT NULL COMMENT '绑定类型（个人/科室/全院）',
  `scene_enum` VARCHAR(255) NOT NULL COMMENT '适用场景（门诊/住院/通用）',
  `template_code` VARCHAR(255) COMMENT '模板编码（可空，非空时建议唯一）',
  `name` VARCHAR(255) NOT NULL COMMENT '模板名称',
  `description` VARCHAR(255) COMMENT '描述',
  `sort_weight` INT COMMENT '列表排序权重（同层级内升序；数值越小越靠前）',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态（草稿/启用/停用）',
  `remark` VARCHAR(255) COMMENT '备注',
  `template_kind_enum` VARCHAR(255) NOT NULL DEFAULT 'GENERAL' COMMENT '组套种类（GENERAL/TCM/PRICING）',
  `default_chinese_herbs_dose_quantity` DECIMAL(18,2) COMMENT 'TCM 组套默认中药付数',
  `default_suffering_flag` TINYINT(1) COMMENT 'TCM 组套默认代煎标志',
  `template_source_enum` VARCHAR(255) NOT NULL DEFAULT 'MAINTAINED' COMMENT '模板来源（MAINTAINED=维护组套，FROM_ADVICE=医嘱模板/开嘱另存）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 医嘱模板';
-- ----------------------------
-- Table structure for cus_order_template_line
-- ----------------------------
CREATE TABLE `cus_order_template_line` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `order_template_id` VARCHAR(64) NOT NULL COMMENT 'order模板标识',
  `line_kind_enum` VARCHAR(255) NOT NULL COMMENT 'linekind枚举值',
  `medication_definition_id` VARCHAR(64) COMMENT '药品定义标识',
  `activity_definition_id` VARCHAR(64) COMMENT '活动定义标识',
  `device_definition_id` VARCHAR(64) COMMENT '设备定义标识',
  `group_key` VARCHAR(255) COMMENT '分组key',
  `sort_order` INT NOT NULL COMMENT '排序号',
  `default_quantity` DECIMAL(18,2) COMMENT '默认数量',
  `default_unit_code` VARCHAR(255) COMMENT '默认单元编码',
  `default_days` INT COMMENT '默认天数',
  `frequency_id` VARCHAR(64) COMMENT '频次标识',
  `route_code` VARCHAR(255) COMMENT 'route编码',
  `dosage_text` VARCHAR(255) COMMENT 'dosage文本',
  `default_perform_org_id` VARCHAR(64) COMMENT '默认performorg标识',
  `line_remark` VARCHAR(255) COMMENT '行备注',
  `chinese_herbs_dose_quantity` DECIMAL(18,2) COMMENT '组套模板行（聚合内子实体）',
  `suffering_flag` TINYINT(1) COMMENT 'TCM 行级代煎标志'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 医嘱模板行';
-- ----------------------------
-- Table structure for cus_price_adjustment
-- ----------------------------
CREATE TABLE `cus_price_adjustment` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '调价单号',
  `item_table` VARCHAR(255) NOT NULL COMMENT '项目物理表（药品/耗材定义表）',
  `item_id` VARCHAR(64) NOT NULL COMMENT '项目定义主键',
  `new_purchase_amount` DECIMAL(19,6) COMMENT '目标进价（可空表示不调进价）',
  `new_selling_amount` DECIMAL(19,6) COMMENT '目标售价（可空表示不调售价）',
  `adjustment_reason` VARCHAR(255) NOT NULL COMMENT '调价原因',
  `adjustment_time` DATETIME(6) NOT NULL COMMENT '调价时间',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `submitter_id` VARCHAR(64) COMMENT 'submitter标识',
  `submit_time` DATETIME(6) COMMENT 'submit时间',
  `approver_id` VARCHAR(64) COMMENT 'approver标识',
  `approve_time` DATETIME(6) COMMENT 'approve时间',
  `approve_comment` VARCHAR(255) COMMENT '审批意见',
  `operator_id` VARCHAR(64) NOT NULL COMMENT '操作人标识',
  `org_id` VARCHAR(64) NOT NULL COMMENT '机构标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='调价单项目行（同 bus_no 多行）';
-- ----------------------------
-- Table structure for cus_price_adjustment_detail
-- ----------------------------
CREATE TABLE `cus_price_adjustment_detail` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `adjustment_id` VARCHAR(64) NOT NULL COMMENT '调价项目行主键',
  `lot_number` VARCHAR(255) NOT NULL COMMENT '批号',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '提交时刻影响数量（拆零）',
  `old_purchase_amount` DECIMAL(19,6) COMMENT '调前进价',
  `old_selling_amount` DECIMAL(19,6) COMMENT '调前售价',
  `purchase_impact` DECIMAL(19,6) COMMENT '进价盈亏',
  `selling_impact` DECIMAL(19,6) COMMENT '售价盈亏'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='调价批号明细（提交时快照盈亏）';
-- ----------------------------
-- Table structure for cus_service_device_template
-- ----------------------------
CREATE TABLE `cus_service_device_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `range_code` VARCHAR(255) NOT NULL COMMENT '诊疗耗材绑定聚合根',
  `type_code` VARCHAR(255) NOT NULL COMMENT '绑定类型编码（1 用法/2 诊疗/3 号源）',
  `item_table` VARCHAR(255) NOT NULL COMMENT '来源表名',
  `item_id` VARCHAR(255) NOT NULL COMMENT '来源项标识（跨表主键类型不一，持久化为 String）',
  `dev_act_table` VARCHAR(255) NOT NULL COMMENT '目标表名（诊疗定义表或耗材定义表）',
  `dev_act_id` VARCHAR(64) NOT NULL COMMENT '目标项标识（诊疗或耗材定义主键）',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '绑定数量（> 0）',
  `unit_code` VARCHAR(255) NOT NULL COMMENT '单位编码',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '发布状态（active/retired）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 服务设备模板';
-- ----------------------------
-- Table structure for cus_service_location_template
-- ----------------------------
CREATE TABLE `cus_service_location_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `item_table` VARCHAR(255) NOT NULL COMMENT '项table',
  `distribution_category_code` VARCHAR(255) NOT NULL COMMENT 'distributioncategory编码',
  `def_location_id` VARCHAR(64) NOT NULL COMMENT 'def位置标识',
  `item_definition_id` VARCHAR(64) COMMENT '项定义标识',
  `method_code` VARCHAR(255) COMMENT 'method编码',
  `start_time` time(6) COMMENT '开始时间',
  `end_time` time(6) COMMENT '结束时间',
  `priority` INT NOT NULL COMMENT '优先级',
  `display_order` INT COMMENT '显示顺序',
  `remark` VARCHAR(255) COMMENT '备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 服务地点模板';
-- ----------------------------
-- Table structure for cus_supplier
-- ----------------------------
CREATE TABLE `cus_supplier` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '业务编号',
  `name` VARCHAR(255) NOT NULL COMMENT '名称',
  `type_enum` VARCHAR(255) NOT NULL COMMENT '类型枚举值',
  `credit_code` VARCHAR(255) NOT NULL COMMENT 'credit编码',
  `legal_representative` VARCHAR(255) COMMENT '法定代表人',
  `address` VARCHAR(255) COMMENT '地址',
  `py_str` VARCHAR(255) NOT NULL COMMENT '拼音码',
  `wb_str` VARCHAR(255) NOT NULL COMMENT '五笔码',
  `phone` VARCHAR(255) COMMENT '电话',
  `email` VARCHAR(255) COMMENT '邮箱',
  `bank_name` VARCHAR(255) COMMENT 'bank名称',
  `bank_account` VARCHAR(255) COMMENT 'bank账户',
  `org_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `display_order` INT COMMENT '显示顺序',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `note` VARCHAR(255) COMMENT '备注说明'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 供应商';
-- ----------------------------
-- Table structure for cus_terminology_code_mapping
-- ----------------------------
CREATE TABLE `cus_terminology_code_mapping` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `source_item_table` VARCHAR(255) NOT NULL COMMENT '来源项table',
  `source_item_no` VARCHAR(255) NOT NULL COMMENT '来源项编号',
  `target_item_no` VARCHAR(255) NOT NULL COMMENT 'target项编号',
  `target_name` VARCHAR(255) COMMENT 'target名称',
  `active_flag` TINYINT(1) NOT NULL COMMENT '是否启用'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 术语编码映射';
-- ----------------------------
-- Table structure for cus_trace_number_record
-- ----------------------------
CREATE TABLE `cus_trace_number_record` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `item_table` VARCHAR(255) NOT NULL COMMENT '项table',
  `item_id` VARCHAR(64) NOT NULL COMMENT '项标识',
  `location_type_enum` VARCHAR(255) NOT NULL COMMENT '位置类型枚举值',
  `location_id` VARCHAR(64) NOT NULL COMMENT '位置/科室标识',
  `location_store_id` VARCHAR(64) COMMENT '位置store标识',
  `lot_number` VARCHAR(255) NOT NULL COMMENT '批号',
  `trace_no` TEXT NOT NULL COMMENT '追踪编号',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `unit_code` VARCHAR(255) COMMENT '单元编码',
  `operation_type` VARCHAR(64) NOT NULL COMMENT '追溯码记录聚合根',
  `bus_no` VARCHAR(255) COMMENT '业务编号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='自定义 追踪编号记录';
-- ----------------------------
-- Table structure for dia_body_structure
-- ----------------------------
CREATE TABLE `dia_body_structure` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '业务编号',
  `name` VARCHAR(255) NOT NULL COMMENT '名称',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `parent_id` VARCHAR(64) COMMENT 'parent标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='诊断 身体结构';
-- ----------------------------
-- Table structure for dia_vital_sign
-- ----------------------------
CREATE TABLE `dia_vital_sign` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `recorded_at` DATETIME(6) NOT NULL COMMENT '记录时间',
  `type_enum` VARCHAR(50) NOT NULL COMMENT '单据类型：TEMPERATURE_SHEET / NURSING_RECORD',
  `bus_no` VARCHAR(100) NOT NULL COMMENT '业务单号，租户内唯一',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `baby_no` INT COMMENT '婴儿编号',
  `recorder_id` VARCHAR(64) COMMENT '记录人标识',
  `remark` VARCHAR(500) COMMENT '备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='生命体征/护理测量单据主表（DM-DIA-002 v2.1）';
-- ----------------------------
-- Table structure for dia_vital_sign_detail
-- ----------------------------
CREATE TABLE `dia_vital_sign_detail` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `vital_sign_id` VARCHAR(64) NOT NULL COMMENT '生命体征体征标识',
  `term_code` VARCHAR(100) NOT NULL COMMENT '术语体系 code（如 vital_signs_code）',
  `item_code` VARCHAR(100) NOT NULL COMMENT '字典项 code',
  `item_value` VARCHAR(500) NOT NULL COMMENT '字典项值',
  `units` VARCHAR(100) COMMENT '单位',
  `remark` VARCHAR(500) COMMENT '明细备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='生命体征/护理测量明细（通用字典项行）';
-- ----------------------------
-- Table structure for doc_inventory_item_snapshot
-- ----------------------------
CREATE TABLE `doc_inventory_item_snapshot` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `bus_no` VARCHAR(32) NOT NULL COMMENT '批次单号（ABU+yyyyMMdd+2位序号）',
  `snapshot_time` DATETIME(6) NOT NULL COMMENT '快照时刻',
  `inventory_item_id` VARCHAR(64) NOT NULL COMMENT '源库存项标识（写入时刻 wkf_inventory_item.id）',
  `item_table` VARCHAR(64) NOT NULL COMMENT '物品定义表名',
  `item_id` VARCHAR(64) NOT NULL COMMENT '物品定义标识',
  `charge_item_definition_id` VARCHAR(64) COMMENT '收费项定义标识',
  `warehouse_id` VARCHAR(64) NOT NULL COMMENT '库房标识（不含货位）',
  `supplier_id` VARCHAR(64) NOT NULL COMMENT '供应商标识',
  `product_bus_no` VARCHAR(64) COMMENT '项目编码',
  `name` VARCHAR(255) NOT NULL COMMENT '项目名称',
  `merchandise_name` VARCHAR(255) COMMENT '商品名称',
  `total_volume` VARCHAR(255) COMMENT '规格',
  `manufacturer` VARCHAR(255) COMMENT '厂家/产地',
  `approval_number` VARCHAR(128) COMMENT '批准文号',
  `yb_no` VARCHAR(64) COMMENT '医保码',
  `trace_no` TEXT COMMENT '追溯码',
  `py_str` VARCHAR(255) COMMENT '拼音码（备份关键字/排序）',
  `wb_str` VARCHAR(255) COMMENT '五笔码（备份关键字）',
  `lot_number` VARCHAR(255) NOT NULL COMMENT '生产批号',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '账面数量（拆零最小单位）',
  `package_unit_ratio` DECIMAL(18,4) COMMENT '拆零↔包装倍数（1包装=ratio拆零）',
  `package_unit_code` VARCHAR(64) COMMENT '包装单位编码',
  `lot_number_cost_amount` DECIMAL(18,4) COMMENT '批号进价（包装整包）',
  `lot_number_price_amount` DECIMAL(18,4) COMMENT '批号售价（包装整包）',
  `line_cost_total` DECIMAL(18,4) COMMENT '进价行总额（写入时刻冻结）',
  `line_price_total` DECIMAL(18,4) COMMENT '售价行总额（写入时刻冻结）',
  `production_date` DATETIME(6) COMMENT '生产日期',
  `expiration_date` DATETIME(6) COMMENT '效期',
  `remaining_days` INT COMMENT '剩余过期天数（写入时刻冻结）',
  `inventory_status_enum` VARCHAR(32) NOT NULL COMMENT '供应状态（PublicationStatus code）',
  `chrgitm_lv` INT COMMENT '医保等级码',
  `medication_category_code` VARCHAR(64) COMMENT '药品分类编码',
  `device_category_code` VARCHAR(64) COMMENT '耗材分类编码',
  `dose_form_code` VARCHAR(64) COMMENT '剂型编码',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='库存明细快照静表（DM-DOC-001）';
-- ----------------------------
-- Table structure for emr_document
-- ----------------------------
CREATE TABLE `emr_document` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `patient_id` VARCHAR(64) COMMENT '电子病历文书实体',
  `encounter_id` VARCHAR(64) COMMENT '就诊 ID',
  `document_type_code` VARCHAR(32) COMMENT '文书类型编码，如入院记录、病程记录等',
  `title` VARCHAR(256) COMMENT '文档标题',
  `content` TEXT COMMENT '文档正文内容，Tiptap/ProseMirror JSON',
  `status` VARCHAR(32) COMMENT '文档状态：DRAFT / SUBMITTED / LOCKED / ARCHIVED 等',
  `source_template_id` VARCHAR(64) COMMENT '创建文书时使用的模板 ID',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='电子病历 document';
-- ----------------------------
-- Table structure for emr_document_data_item_index
-- ----------------------------
CREATE TABLE `emr_document_data_item_index` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `document_id` VARCHAR(64) NOT NULL COMMENT '文书数据项名索引（可选）',
  `node_type` VARCHAR(16) NOT NULL COMMENT '节点类型：region / section / dataElement',
  `data_item_name` VARCHAR(128) NOT NULL COMMENT '数据项名，对应节点 attrs.name',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='电子病历 document data item index';
-- ----------------------------
-- Table structure for emr_document_type
-- ----------------------------
CREATE TABLE `emr_document_type` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `code` VARCHAR(32) NOT NULL COMMENT '文书类型配置',
  `name` VARCHAR(64) NOT NULL COMMENT '文书类型名称',
  `default_template_id` VARCHAR(64) COMMENT '默认模板 ID',
  `is_enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `sort_order` INT COMMENT '排序',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='电子病历 document type';
-- ----------------------------
-- Table structure for emr_document_version
-- ----------------------------
CREATE TABLE `emr_document_version` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `document_id` VARCHAR(64) NOT NULL COMMENT '文书版本快照',
  `version_number` INT NOT NULL COMMENT '版本号，同一文书内递增',
  `content` TEXT NOT NULL COMMENT '版本内容 JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='电子病历 document version';
-- ----------------------------
-- Table structure for emr_metadata_field_def
-- ----------------------------
CREATE TABLE `emr_metadata_field_def` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `field_key` VARCHAR(64) NOT NULL COMMENT '字段key',
  `label` VARCHAR(128) NOT NULL COMMENT '显示标签',
  `data_type` VARCHAR(16) NOT NULL DEFAULT 'string' COMMENT 'data类型',
  `editable_default` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '默认可编辑',
  `value_source` VARCHAR(32) NOT NULL COMMENT 'value来源',
  `source_path` VARCHAR(256) COMMENT '来源path',
  `source_config` TEXT COMMENT '来源config',
  `default_value` VARCHAR(512) COMMENT '默认值',
  `mask_rule` VARCHAR(32) NOT NULL DEFAULT 'NONE' COMMENT '脱敏规则',
  `format_pattern` VARCHAR(64) COMMENT '格式模式',
  `sort_order` INT NOT NULL DEFAULT 0 COMMENT '排序号',
  `is_enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `remark` VARCHAR(512) COMMENT '备注',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='电子病历 metadata field def';
-- ----------------------------
-- Table structure for emr_template
-- ----------------------------
CREATE TABLE `emr_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `name` VARCHAR(128) COMMENT '电子病历模板实体',
  `code` VARCHAR(64) COMMENT '模板编码，唯一',
  `document_type_code` VARCHAR(32) COMMENT '关联文书类型编码',
  `organization_id` VARCHAR(64) COMMENT '适用科室 ID（机构Id）；scope_level=DEPARTMENT 时必填',
  `encounter_class_enum` INT COMMENT '适用就诊类型（遗留整型字段，新数据请用 就诊_class_code）',
  `encounter_type_enum` INT COMMENT '适用就诊子类型（Encounter.typeEnum 等），如普通门诊/专家门诊等',
  `content` TEXT COMMENT '模板内容 JSON',
  `is_enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `scope_level` VARCHAR(16) NOT NULL DEFAULT 'HOSPITAL' COMMENT '使用范围：PERSONAL / DEPARTMENT / HOSPITAL',
  `owner_practitioner_id` VARCHAR(64) COMMENT '个人模板所有者（医务人员 ID）；scope_level=PERSONAL 时必填',
  `encounter_class_code` VARCHAR(16) COMMENT '适用就诊类别（与 health EncounterClass.code 一致）：AMB / IMP / OBSENC 等',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='电子病历 template';
-- ----------------------------
-- Table structure for fin_cashier_settlement
-- ----------------------------
CREATE TABLE `fin_cashier_settlement` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(64) NOT NULL COMMENT '交账单号',
  `type_enum` VARCHAR(32) NOT NULL COMMENT '类型枚举值',
  `status_enum` VARCHAR(32) NOT NULL COMMENT 'HANDED_OVER（已交账）',
  `settled_at` DATETIME(6) NOT NULL COMMENT '交账提交时刻',
  `org_id` VARCHAR(64) NOT NULL COMMENT '交账所属科室',
  `location_id` VARCHAR(64) COMMENT '收费窗口（可选）',
  `cashier_id` VARCHAR(64) NOT NULL COMMENT '交账经办人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='收费员交账头表（只增不改）';
-- ----------------------------
-- Table structure for fin_contract
-- ----------------------------
CREATE TABLE `fin_contract` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '费用性质聚合根',
  `name` VARCHAR(255) NOT NULL COMMENT '名称',
  `category_enum` VARCHAR(255) NOT NULL COMMENT 'category枚举值',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `active_flag` TINYINT(1) NOT NULL COMMENT '是否启用',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `yb_flag` TINYINT(1) COMMENT '医保标志位',
  `display_order` INT COMMENT '显示顺序',
  `adm_vs` VARCHAR(255) COMMENT '院内/历史字段；CHS 统筹区划读 chs-合同.{bus_no}.adm_vs',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `client_id` VARCHAR(255) COMMENT '客户端标识',
  `client_secret` VARCHAR(255) COMMENT '客户端secret',
  `username` VARCHAR(255) COMMENT '用户名',
  `password` VARCHAR(255) COMMENT '密码',
  `cli_prv_key` VARCHAR(255) COMMENT '客户端私钥',
  `cli_pub_key` VARCHAR(255) COMMENT 'cli公钥key',
  `server_pub_key` VARCHAR(255) COMMENT 'server公钥key',
  `scope` VARCHAR(255) COMMENT '授权范围',
  `grant_type` VARCHAR(255) COMMENT '授权类型',
  `fixmedins_code` VARCHAR(255) COMMENT '院内/历史字段；CHS 定点机构编码读 chs-合同.{bus_no}.fixmedins_code',
  `fixmedins_name` VARCHAR(255) COMMENT 'fixmedins名称'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='财务 合同';
-- ----------------------------
-- Table structure for fin_payment_rec_detail
-- ----------------------------
CREATE TABLE `fin_payment_rec_detail` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `reconciliation_id` VARCHAR(64) NOT NULL COMMENT '对账标识',
  `predecessor_id` VARCHAR(64) COMMENT 'predecessor标识',
  `target_enum` VARCHAR(255) COMMENT 'target枚举值',
  `account_id` VARCHAR(64) NOT NULL COMMENT '账户标识',
  `account_code` VARCHAR(255) COMMENT '账户编码',
  `pay_enum` VARCHAR(255) NOT NULL COMMENT '支付枚举值',
  `pay_level_enum` VARCHAR(255) COMMENT '支付level枚举值',
  `amount` DECIMAL(19,6) NOT NULL COMMENT '金额',
  `return_amount` DECIMAL(19,6) COMMENT 'return金额',
  `charge_amount` DECIMAL(19,6) COMMENT '收费金额',
  `pay_trans_no` VARCHAR(255) COMMENT '支付trans编号',
  `pay_trans_text` VARCHAR(255) COMMENT '支付trans文本',
  `pay_trans_date` DATETIME(6) COMMENT '支付trans日期',
  `before_balance` DECIMAL(19,6) COMMENT 'before余额',
  `after_balance` DECIMAL(19,6) COMMENT 'after余额',
  `result_enum` VARCHAR(255) NOT NULL COMMENT 'result枚举值'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='财务 payment rec detail';
-- ----------------------------
-- Table structure for fin_payment_rec_static
-- ----------------------------
CREATE TABLE `fin_payment_rec_static` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `reconciliation_id` VARCHAR(64) NOT NULL COMMENT '对账标识',
  `method_code` VARCHAR(255) NOT NULL COMMENT '支付分类统计快照',
  `type_code` VARCHAR(255) NOT NULL COMMENT '类型编码',
  `type_name` VARCHAR(255) COMMENT '类型名称',
  `amount` DECIMAL(19,6) NOT NULL COMMENT '金额',
  `charge_item_ids` TEXT COMMENT '收费项ids'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='财务 payment rec static';
-- ----------------------------
-- Table structure for fin_payment_reconciliation
-- ----------------------------
CREATE TABLE `fin_payment_reconciliation` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '支付流水聚合根',
  `relation_id` VARCHAR(64) COMMENT 'relation 标识',
  `payment_no` VARCHAR(255) NOT NULL COMMENT 'payment 编号',
  `payment_enum` VARCHAR(255) NOT NULL COMMENT 'payment 枚举值',
  `kind_enum` VARCHAR(255) NOT NULL COMMENT 'kind 枚举值',
  `enterer_id` VARCHAR(64) NOT NULL COMMENT 'enterer 标识',
  `issuer_enum` VARCHAR(255) COMMENT 'issuer 枚举值',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者 标识',
  `practitioner_id` VARCHAR(64) COMMENT 'practitioner 标识',
  `outcome_enum` VARCHAR(255) COMMENT 'outcome 枚举值',
  `location_id` VARCHAR(64) COMMENT '地点 标识',
  `expiration_date` DATETIME(6) COMMENT 'expiration日期',
  `tendered_amount` DECIMAL(19,6) NOT NULL COMMENT 'tendered 金额（元，与库 numeric(19,6) 一致）',
  `returned_amount` DECIMAL(19,6) COMMENT 'returned 金额',
  `display_amount` DECIMAL(19,6) NOT NULL COMMENT 'display 金额',
  `print_count` INT NOT NULL COMMENT 'print 数量',
  `contract_no` VARCHAR(255) COMMENT '合同 编号',
  `charge_item_ids` TEXT NOT NULL COMMENT '收费项ids',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊 标识',
  `bill_date` DATETIME(6) COMMENT 'bill日期',
  `invoice_id` VARCHAR(64) COMMENT '发票 标识',
  `account_id` VARCHAR(64) COMMENT '账号 标识',
  `yb_clear_flag` TINYINT(1) COMMENT 'ybClear 标志位',
  `cashier_settlement_id` VARCHAR(64) COMMENT '收费员交账头 ID；非空表示已交账'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='财务 payment reconciliation';
-- ----------------------------
-- Table structure for fin_payment_yb_settlement
-- ----------------------------
CREATE TABLE `fin_payment_yb_settlement` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `reconciliation_id` VARCHAR(64) NOT NULL COMMENT '对账标识',
  `setl_id` VARCHAR(30) NOT NULL COMMENT '平台 setl_id',
  `chrg_bchno` VARCHAR(30) COMMENT '收费批次号',
  `mdtrt_id` VARCHAR(30) COMMENT '就诊标识',
  `settlement_record_id` VARCHAR(64) COMMENT 'yb_settlement_record.id（CHS 侧）',
  `account_id` VARCHAR(64) COMMENT '账户标识',
  `status` VARCHAR(16) NOT NULL DEFAULT 'CONFIRMED' COMMENT '状态',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='支付流水关联的医保正式结算凭证（一行一个 setl_id）';
-- ----------------------------
-- Table structure for flyway_schema_history
-- ----------------------------
CREATE TABLE `flyway_schema_history` (
  `installed_rank` INT NOT NULL,
  `version` VARCHAR(50),
  `description` VARCHAR(200) NOT NULL,
  `type` VARCHAR(20) NOT NULL,
  `script` VARCHAR(1000) NOT NULL,
  `checksum` INT,
  `installed_by` VARCHAR(100) NOT NULL,
  `installed_on` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6),
  `execution_time` INT NOT NULL,
  `success` TINYINT(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ----------------------------
-- Table structure for flyway_schema_history_booking
-- ----------------------------
CREATE TABLE `flyway_schema_history_booking` (
  `installed_rank` INT NOT NULL,
  `version` VARCHAR(50),
  `description` VARCHAR(200) NOT NULL,
  `type` VARCHAR(20) NOT NULL,
  `script` VARCHAR(1000) NOT NULL,
  `checksum` INT,
  `installed_by` VARCHAR(100) NOT NULL,
  `installed_on` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6),
  `execution_time` INT NOT NULL,
  `success` TINYINT(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ----------------------------
-- Table structure for flyway_schema_history_chs
-- ----------------------------
CREATE TABLE `flyway_schema_history_chs` (
  `installed_rank` INT NOT NULL,
  `version` VARCHAR(50),
  `description` VARCHAR(200) NOT NULL,
  `type` VARCHAR(20) NOT NULL,
  `script` VARCHAR(1000) NOT NULL,
  `checksum` INT,
  `installed_by` VARCHAR(100) NOT NULL,
  `installed_on` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6),
  `execution_time` INT NOT NULL,
  `success` TINYINT(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ----------------------------
-- Table structure for flyway_schema_history_elep
-- ----------------------------
CREATE TABLE `flyway_schema_history_elep` (
  `installed_rank` INT NOT NULL,
  `version` VARCHAR(50),
  `description` VARCHAR(200) NOT NULL,
  `type` VARCHAR(20) NOT NULL,
  `script` VARCHAR(1000) NOT NULL,
  `checksum` INT,
  `installed_by` VARCHAR(100) NOT NULL,
  `installed_on` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6),
  `execution_time` INT NOT NULL,
  `success` TINYINT(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ----------------------------
-- Table structure for flyway_schema_history_emr
-- ----------------------------
CREATE TABLE `flyway_schema_history_emr` (
  `installed_rank` INT NOT NULL,
  `version` VARCHAR(50),
  `description` VARCHAR(200) NOT NULL,
  `type` VARCHAR(20) NOT NULL,
  `script` VARCHAR(1000) NOT NULL,
  `checksum` INT,
  `installed_by` VARCHAR(100) NOT NULL,
  `installed_on` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6),
  `execution_time` INT NOT NULL,
  `success` TINYINT(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
-- ----------------------------
-- Table structure for inventory_lock
-- ----------------------------
CREATE TABLE `inventory_lock` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `inventory_id` VARCHAR(64) NOT NULL COMMENT '库存锁定记录（DM-WKF-008 §3.2）',
  `lock_flag` TINYINT(1) NOT NULL COMMENT '锁定标识：true 已锁定、false 未锁定',
  `status` VARCHAR(255) NOT NULL COMMENT '锁定状态：见 LockStatus',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '业务单号',
  `order_flag` INT NOT NULL COMMENT '同一业务单内的顺序号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='库存锁定';
-- ----------------------------
-- Table structure for med_medication_definition
-- ----------------------------
CREATE TABLE `med_medication_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '药品定义聚合根',
  `name` VARCHAR(255) NOT NULL COMMENT '药品名称',
  `domain_enum` VARCHAR(255) COMMENT '适用范围编码',
  `med_version` VARCHAR(255) COMMENT '药品版本',
  `name_en` VARCHAR(255) COMMENT '英文药名',
  `py_str` VARCHAR(255) COMMENT '药品名称拼音码',
  `wb_str` VARCHAR(255) COMMENT '药品名称五笔码',
  `category_code` VARCHAR(255) COMMENT '药品分类编码',
  `merchandise_name` VARCHAR(255) COMMENT '商品名称',
  `merchandise_py_str` VARCHAR(255) COMMENT '商品名拼音码',
  `merchandise_wb_str` VARCHAR(255) COMMENT '商品名五笔码',
  `purchase_unit_code` VARCHAR(255) COMMENT '采购单位（5类单位之一）',
  `split_unit_code` VARCHAR(255) COMMENT '拆零单位（5类单位之一）',
  `comprised_text` VARCHAR(255) COMMENT '所含耗材描述',
  `ingredient` VARCHAR(255) COMMENT '成分',
  `dose_from` INT COMMENT '剂量形式编码',
  `approval_number` VARCHAR(255) COMMENT '批准文号',
  `yb_match_flag` TINYINT(1) COMMENT '医保是否已对码',
  `yb_no` VARCHAR(255) COMMENT '医保编码',
  `pharmacology_category_code` VARCHAR(255) COMMENT '药理作用分类编码',
  `skin_test_flag` TINYINT(1) COMMENT '是否皮试药',
  `inject_flag` TINYINT(1) COMMENT '是否注射药物',
  `manufacturer_id` VARCHAR(64) COMMENT '生产厂家标识',
  `manufacturer_text` VARCHAR(255) COMMENT '生产厂商文本',
  `supply_id` VARCHAR(64) COMMENT '供应商标识',
  `restricted_flag` TINYINT(1) COMMENT '是否限制使用',
  `restricted_scope` VARCHAR(255) COMMENT '限制使用范围',
  `active_flag` TINYINT(1) COMMENT '启用标记（true=启用，false=停用）',
  `children_flag` TINYINT(1) COMMENT '儿童用药标志',
  `characteristic` INT COMMENT '产品特性编码',
  `item_min_quantity` DECIMAL(18,2) COMMENT '最小库存警戒数量',
  `item_max_quantity` DECIMAL(18,2) COMMENT '最大库存警戒数量',
  `def_encounter_unit_code` VARCHAR(255) COMMENT '默认门诊单位编码',
  `def_inhospital_unit_code` VARCHAR(255) COMMENT '默认住院单位编码',
  `national_drug_code` VARCHAR(255) COMMENT '国家药品贯标编码',
  `part_attribute_enum` VARCHAR(255) COMMENT '拆分属性编码',
  `antibiotic_code` VARCHAR(255) COMMENT '抗生素分类编码',
  `restricted_enum` VARCHAR(255) COMMENT '权限限制枚举编码',
  `self_flag` TINYINT(1) COMMENT '是否自制',
  `antibiotic_flag` TINYINT(1) COMMENT '是否抗生素',
  `basic_flag` TINYINT(1) COMMENT '是否基药',
  `tho_part_attribute_enum` VARCHAR(255) COMMENT '住院临时医嘱拆分属性编码',
  `chrgitm_lv` INT COMMENT '医保等级',
  `rx_flag` TINYINT(1) COMMENT '处方药标志',
  `dosage_instruction` VARCHAR(255) COMMENT '用药说明',
  `drug69_code` VARCHAR(255) COMMENT '药品 69 码',
  `total_volume` VARCHAR(255) COMMENT '规格',
  `dose_form_code` VARCHAR(255) COMMENT '剂型编码',
  `dose_unit_code` VARCHAR(255) COMMENT '剂量单位（5类单位之一）',
  `package_unit_code` VARCHAR(255) COMMENT '销售单位（5类单位之一）',
  `stock_unit_code` VARCHAR(255) COMMENT '库存单位（5类单位之一）',
  `method_code` VARCHAR(255) COMMENT '默认用法编码',
  `rate_code` VARCHAR(255) COMMENT '默认频次编码',
  `dose` DECIMAL(18,2) COMMENT '单次剂量',
  `max_unit` DECIMAL(18,2) COMMENT '单次最大剂量',
  `usage_limit` DECIMAL(18,2) COMMENT '用量限定',
  `location_id` VARCHAR(64) COMMENT '采购入库位置（他域事实列）',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '生命周期状态编码（DRAFT/ACTIVE/INACTIVE/DISCARDED）',
  `org_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `ingredient_item` VARCHAR(255) COMMENT '成分项',
  `medicationdefinition` VARCHAR(255) COMMENT '药品说明',
  `ddd_code` VARCHAR(255) COMMENT 'DDD（日限定剂量）编码',
  `ddd_unit_code` VARCHAR(255) COMMENT 'DDD（日限定剂量）单位编码',
  `min_rate_code` VARCHAR(255) COMMENT '最小频次编码',
  `max_rate_code` VARCHAR(255) COMMENT '最大频次编码',
  `dose_unit_ratio` DECIMAL(18,6) COMMENT '剂量单位→拆零单位换算倍数（拆零单位为1）',
  `purchase_unit_ratio` DECIMAL(18,6) COMMENT '采购单位→拆零单位换算倍数（拆零单位为1）',
  `stock_unit_ratio` DECIMAL(18,6) COMMENT '库存单位→拆零单位换算倍数（拆零单位为1）',
  `package_unit_ratio` DECIMAL(18,6) COMMENT '销售单位→拆零单位换算倍数（拆零单位为1）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='药品 medication 定义';
-- ----------------------------
-- Table structure for med_medication_dispense
-- ----------------------------
CREATE TABLE `med_medication_dispense` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '药品发放聚合根',
  `status_enum` VARCHAR(255) NOT NULL COMMENT 'status 枚举值',
  `not_performed_reason_enum` VARCHAR(255) COMMENT 'notPerformedReason 枚举值',
  `status_changed_time` DATETIME(6) COMMENT 'statusChanged 时间',
  `dispense_enum` VARCHAR(255) NOT NULL COMMENT 'dispense 枚举值',
  `medication_id` VARCHAR(64) NOT NULL COMMENT 'medication 标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者 标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊 标识',
  `location_id` VARCHAR(64) NOT NULL COMMENT '地点 标识',
  `med_req_id` VARCHAR(64) NOT NULL COMMENT 'medReq 标识',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '数量',
  `unit_code` VARCHAR(255) NOT NULL COMMENT 'unit 代码',
  `dispense_quantity` DECIMAL(18,2) COMMENT '发药数量',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `trace_no` TEXT COMMENT 'trace 编号',
  `preparer_id` VARCHAR(64) COMMENT 'preparer 标识',
  `prepare_time` DATETIME(6) COMMENT 'prepare 时间',
  `practitioner_id` VARCHAR(64) COMMENT 'practitioner 标识',
  `dispense_time` DATETIME(6) COMMENT 'dispense 时间',
  `limit_time` DATETIME(6) COMMENT 'limit 时间',
  `planned_dispense_time` DATETIME(6) COMMENT 'plannedDispense 时间',
  `procedure_id` VARCHAR(64) COMMENT '手术/操作 标识',
  `summary_no` VARCHAR(255) COMMENT 'summary 编号',
  `des_location_id` VARCHAR(64) COMMENT 'desLocation 标识',
  `rec_practitioner_id` VARCHAR(64) COMMENT 'recPractitioner 标识',
  `dosage_instruction` VARCHAR(255) COMMENT '用法说明',
  `method_code` VARCHAR(255) COMMENT 'method 代码',
  `frequency_code` VARCHAR(255) COMMENT '频次 代码',
  `dose` DECIMAL(18,2) COMMENT '剂量',
  `dose_unit_code` VARCHAR(255) COMMENT 'doseUnit 代码',
  `max_unit` DECIMAL(18,2) COMMENT 'max单元',
  `support_info` VARCHAR(255) COMMENT '辅助信息',
  `part_type_code` VARCHAR(255) COMMENT 'partType 代码',
  `dispense_frequency_code` VARCHAR(255) COMMENT 'dispenseFrequency 代码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='药品 medication dispense';
-- ----------------------------
-- Table structure for med_medication_request
-- ----------------------------
CREATE TABLE `med_medication_request` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '业务编号',
  `prescription_no` VARCHAR(255) COMMENT '处方编号',
  `group_id` VARCHAR(64) COMMENT '分组标识',
  `package_id` VARCHAR(64) COMMENT 'package标识',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `status_reason` INT COMMENT '状态原因',
  `status_changed_time` DATETIME(6) COMMENT '状态changed时间',
  `intent_enum` VARCHAR(255) COMMENT 'intent枚举值',
  `category_enum` VARCHAR(255) COMMENT 'category枚举值',
  `priority_enum` VARCHAR(255) COMMENT 'priority枚举值',
  `perform_flag` TINYINT(1) COMMENT 'perform标志位',
  `medication_id` VARCHAR(64) NOT NULL COMMENT '药品标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `requester_id` VARCHAR(64) COMMENT '药品申请聚合根',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `org_id` VARCHAR(64) COMMENT '开立科室组织主键（{ adm_机构.id}）',
  `perform_location` BIGINT COMMENT '发放药房库位主键（{ adm_地点.id}）；与 { #orgId} 分列，禁止混存',
  `perform_org` BIGINT COMMENT '执行机构',
  `performer_enum` VARCHAR(255) COMMENT 'performer枚举值',
  `performer_id` VARCHAR(64) COMMENT 'performer标识',
  `device_def_id` VARCHAR(64) COMMENT '设备def标识',
  `recorder_id` VARCHAR(64) COMMENT '记录人标识',
  `req_authored_time` DATETIME(6) COMMENT 'reqauthored时间',
  `report_flag` TINYINT(1) COMMENT '报表标志位',
  `support_info` VARCHAR(255) COMMENT '辅助信息',
  `reason_json` VARCHAR(255) COMMENT '原因JSON',
  `therapy_enum` VARCHAR(255) NOT NULL COMMENT 'therapy枚举值',
  `effective_dose_start` DATETIME(6) COMMENT 'effectivedose开始',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '数量',
  `execute_num` INT COMMENT '执行次数',
  `unit_code` VARCHAR(255) NOT NULL COMMENT '单元编码',
  `method_code` VARCHAR(255) NOT NULL COMMENT 'method编码',
  `rate_code` VARCHAR(255) NOT NULL COMMENT 'rate编码',
  `dose` DECIMAL(18,2) COMMENT '剂量',
  `dose_unit_code` VARCHAR(255) COMMENT 'dose单元编码',
  `max_dose` DECIMAL(18,2) COMMENT '最大剂量',
  `first_dose` DECIMAL(18,2) COMMENT '字段：first dose',
  `first_dose_unit_code` VARCHAR(255) COMMENT 'firstdose单元编码',
  `first_duration` VARCHAR(255) COMMENT 'first耗时',
  `dispense_interval` VARCHAR(255) COMMENT '发药interval',
  `dispense_per_quantity` INT COMMENT '发药per数量',
  `dispense_per_duration` INT COMMENT '发药per耗时',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `trace_no` TEXT COMMENT '追踪编号',
  `skin_test_flag` TINYINT(1) COMMENT 'skintest标志位',
  `infusion_flag` TINYINT(1) COMMENT 'infusion标志位',
  `speed_code` VARCHAR(255) COMMENT 'speed编码',
  `contract_id` VARCHAR(64) COMMENT '合同标识',
  `condition_definition_id` VARCHAR(64) COMMENT '诊断定义主键（列 { 病情_定义_id}，即 { cln_病情_定义.id}）',
  `encounter_diagnosis_id` VARCHAR(64) COMMENT '就诊诊断标识',
  `performer_check_id` VARCHAR(64) COMMENT 'performercheck标识',
  `check_time` DATETIME(6) COMMENT 'check时间',
  `effective_dose_end` DATETIME(6) COMMENT 'effectivedose结束',
  `refund_medicine_id` VARCHAR(64) COMMENT 'refundmedicine标识',
  `rx_type_code` VARCHAR(255) COMMENT 'rx类型编码',
  `yb_class_enum` VARCHAR(255) COMMENT '医保class枚举值',
  `dosage_instruction` VARCHAR(255) COMMENT '用法说明',
  `based_on_table` VARCHAR(255) COMMENT '依据表名',
  `based_on_id` VARCHAR(64) COMMENT 'basedon标识',
  `tcm_flag` TINYINT(1) COMMENT 'tcm标志位',
  `content_json` VARCHAR(255) COMMENT '内容JSON',
  `chinese_herbs_dose_quantity` DECIMAL(18,2) COMMENT 'chineseherbsdose数量',
  `suffering_flag` TINYINT(1) COMMENT 'suffering标志位',
  `sort_number` INT COMMENT '排序号',
  `generate_source_enum` VARCHAR(255) COMMENT 'generate来源枚举值',
  `remark` VARCHAR(255) COMMENT '备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='药品 medication request';
-- ----------------------------
-- Table structure for mrms_borrow_request
-- ----------------------------
CREATE TABLE `mrms_borrow_request` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `request_type_code` VARCHAR(16) NOT NULL DEFAULT 'borrow' COMMENT '申请类型编码',
  `applicant_practitioner_id` VARCHAR(64) COMMENT '申请人医护人员标识',
  `applicant_name` VARCHAR(50) COMMENT '申请人姓名',
  `applicant_dept_name` VARCHAR(100) COMMENT '申请人科室名称',
  `purpose` VARCHAR(500) COMMENT '借阅/复印目的',
  `scope_desc` VARCHAR(500) COMMENT '范围说明',
  `copy_count` INT COMMENT '复印份数',
  `patient_authorization_info` VARCHAR(500) COMMENT '患者授权信息',
  `status_code` VARCHAR(32) NOT NULL COMMENT '申请状态编码',
  `approve_comment` VARCHAR(500) COMMENT '审批意见',
  `approved_by` VARCHAR(64) COMMENT '审批人标识',
  `approved_at` DATETIME(6) COMMENT '审批时间',
  `borrowed_at` DATETIME(6) COMMENT '借出时间',
  `due_return_at` DATETIME(6) COMMENT '应归还时间',
  `returned_at` DATETIME(6) COMMENT '归还时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='病案借阅复印申请';
-- ----------------------------
-- Table structure for mrms_case_record
-- ----------------------------
CREATE TABLE `mrms_case_record` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `medcasno` VARCHAR(32) NOT NULL COMMENT '病案号',
  `status_code` VARCHAR(32) NOT NULL COMMENT '状态编码',
  `patn_ipt_cnt` INT COMMENT 'patnipt数量',
  `psn_name` VARCHAR(100) COMMENT 'psn名称',
  `ipt_no` VARCHAR(64) COMMENT 'ipt编号',
  `gend_code` VARCHAR(16) COMMENT 'gend编码',
  `adm_time` DATETIME(6) COMMENT 'adm时间',
  `dscg_time` DATETIME(6) COMMENT 'dscg时间',
  `adm_caty_name` VARCHAR(100) COMMENT 'admcaty名称',
  `dscg_caty_name` VARCHAR(100) COMMENT 'dscgcaty名称',
  `chfdr_name` VARCHAR(50) COMMENT 'chfdr名称',
  `main_diag_name` VARCHAR(200) COMMENT 'maindiag名称',
  `return_reason` VARCHAR(500) COMMENT 'return原因',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `atddr_practitioner_id` VARCHAR(64) COMMENT 'atddr医护人员标识',
  `atddr_name` VARCHAR(50) COMMENT 'atddr名称',
  `archived_at` DATETIME(6) COMMENT 'archived时间',
  `archived_by` VARCHAR(64) COMMENT '归档人',
  `quality_grade_code` VARCHAR(16) COMMENT '质控等级编码',
  `chs_upload_status_code` VARCHAR(32) COMMENT '4401上传状态冗余',
  `chs_upload_at` DATETIME(6) COMMENT '最近4401上传时间',
  `chs_upload_error` VARCHAR(500) COMMENT '最近4401上传错误摘要',
  `unarchive_reason` VARCHAR(500) COMMENT '解档原因'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='mrms病案记录';
-- ----------------------------
-- Table structure for mrms_case_record_homepage
-- ----------------------------
CREATE TABLE `mrms_case_record_homepage` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `version_no` INT NOT NULL DEFAULT 1 COMMENT 'version编号',
  `frozen` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否冻结',
  `ipt_medcas_hmpg_sn` VARCHAR(30) COMMENT '住院病案首页流水号',
  `field_sources_json` TEXT COMMENT '字段sourcesJSON',
  `extension_json` TEXT COMMENT '扩展字段JSON',
  `psn_name` VARCHAR(100) COMMENT 'psn名称',
  `gend_code` VARCHAR(16) COMMENT 'gend编码',
  `brdy` DATE COMMENT '字段：brdy',
  `ntly_code` VARCHAR(16) COMMENT 'ntly编码',
  `naty_code` VARCHAR(16) COMMENT 'naty编码',
  `certno` VARCHAR(32) COMMENT '字段：certno',
  `prfs_code` VARCHAR(16) COMMENT 'prfs编码',
  `mrg_stas_code` VARCHAR(16) COMMENT 'mrgstas编码',
  `curr_addr` VARCHAR(500) COMMENT '字段：curr addr',
  `psn_tel` VARCHAR(32) COMMENT '字段：psn tel',
  `coner_name` VARCHAR(100) COMMENT 'coner名称',
  `coner_tel` VARCHAR(32) COMMENT '字段：coner tel',
  `ipt_no` VARCHAR(64) COMMENT 'ipt编号',
  `adm_way_code` VARCHAR(16) COMMENT 'admway编码',
  `adm_caty_code` VARCHAR(32) COMMENT 'admcaty编码',
  `adm_caty_name` VARCHAR(100) COMMENT 'admcaty名称',
  `adm_time` DATETIME(6) COMMENT 'adm时间',
  `dscg_caty_code` VARCHAR(32) COMMENT 'dscgcaty编码',
  `dscg_caty_name` VARCHAR(100) COMMENT 'dscgcaty名称',
  `dscg_time` DATETIME(6) COMMENT 'dscg时间',
  `ipt_days` INT COMMENT '住院days',
  `transfer_dept_summary` VARCHAR(500) COMMENT 'transferdept摘要',
  `dscg_way_code` VARCHAR(16) COMMENT 'dscgway编码',
  `dept_director_name` VARCHAR(50) COMMENT 'deptdirector名称',
  `chfdr_name` VARCHAR(50) COMMENT 'chfdr名称',
  `atddr_name` VARCHAR(50) COMMENT 'atddr名称',
  `ipt_dr_name` VARCHAR(50) COMMENT 'iptdr名称',
  `resp_nurs_name` VARCHAR(50) COMMENT 'respnurs名称',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `atddr_practitioner_id` VARCHAR(64) COMMENT 'atddr医护人员标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='mrms病案记录首页';
-- ----------------------------
-- Table structure for mrms_homepage_diagnosis
-- ----------------------------
CREATE TABLE `mrms_homepage_diagnosis` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `diag_type_code` VARCHAR(32) NOT NULL COMMENT 'diag类型编码',
  `sort_no` INT NOT NULL DEFAULT 0 COMMENT '排序号',
  `diag_code` VARCHAR(32) COMMENT 'diag编码',
  `diag_name` VARCHAR(200) COMMENT 'diag名称',
  `adm_cond_code` VARCHAR(16) COMMENT 'admcond编码',
  `maindiag_flag` VARCHAR(3) COMMENT 'maindiag标志位',
  `vali_flag` VARCHAR(3) NOT NULL DEFAULT '1' COMMENT 'vali标志位',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='mrms首页诊断';
-- ----------------------------
-- Table structure for mrms_homepage_procedure
-- ----------------------------
CREATE TABLE `mrms_homepage_procedure` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `sort_no` INT NOT NULL DEFAULT 0 COMMENT '排序号',
  `oprn_oprt_code` VARCHAR(32) COMMENT '手术操作编码',
  `oprn_oprt_name` VARCHAR(200) COMMENT '手术操作名称',
  `oprn_date` DATE COMMENT '手术日期',
  `main_oprn_flag` VARCHAR(3) COMMENT '是否主手术',
  `vali_flag` VARCHAR(3) NOT NULL DEFAULT '1' COMMENT '有效标志',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='mrms首页处置';
-- ----------------------------
-- Table structure for mrms_medcasno_sequence
-- ----------------------------
CREATE TABLE `mrms_medcasno_sequence` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `year_value` INT NOT NULL COMMENT '年份',
  `last_seq` INT NOT NULL DEFAULT 0 COMMENT '末位序号',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='mrms病案号序号';
-- ----------------------------
-- Table structure for mrms_overdue_notify_log
-- ----------------------------
CREATE TABLE `mrms_overdue_notify_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `notify_type_code` VARCHAR(32) NOT NULL COMMENT '通知类型编码',
  `notify_date` DATE NOT NULL COMMENT '通知日期',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='逾期通知幂等日志';
-- ----------------------------
-- Table structure for mrms_qc_defect
-- ----------------------------
CREATE TABLE `mrms_qc_defect` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `rule_code` VARCHAR(64) COMMENT '关联规则编码',
  `defect_message` VARCHAR(1000) NOT NULL COMMENT '缺陷描述',
  `severity_code` VARCHAR(16) NOT NULL COMMENT '严重级别编码',
  `status_code` VARCHAR(16) NOT NULL COMMENT '缺陷状态编码',
  `responsible_practitioner_id` VARCHAR(64) COMMENT '责任医护人员标识',
  `rectified_at` DATETIME(6) COMMENT '整改完成时间',
  `closed_at` DATETIME(6) COMMENT '关闭时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='病案质控缺陷';
-- ----------------------------
-- Table structure for mrms_qc_rule
-- ----------------------------
CREATE TABLE `mrms_qc_rule` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `rule_code` VARCHAR(64) NOT NULL COMMENT '规则编码',
  `rule_name` VARCHAR(200) NOT NULL COMMENT '规则名称',
  `severity_code` VARCHAR(16) NOT NULL COMMENT '严重级别编码',
  `category_code` VARCHAR(32) NOT NULL COMMENT '规则分类编码',
  `enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `expression_json` TEXT COMMENT '规则表达式 JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='病案质控规则';
-- ----------------------------
-- Table structure for mrms_qc_run
-- ----------------------------
CREATE TABLE `mrms_qc_run` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `trigger_code` VARCHAR(32) NOT NULL COMMENT '触发方式编码',
  `defect_open_count` INT NOT NULL DEFAULT 0 COMMENT '未关闭缺陷数',
  `defect_warn_count` INT NOT NULL DEFAULT 0 COMMENT '警告级缺陷数',
  `passed` TINYINT(1) NOT NULL COMMENT '是否通过',
  `finished_at` DATETIME(6) NOT NULL COMMENT '执行完成时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='病案质控执行批次';
-- ----------------------------
-- Table structure for mrms_required_doc_type
-- ----------------------------
CREATE TABLE `mrms_required_doc_type` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `document_type_code` VARCHAR(64) NOT NULL COMMENT '文书类型编码',
  `encounter_class_code` VARCHAR(16) COMMENT '就诊类别编码',
  `required` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否必写',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='必写文书类型配置';
-- ----------------------------
-- Table structure for mrms_upload_log
-- ----------------------------
CREATE TABLE `mrms_upload_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `case_record_id` VARCHAR(64) NOT NULL COMMENT '病案记录标识',
  `contract_bus_no` VARCHAR(64) COMMENT '合约业务号',
  `contract_id` VARCHAR(64) COMMENT '合约标识',
  `infno` VARCHAR(16) NOT NULL DEFAULT '4401' COMMENT '医保接口号',
  `status_code` VARCHAR(32) NOT NULL COMMENT '上传状态编码',
  `msgid` VARCHAR(64) COMMENT '报文 msgid',
  `request_digest` VARCHAR(128) COMMENT '请求摘要',
  `response_snapshot` TEXT COMMENT '响应快照',
  `err_msg` VARCHAR(500) COMMENT '错误信息',
  `infcode` VARCHAR(16) COMMENT '医保 infcode',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='4401 病案首页上传日志';
-- ----------------------------
-- Table structure for peis_auto_express
-- ----------------------------
CREATE TABLE `peis_auto_express` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `name` VARCHAR(512) NOT NULL COMMENT '规则名称',
  `express_script` TEXT NOT NULL COMMENT '表达式脚本',
  `target_condition_def_id` VARCHAR(64) COMMENT '目标诊断定义标识',
  `rule_type_code` VARCHAR(64) NOT NULL COMMENT '规则类型编码',
  `status_enum` VARCHAR(64) NOT NULL DEFAULT 'active' COMMENT '状态枚举'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='PEIS 自动诊断/危急值表达式规则';
-- ----------------------------
-- Table structure for peis_common_result
-- ----------------------------
CREATE TABLE `peis_common_result` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `observation_definition_id` VARCHAR(64) COMMENT '观察项定义标识',
  `dept_org_id` VARCHAR(64) COMMENT '科室机构标识',
  `display` VARCHAR(512) NOT NULL COMMENT '展示文本',
  `value_string` TEXT COMMENT '结果文本',
  `interpretation_code` VARCHAR(64) COMMENT '解读编码',
  `sort_num` INT NOT NULL DEFAULT 0 COMMENT '排序号',
  `status_enum` VARCHAR(64) NOT NULL DEFAULT 'active' COMMENT '状态枚举'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='分科常见结果模板';
-- ----------------------------
-- Table structure for peis_config
-- ----------------------------
CREATE TABLE `peis_config` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `config_key` VARCHAR(255) NOT NULL COMMENT '配置键',
  `config_value` TEXT COMMENT '配置值'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='PEIS 模块 KV 参数（对齐 lis_config）';
-- ----------------------------
-- Table structure for peis_encounter_ext
-- ----------------------------
CREATE TABLE `peis_encounter_ext` (
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识（主键）',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `package_activity_id` VARCHAR(64) COMMENT '套餐活动定义标识',
  `package_snapshot_json` TEXT COMMENT '套餐快照 JSON',
  `group_flag` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否团检',
  `company_id` VARCHAR(64) COMMENT '单位标识',
  `contract_id` VARCHAR(64) COMMENT '合约标识',
  `group_batch_id` VARCHAR(64) COMMENT '团检批次标识',
  `booking_appointment_id` VARCHAR(64) COMMENT '预约队列标识',
  `bus_no` VARCHAR(255) COMMENT '业务编号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Encounter(PE) 体检扩展（个检/团检）';
-- ----------------------------
-- Table structure for peis_report_grant_ext
-- ----------------------------
CREATE TABLE `peis_report_grant_ext` (
  `diagnostic_report_id` VARCHAR(64) NOT NULL COMMENT '总检报告标识（主键）',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `grant_status_enum` VARCHAR(64) NOT NULL DEFAULT 'pending' COMMENT '发放状态枚举',
  `grant_time` DATETIME(6) COMMENT '发放时间',
  `grant_by` VARCHAR(64) COMMENT '发放人标识',
  `recipient_name` VARCHAR(255) COMMENT '签收人姓名'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='体检报告发放/签收扩展（1:1 DiagnosticReport）';
-- ----------------------------
-- Table structure for peis_service_request_ext
-- ----------------------------
CREATE TABLE `peis_service_request_ext` (
  `service_request_id` VARCHAR(64) NOT NULL COMMENT '服务请求标识（主键）',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `exec_status_enum` VARCHAR(64) NOT NULL DEFAULT 'pending' COMMENT '执行状态枚举',
  `lis_dispatch_enum` VARCHAR(64) NOT NULL DEFAULT 'notSent' COMMENT 'LIS 外发状态枚举',
  `pacs_dispatch_enum` VARCHAR(64) NOT NULL DEFAULT 'notSent' COMMENT 'PACS 外发状态枚举'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='体检 ServiceRequest 执行/外发扩展（无 barcode，D6）';
-- ----------------------------
-- Table structure for prt_print_binding
-- ----------------------------
CREATE TABLE `prt_print_binding` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识',
  `binding_code` VARCHAR(64) NOT NULL COMMENT '绑定编码',
  `bus_no` VARCHAR(64) NOT NULL COMMENT '业务编号',
  `name` VARCHAR(128) COMMENT '名称',
  `enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='业务场景模板绑定 PrintBinding';
-- ----------------------------
-- Table structure for prt_print_event_log
-- ----------------------------
CREATE TABLE `prt_print_event_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识',
  `trace_id` VARCHAR(64) NOT NULL COMMENT '追踪标识',
  `bus_no` VARCHAR(64) NOT NULL COMMENT '业务编号',
  `binding_code` VARCHAR(64) COMMENT '绑定编码',
  `template_version` INT COMMENT '模板version',
  `status` VARCHAR(16) NOT NULL COMMENT '状态',
  `printer_name` VARCHAR(128) COMMENT '打印机名称',
  `copies` INT COMMENT '份数',
  `content_hash` VARCHAR(64) COMMENT 'content哈希',
  `error_code` VARCHAR(64) COMMENT '错误编码',
  `error_message` VARCHAR(512) COMMENT '错误消息',
  `biz_ref_json` JSON COMMENT '业务引用JSON',
  `client_type` VARCHAR(32) COMMENT '客户端类型',
  `operator_id` VARCHAR(64) COMMENT '操作人标识',
  `operator_name` VARCHAR(128) COMMENT '操作人名称',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='打印审计日志 PrintLog';
-- ----------------------------
-- Table structure for prt_template
-- ----------------------------
CREATE TABLE `prt_template` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `organization_id` VARCHAR(64) COMMENT '机构标识',
  `bus_no` VARCHAR(64) NOT NULL COMMENT '业务编号',
  `name` VARCHAR(128) NOT NULL COMMENT '名称',
  `status` VARCHAR(16) NOT NULL COMMENT '状态',
  `version` INT NOT NULL COMMENT '乐观锁版本号',
  `print_json` JSON NOT NULL COMMENT '打印JSON',
  `schema_version` INT NOT NULL DEFAULT 1 COMMENT '结构版本',
  `sample_print_data` JSON COMMENT 'sample打印data',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `scenario_code` VARCHAR(64) COMMENT '业务场景码（如 op-rx-print）；published 行用于 preparePrint 按场景解析'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='画布打印模板 PrintTemplate';
-- ----------------------------
-- Table structure for ter_code_system
-- ----------------------------
CREATE TABLE `ter_code_system` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `name` VARCHAR(100) NOT NULL COMMENT '编码系统',
  `title` VARCHAR(200) COMMENT '编码系统标题',
  `description` TEXT COMMENT '描述',
  `version` VARCHAR(50) DEFAULT '1.0' COMMENT '乐观锁版本号',
  `status` VARCHAR(255) NOT NULL COMMENT '状态：draft',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='编码系统';
-- ----------------------------
-- Table structure for ter_concept
-- ----------------------------
CREATE TABLE `ter_concept` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `code_system_id` VARCHAR(64) NOT NULL COMMENT '编码概念',
  `code` VARCHAR(100) NOT NULL COMMENT '编码',
  `display` VARCHAR(500) NOT NULL COMMENT '显示名称',
  `definition` TEXT COMMENT '定义',
  `parent_id` VARCHAR(64) COMMENT 'parent标识',
  `sort_order` BIGINT COMMENT '父概念（支持层级结构，可选） / private Concept parent',
  `is_active` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `css_class` VARCHAR(100) COMMENT 'CSS样式类',
  `list_class` VARCHAR(100) COMMENT '列表样式类',
  `is_default` VARCHAR(1) COMMENT '是否默认',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='编码概念';
-- ----------------------------
-- Table structure for whale_audit_logs
-- ----------------------------
CREATE TABLE `whale_audit_logs` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `entity_type` VARCHAR(256) NOT NULL COMMENT '实体类型',
  `entity_id` VARCHAR(64) NOT NULL COMMENT '实体 ID',
  `operation_type` VARCHAR(32) NOT NULL COMMENT '操作类型',
  `user_id` VARCHAR(64) COMMENT '操作人',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `ip_address` VARCHAR(64) COMMENT 'IP 地址',
  `user_agent` VARCHAR(512) COMMENT '用户agent',
  `changes` TEXT COMMENT '变更内容',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='实体变更审计日志';
-- ----------------------------
-- Table structure for whale_framework_runtime_state
-- ----------------------------
CREATE TABLE `whale_framework_runtime_state` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `insight_code` VARCHAR(128) NOT NULL COMMENT '洞察编码',
  `category` VARCHAR(64) COMMENT '分类',
  `runtime_version` VARCHAR(64) COMMENT '运行时版本',
  `operator_user_id` VARCHAR(64) COMMENT '操作人用户标识',
  `session_started_at` DATETIME(6) COMMENT '会话开始时间',
  `org_category` VARCHAR(128) COMMENT '机构类别',
  `org_name` VARCHAR(256) COMMENT '机构名称',
  `deployment_fingerprint` VARCHAR(128) COMMENT '部署指纹',
  `license_customer` VARCHAR(256) COMMENT '许可证客户',
  `license_not_after` DATETIME(6) COMMENT '许可证失效时间',
  `payload_json` TEXT COMMENT '载荷 JSON',
  `observed_at` DATETIME(6) COMMENT '观测时间',
  `received_at` DATETIME(6) NOT NULL COMMENT '接收时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='框架运行时状态';
-- ----------------------------
-- Table structure for whale_menus
-- ----------------------------
CREATE TABLE `whale_menus` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `code` VARCHAR(128) NOT NULL COMMENT '菜单编码',
  `name` VARCHAR(256) NOT NULL COMMENT '菜单名称',
  `display_name` VARCHAR(256) COMMENT '显示名称',
  `icon` VARCHAR(128) COMMENT '图标',
  `path` VARCHAR(512) COMMENT '路由路径',
  `component` VARCHAR(512) COMMENT '前端组件路径',
  `permission_name` VARCHAR(256) COMMENT '关联权限名称',
  `parent_id` VARCHAR(64) COMMENT '父菜单 ID',
  `sort_order` INT DEFAULT 0 COMMENT '排序号',
  `is_enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `is_hidden` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否隐藏',
  `is_external` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否外链',
  `external_url` VARCHAR(512) COMMENT '外链 URL',
  `menu_type` VARCHAR(32) NOT NULL DEFAULT 'menu' COMMENT '菜单类型（menu/directory）',
  `remark` VARCHAR(512) COMMENT '备注',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `keep_alive` TINYINT(1) COMMENT '是否缓存页面'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='菜单';
-- ----------------------------
-- Table structure for whale_organization_units
-- ----------------------------
CREATE TABLE `whale_organization_units` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `code` VARCHAR(128) NOT NULL COMMENT '编码',
  `display_name` VARCHAR(256) NOT NULL COMMENT '显示名称',
  `parent_id` VARCHAR(64) COMMENT '父节点标识',
  `sort_order` INT DEFAULT 0 COMMENT '排序号',
  `is_enabled` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用，语义等同 { PublicationStatus.ACTIVE}（见 health-domain-shared）',
  `remark` VARCHAR(512) COMMENT '备注',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='组织机构单元';
-- ----------------------------
-- Table structure for whale_permission_grants
-- ----------------------------
CREATE TABLE `whale_permission_grants` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `permission_name` VARCHAR(256) NOT NULL COMMENT '权限名称',
  `provider_name` VARCHAR(64) NOT NULL COMMENT '授权主体类型（R=角色/U=用户）',
  `provider_key` VARCHAR(256) NOT NULL COMMENT '授权主体键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='权限授权';
-- ----------------------------
-- Table structure for whale_permissions
-- ----------------------------
CREATE TABLE `whale_permissions` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `name` VARCHAR(256) NOT NULL COMMENT '权限名称（唯一）',
  `display_name` VARCHAR(256) COMMENT '显示名称',
  `parent_name` VARCHAR(256) COMMENT '父权限名称',
  `description` TEXT COMMENT '描述',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='权限定义';
-- ----------------------------
-- Table structure for whale_qrtz_blob_triggers
-- ----------------------------
CREATE TABLE `whale_qrtz_blob_triggers` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `trigger_name` VARCHAR(200) NOT NULL COMMENT '触发器名称',
  `trigger_group` VARCHAR(200) NOT NULL COMMENT '触发器组',
  `blob_data` LONGBLOB COMMENT '触发器 BLOB 数据'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz BLOB 触发器';
-- ----------------------------
-- Table structure for whale_qrtz_calendars
-- ----------------------------
CREATE TABLE `whale_qrtz_calendars` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `calendar_name` VARCHAR(200) NOT NULL COMMENT '日历名称',
  `calendar` LONGBLOB NOT NULL COMMENT '日历对象（BLOB）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 日历';
-- ----------------------------
-- Table structure for whale_qrtz_cron_triggers
-- ----------------------------
CREATE TABLE `whale_qrtz_cron_triggers` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `trigger_name` VARCHAR(200) NOT NULL COMMENT '触发器名称',
  `trigger_group` VARCHAR(200) NOT NULL COMMENT '触发器组',
  `cron_expression` VARCHAR(120) NOT NULL COMMENT 'Cron 表达式',
  `time_zone_id` VARCHAR(80) COMMENT '时区 ID'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz Cron 触发器';
-- ----------------------------
-- Table structure for whale_qrtz_fired_triggers
-- ----------------------------
CREATE TABLE `whale_qrtz_fired_triggers` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `entry_id` VARCHAR(95) NOT NULL COMMENT '条目 ID',
  `trigger_name` VARCHAR(200) NOT NULL COMMENT '触发器名称',
  `trigger_group` VARCHAR(200) NOT NULL COMMENT '触发器组',
  `instance_name` VARCHAR(200) NOT NULL COMMENT '实例名称',
  `fired_time` BIGINT NOT NULL COMMENT '触发时间（毫秒）',
  `sched_time` BIGINT NOT NULL COMMENT '计划时间（毫秒）',
  `priority` INT NOT NULL COMMENT '优先级',
  `state` VARCHAR(16) NOT NULL COMMENT '状态',
  `job_name` VARCHAR(200) COMMENT '作业名称',
  `job_group` VARCHAR(200) COMMENT '作业组',
  `is_nonconcurrent` TINYINT(1) COMMENT '是否禁止并发',
  `requests_recovery` TINYINT(1) COMMENT '是否请求恢复'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 已触发记录';
-- ----------------------------
-- Table structure for whale_qrtz_job_details
-- ----------------------------
CREATE TABLE `whale_qrtz_job_details` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `job_name` VARCHAR(200) NOT NULL COMMENT '作业名称',
  `job_group` VARCHAR(200) NOT NULL COMMENT '作业组',
  `description` VARCHAR(250) COMMENT '描述',
  `job_class_name` VARCHAR(250) NOT NULL COMMENT '作业类名',
  `is_durable` TINYINT(1) NOT NULL COMMENT '是否持久化',
  `is_nonconcurrent` TINYINT(1) NOT NULL COMMENT '是否禁止并发',
  `is_update_data` TINYINT(1) NOT NULL COMMENT '是否更新数据',
  `requests_recovery` TINYINT(1) NOT NULL COMMENT '是否请求恢复',
  `job_data` LONGBLOB COMMENT '作业数据（BLOB）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 作业详情';
-- ----------------------------
-- Table structure for whale_qrtz_job_execution_log
-- ----------------------------
CREATE TABLE `whale_qrtz_job_execution_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `sched_name` VARCHAR(120) NOT NULL DEFAULT 'WhaleScheduler' COMMENT '调度名称',
  `job_name` VARCHAR(200) NOT NULL COMMENT '任务名称',
  `job_group` VARCHAR(200) NOT NULL COMMENT '任务分组',
  `job_bean_name` VARCHAR(128) NOT NULL COMMENT '任务Bean名称',
  `display_name` VARCHAR(128) COMMENT '显示名称',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `execution_type` VARCHAR(16) NOT NULL COMMENT '执行类型',
  `success` TINYINT(1) NOT NULL COMMENT '成功',
  `error_message` TEXT COMMENT '错误消息',
  `duration_ms` BIGINT NOT NULL COMMENT '耗时ms',
  `started_at` DATETIME(6) NOT NULL COMMENT '开始时间',
  `finished_at` DATETIME(6) NOT NULL COMMENT '结束时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Whale 扩展：定时任务执行历史（非 Quartz 内置 fired_triggers 替代品）';
-- ----------------------------
-- Table structure for whale_qrtz_locks
-- ----------------------------
CREATE TABLE `whale_qrtz_locks` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `lock_name` VARCHAR(40) NOT NULL COMMENT '锁名称'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 调度锁';
-- ----------------------------
-- Table structure for whale_qrtz_paused_trigger_grps
-- ----------------------------
CREATE TABLE `whale_qrtz_paused_trigger_grps` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `trigger_group` VARCHAR(200) NOT NULL COMMENT '触发器组'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 暂停触发器组';
-- ----------------------------
-- Table structure for whale_qrtz_scheduler_state
-- ----------------------------
CREATE TABLE `whale_qrtz_scheduler_state` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `instance_name` VARCHAR(200) NOT NULL COMMENT '实例名称',
  `last_checkin_time` BIGINT NOT NULL COMMENT '最后检入时间（毫秒）',
  `checkin_interval` BIGINT NOT NULL COMMENT '检入间隔（毫秒）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 调度器状态';
-- ----------------------------
-- Table structure for whale_qrtz_simple_triggers
-- ----------------------------
CREATE TABLE `whale_qrtz_simple_triggers` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `trigger_name` VARCHAR(200) NOT NULL COMMENT '触发器名称',
  `trigger_group` VARCHAR(200) NOT NULL COMMENT '触发器组',
  `repeat_count` BIGINT NOT NULL COMMENT '重复次数',
  `repeat_interval` BIGINT NOT NULL COMMENT '重复间隔（毫秒）',
  `times_triggered` BIGINT NOT NULL COMMENT '已触发次数'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 简单触发器';
-- ----------------------------
-- Table structure for whale_qrtz_triggers
-- ----------------------------
CREATE TABLE `whale_qrtz_triggers` (
  `sched_name` VARCHAR(120) NOT NULL COMMENT '调度器名称',
  `trigger_name` VARCHAR(200) NOT NULL COMMENT '触发器名称',
  `trigger_group` VARCHAR(200) NOT NULL COMMENT '触发器组',
  `job_name` VARCHAR(200) NOT NULL COMMENT '关联作业名称',
  `job_group` VARCHAR(200) NOT NULL COMMENT '关联作业组',
  `description` VARCHAR(250) COMMENT '描述',
  `next_fire_time` BIGINT COMMENT '下次触发时间（毫秒）',
  `prev_fire_time` BIGINT COMMENT '上次触发时间（毫秒）',
  `priority` INT COMMENT '优先级',
  `trigger_state` VARCHAR(16) NOT NULL COMMENT '触发器状态',
  `trigger_type` VARCHAR(8) NOT NULL COMMENT '触发器类型',
  `start_time` BIGINT NOT NULL COMMENT '开始时间（毫秒）',
  `end_time` BIGINT COMMENT '结束时间（毫秒）',
  `calendar_name` VARCHAR(200) COMMENT '日历名称',
  `misfire_instr` SMALLINT COMMENT '错失触发策略',
  `job_data` LONGBLOB COMMENT '触发器数据（BLOB）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='Quartz 触发器';
-- ----------------------------
-- Table structure for whale_role_claims
-- ----------------------------
CREATE TABLE `whale_role_claims` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `role_id` VARCHAR(64) NOT NULL COMMENT '角色标识',
  `claim_type` VARCHAR(256) NOT NULL COMMENT '声明类型',
  `claim_value` VARCHAR(512) COMMENT '声明值',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='角色声明';
-- ----------------------------
-- Table structure for whale_roles
-- ----------------------------
CREATE TABLE `whale_roles` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `name` VARCHAR(256) NOT NULL COMMENT '角色名称（唯一）',
  `display_name` VARCHAR(256) COMMENT '显示名称',
  `code` VARCHAR(256) COMMENT '角色编码',
  `description` TEXT COMMENT '描述',
  `is_default` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否默认角色',
  `is_static` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否静态角色（不可删）',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='系统角色';
-- ----------------------------
-- Table structure for whale_security_logs
-- ----------------------------
CREATE TABLE `whale_security_logs` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `user_id` VARCHAR(64) COMMENT '用户标识',
  `user_name` VARCHAR(256) COMMENT '用户名称',
  `action` VARCHAR(64) NOT NULL COMMENT '操作动作',
  `client_ip` VARCHAR(64) COMMENT '客户端ip',
  `user_agent` VARCHAR(512) COMMENT '用户agent',
  `result` VARCHAR(32) COMMENT '结果',
  `failure_reason` VARCHAR(512) COMMENT 'failure原因',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `extra_properties` JSON COMMENT '扩展属性 JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='安全审计日志';
-- ----------------------------
-- Table structure for whale_sequence
-- ----------------------------
CREATE TABLE `whale_sequence` (
  `seq_key` VARCHAR(255) NOT NULL COMMENT '序号键（如 ORDER、PATIENT、或 ORDER:2025-01-30 表示按天）',
  `current_value` BIGINT NOT NULL DEFAULT 0 COMMENT '当前序号值（递增后返回）',
  `updated_at` DATETIME(6) COMMENT '最后更新时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='业务序号表，按 key 记录当前序号';
-- ----------------------------
-- Table structure for whale_settings
-- ----------------------------
CREATE TABLE `whale_settings` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `name` VARCHAR(256) NOT NULL COMMENT '设置键',
  `value` TEXT COMMENT '设置值',
  `provider_name` VARCHAR(64) COMMENT '提供者类型',
  `provider_key` VARCHAR(256) COMMENT '提供者键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `description` VARCHAR(512) COMMENT '描述',
  `created_at` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='系统设置';
-- ----------------------------
-- Table structure for whale_tenants
-- ----------------------------
CREATE TABLE `whale_tenants` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `name` VARCHAR(128) NOT NULL COMMENT '租户名称',
  `code` VARCHAR(64) NOT NULL COMMENT '租户代码',
  `description` VARCHAR(512) COMMENT '租户描述',
  `is_active` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `extra_properties` TEXT COMMENT '扩展属性',
  `created_at` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='租户';
-- ----------------------------
-- Table structure for whale_user_claims
-- ----------------------------
CREATE TABLE `whale_user_claims` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `user_id` VARCHAR(64) NOT NULL COMMENT '用户标识',
  `claim_type` VARCHAR(256) NOT NULL COMMENT '声明类型',
  `claim_value` VARCHAR(512) COMMENT '声明值',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='用户声明';
-- ----------------------------
-- Table structure for whale_user_login_session
-- ----------------------------
CREATE TABLE `whale_user_login_session` (
  `user_id` VARCHAR(64) NOT NULL COMMENT '用户标识',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `hospital_organization_id` VARCHAR(64) COMMENT 'hospital机构标识',
  `organization_unit_id` VARCHAR(64) COMMENT '机构单元标识',
  `updated_at` DATETIME(6) NOT NULL DEFAULT CURRENT_TIMESTAMP(6) COMMENT '最后更新时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='用户登录后的服务端会话：租户 / 医院 / 科室选择（跨重启持久化）';
-- ----------------------------
-- Table structure for whale_user_organization_units
-- ----------------------------
CREATE TABLE `whale_user_organization_units` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `user_id` VARCHAR(64) NOT NULL COMMENT '用户标识',
  `organization_unit_id` VARCHAR(64) NOT NULL COMMENT '组织单元标识',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='用户组织单元关联';
-- ----------------------------
-- Table structure for whale_user_roles
-- ----------------------------
CREATE TABLE `whale_user_roles` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `user_id` VARCHAR(64) NOT NULL COMMENT '用户标识',
  `role_id` VARCHAR(64) NOT NULL COMMENT '角色标识',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='用户角色关联';
-- ----------------------------
-- Table structure for whale_user_tenants
-- ----------------------------
CREATE TABLE `whale_user_tenants` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `user_id` VARCHAR(64) NOT NULL COMMENT '用户标识',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='用户租户关联';
-- ----------------------------
-- Table structure for whale_users
-- ----------------------------
CREATE TABLE `whale_users` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `user_name` VARCHAR(256) NOT NULL COMMENT '登录用户名',
  `email` VARCHAR(256) COMMENT '邮箱',
  `phone_number` VARCHAR(32) COMMENT '手机号',
  `password_hash` VARCHAR(256) NOT NULL COMMENT '密码哈希',
  `name` VARCHAR(64) COMMENT '名',
  `surname` VARCHAR(64) COMMENT '姓',
  `is_active` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否启用',
  `is_locked_out` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '是否锁定',
  `lockout_end` DATETIME(6) COMMENT '锁定结束时间',
  `access_failed_count` INT NOT NULL DEFAULT 0 COMMENT '登录失败次数',
  `extra_properties` JSON COMMENT '扩展属性 JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `ukey_id` VARCHAR(128) COMMENT 'UKey 标识',
  `ukey_src_id` VARCHAR(128) COMMENT 'UKey 来源标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='系统用户';
-- ----------------------------
-- Table structure for wkf_activity_definition
-- ----------------------------
CREATE TABLE `wkf_activity_definition` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `category_code` VARCHAR(255) NOT NULL COMMENT '诊疗项目定义聚合根',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '业务编码（全局唯一）',
  `name` VARCHAR(255) NOT NULL COMMENT '项目名称',
  `py_str` VARCHAR(255) COMMENT '拼音检索码',
  `wb_str` VARCHAR(255) COMMENT '五笔检索码',
  `package_unit_code` VARCHAR(255) COMMENT '销售/计价单位编码',
  `type_enum` VARCHAR(255) NOT NULL COMMENT '诊疗类型枚举编码',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '发布状态枚举编码',
  `description_text` VARCHAR(255) COMMENT '说明文本',
  `body_site_code` VARCHAR(255) COMMENT '身体部位编码',
  `specimen_code` VARCHAR(255) COMMENT '标本编码',
  `org_id` VARCHAR(64) COMMENT '所属机构标识',
  `location_id` VARCHAR(64) COMMENT '位置标识',
  `rule_id` INT COMMENT '计费规则标识',
  `pricing_flag` TINYINT(1) COMMENT '划价标记',
  `yb_flag` TINYINT(1) COMMENT '医保标记',
  `yb_no` VARCHAR(255) COMMENT '医保编码',
  `yb_match_flag` TINYINT(1) COMMENT '医保对码标记',
  `chrgitm_lv` INT COMMENT '医保收费等级',
  `children_json` VARCHAR(255) COMMENT '子项 JSON 快照',
  `children_flag` TINYINT(1) COMMENT '子项标记（需与子项子表事实一致）',
  `activity_version` VARCHAR(255) COMMENT '诊疗项目业务版本（非乐观锁 version）',
  `merchandise_name` VARCHAR(255) COMMENT '商品名称（可与项目名称分列维护）',
  `merchandise_py_str` VARCHAR(255) COMMENT '商品名拼音检索码',
  `merchandise_wb_str` VARCHAR(255) COMMENT '商品名五笔检索码',
  `def_encounter_unit_code` VARCHAR(255) COMMENT '默认门诊/就诊单位编码',
  `def_inhospital_unit_code` VARCHAR(255) COMMENT '默认住院单位编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 activity 定义';
-- ----------------------------
-- Table structure for wkf_activity_definition_children
-- ----------------------------
CREATE TABLE `wkf_activity_definition_children` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `activity_id` VARCHAR(64) NOT NULL COMMENT '诊疗项目子项实体',
  `children_id` VARCHAR(64) NOT NULL COMMENT '子项诊疗项目标识（被引用项目主键）',
  `children_num` INT COMMENT '子项数量',
  `children_name` VARCHAR(255) COMMENT '子项名称快照'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 activity 定义 children';
-- ----------------------------
-- Table structure for wkf_appointment_queue
-- ----------------------------
CREATE TABLE `wkf_appointment_queue` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `appointment_kind` VARCHAR(255) NOT NULL COMMENT '预约分类（OUTPATIENT_BOOKING / CHECK_IN_ONLY 等）',
  `bus_no` VARCHAR(255) COMMENT '业务号',
  `patient_id` VARCHAR(64) COMMENT '患者标识',
  `encounter_id` VARCHAR(64) COMMENT '就诊标识',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `destination_location_id` VARCHAR(64) COMMENT '去向诊室/地点标识',
  `triage_level` VARCHAR(255) COMMENT '分诊等级（文本）',
  `triage_priority_code` VARCHAR(255) COMMENT '分诊优先级编码',
  `triage_time` DATETIME(6) COMMENT '分诊时间',
  `display_order` INT COMMENT '候诊显示顺序',
  `slot_id` VARCHAR(64) COMMENT '号源标识（门诊预约）',
  `service_type_code` VARCHAR(255) COMMENT '服务类型编码',
  `appointment_type_code` VARCHAR(255) COMMENT '预约类型编码',
  `start_instant` DATETIME(6) COMMENT '计划开始时间',
  `end_instant` DATETIME(6) COMMENT '计划结束时间',
  `cancel_reason` VARCHAR(255) COMMENT '取消/终态原因（文本）',
  `cancellation_reason_code` VARCHAR(255) COMMENT '取消/终态原因编码',
  `cancellation_at` DATETIME(6) COMMENT '取消/过号时间',
  `called_at` DATETIME(6) COMMENT '最近叫号时间',
  `last_practitioner_id` VARCHAR(64) COMMENT '最近叫号医师标识',
  `origin_channel` VARCHAR(255) COMMENT '渠道编码（KIOSK/MINIAPP/COUNTER 等）',
  `origin_channel_session_id` VARCHAR(255) COMMENT '渠道会话标识',
  `origin_source_device_id` VARCHAR(64) COMMENT '来源设备标识',
  `origin_operator_id` VARCHAR(64) COMMENT '代操作操作者标识',
  `origin_client_app_version` VARCHAR(255) COMMENT '客户端版本号',
  `healthcare_service_id` VARCHAR(64) COMMENT '冗余：门诊防重（同 患者+service+booking_date）',
  `booking_date` DATE COMMENT '冗余：预约自然日（Asia/Shanghai）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='预约与候诊队列（FHIR 预约 语义）';
-- ----------------------------
-- Table structure for wkf_device_dispense
-- ----------------------------
CREATE TABLE `wkf_device_dispense` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '业务编号',
  `device_req_id` VARCHAR(64) NOT NULL COMMENT '设备req标识',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `based_on_table` VARCHAR(255) COMMENT '依据表名',
  `based_on_id` VARCHAR(64) COMMENT 'basedon标识',
  `not_performed_reason_enum` VARCHAR(255) COMMENT 'notperformed原因枚举值',
  `dispense_category_enum` VARCHAR(255) COMMENT '发药category枚举值',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '数量',
  `unit_code` VARCHAR(255) NOT NULL COMMENT '单元编码',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `device_def_id` VARCHAR(64) NOT NULL COMMENT '设备def标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `performer_id` VARCHAR(64) COMMENT 'performer标识',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `part_type_code` VARCHAR(255) COMMENT 'part类型编码',
  `dispense_quantity` DECIMAL(18,2) COMMENT '发药数量',
  `preparer_id` VARCHAR(64) COMMENT 'preparer标识',
  `prepare_time` DATETIME(6) COMMENT 'prepare时间',
  `dispense_time` DATETIME(6) COMMENT '发药时间',
  `limit_time` DATETIME(6) COMMENT 'limit时间',
  `planned_dispense_time` DATETIME(6) COMMENT 'planned发药时间',
  `des_location_id` VARCHAR(255) COMMENT 'des位置标识',
  `rec_practitioner_id` VARCHAR(255) COMMENT 'rec医护人员标识',
  `support_info` VARCHAR(255) COMMENT '辅助信息',
  `usage_instruction` VARCHAR(255) COMMENT '用法说明',
  `dispense_frequency_code` VARCHAR(255) COMMENT '发药频次编码',
  `trace_no` TEXT COMMENT '追踪编号',
  `procedure_id` VARCHAR(64) COMMENT '处置标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 device dispense';
-- ----------------------------
-- Table structure for wkf_device_request
-- ----------------------------
CREATE TABLE `wkf_device_request` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) COMMENT '业务编号',
  `prescription_no` VARCHAR(255) COMMENT '处方编号',
  `activity_id` VARCHAR(64) COMMENT '活动标识',
  `package_id` VARCHAR(64) COMMENT 'package标识',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `intent_code` VARCHAR(255) COMMENT 'intent编码',
  `category_enum` VARCHAR(255) COMMENT 'category枚举值',
  `priority_enum` VARCHAR(255) COMMENT 'priority枚举值',
  `perform_flag` TINYINT(1) COMMENT 'perform标志位',
  `group_no` VARCHAR(255) COMMENT '分组编号',
  `device_type_code` VARCHAR(255) COMMENT '设备类型编码',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '数量',
  `unit_code` VARCHAR(255) COMMENT '单元编码',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `device_def_id` VARCHAR(64) NOT NULL COMMENT '设备def标识',
  `device_specifications` VARCHAR(255) COMMENT '设备specifications',
  `requester_id` VARCHAR(64) COMMENT 'requester标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `perform_location` BIGINT COMMENT 'perform位置',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `rate_code` VARCHAR(255) COMMENT 'rate编码',
  `use_time` DATETIME(6) COMMENT 'use时间',
  `use_start_time` DATETIME(6) COMMENT 'use开始时间',
  `use_end_time` DATETIME(6) COMMENT 'use结束时间',
  `use_timing` VARCHAR(255) COMMENT '用药时机',
  `req_authored_time` DATETIME(6) COMMENT 'reqauthored时间',
  `performer_enum` VARCHAR(255) COMMENT 'performer枚举值',
  `performer_id` VARCHAR(64) COMMENT 'performer标识',
  `perform_org_id` VARCHAR(64) COMMENT 'performorg标识',
  `as_need_flag` TINYINT(1) COMMENT 'asneed标志位',
  `as_need_reason` VARCHAR(255) COMMENT 'asneed原因',
  `contract_code` VARCHAR(255) COMMENT '合同编码',
  `refund_device_id` VARCHAR(64) COMMENT 'refund设备标识',
  `yb_class_enum` VARCHAR(255) COMMENT '医保class枚举值',
  `trace_no` TEXT COMMENT '追踪编号',
  `condition_definition_id` VARCHAR(64) COMMENT '耗材请求聚合根',
  `encounter_diagnosis_id` VARCHAR(64) COMMENT '就诊诊断标识',
  `observation_id_json` VARCHAR(255) COMMENT '观察项ID JSON',
  `support_info` VARCHAR(255) COMMENT '辅助信息',
  `based_on_table` VARCHAR(255) COMMENT '依据表名',
  `based_on_id` VARCHAR(64) COMMENT 'basedon标识',
  `generate_source_enum` VARCHAR(255) COMMENT 'generate来源枚举值',
  `remark` VARCHAR(255) COMMENT '备注',
  `sort_number` INT COMMENT '排序号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 device request';
-- ----------------------------
-- Table structure for wkf_inventory_item
-- ----------------------------
CREATE TABLE `wkf_inventory_item` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `category_code` VARCHAR(255) COMMENT '库存项聚合根（DM-WKF-008）',
  `item_table` VARCHAR(255) NOT NULL COMMENT '物品定义表名',
  `item_id` VARCHAR(64) NOT NULL COMMENT '物品定义标识',
  `name` VARCHAR(255) NOT NULL COMMENT '物品名称（冗余）',
  `py_str` VARCHAR(255) COMMENT '拼音码',
  `wb_str` VARCHAR(255) COMMENT '五笔码',
  `inventory_status_enum` VARCHAR(255) NOT NULL COMMENT '库存状态（ACTIVE/INACTIVE），与 PublicationStatus 编码对齐',
  `supplier_id` VARCHAR(64) NOT NULL COMMENT '供应商标识',
  `description_text` VARCHAR(255) COMMENT '描述文本',
  `unit_code` VARCHAR(255) NOT NULL COMMENT '计量单位编码',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '当前库存数量',
  `characteristic_json` VARCHAR(255) COMMENT '特征扩展 JSON',
  `lot_number` VARCHAR(255) NOT NULL COMMENT '产品批号',
  `production_date` DATETIME(6) COMMENT '生产日期',
  `expiration_date` DATETIME(6) COMMENT '效期',
  `validity_mon` INT COMMENT '有效期月数',
  `location_store_id` VARCHAR(64) COMMENT '货位标识',
  `location_id` VARCHAR(64) NOT NULL COMMENT '库房标识',
  `trace_no` TEXT COMMENT '追溯码',
  `packaging_levels` INT COMMENT '追溯码包装层级'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 inventory item';
-- ----------------------------
-- Table structure for wkf_schedule
-- ----------------------------
CREATE TABLE `wkf_schedule` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识',
  `name` VARCHAR(255) COMMENT '日程显示名称',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '业务状态（draft/active/inactive/retired）',
  `active_flag` TINYINT(1) NOT NULL COMMENT '启用标记',
  `planning_horizon_start` DATETIME(6) COMMENT '规划窗口起始时间',
  `planning_horizon_end` DATETIME(6) COMMENT '规划窗口结束时间',
  `service_type_concept_json` VARCHAR(255) COMMENT '服务类型概念快照 JSON',
  `healthcare_service_id` VARCHAR(64) COMMENT '医疗服务引用',
  `service_category_json` VARCHAR(255) COMMENT '服务大类快照 JSON',
  `specialty_json` VARCHAR(255) COMMENT '专科快照 JSON',
  `comment_markdown` VARCHAR(255) COMMENT '可用性说明（Markdown）',
  `substitute_practitioner_id` VARCHAR(64) COMMENT '替诊医师主键（顶班 B；原医师仍保留在 Actor）',
  `substitute_reason` VARCHAR(255) COMMENT '替诊原因说明',
  `source_schedule_template_id` VARCHAR(64) COMMENT '来源 T2 日排班模板主键（模板生成时写入）',
  `slot_provision_template_id` VARCHAR(64) COMMENT '关联 T1 放号时段模板主键（生成或手动创建时写入）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='号源日程（FHIR 排班 语义）';
-- ----------------------------
-- Table structure for wkf_schedule_actor
-- ----------------------------
CREATE TABLE `wkf_schedule_actor` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `schedule_id` VARCHAR(64) NOT NULL COMMENT '所属日程标识',
  `actor_type` INT NOT NULL COMMENT '参与者类型编码',
  `actor_id` VARCHAR(64) NOT NULL COMMENT '参与者主键',
  `sort_no` INT NOT NULL COMMENT '排序号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='日程参与者（医师/诊室/设备等）';
-- ----------------------------
-- Table structure for wkf_schedule_identifier
-- ----------------------------
CREATE TABLE `wkf_schedule_identifier` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `schedule_id` VARCHAR(64) NOT NULL COMMENT '所属日程标识',
  `id_system` VARCHAR(255) NOT NULL COMMENT '标识体系 URI',
  `id_value` VARCHAR(255) NOT NULL COMMENT '标识值',
  `use_code` VARCHAR(255) COMMENT '用途编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='日程外部标识（FHIR Identifier 语义）';
-- ----------------------------
-- Table structure for wkf_service_request
-- ----------------------------
CREATE TABLE `wkf_service_request` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) COMMENT '业务编号',
  `prescription_no` VARCHAR(255) COMMENT '处方编号',
  `based_on_table` VARCHAR(255) COMMENT '依据表名',
  `based_on_id` VARCHAR(64) COMMENT 'basedon标识',
  `requisition_id` VARCHAR(64) COMMENT 'requisition标识',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '状态枚举值',
  `intent_enum` VARCHAR(255) COMMENT 'intent枚举值',
  `category_enum` VARCHAR(255) NOT NULL COMMENT 'category枚举值',
  `group_id` VARCHAR(64) COMMENT '分组标识',
  `priority_enum` VARCHAR(255) COMMENT 'priority枚举值',
  `perform_flag` TINYINT(1) COMMENT 'perform标志位',
  `activity_id` VARCHAR(64) NOT NULL COMMENT '活动标识',
  `quantity` DECIMAL(18,2) NOT NULL COMMENT '数量',
  `unit_code` VARCHAR(255) NOT NULL COMMENT '单元编码',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `authored_time` DATETIME(6) COMMENT 'authored时间',
  `requester_id` VARCHAR(64) NOT NULL COMMENT 'requester标识',
  `performer_type_code` VARCHAR(255) COMMENT 'performer类型编码',
  `performer_id` VARCHAR(64) COMMENT 'performer标识',
  `performer_check_id` VARCHAR(64) COMMENT 'performercheck标识',
  `check_time` DATETIME(6) COMMENT 'check时间',
  `location_id` VARCHAR(64) COMMENT '位置/科室标识',
  `org_id` VARCHAR(64) COMMENT '机构标识',
  `reason_text` VARCHAR(255) COMMENT '原因文本',
  `contract_id` VARCHAR(64) COMMENT '合同标识',
  `occurrence_start_time` DATETIME(6) COMMENT 'occurrence开始时间',
  `occurrence_end_time` DATETIME(6) COMMENT 'occurrence结束时间',
  `relevant_history_id` VARCHAR(64) COMMENT 'relevanthistory标识',
  `refund_service_id` VARCHAR(64) COMMENT 'refund服务标识',
  `content_json` VARCHAR(255) COMMENT '内容JSON',
  `yb_class_enum` VARCHAR(255) COMMENT '医保class枚举值',
  `print_count` INT COMMENT '打印count',
  `condition_definition_id` VARCHAR(64) COMMENT '诊断定义主键（列 { 病情_定义_id}，即 { cln_病情_定义.id}）',
  `encounter_diagnosis_id` VARCHAR(64) COMMENT '就诊诊断标识',
  `therapy_enum` VARCHAR(255) COMMENT 'therapy枚举值',
  `rate_code` VARCHAR(255) COMMENT 'rate编码',
  `parent_id` VARCHAR(64) COMMENT 'parent标识',
  `generate_source_enum` VARCHAR(255) COMMENT 'generate来源枚举值',
  `remark` VARCHAR(255) COMMENT '备注',
  `entrust_content` VARCHAR(255) COMMENT '嘱托内容',
  `sort_number` INT COMMENT '排序号',
  `execution_count` INT COMMENT '服务申请聚合根（非药品医嘱）'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 service request';
-- ----------------------------
-- Table structure for wkf_service_request_detail
-- ----------------------------
CREATE TABLE `wkf_service_request_detail` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `service_req_id` VARCHAR(64) NOT NULL COMMENT '服务申请明细子实体',
  `target_table` VARCHAR(64) COMMENT '明细目标表名（如 dia_body_structure、adm_specimen_定义）',
  `target_id` VARCHAR(64) COMMENT '明细目标表主键',
  `remark` VARCHAR(255) COMMENT '明细备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 service request detail';
-- ----------------------------
-- Table structure for wkf_slot
-- ----------------------------
CREATE TABLE `wkf_slot` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` BIGINT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `organization_id` VARCHAR(64) NOT NULL COMMENT '机构标识（冗余自 排班）',
  `schedule_id` VARCHAR(64) NOT NULL COMMENT '所属日程标识',
  `start_time` DATETIME(6) NOT NULL COMMENT '时段开始时刻',
  `end_time` DATETIME(6) NOT NULL COMMENT '时段结束时刻',
  `status_code` VARCHAR(255) NOT NULL COMMENT '状态码（free/busy/busy-unavailable 等）',
  `capacity` INT NOT NULL COMMENT '额定容量',
  `booked_count` INT NOT NULL COMMENT '已预约计数',
  `overbooked_flag` TINYINT(1) NOT NULL COMMENT '超售标记',
  `service_category_json` VARCHAR(255) COMMENT '服务大类快照 JSON',
  `service_type_json` VARCHAR(255) COMMENT '服务类型快照 JSON',
  `specialty_json` VARCHAR(255) COMMENT '专科快照 JSON',
  `appointment_type_json` VARCHAR(255) COMMENT '预约类型/场景快照 JSON',
  `comment_text` VARCHAR(255) COMMENT '备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='号源时段（FHIR 时段 语义）';
-- ----------------------------
-- Table structure for wkf_slot_identifier
-- ----------------------------
CREATE TABLE `wkf_slot_identifier` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `slot_id` VARCHAR(64) NOT NULL COMMENT '所属号源时段标识',
  `id_system` VARCHAR(255) NOT NULL COMMENT '标识体系 URI',
  `id_value` VARCHAR(255) NOT NULL COMMENT '标识值',
  `use_code` VARCHAR(255) COMMENT '用途编码'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='号源时段外部标识（FHIR Identifier 语义）';
-- ----------------------------
-- Table structure for wkf_supply_delivery
-- ----------------------------
CREATE TABLE `wkf_supply_delivery` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `request_id` VARCHAR(64) COMMENT '供应发放聚合根',
  `summary_id` VARCHAR(64) COMMENT 'summary标识',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '发放状态持久化码（如 { DispenseStatus#getCode()}，B.10.8.1）',
  `patient_id` VARCHAR(64) COMMENT '患者标识',
  `type_enum` VARCHAR(255) NOT NULL COMMENT '发放类型/业务子类型持久化码（与命令及事件载荷一致，B.10.8.1）',
  `item_table` VARCHAR(255) COMMENT '项table',
  `item_id` VARCHAR(64) COMMENT '项标识',
  `based_on_table` VARCHAR(255) COMMENT '依据表名',
  `based_on_ids` VARCHAR(255) COMMENT '依据ID列表',
  `unit_code` VARCHAR(255) COMMENT '单元编码',
  `quantity` DECIMAL(18,2) COMMENT '数量',
  `condition` VARCHAR(255) COMMENT '病情',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `trace_no` TEXT COMMENT '追踪编号',
  `supplier_id` VARCHAR(64) COMMENT '供应商标识',
  `practitioner_id` VARCHAR(64) COMMENT '医护人员标识',
  `occurrence_time` DATETIME(6) COMMENT 'occurrence时间',
  `receiver_id` VARCHAR(64) COMMENT 'receiver标识',
  `receive_time` DATETIME(6) COMMENT 'receive时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 supply delivery';
-- ----------------------------
-- Table structure for wkf_supply_request
-- ----------------------------
CREATE TABLE `wkf_supply_request` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) COMMENT '租户标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号',
  `bus_no` VARCHAR(255) NOT NULL COMMENT '供应请求聚合根（同表多行：同一 { bus_no} 聚合多行明细，共享审批状态）',
  `original_bus_no` VARCHAR(255) COMMENT '来源业务单号（如进货关联订货）；可空',
  `type_enum` VARCHAR(255) NOT NULL COMMENT '供应类型持久化码（{ SupplyType#getCode()}，B.10.8.1）',
  `status_enum` VARCHAR(255) NOT NULL COMMENT '供应状态持久化码（{ SupplyStatus#getCode()}，B.10.8.1）',
  `intent_enum` VARCHAR(255) COMMENT 'intent枚举值',
  `category_enum` VARCHAR(255) NOT NULL COMMENT '供应类别持久化码（与 { com.openhis.health.domain.share.enums.SupplyCategory#getCode()} 对齐，B.10.8.1）',
  `priority_enum` VARCHAR(255) COMMENT 'priority枚举值',
  `summary_id` VARCHAR(64) COMMENT 'summary标识',
  `deliver_id` VARCHAR(64) COMMENT 'deliver标识',
  `patient_id` VARCHAR(64) COMMENT '患者标识',
  `item_table` VARCHAR(255) NOT NULL COMMENT '项table',
  `item_quantity` DECIMAL(18,2) NOT NULL COMMENT '行数量：入出库等为执行数量（拆零、正数）；盘点/损益等为盈亏数量（拆零，可正可负可零）',
  `total_quantity` DECIMAL(18,2) COMMENT '合计/实盘数量：盘点场景存实盘数量（拆零、≥0）；其它单据按业务口径使用',
  `item_id` VARCHAR(64) NOT NULL COMMENT '项标识',
  `unit_code` VARCHAR(255) NOT NULL COMMENT '单元编码',
  `occurrence_time` DATETIME(6) COMMENT 'occurrence时间',
  `practitioner_id` VARCHAR(64) COMMENT '医护人员标识',
  `supplier_id` VARCHAR(64) COMMENT '供应商标识',
  `reason` VARCHAR(255) COMMENT '原因',
  `source_type_enum` VARCHAR(255) COMMENT '单库房单据为空；双端点单据必填（出方）',
  `source_location_id` VARCHAR(64) COMMENT '单库房单据为空；双端点单据必填（出方）',
  `purpose_type_enum` VARCHAR(255) COMMENT '单库房单据必填；双端点单据必填',
  `purpose_location_id` VARCHAR(64) COMMENT '单库房就是目的；双端点为进方',
  `approver_id` VARCHAR(64) COMMENT 'approver标识',
  `approval_time` DATETIME(6) COMMENT 'approval时间',
  `applicant_id` VARCHAR(64) NOT NULL COMMENT 'applicant标识',
  `apply_time` DATETIME(6) COMMENT '提交审批时的申请时刻；草稿阶段可为空，提交时由服务端写入当前时间',
  `start_time` DATETIME(6) COMMENT '效期区间起点（与 { end_time} 成对；可空表示未维护）',
  `end_time` DATETIME(6) COMMENT '效期区间止点（入库入账时可用于库存项有效期等编排）',
  `lot_number` VARCHAR(255) COMMENT '批号',
  `trace_no` TEXT COMMENT '追踪编号',
  `price` DECIMAL(19,6) COMMENT '价格',
  `total_price` DECIMAL(19,6) COMMENT '合计价格',
  `remake` VARCHAR(255) COMMENT '备注',
  `profit_loss_price` DECIMAL(19,6) COMMENT '盘点盈亏金额；盘盈为正、盘亏为负；非盘点类型可空'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='工作流 supply request';
-- ----------------------------
-- Table structure for yb_catalog_download_cursor
-- ----------------------------
CREATE TABLE `yb_catalog_download_cursor` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `infno` VARCHAR(16) NOT NULL COMMENT '接口编号',
  `local_ver` VARCHAR(64) NOT NULL DEFAULT '0' COMMENT '医保目录下载游标（1301/1305 等文件型接口）',
  `last_file_qury_no` VARCHAR(40) COMMENT 'lastfilequry编号',
  `last_filename` VARCHAR(200) COMMENT '最近文件名',
  `last_success_at` DATETIME(6) COMMENT 'last成功时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保目录下载游标历史（每次成功入库追加一行，取最新一条为下次 1301 起点）';
-- ----------------------------
-- Table structure for yb_catalog_upload_record
-- ----------------------------
CREATE TABLE `yb_catalog_upload_record` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `operation` VARCHAR(8) NOT NULL COMMENT '操作类型',
  `product_table` VARCHAR(64) NOT NULL COMMENT '产品表名',
  `product_id` VARCHAR(64) NOT NULL COMMENT 'product标识',
  `list_type` VARCHAR(30) NOT NULL COMMENT 'list类型',
  `fixmedins_hilist_id` VARCHAR(30) NOT NULL COMMENT 'fixmedinshilist标识',
  `med_list_codg` VARCHAR(30) NOT NULL COMMENT '医疗目录编码',
  `platform_success` TINYINT(1) NOT NULL COMMENT 'platform成功',
  `msgid` VARCHAR(64) COMMENT '报文标识',
  `request_snapshot` TEXT COMMENT '申请快照',
  `response_snapshot` TEXT COMMENT 'response快照',
  `error_msg` VARCHAR(512) COMMENT '错误msg',
  `operator_id` VARCHAR(64) COMMENT '操作人标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 目录上传记录';
-- ----------------------------
-- Table structure for yb_clear_apply
-- ----------------------------
CREATE TABLE `yb_clear_apply` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `clr_type` VARCHAR(30) COMMENT 'clr类型',
  `clr_optins` VARCHAR(6) COMMENT '清算经办机构',
  `begndate` DATE COMMENT '开始日期',
  `enddate` DATE COMMENT '结束日期',
  `medfee_sumamt` DECIMAL(18,2) COMMENT '医疗费总额',
  `med_sumfee` DECIMAL(18,2) COMMENT '医保费用总额',
  `fund_appy_sum` DECIMAL(18,2) COMMENT '基金申请总额',
  `cash_payamt` DECIMAL(18,2) COMMENT '现金支付金额',
  `acct_pay` DECIMAL(18,2) COMMENT 'acct支付',
  `clr_appy_evt_id` VARCHAR(30) COMMENT 'clrappyevt标识',
  `clr_stas` VARCHAR(6) COMMENT 'clr状态',
  `status` VARCHAR(16) NOT NULL COMMENT '状态',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 清算申请';
-- ----------------------------
-- Table structure for yb_clinic_fee_upload
-- ----------------------------
CREATE TABLE `yb_clinic_fee_upload` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `charge_item_id` VARCHAR(64) NOT NULL COMMENT '收费项标识',
  `feedetl_sn` VARCHAR(30) NOT NULL COMMENT '费用明细流水号',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `chrg_bchno` VARCHAR(30) NOT NULL COMMENT '收费批次号',
  `pre_settle_id` VARCHAR(64) COMMENT '预结算标识',
  `upload_status` VARCHAR(16) NOT NULL COMMENT '上传状态',
  `det_item_fee_sumamt` DECIMAL(18,2) COMMENT '明细项目费用总额',
  `chrgitm_lv` VARCHAR(3) COMMENT '收费项目等级',
  `med_chrgitm_type` VARCHAR(6) COMMENT '医疗收费项目类别',
  `selfpay_prop` DECIMAL(5,4) COMMENT '自付比例',
  `fulamt_ownpay_amt` DECIMAL(18,2) COMMENT '全自费金额',
  `overlmt_amt` DECIMAL(18,2) COMMENT '超限价金额',
  `preselfpay_amt` DECIMAL(18,2) COMMENT '先行自付金额',
  `inscp_scp_amt` DECIMAL(18,2) COMMENT '符合政策范围金额',
  `lmt_used_flag` VARCHAR(3) COMMENT '限制使用标志',
  `platform_memo` VARCHAR(500) COMMENT '平台备注',
  `platform_result_json` TEXT COMMENT '平台分割结果JSON',
  `uploaded_at` DATETIME(6) COMMENT '上传时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='2204 门诊费用上传及平台分割结果';
-- ----------------------------
-- Table structure for yb_clinic_pre_settle
-- ----------------------------
CREATE TABLE `yb_clinic_pre_settle` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `payment_draft_id` VARCHAR(64) COMMENT '支付draft标识',
  `chrg_bchno` VARCHAR(30) NOT NULL COMMENT '收费批次号',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `psn_no` VARCHAR(30) NOT NULL COMMENT 'psn编号',
  `insuplc_admdvs` VARCHAR(6) COMMENT '参保地医保区划',
  `medfee_sumamt` DECIMAL(18,2) COMMENT '医疗费总额',
  `fund_pay_sumamt` DECIMAL(18,2) COMMENT 'fund支付sumamt',
  `acct_pay` DECIMAL(18,2) COMMENT 'acct支付',
  `psn_cash_pay` DECIMAL(18,2) COMMENT 'psncash支付',
  `charge_item_ids` TEXT COMMENT '收费项ids',
  `status` VARCHAR(16) NOT NULL COMMENT '状态',
  `med_type` VARCHAR(6) COMMENT '医疗类别',
  `dise_codg` VARCHAR(30) COMMENT '慢病诊断码',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `account_id` VARCHAR(64) COMMENT '账户标识',
  `mdtrt_cert_type` VARCHAR(3) COMMENT '就诊cert类型',
  `mdtrt_cert_no` VARCHAR(64) COMMENT '就诊cert编号',
  `insutype` VARCHAR(6) COMMENT '险种类型',
  `acct_used_flag` VARCHAR(1) COMMENT '个人账户使用标志',
  `psn_setlway` VARCHAR(6) COMMENT '个人结算方式',
  `fulamt_ownpay_amt` DECIMAL(18,2) COMMENT '全自费金额',
  `overlmt_selfpay` DECIMAL(18,2) COMMENT '超限价自费费用',
  `preselfpay_amt` DECIMAL(18,2) COMMENT '先行自付金额',
  `inscp_scp_amt` DECIMAL(18,2) COMMENT '符合政策范围金额'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='2206 预结算快照（按 chrg_bchno）';
-- ----------------------------
-- Table structure for yb_elep_prescription
-- ----------------------------
CREATE TABLE `yb_elep_prescription` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `patient_id` VARCHAR(64) NOT NULL COMMENT '患者标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `hosp_rxno` VARCHAR(64) NOT NULL COMMENT '院内处方号',
  `hi_rxno` VARCHAR(64) COMMENT '医保处方号',
  `rx_trace_code` VARCHAR(128) COMMENT 'rx追踪编码',
  `init_rxno` VARCHAR(64) COMMENT '初始处方号',
  `local_status` VARCHAR(32) NOT NULL COMMENT 'local状态',
  `rx_stas_codg` VARCHAR(8) COMMENT '处方状态编码',
  `rx_used_stas_codg` VARCHAR(8) COMMENT '处方使用状态编码',
  `prsc_time` DATETIME(6) COMMENT 'prsc时间',
  `prsc_dr_name` VARCHAR(64) COMMENT 'prscdr名称',
  `prsc_dept_name` VARCHAR(128) COMMENT 'prscdept名称',
  `main_diag_code` VARCHAR(32) COMMENT 'maindiag编码',
  `main_diag_name` VARCHAR(256) COMMENT 'maindiag名称',
  `rx_type_code` VARCHAR(8) COMMENT 'rx类型编码',
  `drug_summary` VARCHAR(512) COMMENT '药品摘要',
  `line_count` INT COMMENT '行数',
  `prescription_no` VARCHAR(64) COMMENT '处方编号',
  `rept_flag` VARCHAR(2) COMMENT 'rept标志位',
  `max_rept_cnt` INT COMMENT 'maxrept数量',
  `reptd_cnt` INT COMMENT 'reptd数量',
  `vali_end_time` DATETIME(6) COMMENT 'vali结束时间',
  `platform_synced_at` DATETIME(6) COMMENT 'platformsynced时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保电子处方处方';
-- ----------------------------
-- Table structure for yb_elep_prescription_snapshot
-- ----------------------------
CREATE TABLE `yb_elep_prescription_snapshot` (
  `prescription_id` VARCHAR(64) NOT NULL COMMENT '处方标识',
  `upload_request_json` TEXT COMMENT '上传申请JSON',
  `upload_response_json` TEXT COMMENT '上传responseJSON',
  `sign_response_json` TEXT COMMENT '体征responseJSON',
  `upload_confirm_json` TEXT COMMENT '上传confirmJSON',
  `pdf_file_path` VARCHAR(512) COMMENT 'PDF文件路径',
  `pdf_file_hash` VARCHAR(128) COMMENT 'PDFfile哈希',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保电子处方处方快照';
-- ----------------------------
-- Table structure for yb_elep_upload_log
-- ----------------------------
CREATE TABLE `yb_elep_upload_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `prescription_id` VARCHAR(64) NOT NULL COMMENT '处方标识',
  `op_code` VARCHAR(16) NOT NULL COMMENT 'op编码',
  `request_json` TEXT COMMENT '申请JSON',
  `response_json` TEXT COMMENT '响应JSON',
  `success` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '成功',
  `error_message` VARCHAR(1024) COMMENT '错误消息',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保电子处方上传日志';
-- ----------------------------
-- Table structure for yb_encounter_platform_map
-- ----------------------------
CREATE TABLE `yb_encounter_platform_map` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `psn_no` VARCHAR(30) COMMENT 'psn编号',
  `ipt_otp_no` VARCHAR(30) COMMENT 'iptotp编号',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `med_type` VARCHAR(6) NOT NULL DEFAULT '11' COMMENT 'med类型'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 就诊 platform map';
-- ----------------------------
-- Table structure for yb_inpatient_fee_upload
-- ----------------------------
CREATE TABLE `yb_inpatient_fee_upload` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `charge_item_id` VARCHAR(64) NOT NULL COMMENT '收费项标识',
  `feedetl_sn` VARCHAR(30) NOT NULL COMMENT '费用明细流水号',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `upload_status` VARCHAR(16) NOT NULL COMMENT '上传状态',
  `platform_result_json` TEXT COMMENT 'platform结果JSON',
  `uploaded_at` DATETIME(6) COMMENT 'uploaded时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `det_item_fee_sumamt` DECIMAL(18,4) COMMENT 'det项feesumamt',
  `chrgitm_lv` VARCHAR(3) COMMENT '收费项目等级',
  `med_chrgitm_type` VARCHAR(6) COMMENT '医疗收费项目类别',
  `selfpay_prop` DECIMAL(5,4) COMMENT '自付比例',
  `fulamt_ownpay_amt` DECIMAL(18,2) COMMENT '全自费金额',
  `overlmt_amt` DECIMAL(18,2) COMMENT '超限价金额',
  `preselfpay_amt` DECIMAL(18,2) COMMENT '先行自付金额',
  `inscp_scp_amt` DECIMAL(18,2) COMMENT '符合政策范围金额',
  `lmt_used_flag` VARCHAR(3) COMMENT '限制使用标志',
  `platform_memo` VARCHAR(500) COMMENT '平台备注'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 in患者 fee upload';
-- ----------------------------
-- Table structure for yb_inpatient_pre_settle
-- ----------------------------
CREATE TABLE `yb_inpatient_pre_settle` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `payment_draft_id` VARCHAR(64) NOT NULL COMMENT '支付draft标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `psn_no` VARCHAR(30) NOT NULL COMMENT 'psn编号',
  `med_type` VARCHAR(6) COMMENT 'med类型',
  `mid_setl_flag` VARCHAR(3) COMMENT 'mid结算标志位',
  `settle_mode` VARCHAR(20) COMMENT '结算模式',
  `medfee_sumamt` DECIMAL(18,2) COMMENT '医疗费总额',
  `fund_pay_sumamt` DECIMAL(18,2) COMMENT 'fund支付sumamt',
  `acct_pay` DECIMAL(18,2) COMMENT 'acct支付',
  `psn_cash_pay` DECIMAL(18,2) COMMENT 'psncash支付',
  `charge_item_ids` TEXT COMMENT '收费项ids',
  `setl_id` VARCHAR(30) COMMENT '结算标识',
  `status` VARCHAR(16) NOT NULL COMMENT '状态',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `account_id` VARCHAR(64) COMMENT '账户标识',
  `insuplc_admdvs` VARCHAR(6) COMMENT '参保地医保区划',
  `mdtrt_cert_type` VARCHAR(3) COMMENT '就诊cert类型',
  `mdtrt_cert_no` VARCHAR(64) COMMENT '就诊cert编号',
  `insutype` VARCHAR(6) COMMENT '险种类型',
  `acct_used_flag` VARCHAR(1) COMMENT '个人账户使用标志',
  `psn_setlway` VARCHAR(6) COMMENT '个人结算方式',
  `fulamt_ownpay_amt` DECIMAL(18,2) COMMENT '全自费金额',
  `overlmt_selfpay` DECIMAL(18,2) COMMENT '超限价自费费用',
  `preselfpay_amt` DECIMAL(18,2) COMMENT '先行自付金额',
  `inscp_scp_amt` DECIMAL(18,2) COMMENT '符合政策范围金额'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 in患者 pre settle';
-- ----------------------------
-- Table structure for yb_inv_upload
-- ----------------------------
CREATE TABLE `yb_inv_upload` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `contract_bus_no` VARCHAR(32) NOT NULL COMMENT '合同bus编号',
  `infno` VARCHAR(8) NOT NULL COMMENT '接口编号',
  `inv_data_type` VARCHAR(4) COMMENT '库存data类型',
  `fixmedins_bchno` VARCHAR(30) NOT NULL COMMENT 'fixmedins批次号',
  `med_list_codg` VARCHAR(50) COMMENT '医疗目录编码',
  `source_type` VARCHAR(32) NOT NULL COMMENT '来源类型',
  `source_id` VARCHAR(64) COMMENT '来源标识',
  `source_line_id` VARCHAR(64) COMMENT '来源line标识',
  `upload_status` VARCHAR(16) NOT NULL COMMENT '上传状态',
  `platform_ret_rslt` VARCHAR(8) COMMENT '平台返回结果',
  `platform_msg` VARCHAR(2000) COMMENT '平台消息',
  `msgid` VARCHAR(64) COMMENT '报文标识',
  `request_json` TEXT COMMENT '申请JSON',
  `response_json` TEXT COMMENT '响应JSON',
  `retry_count` INT NOT NULL DEFAULT 0 COMMENT '重试次数',
  `next_retry_at` DATETIME(6) COMMENT 'nextretry时间',
  `operator_id` VARCHAR(64) COMMENT '操作人标识',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 发票上传';
-- ----------------------------
-- Table structure for yb_inv_upload_trace
-- ----------------------------
CREATE TABLE `yb_inv_upload_trace` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `upload_id` VARCHAR(64) NOT NULL COMMENT '上传标识',
  `drug_trac_codg` VARCHAR(100) NOT NULL COMMENT 'drugtrac编码',
  `trdn_flag` VARCHAR(3) COMMENT 'trdn标志位',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 发票上传追踪';
-- ----------------------------
-- Table structure for yb_invoke_log
-- ----------------------------
CREATE TABLE `yb_invoke_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) COMMENT '合同标识',
  `contract_bus_no` VARCHAR(64) COMMENT '合同bus编号',
  `infno` VARCHAR(16) NOT NULL COMMENT '交易编号',
  `msgid` VARCHAR(64) COMMENT '发送方报文ID',
  `encounter_id` VARCHAR(64) COMMENT '就诊标识',
  `payment_draft_id` VARCHAR(64) COMMENT '支付draft标识',
  `chrg_bchno` VARCHAR(30) COMMENT '收费批次号',
  `pre_settle_id` VARCHAR(64) COMMENT '预结算标识',
  `settlement_record_id` VARCHAR(64) COMMENT '结算记录标识',
  `infcode` VARCHAR(8) COMMENT '平台返回码',
  `duration_ms` INT COMMENT '调用耗时毫秒',
  `request_json` TEXT COMMENT '请求JSON',
  `response_json` TEXT COMMENT '响应JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `infname` VARCHAR(128) COMMENT '交易编号对应中文名称（如 2401 入院办理）',
  `err_msg` VARCHAR(512) COMMENT '平台 err_msg 或调用异常摘要'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保平台网关调用日志';
-- ----------------------------
-- Table structure for yb_national_catalog_item
-- ----------------------------
CREATE TABLE `yb_national_catalog_item` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `list_type` VARCHAR(30) NOT NULL COMMENT 'list类型',
  `hilist_code` VARCHAR(30) NOT NULL COMMENT 'hilist编码',
  `hilist_name` VARCHAR(200) COMMENT 'hilist名称',
  `chrgitm_lv` VARCHAR(16) COMMENT '国家医保目录镜像行（1312 查询 / 1301 解析入库）',
  `lmt_used_flag` VARCHAR(16) COMMENT 'lmtused标志位',
  `begndate` DATE COMMENT '开始日期',
  `enddate` DATE COMMENT '结束日期',
  `vali_flag` VARCHAR(16) COMMENT 'vali标志位',
  `spec` VARCHAR(200) COMMENT '规格',
  `dosform` VARCHAR(200) COMMENT '剂型',
  `aprvno` VARCHAR(100) COMMENT '批准文号',
  `pinyin` VARCHAR(100) COMMENT '拼音',
  `raw_json` TEXT COMMENT '原始JSON',
  `source_infno` VARCHAR(16) COMMENT '来源infno',
  `source_file_qury_no` VARCHAR(40) COMMENT '1301 来源文件查询号（9102/1301）',
  `source_line_no` INT COMMENT '1301 TXT 行号（从 1 起）；NULL 表示 1312 等非文件行',
  `prodentp_name` VARCHAR(200) COMMENT '1301 生产企业名称（TXT 第 54 列）',
  `updt_time` DATETIME(6) COMMENT 'updt时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 国家目录项';
-- ----------------------------
-- Table structure for yb_person_cache
-- ----------------------------
CREATE TABLE `yb_person_cache` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `mdtrt_cert_type` VARCHAR(3) NOT NULL COMMENT '就诊cert类型',
  `mdtrt_cert_no` VARCHAR(64) NOT NULL COMMENT '就诊cert编号',
  `psn_no` VARCHAR(30) NOT NULL COMMENT 'psn编号',
  `insuplc_admdvs` VARCHAR(6) COMMENT '参保地医保区划',
  `insutype` VARCHAR(6) COMMENT '险种类型',
  `balc` DECIMAL(18,2) COMMENT '账户余额',
  `snapshot_json` TEXT NOT NULL COMMENT '快照JSON',
  `cached_at` DATETIME(6) NOT NULL COMMENT 'cached时间',
  `expire_at` DATETIME(6) NOT NULL COMMENT 'expire时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 人员缓存';
-- ----------------------------
-- Table structure for yb_platform_dict_item
-- ----------------------------
CREATE TABLE `yb_platform_dict_item` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `dict_type` VARCHAR(30) NOT NULL COMMENT '1901 type，医保区划默认 INSUPLC_ADMDVS',
  `dict_value` VARCHAR(20) NOT NULL COMMENT '1901 value，如 220100',
  `dict_label` VARCHAR(200) NOT NULL COMMENT '1901 label，展示地名',
  `parent_value` VARCHAR(20) COMMENT '父级值',
  `sort_order` INT COMMENT '排序号',
  `vali_flag` VARCHAR(3) COMMENT 'vali标志位',
  `platform_version` BIGINT COMMENT '平台版本',
  `query_admdvs` VARCHAR(6) COMMENT '查询admdvs',
  `source_contract_id` VARCHAR(64) COMMENT '来源合同标识',
  `synced_at` DATETIME(6) NOT NULL COMMENT 'synced时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='1901 平台字典镜像（医保区划 INSUPLC_ADMDVS 等）';
-- ----------------------------
-- Table structure for yb_platform_dict_sync_log
-- ----------------------------
CREATE TABLE `yb_platform_dict_sync_log` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `dict_type` VARCHAR(30) NOT NULL COMMENT 'dict类型',
  `query_admdvs` VARCHAR(6) COMMENT '查询admdvs',
  `parent_value` VARCHAR(20) COMMENT '父级值',
  `recursive` TINYINT(1) NOT NULL DEFAULT 1 COMMENT '是否递归',
  `contract_id` VARCHAR(64) COMMENT '合同标识',
  `rows_upserted` INT NOT NULL DEFAULT 0 COMMENT '写入/更新行数',
  `status` VARCHAR(16) NOT NULL COMMENT '状态',
  `error_message` TEXT COMMENT '错误消息',
  `started_at` DATETIME(6) NOT NULL COMMENT '开始时间',
  `finished_at` DATETIME(6) COMMENT '结束时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `version` INT NOT NULL DEFAULT 0 COMMENT '乐观锁版本号'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='1901 字典手动同步日志';
-- ----------------------------
-- Table structure for yb_pub_sign
-- ----------------------------
CREATE TABLE `yb_pub_sign` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `adm_vs` VARCHAR(16) NOT NULL COMMENT '行政区划版本',
  `fixmedins_code` VARCHAR(32) NOT NULL COMMENT 'fixmedins编码',
  `opter_no` VARCHAR(32) NOT NULL COMMENT 'opter编号',
  `sign_no` VARCHAR(64) NOT NULL COMMENT '体征编号',
  `sign_time` DATETIME(6) NOT NULL COMMENT '体征时间',
  `sign_date` DATE NOT NULL COMMENT '体征日期',
  `yb_username` VARCHAR(64) COMMENT '医保username',
  `status` VARCHAR(8) NOT NULL DEFAULT '1' COMMENT '医保 9001 签到流水（对齐 yb_pub_sign）',
  `sign_out_time` DATETIME(6) COMMENT '体征out时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL DEFAULT 0 COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 公示签章';
-- ----------------------------
-- Table structure for yb_recon_daily
-- ----------------------------
CREATE TABLE `yb_recon_daily` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `insutype` VARCHAR(6) COMMENT '险种类型',
  `clr_type` VARCHAR(6) COMMENT 'clr类型',
  `setl_optins` VARCHAR(6) COMMENT '结算optins',
  `stmt_begndate` DATE COMMENT 'stmt开始日期',
  `stmt_enddate` DATE COMMENT 'stmt结束日期',
  `medfee_sumamt` DECIMAL(18,2) COMMENT '医疗费总额',
  `fund_pay_sumamt` DECIMAL(18,2) COMMENT 'fund支付sumamt',
  `acct_pay` DECIMAL(18,2) COMMENT 'acct支付',
  `fixmedins_setl_cnt` INT COMMENT 'fixmedins结算数量',
  `stmt_rslt` VARCHAR(6) COMMENT 'stmt结果',
  `stmt_rslt_dscr` VARCHAR(200) COMMENT 'stmt结果dscr',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 日对账';
-- ----------------------------
-- Table structure for yb_recon_detail
-- ----------------------------
CREATE TABLE `yb_recon_detail` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `contract_bus_no` VARCHAR(64) NOT NULL COMMENT '合同bus编号',
  `setl_optins` VARCHAR(6) COMMENT '结算optins',
  `clr_type` VARCHAR(6) COMMENT 'clr类型',
  `refd_setl_flag` VARCHAR(3) COMMENT 'refd结算标志位',
  `stmt_begndate` DATE COMMENT 'stmt开始日期',
  `stmt_enddate` DATE COMMENT 'stmt结束日期',
  `upload_file_qury_no` VARCHAR(64) COMMENT '上传filequry编号',
  `upload_filename` VARCHAR(200) COMMENT '上传filename',
  `result_file_qury_no` VARCHAR(64) COMMENT 'resultfilequry编号',
  `result_filename` VARCHAR(200) COMMENT '结果filename',
  `dld_endtime` VARCHAR(30) COMMENT '下载结束时间',
  `row_count` INT COMMENT '行数',
  `mismatch_count` INT COMMENT '不一致笔数',
  `result_json` TEXT COMMENT '结果JSON',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 对账明细';
-- ----------------------------
-- Table structure for yb_settlement_correction
-- ----------------------------
CREATE TABLE `yb_settlement_correction` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `settlement_record_id` VARCHAR(64) COMMENT '结算记录标识',
  `psn_no` VARCHAR(30) NOT NULL COMMENT 'psn编号',
  `omsgid` VARCHAR(30) NOT NULL COMMENT '原发送方报文ID',
  `oinfno` VARCHAR(4) NOT NULL COMMENT '原交易编号',
  `encounter_class` VARCHAR(8) COMMENT '就诊class',
  `invoke_log_id` VARCHAR(64) COMMENT '调用日志标识',
  `corrected_at` DATETIME(6) NOT NULL COMMENT '冲正时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='2601 冲正交易审计凭证';
-- ----------------------------
-- Table structure for yb_settlement_fund_detail
-- ----------------------------
CREATE TABLE `yb_settlement_fund_detail` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `settlement_record_id` VARCHAR(64) NOT NULL COMMENT '结算记录标识',
  `fund_pay_type` VARCHAR(6) COMMENT '基金支付类型',
  `fund_pay_type_name` VARCHAR(128) COMMENT '基金支付类型名称',
  `inscp_scp_amt` DECIMAL(18,2) COMMENT '符合政策范围金额',
  `crt_payb_lmt_amt` DECIMAL(18,2) COMMENT '本次可支付限额金额',
  `fund_payamt` DECIMAL(18,2) COMMENT '基金支付金额',
  `setl_proc_info` TEXT COMMENT '结算过程信息',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='2207/2304 setldetail 基金分项明细';
-- ----------------------------
-- Table structure for yb_settlement_record
-- ----------------------------
CREATE TABLE `yb_settlement_record` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `contract_id` VARCHAR(64) NOT NULL COMMENT '合同标识',
  `encounter_id` VARCHAR(64) NOT NULL COMMENT '就诊标识',
  `payment_id` VARCHAR(64) COMMENT '支付标识',
  `pre_settle_id` VARCHAR(64) COMMENT 'presettle标识',
  `chrg_bchno` VARCHAR(30) NOT NULL COMMENT '收费批次号',
  `setl_id` VARCHAR(30) NOT NULL COMMENT '结算标识',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `psn_no` VARCHAR(30) NOT NULL COMMENT 'psn编号',
  `medfee_sumamt` DECIMAL(18,2) COMMENT '医疗费总额',
  `fund_pay_sumamt` DECIMAL(18,2) COMMENT 'fund支付sumamt',
  `acct_pay` DECIMAL(18,2) COMMENT 'acct支付',
  `psn_cash_pay` DECIMAL(18,2) COMMENT 'psncash支付',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `account_id` VARCHAR(64) COMMENT '账户标识',
  `encounter_class` VARCHAR(8) NOT NULL DEFAULT 'AMB' COMMENT '就诊class',
  `status` VARCHAR(16) NOT NULL DEFAULT 'CONFIRMED' COMMENT '状态',
  `settle_mode` VARCHAR(20) COMMENT '结算模式',
  `psn_name` VARCHAR(50) COMMENT '人员姓名',
  `insutype` VARCHAR(6) COMMENT '险种类型',
  `med_type` VARCHAR(6) COMMENT '医疗类别',
  `setl_time` DATETIME(6) COMMENT '结算时间',
  `fulamt_ownpay_amt` DECIMAL(18,2) COMMENT '全自费金额',
  `overlmt_selfpay` DECIMAL(18,2) COMMENT '超限价自费费用',
  `preselfpay_amt` DECIMAL(18,2) COMMENT '先行自付金额',
  `inscp_scp_amt` DECIMAL(18,2) COMMENT '符合政策范围金额',
  `hifp_pay` DECIMAL(18,2) COMMENT '基本医疗保险统筹基金支出',
  `cvlserv_pay` DECIMAL(18,2) COMMENT '公务员医疗补助资金支出',
  `hifmi_pay` DECIMAL(18,2) COMMENT '居民大病保险资金支出',
  `hifob_pay` DECIMAL(18,2) COMMENT '职工大额医疗费用补助基金支出',
  `hifes_pay` DECIMAL(18,2) COMMENT '企业补充医疗保险基金支出',
  `cvlserv_flag` VARCHAR(3) COMMENT '公务员标志',
  `pool_prop_selfpay` DECIMAL(18,2) COMMENT '基本医疗保险统筹基金支付比例',
  `maf_pay` DECIMAL(18,2) COMMENT '医疗救助基金支出',
  `oth_pay` DECIMAL(18,2) COMMENT '其他支出',
  `psn_part_amt` DECIMAL(18,2) COMMENT '个人负担总金额',
  `hosp_part_amt` DECIMAL(18,2) COMMENT '医院负担金额',
  `balc` DECIMAL(18,2) COMMENT '余额',
  `acct_mulaid_pay` DECIMAL(18,2) COMMENT '个人账户共济支付金额',
  `psn_type` VARCHAR(6) COMMENT '人员类别',
  `act_pay_dedc` DECIMAL(18,2) COMMENT '实际支付起付线',
  `hifdm_pay` DECIMAL(18,2) COMMENT '伤残人员医疗保障基金支出',
  `exp_content` TEXT COMMENT '扩展内容JSON',
  `medins_setl_id` VARCHAR(30) COMMENT '医药机构结算ID',
  `msgid_2207` VARCHAR(64) COMMENT '2207发送方报文ID',
  `clr_optins` VARCHAR(6) COMMENT '清算经办机构',
  `clr_way` VARCHAR(6) COMMENT '清算方式',
  `clr_type` VARCHAR(6) COMMENT '清算类别',
  `fund_breakdown_json` TEXT COMMENT '基金分项JSON'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保 结算记录';
-- ----------------------------
-- Table structure for yb_settlement_reversal
-- ----------------------------
CREATE TABLE `yb_settlement_reversal` (
  `id` VARCHAR(64) NOT NULL COMMENT '主键',
  `settlement_record_id` VARCHAR(64) NOT NULL COMMENT '结算记录标识',
  `revoke_setl_id` VARCHAR(30) COMMENT 'revoke结算标识',
  `mdtrt_id` VARCHAR(30) NOT NULL COMMENT '就诊标识',
  `psn_no` VARCHAR(30) NOT NULL COMMENT 'psn编号',
  `encounter_class` VARCHAR(8) NOT NULL COMMENT '就诊class',
  `medfee_sumamt` DECIMAL(18,2) COMMENT '医疗费总额',
  `fund_pay_sumamt` DECIMAL(18,2) COMMENT 'fund支付sumamt',
  `acct_pay` DECIMAL(18,2) COMMENT 'acct支付',
  `psn_cash_pay` DECIMAL(18,2) COMMENT 'psncash支付',
  `fund_breakdown_json` TEXT COMMENT '基金分项JSON',
  `reversed_at` DATETIME(6) NOT NULL COMMENT 'reversed时间',
  `created_at` DATETIME(6) NOT NULL COMMENT '创建时间',
  `updated_at` DATETIME(6) COMMENT '最后更新时间',
  `created_by` VARCHAR(64) COMMENT '创建人',
  `updated_by` VARCHAR(64) COMMENT '最后更新人',
  `is_deleted` TINYINT(1) NOT NULL DEFAULT 0 COMMENT '软删标记',
  `deleted_at` DATETIME(6) COMMENT '删除时间',
  `deleted_by` VARCHAR(64) COMMENT '删除人',
  `tenant_id` VARCHAR(64) NOT NULL COMMENT '租户标识',
  `invoke_log_id` VARCHAR(64) COMMENT '调用日志标识'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci COMMENT='医保结算reversal';

SET FOREIGN_KEY_CHECKS = 1;