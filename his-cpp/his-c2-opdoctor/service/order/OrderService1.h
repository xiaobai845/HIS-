// service/order/OrderService1.h
#pragma once
#ifndef _ORDER_SERVICE_1_H_
#define _ORDER_SERVICE_1_H_

#include "domain/vo/order/OrderVO1.h"
#include "domain/query/order/OrderQuery1.h"
#include "domain/dto/order/OrderAddDTO1.h"
#include "domain/dto/order/OrderModifyDTO1.h"
#include "domain/dto/order/OrderBatchAddDTO1.h"
#include "domain/dto/order/OrderDetailDTO1.h"
#include "domain/dto/PayloadDTO.h"
#include "dao/order/EnumDAO.h"
#include "dao/order/OrderAuditDAO1.h"
#include "dao/order/OrderDAO1.h"
#include <memory>
#include <vector>
#include <list>

// 前向声明
class RedisClient;
class MongoClient;
class SessionService;

/**
 * 医嘱服务实现
 *
 * 功能：
 * - 查询医嘱列表（支持 keyword、orderType、status 筛选）
 * - 新增单条医嘱（返回完整对象）
 * - 修改单条医嘱（支持乐观锁，返回完整对象）
 * - 批量新增医嘱（事务原子性，使用 SqlSession 原生事务）
 * - 枚举值校验和转换
 */
class OrderService1
{
private:
    std::shared_ptr<RedisClient> m_redisClient;
    std::shared_ptr<MongoClient> m_mongoClient;
    std::shared_ptr<SessionService> m_sessionService;
    std::shared_ptr<OrderAuditDAO1> m_auditDAO;
    std::shared_ptr<EnumDAO> m_enumDAO;

    struct ServiceContext {
        std::string userId;
        std::string username;
        std::string practitionerId;
        std::string practitionerName;
        std::string tenantId;
        std::string orgId;
        std::string hospitalOrgId;     
        std::string organizationUnitId; 
        bool valid;
    };

    /**
     * 构建服务上下文
     */
    ServiceContext buildContext(const PayloadDTO* payload);

    /**
     * 记录审计日志
     */
    void auditLog(
        const ServiceContext& ctx,
        const std::string& orderId,
        const std::string& orderType,
        const std::string& operationType,
        const std::string& beforeData = "",
        const std::string& afterData = "",
        const std::list<std::string>& changedFields = {},
        const std::string& remark = ""
    );

    /**
     * 校验枚举值是否存在（新 MongoDB 双集合结构）
     */
    bool validateEnumCode(const std::string& enumTypeKey,
        const std::string& enumKey,
        std::string& outDisplay,
        std::string& errorMsg);

    bool validateEnumCode(const std::string& enumTypeKey,
        const std::string& enumKey,
        std::string& errorMsg);

    /**
     * 获取枚举显示名
     */
    std::string getEnumDisplay(const std::string& enumTypeKey,
        const std::string& enumKey);

    /**
     * 内部新增方法（供单条和批量新增复用）
     * @param dao 外部传入的 DAO 实例（用于事务共享）
     */
    OrderDetailDTO1::Wrapper addOrderInternal(
        const OrderAddDTO1::Wrapper& dto,
        const PayloadDTO* payload,
        const ServiceContext& ctx,
        OrderDAO1& dao,
        std::string& errorMsg
    );

    /**
     * 插入药品医嘱（内部方法，使用传入的 DAO）
     */
    OrderDetailDTO1::Wrapper insertMedicationOrder(
        const OrderAddDTO1::Wrapper& dto,
        const ServiceContext& ctx,
        const std::string& encounterId,
        const std::string& patientId,
        const std::string& medicationId,
        const std::string& orderId,
        const std::string& now,
        int orderNo,
        OrderDAO1& dao,
        std::string& errorMsg
    );

    /**
     * 插入诊疗医嘱（内部方法，使用传入的 DAO）
     */
    OrderDetailDTO1::Wrapper insertServiceOrder(
        const OrderAddDTO1::Wrapper& dto,
        const ServiceContext& ctx,
        const std::string& encounterId,
        const std::string& patientId,
        const std::string& activityId,
        const std::string& orderId,
        const std::string& now,
        int orderNo,
        OrderDAO1& dao,
        std::string& errorMsg
    );

    /**
     * 插入耗材医嘱（内部方法，使用传入的 DAO）
     */
    OrderDetailDTO1::Wrapper insertDeviceOrder(
        const OrderAddDTO1::Wrapper& dto,
        const ServiceContext& ctx,
        const std::string& encounterId,
        const std::string& patientId,
        const std::string& deviceDefId,
        const std::string& orderId,
        const std::string& now,
        int orderNo,
        OrderDAO1& dao,
        std::string& errorMsg
    );

    /**
     * 更新药品医嘱（内部方法）
     */
    bool updateMedicationOrderInternal(
        const OrderModifyDTO1::Wrapper& dto,
        PtrMedicationRequestDO1& medOrder,
        const ServiceContext& ctx,
        std::string& errorMsg
    );

    /**
     * 更新诊疗医嘱（内部方法）
     */
    bool updateServiceOrderInternal(
        const OrderModifyDTO1::Wrapper& dto,
        PtrServiceRequestDO1& svcOrder,
        const ServiceContext& ctx,
        std::string& errorMsg
    );

    /**
     * 更新耗材医嘱（内部方法）
     */
    bool updateDeviceOrderInternal(
        const OrderModifyDTO1::Wrapper& dto,
        PtrDeviceRequestDO1& devOrder,
        const ServiceContext& ctx,
        std::string& errorMsg
    );

    /**
     * 从 DO 构建完整 DTO（用于返回）
     */
    OrderDetailDTO1::Wrapper buildOrderDetailDTO(
        const std::string& orderId,
        const std::string& orderType,
        const std::string& doctorName,
        OrderDAO1& dao  
    );
    /**
     * 日期工具：添加天数
     */
    static std::string addDaysToDate(const std::string& dateStr, int days);

public:
    OrderService1(std::shared_ptr<RedisClient> redisClient,
        std::shared_ptr<MongoClient> mongoClient);
    ~OrderService1() = default;

    /**
     * 查询医嘱列表
     */
    OrderDetailPageDTO1::Wrapper queryOrderList(
        const OrderQuery1::Wrapper& query,
        const PayloadDTO* payload
    );

    /**
     * 新增单条医嘱
     * @return 完整医嘱对象，失败返回 nullptr，errorMsg 包含错误信息
     */
    OrderDetailDTO1::Wrapper addOrder(
        const OrderAddDTO1::Wrapper& dto,
        const PayloadDTO* payload,
        std::string& errorMsg
    );

    /**
     * 修改单条医嘱（支持乐观锁）
     * @return 修改后的完整医嘱对象，失败返回 nullptr，errorMsg 包含错误信息
     */
    OrderDetailDTO1::Wrapper modifyOrder(
        const OrderModifyDTO1::Wrapper& dto,
        const PayloadDTO* payload,
        std::string& errorMsg
    );

    /**
     * 批量新增医嘱（事务原子性，使用 SqlSession 原生事务）
     * @param orderList 医嘱列表
     * @param payload 用户上下文
     * @param errorList 输出错误列表
     * @return 成功新增的医嘱列表（全部成功时返回所有，部分失败时回滚返回空）
     */
    std::list<OrderDetailDTO1::Wrapper> batchAddOrder(
        const oatpp::List<OrderAddDTO1::Wrapper>& orderList,
        const PayloadDTO* payload,
        std::list<std::string>& errorList
    );

    /**
     * 获取枚举值列表（供前端下拉使用）
     */
    std::vector<EnumValue> getEnumValues(const std::string& enumTypeKey);
};

#endif // !_ORDER_SERVICE_1_H_