// dao/order/OrderDAO1.h
#pragma once
#ifndef _ORDER_DAO_1_H_
#define _ORDER_DAO_1_H_

#include "BaseDAO.h"
#include "../../domain/do/order/MedicationRequestDO1.h"
#include "../../domain/do/order/ServiceRequestDO1.h"
#include "../../domain/do/order/DeviceRequestDO1.h"
#include "../../domain/do/order/MedicationDefinitionDO1.h"
#include "../../domain/do/order/ActivityDefinitionDO1.h"
#include "../../domain/do/order/DeviceDefinitionDO1.h"
#include "../../domain/do/order/ChargeItemDefinitionDO1.h"
#include "../../domain/do/order/PractitionerDO1.h"
#include "../../domain/do/order/EncounterDO1.h"
#include "../../domain/dto/order/OrderDetailDTO1.h"
#include <list>
#include <map>

// 前向声明 Mapper
class MedicationRequestMapper1;
class ServiceRequestMapper1;
class DeviceRequestMapper1;
class PtrMedicationDefinitionMapper1;
class PtrActivityDefinitionMapper1;
class PtrDeviceDefinitionMapper1;

/**
 * 医嘱相关数据库操作
 *
 * 重构说明：
 * - 医生姓名由 Service 层从 Payload 传入，不再查数据库
 * - queryOrderList 支持 keyword、orderType、statusList 动态筛选
 * - sortNumber（orderNo）由前端维护，DAO 只负责存储和排序
 */
class OrderDAO1 : public BaseDAO
{
private:
    

    /**
     * 构建关键词搜索的 EXISTS 子查询条件
     * @param keyword 关键词
     * @param defTable 定义表名
     * @param idField 定义表主键字段名
     * @param idColumn 医嘱表中关联定义表的列名
     * @return SQL 条件字符串（如 "AND EXISTS (...)"）
     */
    std::string buildKeywordCondition(const std::string& keyword,
        const std::string& defTable,
        const std::string& idField,
        const std::string& idColumn);

    /**
     * 构建状态筛选的 IN 子句
     */
    std::string buildStatusCondition(const std::list<std::string>& statusList);

    /**
     * 从 DO 构建药品医嘱 DTO
     */
    OrderDetailDTO1::Wrapper buildMedicationDTO(const MedicationRequestDO1& item,
        const MedicationDefinitionDO1& def,
        const std::string& doctorName);

    /**
     * 从 DO 构建诊疗医嘱 DTO
     */
    OrderDetailDTO1::Wrapper buildServiceDTO(const ServiceRequestDO1& item,
        const ActivityDefinitionDO1& def,
        const std::string& doctorName);

    /**
     * 从 DO 构建耗材医嘱 DTO
     */
    OrderDetailDTO1::Wrapper buildDeviceDTO(const DeviceRequestDO1& item,
        const DeviceDefinitionDO1& def,
        const std::string& doctorName);

public:
    /**
     * 获取物品单价（从 adm_charge_item_definition 查询）
     */
    uint64_t getUnitPrice(const std::string& instanceTable, const std::string& instanceId);

    /**
     * 通过 bus_no 查询药品定义 ID
     */
    std::string getMedicationIdByBusNo(const std::string& busNo);

    /**
     * 通过 bus_no 查询诊疗定义 ID
     */
    std::string getActivityIdByBusNo(const std::string& busNo);

    /**
     * 通过 bus_no 查询耗材定义 ID
     */
    std::string getDeviceDefIdByBusNo(const std::string& busNo);

    /**
     * 根据就诊ID查询患者ID
     */
    std::string getPatientIdByEncounterId(const std::string& encounterId);

    /**
     * 查询患者医嘱列表（合并药品、诊疗、耗材医嘱）
     * 支持动态筛选
     * @param encounterId 就诊ID（必填）
     * @param keyword 关键词（可选，搜索编码/名称/拼音码/商品名）
     * @param orderType 医嘱类型（可选，medication/service/device）
     * @param statusList 状态列表（可选，多状态筛选）
     * @param pageIndex 页码
     * @param pageSize 每页大小
     * @param total 输出总记录数
     * @param doctorName 医生姓名（由 Service 层从 Payload 传入）
     */
    std::list<OrderDetailDTO1::Wrapper> queryOrderList(
        const std::string& encounterId,
        const std::string& keyword,
        const std::string& orderType,
        const std::list<std::string>& statusList,
        uint64_t pageIndex,
        uint64_t pageSize,
        uint64_t& total,
        const std::string& doctorName = ""
    );

    /**
     * 插入药品医嘱
     */
    bool insertMedicationOrder(const MedicationRequestDO1& data);

    /**
     * 插入诊疗医嘱
     */
    bool insertServiceOrder(const ServiceRequestDO1& data);

    /**
     * 插入耗材医嘱
     */
    bool insertDeviceOrder(const DeviceRequestDO1& data);

    /**
     * 更新药品医嘱
     */
    bool updateMedicationOrder(const MedicationRequestDO1& data);

    /**
     * 更新诊疗医嘱
     */
    bool updateServiceOrder(const ServiceRequestDO1& data);

    /**
     * 更新耗材医嘱
     */
    bool updateDeviceOrder(const DeviceRequestDO1& data);

    /**
     * 根据ID查询药品医嘱
     */
    PtrMedicationRequestDO1 selectMedicationOrderById(const std::string& id);

    /**
     * 根据ID查询诊疗医嘱
     */
    PtrServiceRequestDO1 selectServiceOrderById(const std::string& id);

    /**
     * 根据ID查询耗材医嘱
     */
    PtrDeviceRequestDO1 selectDeviceOrderById(const std::string& id);

    /**
     * 根据ID查询药品定义
     */
    PtrMedicationDefinitionDO1 selectMedicationDefinitionById(const std::string& id);

    /**
     * 根据ID查询诊疗定义
     */
    PtrActivityDefinitionDO1 selectActivityDefinitionById(const std::string& id);

    /**
     * 根据ID查询耗材定义
     */
    PtrDeviceDefinitionDO1 selectDeviceDefinitionById(const std::string& id);
};

#endif // !_ORDER_DAO_1_H_