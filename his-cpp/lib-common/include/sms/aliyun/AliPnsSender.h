#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/05/14 14:16:39

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
#ifndef _ALIPNSSENDER_H_
#define _ALIPNSSENDER_H_
#include "AliPnsResult.h"
#include <memory>
#ifdef USE_ALISMS
#include "alibabacloud/dypnsapi/DypnsapiClient.h"
using namespace AlibabaCloud::Dypnsapi;
#endif

/**
 * 短信认证服务组件
 * 注意：
 * 1、此组件不支持Windows平台，要使用此组件请在Linux环境下面使用
 * 2、使用的时候需要定义AliKeyConfig类相关成员变量和成员函数，用于指定ak和sk相关值
 */
class AliPnsSender
{
private:
#ifdef USE_ALISMS
	// 创建短信认证服务客户端
	std::shared_ptr<DypnsapiClient> createClient();
#endif
public:
	/**
	 * 构造初始化
	 * @param keyfilename key配置文件名称
	 * @param prefix 配置读取前缀
	 */
	AliPnsSender(const std::string& keyfilename = "key-config.yaml", const std::string& prefix = "aliyun.sms");
	~AliPnsSender();
	/**
	 * 发送短信验证码
	 * @param phoneNumber 手机号
	 * @param signName 签名名称
	 * @param templateCode 模板编码
	 * @param templateParams 模板参数,json数据格式。如：{"code":"##code##"}
	 * @return 返回结果
	 */
	std::shared_ptr<AliPnsResult> sendVerifyCode(const std::string& phoneNumber, const std::string& signName, std::string& templateCode, const std::string& templateParams);
	/**
	 * 校验短信验证码
	 * @param phoneNumber 手机号
	 * @param verifyCode 验证码
	 */
	std::shared_ptr<AliPnsResult> checkVerifyCode(const std::string& phoneNumber, const std::string& verifyCode);
};

#endif // !_ALIPNSSENDER_H_