#include "stdafx.h"
#include "EnumDictUtil.h"
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/cursor.hpp>
#include <bsoncxx/types.hpp>

using namespace bsoncxx::builder::stream;
using bsoncxx::builder::stream::document;

std::unordered_map<std::string, std::string> EnumDictUtil::loadEnumDict(MongoClient& mongoCli,
    const std::string& tenantId, const std::string& enumTypeKey)
{
    std::unordered_map<std::string, std::string> resultMap;
    std::string enumTypeId;

    // 第一步：查询 enum_type，获取类型ID
    bool findTypeOk = mongoCli.execute("enum_type", [&](mongocxx::collection* coll) {
        auto filter = document()
            << "tenantId" << tenantId
            << "enumTypeKey" << enumTypeKey
            << "status" << "active"
            << "isDeleted" << false
            << finalize;

        auto optDoc = coll->find_one(filter.view());
        if (!optDoc.has_value())
            return;

        auto& doc = optDoc.value();
        auto oidVal = doc["_id"].get_oid();
        enumTypeId = oidVal.value.to_string();
    });

    if (enumTypeId.empty())
        return resultMap;

    // 第二步：使用enumTypeId 查询 enum_value 明细
    mongoCli.execute("enum_value", [&](mongocxx::collection* coll) {
        auto filter = document()
            << "tenantId" << tenantId
            << "enumTypeId" << bsoncxx::oid(enumTypeId)
            << "status" << "active"
            << "isDeleted" << false
            << finalize;

        // 按order升序
        mongocxx::options::find opt;
        auto sortDoc = document() << "order" << 1 << finalize;
        opt.sort(sortDoc.view());

        mongocxx::cursor cursor = coll->find(filter.view(), opt);
        for (auto&& doc : cursor)
        {
            // 显式从 bsoncxx::stdx::string_view 构造 std::string，避免调用项目自定义的 string 构造
            auto keyView = doc["enumKey"].get_string().value;
            std::string key(keyView.data(), keyView.size());

            auto displayView = doc["display"].get_string().value;
            std::string display(displayView.data(), displayView.size());

            resultMap[key] = display;
        }
    });

    return resultMap;
}

std::string EnumDictUtil::getText(const std::unordered_map<std::string, std::string>& dict,
    const std::string& enumKey, const std::string& defaultText)
{
    auto it = dict.find(enumKey);
    if (it != dict.end())
    {
        return it->second;
    }
    return defaultText;
}