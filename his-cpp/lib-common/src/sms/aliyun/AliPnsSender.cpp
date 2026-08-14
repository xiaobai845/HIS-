/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/05/14 14:18:43

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
#include "sms/aliyun/AliPnsSender.h"
#include "sms/aliyun/AliKeyConfig.h"
#include <iostream>

#ifdef USE_ALISMS
#include "alibabacloud/core/AlibabaCloud.h"
#include "alibabacloud/core/ClientConfiguration.h"
using namespace AlibabaCloud;
#endif

#ifdef USE_ALISMS
std::shared_ptr<DypnsapiClient> AliPnsSender::createClient()
{
	// 配置实例
	ClientConfiguration configuration(AliKeyConfig::region);
	configuration.setEndpoint("dypnsapi.aliyuncs.com");
	// 创建客户端实例
	return std::make_shared<DypnsapiClient>(AliKeyConfig::ak, AliKeyConfig::sk, configuration);
}
#endif

AliPnsSender::AliPnsSender(const std::string& keyfilename /*= "key-config.yaml"*/, const std::string& prefix /*= "aliyun.sms"*/)
{
#ifdef USE_ALISMS
	// 初始化SDK
	AlibabaCloud::InitializeSdk();
	// 初始化key配置
	AliKeyConfig::init(keyfilename, prefix);
#endif
}

AliPnsSender::~AliPnsSender()
{
#ifdef USE_ALISMS
	// 关闭SDK
	AlibabaCloud::ShutdownSdk();
#endif
}

std::shared_ptr<AliPnsResult> AliPnsSender::sendVerifyCode(const std::string& phoneNumber, const std::string& signName, std::string& templateCode, const std::string& templateParams)
{
#ifdef USE_ALISMS
	// 创建API请求并设置参数
	Model::SendSmsVerifyCodeRequest request;
	request.setPhoneNumber(phoneNumber);
	request.setSignName(signName);
	request.setTemplateCode(templateCode);
	request.setTemplateParam(templateParams);
	// 发送短信验证码
	auto outcome = createClient()->sendSmsVerifyCode(request);
	auto result = std::make_shared<AliPnsResult>();
	// 发送异常
	if (!outcome.isSuccess())
	{
		// 异常处理
		std::cout << outcome.error().errorCode() << std::endl;
		result->Code(outcome.error().errorCode());
		result->Message(outcome.error().errorMessage());
		return result;
	}
	// 发送正常，处理对应返回结果
	result->Code(outcome.result().getCode());
	result->Message(outcome.result().getMessage());
	result->AccessDeniedDetail(outcome.result().getAccessDeniedDetail());
	result->BizId(outcome.result().getModel().bizId);
	result->OutId(outcome.result().getModel().outId);
	result->RequestId(outcome.result().requestId());
	return result;
#else
	auto result = std::make_shared<AliPnsResult>();
	result->Code("Fail");
	result->Message("system not support aliyun pns.");
	return result;
#endif
}

std::shared_ptr<AliPnsResult> AliPnsSender::checkVerifyCode(const std::string& phoneNumber, const std::string& verifyCode)
{
#ifdef USE_ALISMS
	// 创建API请求并设置参数
	Model::CheckSmsVerifyCodeRequest request;
	request.setPhoneNumber(phoneNumber);
	request.setVerifyCode(verifyCode);
	// 请求校验
	auto outcome = createClient()->checkSmsVerifyCode(request);
	auto result = std::make_shared<AliPnsResult>();
	// 发送异常
	if (!outcome.isSuccess())
	{
		// 异常处理
		std::cout << outcome.error().errorCode() << std::endl;
		result->Code(outcome.error().errorCode());
		result->Message(outcome.error().errorMessage());
		return result;
	}
	// 发送正常，处理对应返回结果
	result->Code(outcome.result().getCode());
	result->Message(outcome.result().getMessage());
	result->AccessDeniedDetail(outcome.result().getAccessDeniedDetail());
	result->OutId(outcome.result().getModel().outId);
	result->VerifyResult(outcome.result().getModel().verifyResult);
	result->RequestId(outcome.result().requestId());
	return result;
#else
	auto result = std::make_shared<AliPnsResult>();
	result->Code("Fail");
	result->Message("system not support aliyun pns.");
	return result;
#endif
}
