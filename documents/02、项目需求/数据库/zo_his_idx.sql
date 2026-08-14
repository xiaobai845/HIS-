-- Change DataBase
USE `zo_his`;

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- Primary Key structure for table adm_account
ALTER TABLE `adm_account` ADD CONSTRAINT `adm_account_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_charge_item
ALTER TABLE `adm_charge_item` ADD CONSTRAINT `adm_charge_item_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_charge_item_definition
ALTER TABLE `adm_charge_item_definition` ADD CONSTRAINT `adm_charge_item_definition_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_device_definition
ALTER TABLE `adm_device_definition` ADD CONSTRAINT `adm_device_definition_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_encounter
ALTER TABLE `adm_encounter` ADD CONSTRAINT `adm_encounter_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_encounter_diagnosis
ALTER TABLE `adm_encounter_diagnosis` ADD CONSTRAINT `adm_encounter_diagnosis_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_encounter_location
ALTER TABLE `adm_encounter_location` ADD CONSTRAINT `adm_encounter_location_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_encounter_participant
ALTER TABLE `adm_encounter_participant` ADD CONSTRAINT `adm_encounter_participant_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_encounter_reason
ALTER TABLE `adm_encounter_reason` ADD CONSTRAINT `adm_encounter_reason_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_episode_of_care
ALTER TABLE `adm_episode_of_care` ADD CONSTRAINT `adm_episode_of_care_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_episode_of_care_encounter
ALTER TABLE `adm_episode_of_care_encounter` ADD CONSTRAINT `adm_episode_of_care_encounter_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_healthcare_service
ALTER TABLE `adm_healthcare_service` ADD CONSTRAINT `adm_healthcare_service_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_invoice
ALTER TABLE `adm_invoice` ADD CONSTRAINT `adm_invoice_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_location
ALTER TABLE `adm_location` ADD CONSTRAINT `adm_location_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_organization
ALTER TABLE `adm_organization` ADD CONSTRAINT `adm_organization_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_patient
ALTER TABLE `adm_patient` ADD CONSTRAINT `adm_patient_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_patient_identifier
ALTER TABLE `adm_patient_identifier` ADD CONSTRAINT `adm_patient_identifier_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_patient_student
ALTER TABLE `adm_patient_student` ADD CONSTRAINT `adm_patient_student_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table adm_pr_assign
CREATE INDEX `idx_adm_pr_assign_role_id` ON `adm_pr_assign` (`role_id`);
ALTER TABLE `adm_pr_assign` ADD CONSTRAINT `ck_adm_pr_assign_org_or_location_not_null` CHECK (org_id IS NOT NULL OR location_id IS NOT NULL);
-- Primary Key structure for table adm_pr_assign
ALTER TABLE `adm_pr_assign` ADD CONSTRAINT `adm_pr_assign_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_pr_assign_schedule
ALTER TABLE `adm_pr_assign_schedule` ADD CONSTRAINT `adm_pr_assign_schedule_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_pr_assign_service
ALTER TABLE `adm_pr_assign_service` ADD CONSTRAINT `adm_pr_assign_service_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table adm_practitioner
ALTER TABLE `adm_practitioner` ADD CONSTRAINT `adm_practitioner_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table adm_specimen_definition
CREATE INDEX `idx_adm_specimen_definition_status_enum` ON `adm_specimen_definition` (`status_enum`(64));
CREATE INDEX `idx_adm_specimen_definition_type_enum` ON `adm_specimen_definition` (`type_enum`(64));
CREATE UNIQUE INDEX `uk_adm_specimen_definition_bus_no` ON `adm_specimen_definition` (`bus_no`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table adm_specimen_definition
ALTER TABLE `adm_specimen_definition` ADD CONSTRAINT `adm_specimen_definition_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_bed_reservation_ext
CREATE UNIQUE INDEX `uk_bkg_bed_reservation_ext_bed_date_active` ON `bkg_bed_reservation_ext` (`location_id`, `intended_admission_date`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_bed_reservation_ext
ALTER TABLE `bkg_bed_reservation_ext` ADD CONSTRAINT `bkg_bed_reservation_ext_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_calendar_exception
CREATE INDEX `idx_bkg_calendar_exc_org_date` ON `bkg_calendar_exception` (`organization_id`, `exception_date`, `range_end`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_calendar_exception
ALTER TABLE `bkg_calendar_exception` ADD CONSTRAINT `bkg_calendar_exception_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_channel_config
ALTER TABLE `bkg_channel_config` ADD CONSTRAINT `bkg_channel_config_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_diagnostic_resource_map
ALTER TABLE `bkg_diagnostic_resource_map` ADD CONSTRAINT `bkg_diagnostic_resource_map_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_group_checkup_batch
ALTER TABLE `bkg_group_checkup_batch` ADD CONSTRAINT `bkg_group_checkup_batch_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_group_checkup_org
ALTER TABLE `bkg_group_checkup_org` ADD CONSTRAINT `bkg_group_checkup_org_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_group_checkup_roster
ALTER TABLE `bkg_group_checkup_roster` ADD CONSTRAINT `bkg_group_checkup_roster_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_health_check_booking_ext
ALTER TABLE `bkg_health_check_booking_ext` ADD CONSTRAINT `bkg_health_check_booking_ext_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_health_check_package
ALTER TABLE `bkg_health_check_package` ADD CONSTRAINT `bkg_health_check_package_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_health_check_package_item
ALTER TABLE `bkg_health_check_package_item` ADD CONSTRAINT `bkg_health_check_package_item_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_queue_display_config
ALTER TABLE `bkg_queue_display_config` ADD CONSTRAINT `bkg_queue_display_config_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_registration_policy
ALTER TABLE `bkg_registration_policy` ADD CONSTRAINT `bkg_registration_policy_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_release_policy
ALTER TABLE `bkg_release_policy` ADD CONSTRAINT `bkg_release_policy_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table bkg_resource_profile
ALTER TABLE `bkg_resource_profile` ADD CONSTRAINT `bkg_resource_profile_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_schedule_change_policy
CREATE INDEX `idx_bkg_schedule_change_policy_org` ON `bkg_schedule_change_policy` (`organization_id`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_schedule_change_policy
ALTER TABLE `bkg_schedule_change_policy` ADD CONSTRAINT `bkg_schedule_change_policy_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_schedule_template
CREATE INDEX `idx_bkg_schedule_tpl_org` ON `bkg_schedule_template` (`organization_id`, `template_code`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_schedule_template
ALTER TABLE `bkg_schedule_template` ADD CONSTRAINT `bkg_schedule_template_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_slot_provision_template
CREATE INDEX `idx_bkg_slot_provision_tpl_org` ON `bkg_slot_provision_template` (`organization_id`, `template_code`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_slot_provision_template
ALTER TABLE `bkg_slot_provision_template` ADD CONSTRAINT `bkg_slot_provision_template_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_stop_clinic_slot_freeze
CREATE INDEX `idx_bkg_stop_clinic_slot_freeze_expires` ON `bkg_stop_clinic_slot_freeze` (`expires_at`); -- WHERE is_deleted = false
CREATE INDEX `idx_bkg_stop_clinic_slot_freeze_schedule` ON `bkg_stop_clinic_slot_freeze` (`schedule_id`); -- WHERE is_deleted = false
CREATE INDEX `idx_bkg_stop_clinic_slot_freeze_slot` ON `bkg_stop_clinic_slot_freeze` (`slot_id`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_stop_clinic_slot_freeze
ALTER TABLE `bkg_stop_clinic_slot_freeze` ADD CONSTRAINT `bkg_stop_clinic_slot_freeze_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_waitlist_entry
CREATE INDEX `idx_waitlist_patient` ON `bkg_waitlist_entry` (`patient_id`, `status`); -- WHERE is_deleted = false
CREATE INDEX `idx_waitlist_slot_status` ON `bkg_waitlist_entry` (`slot_id`, `status`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_waitlist_entry
ALTER TABLE `bkg_waitlist_entry` ADD CONSTRAINT `bkg_waitlist_entry_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_week_schedule_template
CREATE INDEX `idx_bkg_week_sched_tpl_org` ON `bkg_week_schedule_template` (`organization_id`, `template_code`); -- WHERE is_deleted = false
CREATE INDEX `idx_bkg_week_sched_tpl_org_default` ON `bkg_week_schedule_template` (`organization_id`, `is_default`); -- WHERE is_deleted = false AND is_default = true
-- Primary Key structure for table bkg_week_schedule_template
ALTER TABLE `bkg_week_schedule_template` ADD CONSTRAINT `bkg_week_schedule_template_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table bkg_week_schedule_template_item
CREATE INDEX `idx_bkg_week_sched_tpl_item_week` ON `bkg_week_schedule_template_item` (`week_schedule_template_id`, `weekday`, `sort_no`); -- WHERE is_deleted = false
-- Primary Key structure for table bkg_week_schedule_template_item
ALTER TABLE `bkg_week_schedule_template_item` ADD CONSTRAINT `bkg_week_schedule_template_item_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cln_allergy_intolerance
ALTER TABLE `cln_allergy_intolerance` ADD CONSTRAINT `cln_allergy_intolerance_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cln_condition
ALTER TABLE `cln_condition` ADD CONSTRAINT `cln_condition_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cln_condition_definition
ALTER TABLE `cln_condition_definition` ADD CONSTRAINT `cln_condition_definition_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cln_diagnostic_report
CREATE UNIQUE INDEX `uk_cln_dr_encounter` ON `cln_diagnostic_report` (`encounter_id`); -- WHERE is_deleted = false
-- Primary Key structure for table cln_diagnostic_report
ALTER TABLE `cln_diagnostic_report` ADD CONSTRAINT `cln_diagnostic_report_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cln_diagnostic_report_index
CREATE UNIQUE INDEX `uk_cln_dr_index_unique_key` ON `cln_diagnostic_report_index` (`unique_key`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table cln_diagnostic_report_index
ALTER TABLE `cln_diagnostic_report_index` ADD CONSTRAINT `cln_diagnostic_report_index_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cln_observation
CREATE INDEX `idx_cln_obs_encounter` ON `cln_observation` (`encounter_id`); -- WHERE is_deleted = false
CREATE INDEX `idx_cln_obs_sr_def` ON `cln_observation` (`service_request_id`, `definition_id`); -- WHERE is_deleted = false
-- Primary Key structure for table cln_observation
ALTER TABLE `cln_observation` ADD CONSTRAINT `cln_observation_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cln_observation_definition
CREATE UNIQUE INDEX `uk_cln_obs_def_tenant_code` ON `cln_observation_definition` (`tenant_id`, `code`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table cln_observation_definition
ALTER TABLE `cln_observation_definition` ADD CONSTRAINT `cln_observation_definition_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cln_procedure
CREATE UNIQUE INDEX `uk_cln_procedure_request_occurrence_terminal` ON `cln_procedure` (`request_id`, `request_table`(64), `occurrence_time`); -- WHERE is_deleted = false AND occurrence_slot_active = true AND (status_enum = ANY (ARRAY['COMPLETED', 'STOPPED'][])); COMMENT ON INDEX `uk_cln_procedure_request_occurrence_terminal` IS '同请求锚点+occurrence 仅允许一条有效终态占用（COMPLETED/STOPPED）'
-- Primary Key structure for table cln_procedure
ALTER TABLE `cln_procedure` ADD CONSTRAINT `cln_procedure_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cln_procedure_performer
ALTER TABLE `cln_procedure_performer` ADD CONSTRAINT `cln_procedure_performer_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_activity_execution_location
ALTER TABLE `cus_activity_execution_location` ADD CONSTRAINT `cus_activity_execution_location_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cus_activity_observation_link
CREATE UNIQUE INDEX `uk_aol_activity_od` ON `cus_activity_observation_link` (`activity_definition_id`, `observation_definition_id`); -- WHERE is_deleted = false
-- Primary Key structure for table cus_activity_observation_link
ALTER TABLE `cus_activity_observation_link` ADD CONSTRAINT `cus_activity_observation_link_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cus_charge_item_auto_gen
CREATE INDEX `idx_cus_charge_item_auto_gen_encounter_id` ON `cus_charge_item_auto_gen` (`encounter_id`); -- WHERE is_deleted = false
-- Primary Key structure for table cus_charge_item_auto_gen
ALTER TABLE `cus_charge_item_auto_gen` ADD CONSTRAINT `cus_charge_item_auto_gen_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_condition_template
ALTER TABLE `cus_condition_template` ADD CONSTRAINT `cus_condition_template_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_encounter_history
ALTER TABLE `cus_encounter_history` ADD CONSTRAINT `cus_encounter_history_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_frequency
ALTER TABLE `cus_frequency` ADD CONSTRAINT `cus_frequency_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cus_order_template
CREATE INDEX `idx_cus_order_template_source_list` ON `cus_order_template` (`tenant_id`, `object_id`, `binding_enum`(64), `template_source_enum`(64), `template_kind_enum`(64), `status_enum`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table cus_order_template
ALTER TABLE `cus_order_template` ADD CONSTRAINT `cus_order_template_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_order_template_line
ALTER TABLE `cus_order_template_line` ADD CONSTRAINT `cus_order_template_line_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cus_price_adjustment
CREATE INDEX `idx_cus_price_adjustment_bus_no` ON `cus_price_adjustment` (`bus_no`(64));
CREATE INDEX `idx_cus_price_adjustment_item_pending` ON `cus_price_adjustment` (`item_table`(64), `item_id`, `status_enum`(64));
-- Primary Key structure for table cus_price_adjustment
ALTER TABLE `cus_price_adjustment` ADD CONSTRAINT `cus_price_adjustment_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table cus_price_adjustment_detail
CREATE INDEX `idx_cus_price_adjustment_detail_adjustment_id` ON `cus_price_adjustment_detail` (`adjustment_id`);
-- Primary Key structure for table cus_price_adjustment_detail
ALTER TABLE `cus_price_adjustment_detail` ADD CONSTRAINT `cus_price_adjustment_detail_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_service_device_template
ALTER TABLE `cus_service_device_template` ADD CONSTRAINT `cus_service_device_template_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_service_location_template
ALTER TABLE `cus_service_location_template` ADD CONSTRAINT `cus_service_location_template_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_supplier
ALTER TABLE `cus_supplier` ADD CONSTRAINT `cus_supplier_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_terminology_code_mapping
ALTER TABLE `cus_terminology_code_mapping` ADD CONSTRAINT `cus_terminology_code_mapping_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table cus_trace_number_record
ALTER TABLE `cus_trace_number_record` ADD CONSTRAINT `cus_trace_number_record_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table dia_body_structure
ALTER TABLE `dia_body_structure` ADD CONSTRAINT `dia_body_structure_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table dia_vital_sign
CREATE INDEX `idx_dia_vital_sign_encounter_recorded` ON `dia_vital_sign` (`encounter_id`, `recorded_at`); -- WHERE is_deleted = false
CREATE INDEX `idx_dia_vital_sign_encounter_type_recorded` ON `dia_vital_sign` (`encounter_id`, `type_enum`, `recorded_at`); -- WHERE is_deleted = false
CREATE INDEX `idx_dia_vital_sign_patient_recorded` ON `dia_vital_sign` (`patient_id`, `recorded_at`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_dia_vital_sign_bus_no` ON `dia_vital_sign` (`tenant_id`, `bus_no`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table dia_vital_sign
ALTER TABLE `dia_vital_sign` ADD CONSTRAINT `dia_vital_sign_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table dia_vital_sign_detail
CREATE INDEX `idx_dia_vital_sign_detail_vital_sign_id` ON `dia_vital_sign_detail` (`vital_sign_id`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_dia_vital_sign_detail_natural_key` ON `dia_vital_sign_detail` (`tenant_id`, `vital_sign_id`, `term_code`(64), `item_code`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table dia_vital_sign_detail
ALTER TABLE `dia_vital_sign_detail` ADD CONSTRAINT `dia_vital_sign_detail_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table doc_inventory_item_snapshot
CREATE INDEX `idx_doc_inv_snap_tenant_bus` ON `doc_inventory_item_snapshot` (`tenant_id`, `bus_no`); -- WHERE is_deleted = false
CREATE INDEX `idx_doc_inv_snap_tenant_bus_py` ON `doc_inventory_item_snapshot` (`tenant_id`, `bus_no`, `py_str`(64)); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_doc_inv_snap_tenant_bus_item` ON `doc_inventory_item_snapshot` (`tenant_id`, `bus_no`, `inventory_item_id`); -- WHERE is_deleted = false
-- Primary Key structure for table doc_inventory_item_snapshot
ALTER TABLE `doc_inventory_item_snapshot` ADD CONSTRAINT `doc_inventory_item_snapshot_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table emr_document
CREATE INDEX `idx_emr_document_encounter` ON `emr_document` (`encounter_id`);
CREATE INDEX `idx_emr_document_patient` ON `emr_document` (`patient_id`);
CREATE INDEX `idx_emr_document_source_template` ON `emr_document` (`source_template_id`);
CREATE INDEX `idx_emr_document_status` ON `emr_document` (`status`);
CREATE INDEX `idx_emr_document_tenant` ON `emr_document` (`tenant_id`);
CREATE INDEX `idx_emr_document_type` ON `emr_document` (`document_type_code`);
-- Primary Key structure for table emr_document
ALTER TABLE `emr_document` ADD CONSTRAINT `emr_document_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table emr_document_data_item_index
CREATE INDEX `idx_emr_doc_data_item_document` ON `emr_document_data_item_index` (`document_id`);
CREATE INDEX `idx_emr_doc_data_item_name` ON `emr_document_data_item_index` (`data_item_name`(64), `document_id`);
CREATE INDEX `idx_emr_doc_data_item_tenant` ON `emr_document_data_item_index` (`tenant_id`);
-- Primary Key structure for table emr_document_data_item_index
ALTER TABLE `emr_document_data_item_index` ADD CONSTRAINT `emr_document_data_item_index_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table emr_document_type
CREATE INDEX `idx_emr_document_type_enabled` ON `emr_document_type` (`is_enabled`);
CREATE INDEX `idx_emr_document_type_tenant` ON `emr_document_type` (`tenant_id`);
CREATE UNIQUE INDEX `uk_emr_document_type_code` ON `emr_document_type` (`code`);
-- Primary Key structure for table emr_document_type
ALTER TABLE `emr_document_type` ADD CONSTRAINT `emr_document_type_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table emr_document_version
CREATE INDEX `idx_emr_document_version_created_at` ON `emr_document_version` (`created_at`);
CREATE INDEX `idx_emr_document_version_doc` ON `emr_document_version` (`document_id`);
CREATE INDEX `idx_emr_document_version_tenant` ON `emr_document_version` (`tenant_id`);
-- Primary Key structure for table emr_document_version
ALTER TABLE `emr_document_version` ADD CONSTRAINT `emr_document_version_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table emr_metadata_field_def
CREATE INDEX `idx_emr_metadata_field_enabled` ON `emr_metadata_field_def` (`is_enabled`);
CREATE INDEX `idx_emr_metadata_field_source` ON `emr_metadata_field_def` (`value_source`);
CREATE INDEX `idx_emr_metadata_field_tenant` ON `emr_metadata_field_def` (`tenant_id`);
CREATE UNIQUE INDEX `uk_emr_metadata_field_key_tenant` ON `emr_metadata_field_def` (`field_key`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table emr_metadata_field_def
ALTER TABLE `emr_metadata_field_def` ADD CONSTRAINT `emr_metadata_field_def_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table emr_template
CREATE INDEX `idx_emr_template_enabled` ON `emr_template` (`is_enabled`);
CREATE INDEX `idx_emr_template_enc_class_code` ON `emr_template` (`encounter_class_code`);
CREATE INDEX `idx_emr_template_encounter_class` ON `emr_template` (`encounter_class_enum`);
CREATE INDEX `idx_emr_template_encounter_type` ON `emr_template` (`encounter_type_enum`);
CREATE INDEX `idx_emr_template_org` ON `emr_template` (`organization_id`);
CREATE INDEX `idx_emr_template_owner_practitioner` ON `emr_template` (`owner_practitioner_id`);
CREATE INDEX `idx_emr_template_scope` ON `emr_template` (`scope_level`);
CREATE INDEX `idx_emr_template_tenant` ON `emr_template` (`tenant_id`);
CREATE INDEX `idx_emr_template_type` ON `emr_template` (`document_type_code`);
CREATE UNIQUE INDEX `uk_emr_template_code` ON `emr_template` (`code`);
-- Primary Key structure for table emr_template
ALTER TABLE `emr_template` ADD CONSTRAINT `emr_template_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table fin_cashier_settlement
CREATE UNIQUE INDEX `uk_fin_cashier_settlement_bus_no` ON `fin_cashier_settlement` (`tenant_id`, `bus_no`); -- WHERE is_deleted = false
-- Primary Key structure for table fin_cashier_settlement
ALTER TABLE `fin_cashier_settlement` ADD CONSTRAINT `fin_cashier_settlement_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table fin_contract
ALTER TABLE `fin_contract` ADD CONSTRAINT `fin_contract_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table fin_payment_rec_detail
ALTER TABLE `fin_payment_rec_detail` ADD CONSTRAINT `fin_payment_rec_detail_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table fin_payment_rec_static
ALTER TABLE `fin_payment_rec_static` ADD CONSTRAINT `fin_payment_rec_static_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table fin_payment_reconciliation
CREATE INDEX `idx_fin_payment_cashier_settlement` ON `fin_payment_reconciliation` (`enterer_id`, `bill_date`, `cashier_settlement_id`); -- WHERE is_deleted = false
-- Primary Key structure for table fin_payment_reconciliation
ALTER TABLE `fin_payment_reconciliation` ADD CONSTRAINT `fin_payment_reconciliation_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table fin_payment_yb_settlement
CREATE INDEX `idx_fin_payment_yb_settlement_payment` ON `fin_payment_yb_settlement` (`reconciliation_id`, `status`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_fin_payment_yb_settlement_payment_setl` ON `fin_payment_yb_settlement` (`reconciliation_id`, `setl_id`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table fin_payment_yb_settlement
ALTER TABLE `fin_payment_yb_settlement` ADD CONSTRAINT `fin_payment_yb_settlement_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table flyway_schema_history
CREATE INDEX `flyway_schema_history_s_idx` ON `flyway_schema_history` (`success`);
-- Primary Key structure for table flyway_schema_history
ALTER TABLE `flyway_schema_history` ADD CONSTRAINT `flyway_schema_history_pk` PRIMARY KEY (`installed_rank`);
-- Indexes structure for table flyway_schema_history_booking
CREATE INDEX `flyway_schema_history_booking_s_idx` ON `flyway_schema_history_booking` (`success`);
-- Primary Key structure for table flyway_schema_history_booking
ALTER TABLE `flyway_schema_history_booking` ADD CONSTRAINT `flyway_schema_history_booking_pk` PRIMARY KEY (`installed_rank`);
-- Indexes structure for table flyway_schema_history_chs
CREATE INDEX `flyway_schema_history_chs_s_idx` ON `flyway_schema_history_chs` (`success`);
-- Primary Key structure for table flyway_schema_history_chs
ALTER TABLE `flyway_schema_history_chs` ADD CONSTRAINT `flyway_schema_history_chs_pk` PRIMARY KEY (`installed_rank`);
-- Indexes structure for table flyway_schema_history_elep
CREATE INDEX `flyway_schema_history_elep_s_idx` ON `flyway_schema_history_elep` (`success`);
-- Primary Key structure for table flyway_schema_history_elep
ALTER TABLE `flyway_schema_history_elep` ADD CONSTRAINT `flyway_schema_history_elep_pk` PRIMARY KEY (`installed_rank`);
-- Indexes structure for table flyway_schema_history_emr
CREATE INDEX `flyway_schema_history_emr_s_idx` ON `flyway_schema_history_emr` (`success`);
-- Primary Key structure for table flyway_schema_history_emr
ALTER TABLE `flyway_schema_history_emr` ADD CONSTRAINT `flyway_schema_history_emr_pk` PRIMARY KEY (`installed_rank`);
-- Primary Key structure for table inventory_lock
ALTER TABLE `inventory_lock` ADD CONSTRAINT `inventory_lock_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table med_medication_definition
ALTER TABLE `med_medication_definition` ADD CONSTRAINT `med_medication_definition_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table med_medication_dispense
ALTER TABLE `med_medication_dispense` ADD CONSTRAINT `med_medication_dispense_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table med_medication_request
ALTER TABLE `med_medication_request` ADD CONSTRAINT `med_medication_request_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_borrow_request
CREATE INDEX `idx_mrms_borrow_case_record` ON `mrms_borrow_request` (`case_record_id`); -- WHERE is_deleted = false
CREATE INDEX `idx_mrms_borrow_tenant_status` ON `mrms_borrow_request` (`tenant_id`, `status_code`, `created_at`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_borrow_request
ALTER TABLE `mrms_borrow_request` ADD CONSTRAINT `mrms_borrow_request_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_case_record
CREATE INDEX `idx_mrms_case_list` ON `mrms_case_record` (`tenant_id`, `dscg_time`, `status_code`, `adm_caty_name`(64));
CREATE INDEX `idx_mrms_case_list_atddr` ON `mrms_case_record` (`tenant_id`, `atddr_practitioner_id`, `dscg_time`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_mrms_case_encounter` ON `mrms_case_record` (`tenant_id`, `encounter_id`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_mrms_case_medcasno` ON `mrms_case_record` (`tenant_id`, `medcasno`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_case_record
ALTER TABLE `mrms_case_record` ADD CONSTRAINT `mrms_case_record_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_case_record_homepage
CREATE UNIQUE INDEX `uk_mrms_homepage_case` ON `mrms_case_record_homepage` (`case_record_id`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_case_record_homepage
ALTER TABLE `mrms_case_record_homepage` ADD CONSTRAINT `mrms_case_record_homepage_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_homepage_diagnosis
CREATE INDEX `idx_mrms_homepage_diag_case` ON `mrms_homepage_diagnosis` (`case_record_id`, `diag_type_code`);
-- Primary Key structure for table mrms_homepage_diagnosis
ALTER TABLE `mrms_homepage_diagnosis` ADD CONSTRAINT `mrms_homepage_diagnosis_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_homepage_procedure
CREATE INDEX `idx_mrms_homepage_proc_case` ON `mrms_homepage_procedure` (`case_record_id`);
-- Primary Key structure for table mrms_homepage_procedure
ALTER TABLE `mrms_homepage_procedure` ADD CONSTRAINT `mrms_homepage_procedure_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_medcasno_sequence
CREATE UNIQUE INDEX `uk_mrms_medcasno_seq` ON `mrms_medcasno_sequence` (`tenant_id`, `year_value`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_medcasno_sequence
ALTER TABLE `mrms_medcasno_sequence` ADD CONSTRAINT `mrms_medcasno_sequence_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_overdue_notify_log
CREATE INDEX `idx_mrms_overdue_notify_cr` ON `mrms_overdue_notify_log` (`case_record_id`, `notify_date`);
CREATE UNIQUE INDEX `uk_mrms_overdue_notify_day` ON `mrms_overdue_notify_log` (`case_record_id`, `notify_type_code`, `notify_date`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_overdue_notify_log
ALTER TABLE `mrms_overdue_notify_log` ADD CONSTRAINT `mrms_overdue_notify_log_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_qc_defect
CREATE INDEX `idx_mrms_qc_defect_cr_rule` ON `mrms_qc_defect` (`case_record_id`, `rule_code`); -- WHERE is_deleted = false
CREATE INDEX `idx_mrms_qc_defect_cr_status` ON `mrms_qc_defect` (`case_record_id`, `status_code`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_qc_defect
ALTER TABLE `mrms_qc_defect` ADD CONSTRAINT `mrms_qc_defect_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_qc_rule
CREATE UNIQUE INDEX `uk_mrms_qc_rule_tenant_code` ON `mrms_qc_rule` (`tenant_id`, `rule_code`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_qc_rule
ALTER TABLE `mrms_qc_rule` ADD CONSTRAINT `mrms_qc_rule_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_qc_run
CREATE INDEX `idx_mrms_qc_run_cr` ON `mrms_qc_run` (`case_record_id`, `finished_at`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_qc_run
ALTER TABLE `mrms_qc_run` ADD CONSTRAINT `mrms_qc_run_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_required_doc_type
CREATE UNIQUE INDEX `uk_mrms_required_doc_type` ON `mrms_required_doc_type` (`tenant_id`, `document_type_code`, `encounter_class_code`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_required_doc_type
ALTER TABLE `mrms_required_doc_type` ADD CONSTRAINT `mrms_required_doc_type_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table mrms_upload_log
CREATE INDEX `idx_mrms_upload_log_cr` ON `mrms_upload_log` (`case_record_id`, `created_at`); -- WHERE is_deleted = false
CREATE INDEX `idx_mrms_upload_log_tenant_status` ON `mrms_upload_log` (`tenant_id`, `status_code`, `created_at`); -- WHERE is_deleted = false
-- Primary Key structure for table mrms_upload_log
ALTER TABLE `mrms_upload_log` ADD CONSTRAINT `mrms_upload_log_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table peis_auto_express
CREATE INDEX `idx_peis_auto_express_rule_type` ON `peis_auto_express` (`tenant_id`, `rule_type_code`, `status_enum`); -- WHERE is_deleted = false
-- Primary Key structure for table peis_auto_express
ALTER TABLE `peis_auto_express` ADD CONSTRAINT `peis_auto_express_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table peis_common_result
ALTER TABLE `peis_common_result` ADD CONSTRAINT `peis_common_result_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table peis_config
CREATE UNIQUE INDEX `uk_peis_config_tenant_key` ON `peis_config` (`tenant_id`, `config_key`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table peis_config
ALTER TABLE `peis_config` ADD CONSTRAINT `peis_config_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table peis_encounter_ext
CREATE INDEX `idx_peis_enc_ext_bus_no` ON `peis_encounter_ext` (`bus_no`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table peis_encounter_ext
ALTER TABLE `peis_encounter_ext` ADD CONSTRAINT `peis_encounter_ext_pkey` PRIMARY KEY (`encounter_id`);
-- Primary Key structure for table peis_report_grant_ext
ALTER TABLE `peis_report_grant_ext` ADD CONSTRAINT `peis_report_grant_ext_pkey` PRIMARY KEY (`diagnostic_report_id`);
-- Primary Key structure for table peis_service_request_ext
ALTER TABLE `peis_service_request_ext` ADD CONSTRAINT `peis_service_request_ext_pkey` PRIMARY KEY (`service_request_id`);
ALTER TABLE `prt_print_binding` ADD CONSTRAINT `uk_prt_print_binding` UNIQUE (`tenant_id`, `organization_id`, `binding_code`);
-- Primary Key structure for table prt_print_binding
ALTER TABLE `prt_print_binding` ADD CONSTRAINT `prt_print_binding_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table prt_print_event_log
CREATE INDEX `idx_prt_log_bus_no` ON `prt_print_event_log` (`tenant_id`, `bus_no`, `created_at`); -- WHERE is_deleted = false
CREATE INDEX `idx_prt_log_tenant_time` ON `prt_print_event_log` (`tenant_id`, `created_at`); -- WHERE is_deleted = false
CREATE INDEX `idx_prt_log_trace` ON `prt_print_event_log` (`trace_id`); -- WHERE is_deleted = false
-- Primary Key structure for table prt_print_event_log
ALTER TABLE `prt_print_event_log` ADD CONSTRAINT `prt_print_event_log_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table prt_template
CREATE INDEX `idx_prt_template_lookup` ON `prt_template` (`tenant_id`, `bus_no`, `status`, `version`); -- WHERE is_deleted = false
CREATE INDEX `idx_prt_template_scenario` ON `prt_template` (`tenant_id`, `scenario_code`, `status`, `version`); -- WHERE is_deleted = false AND scenario_code IS NOT NULL
CREATE UNIQUE INDEX `uk_prt_template_ver` ON `prt_template` (`tenant_id`, `organization_id`, `bus_no`, `status`, `version`); -- WHERE is_deleted = false
-- Primary Key structure for table prt_template
ALTER TABLE `prt_template` ADD CONSTRAINT `prt_template_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table ter_code_system
CREATE INDEX `idx_code_system_created_at` ON `ter_code_system` (`created_at`);
CREATE INDEX `idx_code_system_is_deleted` ON `ter_code_system` (`is_deleted`);
CREATE INDEX `idx_code_system_status` ON `ter_code_system` (`status`(64));
CREATE INDEX `idx_code_system_tenant_id` ON `ter_code_system` (`tenant_id`);
ALTER TABLE `ter_code_system` ADD CONSTRAINT `ter_code_system_name_key` UNIQUE (`name`(64));
-- Primary Key structure for table ter_code_system
ALTER TABLE `ter_code_system` ADD CONSTRAINT `ter_code_system_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table ter_concept
CREATE INDEX `idx_concept_code` ON `ter_concept` (`code`(64));
CREATE INDEX `idx_concept_created_at` ON `ter_concept` (`created_at`);
CREATE INDEX `idx_concept_is_active` ON `ter_concept` (`is_active`);
CREATE INDEX `idx_concept_is_deleted` ON `ter_concept` (`is_deleted`);
CREATE INDEX `idx_concept_parent` ON `ter_concept` (`parent_id`);
CREATE INDEX `idx_concept_sort_order` ON `ter_concept` (`sort_order`);
ALTER TABLE `ter_concept` ADD CONSTRAINT `uk_concept_code_system_code` UNIQUE (`code_system_id`, `code`(64));
-- Primary Key structure for table ter_concept
ALTER TABLE `ter_concept` ADD CONSTRAINT `ter_concept_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_audit_logs
CREATE INDEX `idx_audit_logs_created_at` ON `whale_audit_logs` (`created_at`);
CREATE INDEX `idx_audit_logs_entity_id` ON `whale_audit_logs` (`entity_id`);
CREATE INDEX `idx_audit_logs_entity_type` ON `whale_audit_logs` (`entity_type`(64));
CREATE INDEX `idx_audit_logs_user_id` ON `whale_audit_logs` (`user_id`);
-- Primary Key structure for table whale_audit_logs
ALTER TABLE `whale_audit_logs` ADD CONSTRAINT `whale_audit_logs_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_framework_runtime_state
CREATE INDEX `idx_fw_runtime_state_fingerprint` ON `whale_framework_runtime_state` (`deployment_fingerprint`(64));
CREATE INDEX `idx_fw_runtime_state_insight_code` ON `whale_framework_runtime_state` (`insight_code`(64));
CREATE INDEX `idx_fw_runtime_state_received_at` ON `whale_framework_runtime_state` (`received_at`);
-- Primary Key structure for table whale_framework_runtime_state
ALTER TABLE `whale_framework_runtime_state` ADD CONSTRAINT `whale_framework_runtime_state_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_menus
CREATE INDEX `idx_whale_menus_is_enabled` ON `whale_menus` (`is_enabled`);
CREATE INDEX `idx_whale_menus_menu_type` ON `whale_menus` (`menu_type`);
CREATE INDEX `idx_whale_menus_parent_id` ON `whale_menus` (`parent_id`);
CREATE INDEX `idx_whale_menus_tenant_id` ON `whale_menus` (`tenant_id`);
ALTER TABLE `whale_menus` ADD CONSTRAINT `whale_menus_code_key` UNIQUE (`code`(64));
-- Primary Key structure for table whale_menus
ALTER TABLE `whale_menus` ADD CONSTRAINT `whale_menus_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_organization_units
CREATE INDEX `idx_whale_ou_parent_id` ON `whale_organization_units` (`parent_id`);
CREATE INDEX `idx_whale_ou_tenant_id` ON `whale_organization_units` (`tenant_id`);
ALTER TABLE `whale_organization_units` ADD CONSTRAINT `whale_organization_units_code_key` UNIQUE (`code`(64));
-- Primary Key structure for table whale_organization_units
ALTER TABLE `whale_organization_units` ADD CONSTRAINT `whale_organization_units_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_permission_grants
CREATE INDEX `idx_whale_permission_grants_is_deleted` ON `whale_permission_grants` (`is_deleted`);
CREATE INDEX `idx_whale_permission_grants_provider` ON `whale_permission_grants` (`provider_name`, `provider_key`(64));
CREATE INDEX `idx_whale_permission_grants_provider_lookup` ON `whale_permission_grants` (`provider_name`, `provider_key`(64), `permission_name`(64));
CREATE INDEX `idx_whale_permission_grants_tenant_id` ON `whale_permission_grants` (`tenant_id`);
ALTER TABLE `whale_permission_grants` ADD CONSTRAINT `whale_permission_grants_permission_name_provider_name_provi_key` UNIQUE (`permission_name`(64), `provider_name`, `provider_key`(64));
-- Primary Key structure for table whale_permission_grants
ALTER TABLE `whale_permission_grants` ADD CONSTRAINT `whale_permission_grants_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_permissions
CREATE INDEX `idx_whale_permissions_is_deleted` ON `whale_permissions` (`is_deleted`);
CREATE INDEX `idx_whale_permissions_parent_name` ON `whale_permissions` (`parent_name`(64));
CREATE INDEX `idx_whale_permissions_tenant_id` ON `whale_permissions` (`tenant_id`);
ALTER TABLE `whale_permissions` ADD CONSTRAINT `whale_permissions_name_key` UNIQUE (`name`(64));
-- Primary Key structure for table whale_permissions
ALTER TABLE `whale_permissions` ADD CONSTRAINT `whale_permissions_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table whale_qrtz_blob_triggers
ALTER TABLE `whale_qrtz_blob_triggers` ADD CONSTRAINT `whale_qrtz_blob_triggers_pkey` PRIMARY KEY (`sched_name`, `trigger_name`, `trigger_group`);
-- Primary Key structure for table whale_qrtz_calendars
ALTER TABLE `whale_qrtz_calendars` ADD CONSTRAINT `whale_qrtz_calendars_pkey` PRIMARY KEY (`sched_name`, `calendar_name`);
-- Primary Key structure for table whale_qrtz_cron_triggers
ALTER TABLE `whale_qrtz_cron_triggers` ADD CONSTRAINT `whale_qrtz_cron_triggers_pkey` PRIMARY KEY (`sched_name`, `trigger_name`, `trigger_group`);
-- Indexes structure for table whale_qrtz_fired_triggers
CREATE INDEX `idx_whale_qrtz_ft_inst_job_req_rcvry` ON `whale_qrtz_fired_triggers` (`sched_name`(64), `instance_name`(64), `requests_recovery`);
CREATE INDEX `idx_whale_qrtz_ft_j_g` ON `whale_qrtz_fired_triggers` (`sched_name`(64), `job_name`(64), `job_group`(64));
CREATE INDEX `idx_whale_qrtz_ft_jg` ON `whale_qrtz_fired_triggers` (`sched_name`(64), `job_group`(64));
CREATE INDEX `idx_whale_qrtz_ft_t_g` ON `whale_qrtz_fired_triggers` (`sched_name`(64), `trigger_name`(64), `trigger_group`(64));
CREATE INDEX `idx_whale_qrtz_ft_tg` ON `whale_qrtz_fired_triggers` (`sched_name`(64), `trigger_group`(64));
CREATE INDEX `idx_whale_qrtz_ft_trig_inst_name` ON `whale_qrtz_fired_triggers` (`sched_name`(64), `instance_name`(64));
-- Primary Key structure for table whale_qrtz_fired_triggers
ALTER TABLE `whale_qrtz_fired_triggers` ADD CONSTRAINT `whale_qrtz_fired_triggers_pkey` PRIMARY KEY (`sched_name`, `entry_id`);
-- Indexes structure for table whale_qrtz_job_details
CREATE INDEX `idx_whale_qrtz_j_grp` ON `whale_qrtz_job_details` (`sched_name`(64), `job_group`(64));
-- Primary Key structure for table whale_qrtz_job_details
ALTER TABLE `whale_qrtz_job_details` ADD CONSTRAINT `whale_qrtz_job_details_pkey` PRIMARY KEY (`sched_name`, `job_name`, `job_group`);
-- Indexes structure for table whale_qrtz_job_execution_log
CREATE INDEX `idx_whale_qrtz_job_exec_log_finished` ON `whale_qrtz_job_execution_log` (`finished_at`);
CREATE INDEX `idx_whale_qrtz_job_exec_log_job_key` ON `whale_qrtz_job_execution_log` (`sched_name`(64), `job_group`(64), `job_name`(64));
CREATE INDEX `idx_whale_qrtz_job_exec_log_success` ON `whale_qrtz_job_execution_log` (`success`);
CREATE INDEX `idx_whale_qrtz_job_exec_log_tenant` ON `whale_qrtz_job_execution_log` (`tenant_id`);
-- Primary Key structure for table whale_qrtz_job_execution_log
ALTER TABLE `whale_qrtz_job_execution_log` ADD CONSTRAINT `whale_qrtz_job_execution_log_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table whale_qrtz_locks
ALTER TABLE `whale_qrtz_locks` ADD CONSTRAINT `whale_qrtz_locks_pkey` PRIMARY KEY (`sched_name`, `lock_name`);
-- Primary Key structure for table whale_qrtz_paused_trigger_grps
ALTER TABLE `whale_qrtz_paused_trigger_grps` ADD CONSTRAINT `whale_qrtz_paused_trigger_grps_pkey` PRIMARY KEY (`sched_name`, `trigger_group`);
-- Primary Key structure for table whale_qrtz_scheduler_state
ALTER TABLE `whale_qrtz_scheduler_state` ADD CONSTRAINT `whale_qrtz_scheduler_state_pkey` PRIMARY KEY (`sched_name`, `instance_name`);
-- Primary Key structure for table whale_qrtz_simple_triggers
ALTER TABLE `whale_qrtz_simple_triggers` ADD CONSTRAINT `whale_qrtz_simple_triggers_pkey` PRIMARY KEY (`sched_name`, `trigger_name`, `trigger_group`);
-- Indexes structure for table whale_qrtz_triggers
CREATE INDEX `idx_whale_qrtz_t_c` ON `whale_qrtz_triggers` (`sched_name`(64), `calendar_name`(64));
CREATE INDEX `idx_whale_qrtz_t_g` ON `whale_qrtz_triggers` (`sched_name`(64), `trigger_group`(64));
CREATE INDEX `idx_whale_qrtz_t_j` ON `whale_qrtz_triggers` (`sched_name`(64), `job_name`(64), `job_group`(64));
CREATE INDEX `idx_whale_qrtz_t_jg` ON `whale_qrtz_triggers` (`sched_name`(64), `job_group`(64));
CREATE INDEX `idx_whale_qrtz_t_n_g_state` ON `whale_qrtz_triggers` (`sched_name`(64), `trigger_group`(64), `trigger_state`);
CREATE INDEX `idx_whale_qrtz_t_n_state` ON `whale_qrtz_triggers` (`sched_name`(64), `trigger_name`(64), `trigger_group`(64), `trigger_state`);
CREATE INDEX `idx_whale_qrtz_t_next_fire_time` ON `whale_qrtz_triggers` (`sched_name`(64), `next_fire_time`);
CREATE INDEX `idx_whale_qrtz_t_nft_misfire` ON `whale_qrtz_triggers` (`sched_name`(64), `misfire_instr`, `next_fire_time`);
CREATE INDEX `idx_whale_qrtz_t_nft_st` ON `whale_qrtz_triggers` (`sched_name`(64), `trigger_state`, `next_fire_time`);
CREATE INDEX `idx_whale_qrtz_t_nft_st_misfire` ON `whale_qrtz_triggers` (`sched_name`(64), `misfire_instr`, `next_fire_time`, `trigger_state`);
CREATE INDEX `idx_whale_qrtz_t_state` ON `whale_qrtz_triggers` (`sched_name`(64), `trigger_state`);
-- Primary Key structure for table whale_qrtz_triggers
ALTER TABLE `whale_qrtz_triggers` ADD CONSTRAINT `whale_qrtz_triggers_pkey` PRIMARY KEY (`sched_name`, `trigger_name`, `trigger_group`);
-- Indexes structure for table whale_role_claims
CREATE INDEX `idx_whale_rc_claim_type` ON `whale_role_claims` (`claim_type`(64));
CREATE INDEX `idx_whale_rc_tenant_id` ON `whale_role_claims` (`tenant_id`);
ALTER TABLE `whale_role_claims` ADD CONSTRAINT `uk_whale_rc_role_type_value` UNIQUE (`role_id`, `claim_type`(64), `claim_value`(64));
-- Primary Key structure for table whale_role_claims
ALTER TABLE `whale_role_claims` ADD CONSTRAINT `whale_role_claims_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_roles
CREATE INDEX `idx_whale_roles_code` ON `whale_roles` (`code`(64));
CREATE INDEX `idx_whale_roles_created_at` ON `whale_roles` (`created_at`);
CREATE INDEX `idx_whale_roles_is_default` ON `whale_roles` (`is_default`); -- WHERE is_default = true
CREATE INDEX `idx_whale_roles_is_deleted` ON `whale_roles` (`is_deleted`);
CREATE INDEX `idx_whale_roles_is_static` ON `whale_roles` (`is_static`); -- WHERE is_static = true
CREATE INDEX `idx_whale_roles_tenant_id` ON `whale_roles` (`tenant_id`);
ALTER TABLE `whale_roles` ADD CONSTRAINT `whale_roles_name_key` UNIQUE (`name`(64));
-- Primary Key structure for table whale_roles
ALTER TABLE `whale_roles` ADD CONSTRAINT `whale_roles_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_security_logs
CREATE INDEX `idx_whale_security_logs_action` ON `whale_security_logs` (`action`);
CREATE INDEX `idx_whale_security_logs_created_at` ON `whale_security_logs` (`created_at`);
CREATE INDEX `idx_whale_security_logs_is_deleted` ON `whale_security_logs` (`is_deleted`);
CREATE INDEX `idx_whale_security_logs_result` ON `whale_security_logs` (`result`); -- WHERE result = 'FAILED'
CREATE INDEX `idx_whale_security_logs_tenant_id` ON `whale_security_logs` (`tenant_id`);
CREATE INDEX `idx_whale_security_logs_user_action` ON `whale_security_logs` (`user_id`, `action`, `created_at`);
-- Primary Key structure for table whale_security_logs
ALTER TABLE `whale_security_logs` ADD CONSTRAINT `whale_security_logs_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_sequence
CREATE INDEX `idx_whale_sequence_updated_at` ON `whale_sequence` (`updated_at`);
-- Primary Key structure for table whale_sequence
ALTER TABLE `whale_sequence` ADD CONSTRAINT `whale_sequence_pkey` PRIMARY KEY (`seq_key`);
-- Indexes structure for table whale_settings
CREATE INDEX `idx_whale_settings_created_at` ON `whale_settings` (`created_at`);
CREATE INDEX `idx_whale_settings_is_deleted` ON `whale_settings` (`is_deleted`);
CREATE INDEX `idx_whale_settings_provider_key` ON `whale_settings` (`provider_key`(64));
CREATE INDEX `idx_whale_settings_provider_name` ON `whale_settings` (`provider_name`);
CREATE INDEX `idx_whale_settings_tenant_id` ON `whale_settings` (`tenant_id`);
-- Primary Key structure for table whale_settings
ALTER TABLE `whale_settings` ADD CONSTRAINT `whale_settings_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_tenants
CREATE INDEX `idx_whale_tenants_code` ON `whale_tenants` (`code`);
CREATE INDEX `idx_whale_tenants_created_at` ON `whale_tenants` (`created_at`);
CREATE INDEX `idx_whale_tenants_is_active` ON `whale_tenants` (`is_active`);
CREATE INDEX `idx_whale_tenants_is_deleted` ON `whale_tenants` (`is_deleted`);
ALTER TABLE `whale_tenants` ADD CONSTRAINT `whale_tenants_code_key` UNIQUE (`code`);
-- Primary Key structure for table whale_tenants
ALTER TABLE `whale_tenants` ADD CONSTRAINT `whale_tenants_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_user_claims
CREATE INDEX `idx_whale_uc_claim_type` ON `whale_user_claims` (`claim_type`(64));
CREATE INDEX `idx_whale_uc_tenant_id` ON `whale_user_claims` (`tenant_id`);
ALTER TABLE `whale_user_claims` ADD CONSTRAINT `uk_whale_uc_user_type_value` UNIQUE (`user_id`, `claim_type`(64), `claim_value`(64));
-- Primary Key structure for table whale_user_claims
ALTER TABLE `whale_user_claims` ADD CONSTRAINT `whale_user_claims_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_user_login_session
CREATE INDEX `idx_whale_user_login_session_tenant` ON `whale_user_login_session` (`tenant_id`);
-- Primary Key structure for table whale_user_login_session
ALTER TABLE `whale_user_login_session` ADD CONSTRAINT `whale_user_login_session_pkey` PRIMARY KEY (`user_id`);
-- Indexes structure for table whale_user_organization_units
CREATE INDEX `idx_whale_uou_ou_id` ON `whale_user_organization_units` (`organization_unit_id`);
CREATE INDEX `idx_whale_uou_tenant_id` ON `whale_user_organization_units` (`tenant_id`);
ALTER TABLE `whale_user_organization_units` ADD CONSTRAINT `uk_whale_uou_user_ou` UNIQUE (`user_id`, `organization_unit_id`);
-- Primary Key structure for table whale_user_organization_units
ALTER TABLE `whale_user_organization_units` ADD CONSTRAINT `whale_user_organization_units_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_user_roles
CREATE INDEX `idx_whale_user_roles_is_deleted` ON `whale_user_roles` (`is_deleted`);
CREATE INDEX `idx_whale_user_roles_role_id` ON `whale_user_roles` (`role_id`);
CREATE INDEX `idx_whale_user_roles_tenant_id` ON `whale_user_roles` (`tenant_id`);
ALTER TABLE `whale_user_roles` ADD CONSTRAINT `whale_user_roles_user_id_role_id_key` UNIQUE (`user_id`, `role_id`);
-- Primary Key structure for table whale_user_roles
ALTER TABLE `whale_user_roles` ADD CONSTRAINT `whale_user_roles_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_user_tenants
CREATE INDEX `idx_whale_user_tenants_is_deleted` ON `whale_user_tenants` (`is_deleted`);
CREATE INDEX `idx_whale_user_tenants_tenant_id` ON `whale_user_tenants` (`tenant_id`);
CREATE INDEX `idx_whale_user_tenants_user_id` ON `whale_user_tenants` (`user_id`);
ALTER TABLE `whale_user_tenants` ADD CONSTRAINT `uk_user_tenant` UNIQUE (`user_id`, `tenant_id`);
-- Primary Key structure for table whale_user_tenants
ALTER TABLE `whale_user_tenants` ADD CONSTRAINT `whale_user_tenants_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table whale_users
CREATE INDEX `idx_users_email` ON `whale_users` (`email`(64));
CREATE UNIQUE INDEX `idx_users_email_unique` ON `whale_users` (`email`(64)); -- WHERE email IS NOT NULL AND is_deleted = false
CREATE INDEX `idx_users_ukey_id` ON `whale_users` (`ukey_id`(64));
CREATE INDEX `idx_users_ukey_src_id` ON `whale_users` (`ukey_src_id`(64));
CREATE UNIQUE INDEX `idx_users_user_name_unique` ON `whale_users` (`user_name`(64)); -- WHERE is_deleted = false
CREATE INDEX `idx_whale_users_created_at` ON `whale_users` (`created_at`);
CREATE INDEX `idx_whale_users_is_active` ON `whale_users` (`is_active`); -- WHERE is_active = true
CREATE INDEX `idx_whale_users_is_deleted` ON `whale_users` (`is_deleted`);
CREATE INDEX `idx_whale_users_is_locked_out` ON `whale_users` (`is_locked_out`); -- WHERE is_locked_out = true
-- Primary Key structure for table whale_users
ALTER TABLE `whale_users` ADD CONSTRAINT `whale_users_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_activity_definition
ALTER TABLE `wkf_activity_definition` ADD CONSTRAINT `wkf_activity_definition_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_activity_definition_children
ALTER TABLE `wkf_activity_definition_children` ADD CONSTRAINT `wkf_activity_definition_children_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table wkf_appointment_queue
CREATE UNIQUE INDEX `uk_wkf_appt_patient_service_day` ON `wkf_appointment_queue` (`patient_id`, `healthcare_service_id`, `booking_date`); -- WHERE is_deleted = false AND appointment_kind = 'OUTPATIENT_BOOKING' AND healthcare_service_id IS NOT NULL AND booking_date IS NOT NULL
-- Primary Key structure for table wkf_appointment_queue
ALTER TABLE `wkf_appointment_queue` ADD CONSTRAINT `wkf_appointment_queue_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_device_dispense
ALTER TABLE `wkf_device_dispense` ADD CONSTRAINT `wkf_device_dispense_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_device_request
ALTER TABLE `wkf_device_request` ADD CONSTRAINT `wkf_device_request_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_inventory_item
ALTER TABLE `wkf_inventory_item` ADD CONSTRAINT `wkf_inventory_item_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table wkf_schedule
CREATE INDEX `idx_wkf_schedule_source_tpl` ON `wkf_schedule` (`organization_id`, `source_schedule_template_id`); -- WHERE is_deleted = false
-- Primary Key structure for table wkf_schedule
ALTER TABLE `wkf_schedule` ADD CONSTRAINT `wkf_schedule_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_schedule_actor
ALTER TABLE `wkf_schedule_actor` ADD CONSTRAINT `wkf_schedule_actor_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_schedule_identifier
ALTER TABLE `wkf_schedule_identifier` ADD CONSTRAINT `wkf_schedule_identifier_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_service_request
ALTER TABLE `wkf_service_request` ADD CONSTRAINT `wkf_service_request_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_service_request_detail
ALTER TABLE `wkf_service_request_detail` ADD CONSTRAINT `wkf_service_request_detail_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table wkf_slot
CREATE UNIQUE INDEX `uk_wkf_slot_org_time_window` ON `wkf_slot` (`organization_id`, `start_time`, `end_time`); -- WHERE is_deleted = false
-- Primary Key structure for table wkf_slot
ALTER TABLE `wkf_slot` ADD CONSTRAINT `wkf_slot_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_slot_identifier
ALTER TABLE `wkf_slot_identifier` ADD CONSTRAINT `wkf_slot_identifier_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_supply_delivery
ALTER TABLE `wkf_supply_delivery` ADD CONSTRAINT `wkf_supply_delivery_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table wkf_supply_request
ALTER TABLE `wkf_supply_request` ADD CONSTRAINT `wkf_supply_request_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_catalog_download_cursor
CREATE INDEX `ix_yb_cat_dl_cursor_contract_tenant_time` ON `yb_catalog_download_cursor` (`contract_id`, `tenant_id`, `last_success_at`, `id`); -- WHERE is_deleted = false
CREATE INDEX `ix_yb_cat_dl_cursor_lookup` ON `yb_catalog_download_cursor` (`contract_id`, `infno`, `tenant_id`, `last_success_at`, `id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_catalog_download_cursor
ALTER TABLE `yb_catalog_download_cursor` ADD CONSTRAINT `yb_catalog_download_cursor_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_catalog_upload_record
CREATE INDEX `idx_yb_cat_upload_product` ON `yb_catalog_upload_record` (`product_table`, `product_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_catalog_upload_record
ALTER TABLE `yb_catalog_upload_record` ADD CONSTRAINT `yb_catalog_upload_record_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_clear_apply
CREATE INDEX `idx_yb_clear_apply_contract` ON `yb_clear_apply` (`contract_bus_no`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_clear_apply
ALTER TABLE `yb_clear_apply` ADD CONSTRAINT `yb_clear_apply_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_clinic_fee_upload
CREATE INDEX `idx_yb_clinic_fee_upload_bchno` ON `yb_clinic_fee_upload` (`chrg_bchno`, `upload_status`, `tenant_id`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_yb_clinic_fee_upload_item` ON `yb_clinic_fee_upload` (`charge_item_id`, `chrg_bchno`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_clinic_fee_upload
ALTER TABLE `yb_clinic_fee_upload` ADD CONSTRAINT `yb_clinic_fee_upload_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_clinic_pre_settle
CREATE INDEX `idx_yb_clinic_pre_settle_draft` ON `yb_clinic_pre_settle` (`payment_draft_id`); -- WHERE is_deleted = false
CREATE INDEX `idx_yb_clinic_pre_settle_draft_status` ON `yb_clinic_pre_settle` (`payment_draft_id`, `status`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_yb_clinic_pre_settle_bchno` ON `yb_clinic_pre_settle` (`chrg_bchno`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_clinic_pre_settle
ALTER TABLE `yb_clinic_pre_settle` ADD CONSTRAINT `yb_clinic_pre_settle_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_elep_prescription
CREATE INDEX `idx_yb_elep_rx_patient_time` ON `yb_elep_prescription` (`tenant_id`, `patient_id`, `prsc_time`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_yb_elep_rx_hosp` ON `yb_elep_prescription` (`tenant_id`, `contract_bus_no`, `hosp_rxno`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_elep_prescription
ALTER TABLE `yb_elep_prescription` ADD CONSTRAINT `yb_elep_prescription_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table yb_elep_prescription_snapshot
ALTER TABLE `yb_elep_prescription_snapshot` ADD CONSTRAINT `yb_elep_prescription_snapshot_pkey` PRIMARY KEY (`prescription_id`);
-- Indexes structure for table yb_elep_upload_log
CREATE INDEX `idx_yb_elep_upload_log_rx` ON `yb_elep_upload_log` (`prescription_id`, `created_at`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_elep_upload_log
ALTER TABLE `yb_elep_upload_log` ADD CONSTRAINT `yb_elep_upload_log_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_encounter_platform_map
CREATE UNIQUE INDEX `uk_yb_encounter_platform_map` ON `yb_encounter_platform_map` (`encounter_id`, `contract_id`, `med_type`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_encounter_platform_map
ALTER TABLE `yb_encounter_platform_map` ADD CONSTRAINT `yb_encounter_platform_map_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_inpatient_fee_upload
CREATE INDEX `idx_yb_ip_fee_upload_encounter` ON `yb_inpatient_fee_upload` (`encounter_id`, `upload_status`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_yb_ip_fee_upload_charge_item` ON `yb_inpatient_fee_upload` (`charge_item_id`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_inpatient_fee_upload
ALTER TABLE `yb_inpatient_fee_upload` ADD CONSTRAINT `yb_inpatient_fee_upload_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_inpatient_pre_settle
CREATE INDEX `idx_yb_ip_pre_settle_draft_status` ON `yb_inpatient_pre_settle` (`payment_draft_id`, `status`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_inpatient_pre_settle
ALTER TABLE `yb_inpatient_pre_settle` ADD CONSTRAINT `yb_inpatient_pre_settle_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_inv_upload
CREATE INDEX `idx_yb_inv_upload_source` ON `yb_inv_upload` (`source_type`, `source_id`);
CREATE INDEX `idx_yb_inv_upload_status` ON `yb_inv_upload` (`tenant_id`, `upload_status`, `next_retry_at`);
ALTER TABLE `yb_inv_upload` ADD CONSTRAINT `uk_yb_inv_upload_idempotent` UNIQUE (`tenant_id`, `infno`, `fixmedins_bchno`, `source_line_id`);
-- Primary Key structure for table yb_inv_upload
ALTER TABLE `yb_inv_upload` ADD CONSTRAINT `yb_inv_upload_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_inv_upload_trace
CREATE INDEX `idx_yb_inv_upload_trace_upload` ON `yb_inv_upload_trace` (`upload_id`);
CREATE UNIQUE INDEX `uk_yb_inv_upload_trace_codg` ON `yb_inv_upload_trace` (`tenant_id`, `drug_trac_codg`(64)); -- WHERE is_deleted = false
-- Primary Key structure for table yb_inv_upload_trace
ALTER TABLE `yb_inv_upload_trace` ADD CONSTRAINT `yb_inv_upload_trace_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_invoke_log
CREATE INDEX `idx_yb_invoke_log_encounter` ON `yb_invoke_log` (`encounter_id`, `infno`); -- WHERE is_deleted = false
CREATE INDEX `idx_yb_invoke_log_msgid` ON `yb_invoke_log` (`msgid`, `tenant_id`); -- WHERE is_deleted = false
CREATE INDEX `idx_yb_invoke_log_settlement` ON `yb_invoke_log` (`settlement_record_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_invoke_log
ALTER TABLE `yb_invoke_log` ADD CONSTRAINT `yb_invoke_log_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_national_catalog_item
CREATE INDEX `idx_yb_nat_cat_name` ON `yb_national_catalog_item` (`contract_id`, `hilist_name`(64)); -- WHERE is_deleted = false
CREATE INDEX `idx_yb_nat_cat_pinyin` ON `yb_national_catalog_item` (`pinyin`(64)); -- WHERE is_deleted = false
CREATE INDEX `ix_yb_nat_cat_aprvno` ON `yb_national_catalog_item` (`contract_id`, `tenant_id`, `aprvno`(64)); -- WHERE is_deleted = false AND aprvno IS NOT NULL AND aprvno <> ''
CREATE INDEX `ix_yb_nat_cat_contract_list_tenant` ON `yb_national_catalog_item` (`contract_id`, `list_type`, `tenant_id`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_yb_nat_cat_item_1301` ON `yb_national_catalog_item` (`contract_id`, `list_type`, `tenant_id`, `source_file_qury_no`, `source_line_no`); -- WHERE is_deleted = false AND source_line_no IS NOT NULL
CREATE UNIQUE INDEX `uk_yb_nat_cat_item_1312` ON `yb_national_catalog_item` (`contract_id`, `list_type`, `hilist_code`, `tenant_id`); -- WHERE is_deleted = false AND source_line_no IS NULL
-- Primary Key structure for table yb_national_catalog_item
ALTER TABLE `yb_national_catalog_item` ADD CONSTRAINT `yb_national_catalog_item_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_person_cache
CREATE UNIQUE INDEX `uk_yb_person_cache_cert` ON `yb_person_cache` (`contract_id`, `mdtrt_cert_type`, `mdtrt_cert_no`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_person_cache
ALTER TABLE `yb_person_cache` ADD CONSTRAINT `yb_person_cache_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_platform_dict_item
CREATE INDEX `idx_yb_platform_dict_parent` ON `yb_platform_dict_item` (`tenant_id`, `dict_type`, `parent_value`); -- WHERE is_deleted = false
CREATE UNIQUE INDEX `uk_yb_platform_dict_item` ON `yb_platform_dict_item` (`tenant_id`, `dict_type`, `dict_value`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_platform_dict_item
ALTER TABLE `yb_platform_dict_item` ADD CONSTRAINT `yb_platform_dict_item_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_platform_dict_sync_log
CREATE INDEX `idx_yb_platform_dict_sync_log_tenant` ON `yb_platform_dict_sync_log` (`tenant_id`, `dict_type`, `started_at`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_platform_dict_sync_log
ALTER TABLE `yb_platform_dict_sync_log` ADD CONSTRAINT `yb_platform_dict_sync_log_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_pub_sign
CREATE INDEX `idx_yb_pub_sign_lookup` ON `yb_pub_sign` (`contract_bus_no`, `opter_no`, `sign_date`, `tenant_id`); -- WHERE is_deleted = false AND status = '1'
-- Primary Key structure for table yb_pub_sign
ALTER TABLE `yb_pub_sign` ADD CONSTRAINT `yb_pub_sign_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_recon_daily
CREATE INDEX `idx_yb_recon_daily_contract` ON `yb_recon_daily` (`contract_bus_no`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_recon_daily
ALTER TABLE `yb_recon_daily` ADD CONSTRAINT `yb_recon_daily_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_recon_detail
CREATE INDEX `idx_yb_recon_detail_contract` ON `yb_recon_detail` (`contract_bus_no`, `tenant_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_recon_detail
ALTER TABLE `yb_recon_detail` ADD CONSTRAINT `yb_recon_detail_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_settlement_correction
CREATE INDEX `idx_yb_settlement_correction_record` ON `yb_settlement_correction` (`settlement_record_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_settlement_correction
ALTER TABLE `yb_settlement_correction` ADD CONSTRAINT `yb_settlement_correction_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_settlement_fund_detail
CREATE INDEX `idx_yb_settlement_fund_detail_record` ON `yb_settlement_fund_detail` (`settlement_record_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_settlement_fund_detail
ALTER TABLE `yb_settlement_fund_detail` ADD CONSTRAINT `yb_settlement_fund_detail_pkey` PRIMARY KEY (`id`);
-- Indexes structure for table yb_settlement_record
CREATE INDEX `idx_yb_settlement_record_payment` ON `yb_settlement_record` (`payment_id`); -- WHERE is_deleted = false
-- Primary Key structure for table yb_settlement_record
ALTER TABLE `yb_settlement_record` ADD CONSTRAINT `yb_settlement_record_pkey` PRIMARY KEY (`id`);
-- Primary Key structure for table yb_settlement_reversal
ALTER TABLE `yb_settlement_reversal` ADD CONSTRAINT `yb_settlement_reversal_pkey` PRIMARY KEY (`id`);
-- Foreign Keys structure for table adm_pr_assign
ALTER TABLE `adm_pr_assign` ADD CONSTRAINT `fk_adm_pr_assign_whale_role` FOREIGN KEY (`role_id`) REFERENCES `whale_roles` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_borrow_request
ALTER TABLE `mrms_borrow_request` ADD CONSTRAINT `mrms_borrow_request_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_case_record_homepage
ALTER TABLE `mrms_case_record_homepage` ADD CONSTRAINT `mrms_case_record_homepage_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_homepage_diagnosis
ALTER TABLE `mrms_homepage_diagnosis` ADD CONSTRAINT `mrms_homepage_diagnosis_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_homepage_procedure
ALTER TABLE `mrms_homepage_procedure` ADD CONSTRAINT `mrms_homepage_procedure_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_qc_defect
ALTER TABLE `mrms_qc_defect` ADD CONSTRAINT `mrms_qc_defect_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_qc_run
ALTER TABLE `mrms_qc_run` ADD CONSTRAINT `mrms_qc_run_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table mrms_upload_log
ALTER TABLE `mrms_upload_log` ADD CONSTRAINT `mrms_upload_log_case_record_id_fkey` FOREIGN KEY (`case_record_id`) REFERENCES `mrms_case_record` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table ter_concept
ALTER TABLE `ter_concept` ADD CONSTRAINT `fk_concept_code_system` FOREIGN KEY (`code_system_id`) REFERENCES `ter_code_system` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
ALTER TABLE `ter_concept` ADD CONSTRAINT `fk_concept_parent` FOREIGN KEY (`parent_id`) REFERENCES `ter_concept` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_menus
ALTER TABLE `whale_menus` ADD CONSTRAINT `fk_whale_menus_parent` FOREIGN KEY (`parent_id`) REFERENCES `whale_menus` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_organization_units
ALTER TABLE `whale_organization_units` ADD CONSTRAINT `fk_whale_ou_parent` FOREIGN KEY (`parent_id`) REFERENCES `whale_organization_units` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_qrtz_blob_triggers
ALTER TABLE `whale_qrtz_blob_triggers` ADD CONSTRAINT `whale_qrtz_blob_triggers_sched_name_trigger_name_trigger_g_fkey` FOREIGN KEY (`sched_name`, `trigger_name`, `trigger_group`) REFERENCES `whale_qrtz_triggers` (`sched_name`, `trigger_name`, `trigger_group`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_qrtz_cron_triggers
ALTER TABLE `whale_qrtz_cron_triggers` ADD CONSTRAINT `whale_qrtz_cron_triggers_sched_name_trigger_name_trigger_g_fkey` FOREIGN KEY (`sched_name`, `trigger_name`, `trigger_group`) REFERENCES `whale_qrtz_triggers` (`sched_name`, `trigger_name`, `trigger_group`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_qrtz_simple_triggers
ALTER TABLE `whale_qrtz_simple_triggers` ADD CONSTRAINT `whale_qrtz_simple_triggers_sched_name_trigger_name_trigger_fkey` FOREIGN KEY (`sched_name`, `trigger_name`, `trigger_group`) REFERENCES `whale_qrtz_triggers` (`sched_name`, `trigger_name`, `trigger_group`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_qrtz_triggers
ALTER TABLE `whale_qrtz_triggers` ADD CONSTRAINT `whale_qrtz_triggers_sched_name_job_name_job_group_fkey` FOREIGN KEY (`sched_name`, `job_name`, `job_group`) REFERENCES `whale_qrtz_job_details` (`sched_name`, `job_name`, `job_group`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_role_claims
ALTER TABLE `whale_role_claims` ADD CONSTRAINT `fk_whale_rc_role` FOREIGN KEY (`role_id`) REFERENCES `whale_roles` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_user_claims
ALTER TABLE `whale_user_claims` ADD CONSTRAINT `fk_whale_uc_user` FOREIGN KEY (`user_id`) REFERENCES `whale_users` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_user_login_session
ALTER TABLE `whale_user_login_session` ADD CONSTRAINT `fk_whale_user_login_session_user` FOREIGN KEY (`user_id`) REFERENCES `whale_users` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION;
-- Foreign Keys structure for table whale_user_organization_units
ALTER TABLE `whale_user_organization_units` ADD CONSTRAINT `fk_whale_uou_ou` FOREIGN KEY (`organization_unit_id`) REFERENCES `whale_organization_units` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
ALTER TABLE `whale_user_organization_units` ADD CONSTRAINT `fk_whale_uou_user` FOREIGN KEY (`user_id`) REFERENCES `whale_users` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

SET FOREIGN_KEY_CHECKS = 1;