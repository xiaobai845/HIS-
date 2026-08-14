// dao/order/OrderAuditDAO1.h
#pragma once
#ifndef _ORDER_AUDIT_DAO_1_H_
#define _ORDER_AUDIT_DAO_1_H_

#include "domain/dto/order/OrderAuditDTO1.h"
#include "MongoClient.h"
#include <string>

class OrderAuditDAO1 {
private:
    std::shared_ptr<MongoClient> m_mongoClient;
    static constexpr const char* COLLECTION_NAME = "order_audit_logs";

public:
    explicit OrderAuditDAO1(std::shared_ptr<MongoClient> client);
    ~OrderAuditDAO1() = default;

    /**
     * 保存审计日志
     */
    bool saveAuditLog(const OrderAuditDTO1::Wrapper& audit);

    /**
     * 确保集合存在并创建索引
     */
    bool ensureCollectionAndIndexes();
};

#endif // _ORDER_AUDIT_DAO_1_H_