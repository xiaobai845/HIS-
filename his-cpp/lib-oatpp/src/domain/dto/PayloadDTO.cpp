/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/05/15 11:27:44

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
#include "pch.h"
#include "../../../include/domain/dto/PayloadDTO.h"

std::string PayloadDTO::getCodeName(PayloadCode code)
{
	switch (code)
	{
	case PayloadCode::SUCCESS:
		return "SUCCESS";
	case PayloadCode::TOKEN_EXPIRED_ERROR:
		return "TOKEN_EXPIRED_ERROR";
	case PayloadCode::SIGNATUREFORMAT_ERROR:
		return "SIGNATUREFORMAT_ERROR";
	case PayloadCode::DECODE_ERROR:
		return "DECODE_ERROR";
	case PayloadCode::VERIFICATION_ERROR:
		return "VERIFICATION_ERROR";
	case PayloadCode::OTHER_ERROR:
		return "OTHER_ERROR";
	default:
		return "NONE";
	}
}

std::string PayloadDTO::getTokenPrefix()
{
	return "Bearer ";
}

PayloadDTO::PayloadDTO(std::string username, int64_t _exp, std::list<std::string> _authorities) :PayloadDTO()
{
	this->sub = username;
	this->exp = _exp;
	this->authorities = _authorities;
}

PayloadDTO::PayloadDTO()
{
	this->exp = 36000;
	this->Aud("manager");
	this->Iss("01xq");
	this->Sub("none");
	// 生成jti，使用当前时间作为jti的值
	this->Jti(std::to_string(time(nullptr)));
	this->setCode(PayloadCode::SUCCESS);
}

void PayloadDTO::putAuthority(std::string authstr)
{
	this->authorities.emplace_back(authstr);
}

void PayloadDTO::putOrg(std::string orgId, std::string orgName)
{
	this->organizationUnits.insert(std::make_pair(orgId, orgName));
}

void PayloadDTO::propToJwt(jwt::builder<jwt::default_clock, jwt::traits::kazuho_picojson>& builder) const
{
	// 转换权限列表
	picojson::array auth_array;
	// 将std::list转换为picojson::array
	for (const auto& auth : authorities) {
		auth_array.push_back(picojson::value(auth));
	}
	builder.set_payload_claim("roles", jwt::basic_claim<jwt::traits::kazuho_picojson>(auth_array));
	// 转换id
	builder.set_payload_claim("id", jwt::basic_claim<jwt::traits::kazuho_picojson>(id));


	// 转换人员名称
	builder.set_payload_claim("name", jwt::basic_claim<jwt::traits::kazuho_picojson>(name));
	// 转换组织机构信息

	// 提示：新增字段需要在后补充方法

	// 转换真实姓名
	builder.set_payload_claim("name", jwt::basic_claim<jwt::traits::kazuho_picojson>(name));
	// 转换组织单元信息
	picojson::object org_obj;
	for (const auto& org : organizationUnits) {
		org_obj.insert(std::make_pair(org.first, picojson::value(org.second)));
	}
	builder.set_payload_claim("organizationUnits", jwt::basic_claim<jwt::traits::kazuho_picojson>(picojson::value(org_obj)));

	// 转换对应执业人员ID
	builder.set_payload_claim("practitionerId", jwt::basic_claim<jwt::traits::kazuho_picojson>(practitionerId));
	// 转换对应执业人员名称
	builder.set_payload_claim("practitionerName", jwt::basic_claim<jwt::traits::kazuho_picojson>(practitionerName));
	// 转换职称名称
	builder.set_payload_claim("titleName", jwt::basic_claim<jwt::traits::kazuho_picojson>(titleName));
	// 转换职称编码
	builder.set_payload_claim("titleCode", jwt::basic_claim<jwt::traits::kazuho_picojson>(titleCode));
}

void PayloadDTO::propToPayload(const jwt::decoded_jwt<jwt::traits::kazuho_picojson>& decoded)
{
	// 获取payload claims（原始picojson::object）
	const auto& claims = decoded.get_payload_json();
	// 转换权限列表
	if (claims.count("roles")) {
		const auto& auth_value = claims.at("roles");
		// 从picojson数组读取
		if (auth_value.is<picojson::array>()) {
			try {
				auto arr = auth_value.get<picojson::array>();
				for (const auto& item : arr) {
					if (item.is<std::string>()) {
						putAuthority(item.get<std::string>());
					}
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Error parsing authorities: " << e.what() << std::endl;
			}
		}
	}
	// 转换id（兼容字符串/数字两种类型）
	if (claims.count("id")) {
		const auto& id_value = claims.at("id");
		try {
			// 如果是字符串
			if (id_value.is<std::string>()) {
				setId(id_value.get<std::string>());
			}
			// 如果是数字
			else if (id_value.is<int64_t>()) {
				setId(std::to_string(id_value.get<int64_t>()));
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing id: " << e.what() << std::endl;
		}
	}


	if (claims.count("name")) {
		const auto& name_value = claims.at("name");
		try {
			setName(name_value.get<std::string>());
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing name: " << e.what() << std::endl;
		}
	}
	if (claims.count("organizationUnits")) {
		const auto& org_value = claims.at("organizationUnits");
		try {
			auto obj = org_value.get<picojson::object>();
			for (const auto& kv : obj) {
				putOrg(kv.first, kv.second.get<std::string>());
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing organizationUnits: " << e.what() << std::endl;
		}
	}
	if (claims.count("practitionerId")) {
		const auto& practitioner_id = claims.at("practitionerId");
		try {
			setPractitionerId(practitioner_id.get<std::string>());
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing practitionerId: " << e.what() << std::endl;
		}
	}
	if (claims.count("practitionerName")) {
		const auto& practitioner_name = claims.at("practitionerName");
		try {
			setPractitionerName(practitioner_name.get<std::string>());
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing practitionerName: " << e.what() << std::endl;
		}
	}
	// 转换职称名称
	if (claims.count("titleName")) {
		const auto& title_name = claims.at("titleName");
		try {
			setTitleName(title_name.get<std::string>());
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing titleName: " << e.what() << std::endl;
		}
	}
	// 转换职称编码
	if (claims.count("titleCode"))
	{
		const auto& title_code = claims.at("titleCode");
		try {
			setTitleCode(title_code.get<std::string>());
		}
		catch (const std::exception& e) {
			std::cerr << "Error parsing titleCode: " << e.what() << std::endl;

			
			
			}
		}
	}
	
	



