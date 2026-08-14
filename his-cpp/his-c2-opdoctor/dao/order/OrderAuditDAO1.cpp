#include "stdafx.h"
#include "OrderAuditDAO1.h"
#include "SimpleDateTimeFormat.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

OrderAuditDAO1::OrderAuditDAO1(std::shared_ptr<MongoClient> client)
    : m_mongoClient(client) {
}

bool OrderAuditDAO1::saveAuditLog(const OrderAuditDTO1::Wrapper& audit) {
    if (!m_mongoClient) {
        return false;
    }

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    auto doc = document{};

    doc << "orderId" << (audit->orderId ? audit->orderId->c_str() : "")
        << "orderType" << (audit->orderType ? audit->orderType->c_str() : "")
        << "operationType" << (audit->operationType ? audit->operationType->c_str() : "")
        << "operatorId" << (audit->operatorId ? audit->operatorId->c_str() : "")
        << "operatorName" << (audit->operatorName ? audit->operatorName->c_str() : "")
        << "operatorOrgId" << (audit->operatorOrgId ? audit->operatorOrgId->c_str() : "")
        << "operationTime" << (audit->operationTime ? audit->operationTime->c_str() : "")
        << "remark" << (audit->remark ? audit->remark->c_str() : "");

    if (audit->beforeData) {
        doc << "beforeData" << audit->beforeData->c_str();
    }
    if (audit->afterData) {
        doc << "afterData" << audit->afterData->c_str();
    }
    if (audit->changedFields && !audit->changedFields->empty()) {
        bsoncxx::builder::stream::array arr;
        for (auto& field : *audit->changedFields) {
            arr << (field ? field->c_str() : "");
        }
        doc << "changedFields" << arr;
    }

    // addOne 返回 bsoncxx::types::bson_value::view
    // 插入成功返回非空值，失败返回空值
    auto result = m_mongoClient->addOne(COLLECTION_NAME, doc << finalize);

    // 判断是否插入成功：检查返回值是否有效
    return result.type() != bsoncxx::type::k_null;
}

bool OrderAuditDAO1::ensureCollectionAndIndexes() {
    if (!m_mongoClient) {
        return false;
    }

    return m_mongoClient->execute(COLLECTION_NAME,
        [&](mongocxx::collection* collection) {
            try {
                // 1. orderId + operationTime 复合索引（用于查询某医嘱的所有操作记录）
                bsoncxx::builder::stream::document index1;
                index1 << "orderId" << 1 << "operationTime" << -1;
                collection->create_index(index1.view());

                // 2. operatorId + operationTime 复合索引（用于查询某医生的操作记录）
                bsoncxx::builder::stream::document index2;
                index2 << "operatorId" << 1 << "operationTime" << -1;
                collection->create_index(index2.view());

                // 3. operationType + operationTime 复合索引（用于按操作类型统计）
                bsoncxx::builder::stream::document index3;
                index3 << "operationType" << 1 << "operationTime" << -1;
                collection->create_index(index3.view());

                // 4. orderType + operationTime 复合索引
                bsoncxx::builder::stream::document index4;
                index4 << "orderType" << 1 << "operationTime" << -1;
                collection->create_index(index4.view());

                std::cout << "[MongoDB] order_audit_logs indexes created." << std::endl;
                return true;

            }
            catch (const std::exception& e) {
                std::cerr << "[MongoDB] order_audit_logs index creation failed: " << e.what() << std::endl;
                return false;
            }
        }
    );
}