/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/11/02 14:37:39

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
#include "../include/id/SnowFlake.h"
#include <thread>
#include <stdexcept>
#include <iostream>
#include <random>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#if defined(_MSC_VER)
#pragma comment(lib, "iphlpapi.lib")
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <cstring>
#include <set>
#endif

#ifndef _WIN32
// 判断Linux接口是否为虚拟网卡（通过名称前缀排除）
bool isVirtualInterface(const std::string& name)
{
	// 常见虚拟接口前缀：lo, docker, veth, br-, virbr, tun, tap
	return name == "lo" ||
		name.rfind("docker", 0) == 0 ||
		name.rfind("veth", 0) == 0 ||
		name.rfind("br-", 0) == 0 ||
		name.rfind("virbr", 0) == 0 ||
		name.rfind("tun", 0) == 0 ||
		name.rfind("tap", 0) == 0;
}
#endif

uint64_t SnowFlake::getNextMill()
{
	uint64_t mill = getNewTimeStamp();
	while (mill <= m_last_time_stamp) {
		mill = getNewTimeStamp();
	}
	return mill;
}

uint64_t SnowFlake::getNewTimeStamp()
{
	auto t = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
	return t.time_since_epoch().count();
}

SnowFlake::SnowFlake(int datacenterId, int machineId)
{
	m_datacenterId = 0L;
	m_machineId = 0L;
	m_sequence = 0L;
	m_last_time_stamp = 0L;
	m_is_init = false;
	if ((uint64_t)datacenterId > m_max_datacenter_num || (uint64_t)datacenterId < 0) {
		std::cerr << "datacenterId can't be greater than max_datacenter_num_ or less than 0" << std::endl;
		return;
	}
	if ((uint64_t)machineId > m_max_machine_num || (uint64_t)machineId < 0) {
		std::cerr << "machineId can't be greater than max_machine_num_or less than 0" << std::endl;
		return;
	}
	m_datacenterId = datacenterId;
	m_machineId = machineId;
	m_is_init = true;
}

uint64_t SnowFlake::nextId()
{
	// 构造初始化错误，不执行后续逻辑
	if (!m_is_init) return 0;

	std::unique_lock<std::mutex> lock(m_mtx);
	uint64_t curTimeStamp = getNewTimeStamp();
	// 如果当前时间小于上一次ID生成的时间戳，说明系统时钟回退过这个时候应当抛出异常
	if (curTimeStamp < m_last_time_stamp) {
		std::cerr << "clock moved backwards. refusing to generate id" << std::endl;
		return 0;
	}
	// 如果是同一时间生成的，则进行毫秒内序列
	if (curTimeStamp == m_last_time_stamp) {
		m_sequence = (m_sequence + 1) & m_max_sequence_num;
		// 毫秒内序列溢出
		if (m_sequence == 0) {
			// 获取下一个毫秒时间戳
			curTimeStamp = getNextMill();
		}
	}
	// 时间戳改变，毫秒内序列重置
	else
	{
		m_sequence = 0;
	}
	// 更新上次生成ID的时间戳
	m_last_time_stamp = curTimeStamp;
	// 移位并通过或运算拼到一起组成64位的ID
	return (curTimeStamp - m_start_time_stamp) << m_timestamp_left
		| m_datacenterId << m_datacenter_left
		| m_machineId << m_machine_left
		| m_sequence;
}

SnowFlake* SnowFlake::getInstance(int datacenterId /*= 0*/, int machineId/*= generateMachineId()*/)
{
	static SnowFlake instance(datacenterId, machineId);
	return &instance;
}

uint64_t SnowFlake::generateMachineId()
{
	uint64_t hash = 0;
	std::string macStr;
#ifdef _WIN32
	// 获取适配器列表，排除虚拟网卡（Type != 物理网卡）
	PIP_ADAPTER_INFO pAdapterInfo = nullptr;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR && pAdapterInfo)
	{
		PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			// 过滤虚拟网卡：排除Software Loopback(24) 和 Tunnel(131)等
			bool isPhysical = false;
			switch (pAdapter->Type)
			{
				// 有线网卡
			case MIB_IF_TYPE_ETHERNET:
				// 无线网卡
			case IF_TYPE_IEEE80211:
				isPhysical = true;
				break;
			default:
				break;
			}
			// 如果是物理网卡，则取MAC地址
			if (isPhysical && pAdapter->AddressLength >= 6)
			{
				for (UINT i = 0; i < pAdapter->AddressLength; i++)
				{
					macStr += std::to_string(pAdapter->Address[i]);
				}
				// 使用第一个物理网卡
				break;
			}
			pAdapter = pAdapter->Next;
		}
	}
	if (pAdapterInfo) free(pAdapterInfo);
#else
	// 遍历网络接口，排除虚拟接口名称
	struct ifaddrs* ifaddr = nullptr;
	if (getifaddrs(&ifaddr) == 0)
	{
		std::set<std::string> processed;
		// 防止同一接口重复处理（多地址族）
		for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next)
		{
			if (!ifa->ifa_name) continue;
			std::string ifname(ifa->ifa_name);
			// 跳过虚拟接口及已处理接口
			if (isVirtualInterface(ifname) || processed.count(ifname))
				continue;
			processed.insert(ifname);

			// 直接通过接口名称获取MAC（不依赖IP地址）
			int sock = socket(AF_INET, SOCK_DGRAM, 0);
			if (sock < 0) continue;

			struct ifreq ifr;
			memset(&ifr, 0, sizeof(ifr));
			strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ - 1);
			if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0)
			{
				unsigned char* mac = (unsigned char*)ifr.ifr_hwaddr.sa_data;
				for (int i = 0; i < 6; i++) {
					macStr += std::to_string(mac[i]);
				}
				// 使用第一个物理网卡
				close(sock);
				break;
			}
			close(sock);
		}
		freeifaddrs(ifaddr);
	}
#endif

	// 无法获取物理MAC时，使用随机数+时间戳
	if (macStr.empty())
	{
		std::random_device rd;
		macStr = std::to_string(rd()) + std::to_string(time(nullptr));
	}

	// 哈希后取低5位，确保在0~31之间
	std::hash<std::string> strHash;
	hash = strHash(macStr) & m_max_machine_num;
	return hash;
}
