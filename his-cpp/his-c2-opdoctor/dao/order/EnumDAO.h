// dao/order/EnumDAO.h
#pragma once
#ifndef _ENUM_DAO_H_
#define _ENUM_DAO_H_

#include "MongoClient.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <bsoncxx/oid.hpp>

/**
 * 枚举值结构体
 */
struct EnumValue {
    std::string code;        // 枚举编码（对应 enumKey）
    std::string name;        // 显示名称（对应 display）
    std::string nameEn;      // 英文名称
    int sortOrder;           // 排序权重（对应 order）
    bool isDefault;          // 是否默认
    bool active;             // 是否启用（对应 status == 1）

    EnumValue() : sortOrder(0), isDefault(false), active(true) {}
};

/**
 * MongoDB 枚举数据访问层
 *
 * 适配新双集合结构：
 * - enum_type: 存储枚举类型定义（enumTypeKey, displayName, description...）
 * - enum_value: 存储具体枚举值（enumTypeId, enumKey, display, order, status...）
 *
 * 查询流程：
 * 1. 根据 enumTypeKey 查询 enum_type 获取 _id
 * 2. 根据 enumTypeId 查询 enum_value 获取枚举值列表
 */
class EnumDAO {
private:
    std::shared_ptr<MongoClient> m_mongoClient;
    static constexpr const char* ENUM_TYPE_COLLECTION = "enum_type";
    static constexpr const char* ENUM_VALUE_COLLECTION = "enum_value";

    /**
     * 根据 enumTypeKey 获取 enum_type 的 _id
     * @param enumTypeKey 枚举类型键（如 "ORDER_TYPE"）
     * @param outTypeId 输出参数，存储查询到的 _id
     * @return true 表示找到，false 表示未找到
     */
    bool getEnumTypeId(const std::string& enumTypeKey, bsoncxx::oid& outTypeId);

    /**
     * 从文档构建 EnumValue 对象
     */
    EnumValue buildEnumValueFromDoc(const bsoncxx::document::view& doc);

public:
    explicit EnumDAO(std::shared_ptr<MongoClient> client);
    ~EnumDAO() = default;

    /**
     * 根据枚举类型获取所有枚举值
     * @param enumTypeKey 枚举类型键（如 "ORDER_TYPE"）
     * @return 枚举值列表
     */
    std::vector<EnumValue> getEnumValues(const std::string& enumTypeKey);

    /**
     * 根据枚举类型和编码获取单个枚举值
     * @param enumTypeKey 枚举类型键
     * @param code 枚举编码（enumKey）
     * @param out 输出参数，存储查询结果
     * @return true 表示找到，false 表示未找到
     */
    bool getEnumValue(const std::string& enumTypeKey, const std::string& code, EnumValue& out);

    /**
     * 获取枚举值名称（单个查询，用于前端展示）
     * @param enumTypeKey 枚举类型键
     * @param code 枚举编码
     * @return 枚举显示名称，如果未找到则返回 code 本身
     */
    std::string getEnumName(const std::string& enumTypeKey, const std::string& code);

    /**
     * 批量获取枚举名称（用于列表查询优化）
     * @param enumTypeKey 枚举类型键
     * @param codes 枚举编码列表
     * @return map<code, name>
     */
    std::map<std::string, std::string> getEnumNamesMap(
        const std::string& enumTypeKey,
        const std::list<std::string>& codes
    );

    /**
     * 获取默认枚举值
     * @param enumTypeKey 枚举类型键
     * @param out 输出参数，存储查询结果
     * @return true 表示找到，false 表示未找到
     */
    bool getDefaultEnumValue(const std::string& enumTypeKey, EnumValue& out);

    /**
     * 确保集合存在并创建索引
     */
    bool ensureCollectionAndIndexes();
};

#endif // _ENUM_DAO_H_