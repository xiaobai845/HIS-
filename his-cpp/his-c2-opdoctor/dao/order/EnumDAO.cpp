// dao/order/EnumDAO.cpp
#include "stdafx.h"
#include "../../dao/order/EnumDAO.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/oid.hpp>
#include <iostream>

// ========== 辅助函数：安全获取 int 值 ==========
static int getIntValue(bsoncxx::document::element elem) {
    if (!elem) {
        return 0;
    }

    bsoncxx::type t = elem.type();
    if (t == bsoncxx::type::k_int32) {
        return elem.get_int32().value;
    }
    else if (t == bsoncxx::type::k_int64) {
        return static_cast<int>(elem.get_int64().value);
    }
    else if (t == bsoncxx::type::k_double) {
        return static_cast<int>(elem.get_double().value);
    }
    return 0;
}

// ========== 辅助函数：安全获取 bool 值 ==========
static bool getBoolValue(bsoncxx::document::element elem) {
    if (!elem) {
        return false;
    }

    bsoncxx::type t = elem.type();
    if (t == bsoncxx::type::k_bool) {
        return elem.get_bool().value;
    }
    return false;
}

// ========== 辅助函数：安全获取字符串值 ==========
static std::string getStringValue(bsoncxx::document::element elem) {
    if (!elem) {
        return "";
    }

    bsoncxx::type t = elem.type();
    if (t == bsoncxx::type::k_string) {
        auto sv = elem.get_string().value;
        return std::string(sv.data(), sv.size());
    }
    return "";
}

// ========== 辅助函数：安全获取 OID 值 ==========
static bsoncxx::oid getOidValue(bsoncxx::document::element elem) {
    if (!elem || elem.type() != bsoncxx::type::k_oid) {
        return bsoncxx::oid();
    }
    return elem.get_oid().value;
}

// ========== 构造函数 ==========
EnumDAO::EnumDAO(std::shared_ptr<MongoClient> client)
    : m_mongoClient(client) {
}

// ========== 根据 enumTypeKey 获取 enum_type 的 _id ==========
bool EnumDAO::getEnumTypeId(const std::string& enumTypeKey, bsoncxx::oid& outTypeId) {
    if (!m_mongoClient || enumTypeKey.empty()) {
        return false;
    }

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    auto filter = document{}
        << "enumTypeKey" << enumTypeKey
        << "status" << "active"
        << "isDeleted" << false
        << finalize;

    bool found = false;

    m_mongoClient->execute(ENUM_TYPE_COLLECTION,
        [&](mongocxx::collection* collection) {
            try {
                auto doc = collection->find_one(filter.view());
                if (doc) {
                    const auto& docView = *doc;
                    outTypeId = getOidValue(docView["_id"]);
                    found = !(outTypeId == bsoncxx::oid());
                }
            }
            catch (const std::exception& e) {
                std::cerr << "EnumDAO::getEnumTypeId failed: " << e.what() << std::endl;
            }
        }
    );

    return found;
}

// ========== 从文档构建 EnumValue ==========
EnumValue EnumDAO::buildEnumValueFromDoc(const bsoncxx::document::view& doc) {
    EnumValue val;

    val.code = getStringValue(doc["enumKey"]);
    val.name = getStringValue(doc["display"]);
    val.nameEn = getStringValue(doc["nameEn"]);
    val.sortOrder = getIntValue(doc["order"]);
    val.isDefault = getBoolValue(doc["isDefault"]);

    int status = getIntValue(doc["status"]);
    val.active = (status == 1);

    return val;
}

// ========== 获取所有枚举值 ==========
std::vector<EnumValue> EnumDAO::getEnumValues(const std::string& enumTypeKey) {
    std::vector<EnumValue> result;

    if (!m_mongoClient || enumTypeKey.empty()) {
        std::cerr << "EnumDAO: MongoClient is null or enumTypeKey is empty" << std::endl;
        return result;
    }

    bsoncxx::oid enumTypeId;
    if (!getEnumTypeId(enumTypeKey, enumTypeId)) {
        std::cerr << "EnumDAO: enumTypeKey not found: " << enumTypeKey << std::endl;
        return result;
    }

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    auto filter = document{}
        << "enumTypeId" << enumTypeId
        << "status" << 1
        << "isDeleted" << false
        << finalize;

    auto sort = document{} << "order" << 1 << finalize;

    m_mongoClient->execute(ENUM_VALUE_COLLECTION,
        [&](mongocxx::collection* collection) {
            try {
                mongocxx::options::find opts;
                opts.sort(sort.view());
                auto cursor = collection->find(filter.view(), opts);

                for (auto&& doc : cursor) {
                    result.push_back(buildEnumValueFromDoc(doc));
                }
            }
            catch (const std::exception& e) {
                std::cerr << "EnumDAO::getEnumValues failed: " << e.what() << std::endl;
            }
        }
    );

    return result;
}

// ========== 根据类型和编码获取单个枚举值 ==========
bool EnumDAO::getEnumValue(const std::string& enumTypeKey, const std::string& code, EnumValue& out) {
    if (!m_mongoClient || enumTypeKey.empty() || code.empty()) {
        return false;
    }

    bsoncxx::oid enumTypeId;
    if (!getEnumTypeId(enumTypeKey, enumTypeId)) {
        return false;
    }

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    auto filter = document{}
        << "enumTypeId" << enumTypeId
        << "enumKey" << code
        << "status" << 1
        << "isDeleted" << false
        << finalize;

    bool found = false;

    m_mongoClient->execute(ENUM_VALUE_COLLECTION,
        [&](mongocxx::collection* collection) {
            try {
                auto doc = collection->find_one(filter.view());
                if (doc) {
                    const auto& docView = *doc;
                    out = buildEnumValueFromDoc(docView);
                    found = true;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "EnumDAO::getEnumValue failed: " << e.what() << std::endl;
            }
        }
    );

    return found;
}

// ========== 获取枚举名称 ==========
std::string EnumDAO::getEnumName(const std::string& enumTypeKey, const std::string& code) {
    EnumValue val;
    if (getEnumValue(enumTypeKey, code, val)) {
        return val.name;
    }
    return code;
}

// ========== 批量获取枚举名称（使用 $in 优化） ==========
std::map<std::string, std::string> EnumDAO::getEnumNamesMap(
    const std::string& enumTypeKey,
    const std::list<std::string>& codes
) {
    std::map<std::string, std::string> result;

    if (!m_mongoClient || enumTypeKey.empty() || codes.empty()) {
        return result;
    }

    bsoncxx::oid enumTypeId;
    if (!getEnumTypeId(enumTypeKey, enumTypeId)) {
        for (const std::string& code : codes) {
            result[code] = code;
        }
        return result;
    }

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::array;
    using bsoncxx::builder::stream::finalize;

    // 构建 $in 数组
    auto inArray = array{};
    for (const std::string& code : codes) {
        if (!code.empty()) {
            inArray << code;
        }
    }

    // 获取数组视图并检查长度
    bsoncxx::array::view arrView = inArray;
    if (arrView.length() == 0) {
        return result;
    }

    //  先构建子文档：{"$in": [...]}
    auto inDoc = document{} << "$in" << arrView << finalize;

    //  再构建主文档
    auto filter = document{}
        << "enumTypeId" << enumTypeId
        << "status" << 1
        << "isDeleted" << false
        << "enumKey" << inDoc
        << finalize;

    m_mongoClient->execute(ENUM_VALUE_COLLECTION,
        [&](mongocxx::collection* collection) {
            try {
                auto cursor = collection->find(filter.view());

                std::map<std::string, std::string> foundMap;
                for (auto&& doc : cursor) {
                    std::string code = getStringValue(doc["enumKey"]);
                    std::string display = getStringValue(doc["display"]);
                    if (!code.empty()) {
                        foundMap[code] = display;
                    }
                }

                for (const std::string& code : codes) {
                    auto it = foundMap.find(code);
                    if (it != foundMap.end()) {
                        result[code] = it->second;
                    }
                    else {
                        result[code] = code;
                    }
                }
            }
            catch (const std::exception& e) {
                std::cerr << "EnumDAO::getEnumNamesMap failed: " << e.what() << std::endl;
                for (const std::string& code : codes) {
                    result[code] = code;
                }
            }
        }
    );

    return result;
}

// ========== 获取默认枚举值 ==========
bool EnumDAO::getDefaultEnumValue(const std::string& enumTypeKey, EnumValue& out) {
    if (!m_mongoClient || enumTypeKey.empty()) {
        return false;
    }

    bsoncxx::oid enumTypeId;
    if (!getEnumTypeId(enumTypeKey, enumTypeId)) {
        return false;
    }

    using bsoncxx::builder::stream::document;
    using bsoncxx::builder::stream::finalize;

    auto filter = document{}
        << "enumTypeId" << enumTypeId
        << "isDefault" << true
        << "status" << 1
        << "isDeleted" << false
        << finalize;

    auto sort = document{} << "order" << 1 << finalize;

    bool found = false;

    m_mongoClient->execute(ENUM_VALUE_COLLECTION,
        [&](mongocxx::collection* collection) {
            try {
                mongocxx::options::find opts;
                opts.sort(sort.view());
                auto doc = collection->find_one(filter.view(), opts);
                if (doc) {
                    const auto& docView = *doc;
                    out = buildEnumValueFromDoc(docView);
                    found = true;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "EnumDAO::getDefaultEnumValue failed: " << e.what() << std::endl;
            }
        }
    );

    return found;
}

// ========== 创建索引 ==========
/* 建库时自行添加索引，不在代码中实现此逻辑 */
bool EnumDAO::ensureCollectionAndIndexes() {
    return true;
}