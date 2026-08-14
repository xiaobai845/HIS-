#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2023/02/22 20:18:53

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _PAYLOADDTO_H_
#define _PAYLOADDTO_H_
#include "jwt-cpp/jwt.h"
#include <list>
#include <map>

/**
 * 负载信息获取状态枚举
 */
enum class PayloadCode
{
	// 信息校验解析成功
	SUCCESS,
	// Token过期
	TOKEN_EXPIRED_ERROR,
	// 签名格式错误
	SIGNATUREFORMAT_ERROR,
	// 解码失败
	DECODE_ERROR,
	// 校验失败
	VERIFICATION_ERROR,
	// 其他错误
	OTHER_ERROR
};

/**
 * 负载信息实体
 */
class PayloadDTO
{
public:
	// 获取状态码对应的文本信息
	static std::string getCodeName(PayloadCode code);
	// 获取令牌前缀
	static std::string getTokenPrefix();
private:
	// Token字符串对应的值
	std::string token;
	// 受众，一个客户端id标识
	std::string aud;
	// 签发者
	std::string iss;
	// 主题，一般不用
	std::string sub;
	// 过期时间；注意：令牌过期时间对应有效截止时间，为Unix时间戳
	int64_t exp;
	// 签发时间，为Unix时间戳
	int64_t iat;
	// 生效时间，为Unix时间戳
	int64_t nbf;
	// jwt id 唯一标识
	std::string jti;
	// 认证状态信息
	PayloadCode code;
	// 用户ID
	std::string id;
	// 用户拥有的权限列表
	std::list<std::string> authorities;
	// TIP：新增属性字段在后面添加即可
	//-------------------------------
	/**
	 * 用户名称（真实姓名）
	 */
	std::string name;
	/**
	 * 组织单元信息
	 * 每个元素：key为组织单元编号，value为组织单元名称
	 */
	std::map<std::string, std::string> organizationUnits;
	/**
	 * 对应的医务人员编号
	 */
	std::string practitionerId;
	/**
	 * 对应的医务人员名称
	 */
	std::string practitionerName;
	/**
	 * 职称名称，如：主任医师、护士、药师、技师等

	 */
	std::string titleName;
	/**
	 * 职称编码，职称名称对应的编码值
	 */
	std::string titleCode;
public:

	PayloadDTO();
	/**
	 * 构造函数
	 * @param username 用户名称
	 * @param exp 过期时间，单位秒
	 * @param _authorities 权限列表
	 */
	PayloadDTO(std::string username, int64_t exp, std::list<std::string> _authorities);
	// 获取Token字符串
	std::string getToken() const { return token; }
	// 设置Token字符串
	void setToken(std::string val) { token = val; }
	// 获取认证状态信息
	PayloadCode getCode() const { return code; }
	// 设置认证状态信息
	void setCode(PayloadCode val) { code = val; }

	std::string Aud() const { return aud; }
	void Aud(std::string val) { aud = val; }
	std::string Iss() const { return iss; }
	void Iss(std::string val) { iss = val; }
	std::string Sub() const { return sub; }
	void Sub(std::string val) { sub = val; }
	int64_t Exp() const { return exp; }
	void Exp(int64_t val) { exp = val; }
	int64_t Iat() const { return iat; }
	void Iat(int64_t val) { iat = val; }
	int64_t Nbf() const { return nbf; }
	void Nbf(int64_t val) { nbf = val; }
	std::string Jti() const { return jti; }
	void Jti(std::string val) { jti = val; }

	// 自定义字段getter/setter
	std::string getUsername() const { return Sub(); }
	void setUsername(std::string val) { Sub(val); }
	std::string getId() const { return id; }
	void setId(std::string val) { id = val; }
	const std::list<std::string>& getAuthorities() const { return authorities; }
	void setAuthorities(std::list<std::string> val) { authorities = val; }
	std::string getName() const { return name; }
	void setName(std::string val) { name = val; }
	std::map<std::string, std::string> getOrganizationUnits() const { return organizationUnits; }
	void setOrganizationUnits(std::map<std::string, std::string> val) { organizationUnits = val; }
	std::string getPractitionerId() const { return practitionerId; }
	void setPractitionerId(std::string val) { practitionerId = val; }
	std::string getPractitionerName() const { return practitionerName; }
	void setPractitionerName(std::string val) { practitionerName = val; }
	std::string getTitleName() const { return titleName; }
	void setTitleName(std::string val) { titleName = val; }
	std::string getTitleCode() const { return titleCode; }
	void setTitleCode(std::string val) { titleCode = val; }
	//-------------------------------
	// 添加权限
	void putAuthority(std::string authstr);

	//-------------------------------
	// 添加组织
	void putOrg(std::string orgId, std::string orgName);
	//-------------------------------
	
	// 将Payload的属性转换到jwt builder中
	// 注意：新增属性字段后需要维护此方法的定义
	void propToJwt(jwt::builder<jwt::default_clock, jwt::traits::kazuho_picojson>& builder) const;

	// 将jwt decoded_jwt属性转换载入Payload
	// 注意：新增字段需要适配此方法实现
	void propToPayload(const jwt::decoded_jwt<jwt::traits::kazuho_picojson>& decoded);
 };

#endif // !_PAYLOADDTO_H_