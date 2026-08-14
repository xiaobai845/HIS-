#pragma once
#ifndef _SESSION_SERVICE_H_
#define _SESSION_SERVICE_H_

#include "RedisClient.h"
#include "domain/dto/PayloadDTO.h"
#include <string>
#include <optional>

/**
 * 用户会话服务
 * 从 Redis user:session:{userId} 读取登录上下文
 */
class SessionService {
private:
    std::shared_ptr<RedisClient> m_redisClient;

    static std::string sessionKey(const std::string& userId);

public:
    explicit SessionService(std::shared_ptr<RedisClient> client);
    ~SessionService() = default;

    /**
     * 获取用户会话中的租户ID
     */
    std::optional<std::string> getTenantId(const std::string& userId);

    /**
     * 获取用户会话中的机构ID (hospital_organization_id)
     */
    std::optional<std::string> getOrgId(const std::string& userId);

    /**
     * 获取用户会话中的医院机构ID (hospital_organization_id)
     * 与 getOrgId 语义相同，为了代码可读性保留
     */
    std::optional<std::string> getHospitalOrganizationId(const std::string& userId);

    /**
     * 获取用户会话中的组织单元ID (organization_unit_id)
     */
    std::optional<std::string> getOrganizationUnitId(const std::string& userId);

    /**
     * 获取完整的会话信息 (Hash 所有字段)
     * 返回 JSON 字符串
     */
    std::optional<std::string> getSessionJson(const std::string& userId);
};

#endif // _SESSION_SERVICE_H_