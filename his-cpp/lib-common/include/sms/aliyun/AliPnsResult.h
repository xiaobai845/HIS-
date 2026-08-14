#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/05/14 11:56:57

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
#ifndef _ALIPNSRESULT_H_
#define _ALIPNSRESULT_H_
#include <string>
/**
 * 发送消息响应结果
 */
class AliPnsResult
{
private:
	/**
	 * 请求状态码。
	 * 返回OK代表请求成功。
	 * 其他错误码请参见:https://help.aliyun.com/zh/pnvs/developer-reference/api-return-code
	 */
	std::string code;
	/**
	 * 状态码的描述。
	 */
	std::string message;
	/**
	 * 访问被拒绝详细信息。
	 */
	std::string accessDeniedDetail;
	/**
	 * 业务 ID。
	 */
	std::string bizId;
	/**
	 * 外部流水号。
	 */
	std::string outId;
	/**
	 * 请求ID。
	 */
	std::string requestId;
	/**
	 * 短信验证码核验结果。取值：
	 * PASS：短信验证码核验成功。
	 * UNKNOWN：短信验证码核验失败
	 */
	std::string verifyResult;
public:
	std::string Code() const { return code; }
	void Code(std::string val) { code = val; }
	std::string Message() const { return message; }
	void Message(std::string val) { message = val; }
	std::string AccessDeniedDetail() const { return accessDeniedDetail; }
	void AccessDeniedDetail(std::string val) { accessDeniedDetail = val; }
	std::string BizId() const { return bizId; }
	void BizId(std::string val) { bizId = val; }
	std::string OutId() const { return outId; }
	void OutId(std::string val) { outId = val; }
	std::string RequestId() const { return requestId; }
	void RequestId(std::string val) { requestId = val; }
	std::string VerifyResult() const { return verifyResult; }
	void VerifyResult(std::string val) { verifyResult = val; }
};

#endif // !_ALIPNSRESULT_H_