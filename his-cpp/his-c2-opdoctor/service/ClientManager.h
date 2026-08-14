#pragma once
#ifndef _CLIENT_MANAGER_H_
#define _CLIENT_MANAGER_H_

#include "RedisClient.h"
#include "MongoClient.h"
#include <memory>

/**
 * 全局客户端管理器
 * 单例模式，统一管理 Redis 和 MongoDB 客户端
 */
class ClientManager {
private:
    static std::shared_ptr<RedisClient> m_redisClient;
    static std::shared_ptr<MongoClient> m_mongoClient;
    static bool m_initialized;

    ClientManager() = default;

public:
    /**
     * 初始化客户端（从配置加载）
     * 应在服务启动时调用一次
     */
    static void init();

    /**
     * 销毁客户端
     */
    static void destroy();

    /**
     * 是否已初始化
     */
    static bool isInitialized() { return m_initialized; }

    /**
     * 获取 Redis 客户端
     */
    static std::shared_ptr<RedisClient> getRedisClient() { return m_redisClient; }

    /**
     * 获取 MongoDB 客户端
     */
    static std::shared_ptr<MongoClient> getMongoClient() { return m_mongoClient; }
};

#endif // _CLIENT_MANAGER_H_