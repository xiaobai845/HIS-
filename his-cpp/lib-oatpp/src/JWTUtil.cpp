/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/24 14:37:50

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
#include "jwt-cpp/jwt.h"
#include <openssl/md5.h>
#include <iostream>
#include "JWTUtil.h"

#define JU_VERIFY_CATCH(__p__) \
catch (const jwt::error::token_verification_exception& e) { \
	std::cerr << "TokenVerificationError:" << e.what() << std::endl; \
	__p__.setCode(PayloadCode::VERIFICATION_ERROR); \
} \
catch (const jwt::error::signature_verification_exception& e) { \
	std::cerr << "SignatureVerificationError:" << e.what() << std::endl; \
	__p__.setCode(PayloadCode::VERIFICATION_ERROR); \
} \
catch (const jwt::error::signature_generation_exception& e) { \
	std::cerr << "SignatureGenerationError:" << e.what() << std::endl; \
	__p__.setCode(PayloadCode::SIGNATUREFORMAT_ERROR); \
} \
catch (const jwt::error::rsa_exception& e) { \
	std::cerr << "RSAError:" << e.what() << std::endl; \
	__p__.setCode(PayloadCode::SIGNATUREFORMAT_ERROR); \
} \
catch (const jwt::error::ecdsa_exception& e) { \
	std::cerr << "ECDSAError:" << e.what() << std::endl; \
	__p__.setCode(PayloadCode::SIGNATUREFORMAT_ERROR); \
} \
catch (const std::exception& e) { \
	std::cerr << "OtherError:" << e.what() << std::endl; \
	__p__.setCode(PayloadCode::OTHER_ERROR); \
}

#define JU_CREATE_BUIDER(__b__, __p__) \
auto __b__ = jwt::create() \
.set_type("JWT") \
.set_audience(__p__.Aud()) \
.set_issuer(__p__.Iss()) \
.set_subject(__p__.Sub()) \
.set_expires_in(std::chrono::seconds{ __p__.Exp() }) \
.set_issued_now() \
.set_not_before(std::chrono::system_clock::now()) \
.set_id(__p__.Jti())

#define JU_TRANS_STANDER_PROP_TO_PAYLOADDTO(__p__, __d__) \
if (__d__.has_audience() && __d__.get_audience().size() > 0) { \
	__p__.Aud(decoded.get_audience().begin()->c_str()); \
} \
if (__d__.has_issuer()) { \
	__p__.Iss(__d__.get_issuer()); \
} \
if (__d__.has_subject()) { \
	__p__.Sub(__d__.get_subject()); \
} \
if (__d__.has_issued_at()) { \
	__p__.Iat(std::chrono::duration_cast<std::chrono::seconds>(__d__.get_issued_at().time_since_epoch()).count()); \
} \
if (__d__.has_not_before()) { \
	__p__.Nbf(std::chrono::duration_cast<std::chrono::seconds>(__d__.get_not_before().time_since_epoch()).count()); \
} \
if (__d__.has_id()) { \
	__p__.Jti(__d__.get_id()); \
} \
__p__.Exp(std::chrono::duration_cast<std::chrono::seconds>(__d__.get_expires_at().time_since_epoch()).count())

std::string JWTUtil::md5(const std::string& src) {
	unsigned char md[16] = { 0 };
	unsigned int len = 0;
	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);
	EVP_DigestUpdate(ctx, src.c_str(), src.size());
	EVP_DigestFinal_ex(ctx, md, &len);
	EVP_MD_CTX_free(ctx);

	char tmp[3] = { 0 };
	std::string md5_string;
	for (int i = 0; i < 16; ++i) {
		snprintf(tmp, sizeof(tmp), "%02X", md[i]);
		md5_string += tmp;
	}
	return md5_string;
}

std::string JWTUtil::generateTokenByHmac(const PayloadDTO& payloadDto, const std::string& secretStr)
{
	// 使用jwt-cpp的builder模式生成HMAC
	JU_CREATE_BUIDER(builder, payloadDto);

	// 使用PayloadDTO的propToJwt方法添加自定义字段
	payloadDto.propToJwt(builder);

	// 生成token
	return builder.sign(jwt::algorithm::hs256{ md5(secretStr) });
}

PayloadDTO JWTUtil::verifyTokenByHmac(const std::string& token, const std::string& secretStr)
{
	PayloadDTO p;
	try {
		// 使用jwt-cpp的decode方法解码token
		auto decoded = jwt::decode<jwt::traits::kazuho_picojson>(token);

		// 验证token签名和过期时间
		auto verifier = jwt::verify()
			.allow_algorithm(jwt::algorithm::hs256{ md5(secretStr) });
		verifier.verify(decoded);

		// 转换标准属性
		JU_TRANS_STANDER_PROP_TO_PAYLOADDTO(p, decoded);

		// 转换附加属性
		p.propToPayload(decoded);
		p.setCode(PayloadCode::SUCCESS);
	}
	JU_VERIFY_CATCH(p);
	return p;
}

std::string JWTUtil::generateTokenByRsa(const PayloadDTO& payloadDto, const std::string& rsaPriKey)
{
	// 使用jwt-cpp的builder模式生成RSA
	JU_CREATE_BUIDER(builder, payloadDto);

	// 使用PayloadDTO的propToJwt方法添加自定义字段
	payloadDto.propToJwt(builder);

	// 使用RSA私钥签名
	return builder.sign(jwt::algorithm::rs256{ "", rsaPriKey, "", "" });
}

PayloadDTO JWTUtil::verifyTokenByRsa(const std::string& token, const std::string& rsaPubKey)
{
	PayloadDTO p;
	try {
		// 使用jwt-cpp的decode方法解码token
		auto decoded = jwt::decode<jwt::traits::kazuho_picojson>(token);

		// 验证token签名和过期时间
		auto verifier = jwt::verify()
			.allow_algorithm(jwt::algorithm::rs256(rsaPubKey, "", "", ""));
		verifier.verify(decoded);
		
		// 转换标准属性
		JU_TRANS_STANDER_PROP_TO_PAYLOADDTO(p, decoded);
		
		// 转换附加属性
		p.propToPayload(decoded);
		p.setCode(PayloadCode::SUCCESS);
	}
	JU_VERIFY_CATCH(p);
	return p;
}