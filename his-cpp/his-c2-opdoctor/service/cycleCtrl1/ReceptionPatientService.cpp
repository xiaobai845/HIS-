#include "stdafx.h"
#include "ReceptionPatientService.h"
#include "EnumDictUtil.h"
#include "mongocxx/client.hpp"

RecePatientDTO::Wrapper ReceptionPatientService::getRecePatient(const RecePatientQuery::Wrapper& query,
    const string& tenantId, const string& practitionerId)
{
    auto data = m_dao.queryReceptionPatient(query, tenantId, practitionerId);
    auto dto = RecePatientDTO::createShared();

    if (data == nullptr)
    {
        return dto;
    }

    // 加载状态枚举字典
    std::unordered_map<std::string, std::string> statusDict;
    if (m_mongoClient)
    {
        statusDict = EnumDictUtil::loadEnumDict(*m_mongoClient, tenantId, "visit_status");
    }

    // 填充 DTO 字段
    dto->patientName = data->getPatientDO()->getName();

    std::string statusCode = data->getEncounterDO()->getStatusEnum();
    std::string statusText = "未知";
    auto itDict = statusDict.find(statusCode);
    if (itDict != statusDict.end())
    {
        statusText = itDict->second;
    }
    else
    {
      
        static const std::unordered_map<std::string, std::string> statusMapping = {
            {"arrived", "待诊"},
            {"in-progress", "在诊"},
            {"on-hold", "暂离"},
            {"finished", "完诊"}
        };
        auto itMap = statusMapping.find(statusCode);
        if (itMap != statusMapping.end())
        {
            statusText = itMap->second;
        }
    }
    dto->visitStatus = statusText;


    // 修复：原来写成 "MAIL"，应为 "MALE"
    if (data->getPatientDO()->getGenderEnum() == "MALE")
    {
        dto->gender = u8"男性";
    }
    else if (data->getPatientDO()->getGenderEnum() == "FEMALE")
    {
        dto->gender = u8"女性";
    }
    else
    {
        dto->gender = u8"未知";
    }
    

    dto->age = calcAge(data->getPatientDO()->getBirthDate());
    dto->registerType = data->getServiceDO()->getName();
    dto->encounterId = data->getEncounterDO()->getBusNo();
    dto->payType = data->getAccountDO()->getTypeCode();
    dto->visitTime = data->getEncounterDO()->getReceptionTime();
    dto->registerDept = data->getOrgDO()->getName();
    dto->phoneNum = data->getPatientDO()->getPhone();
    dto->allergyHistory = data->getAllergyDO()->getAllergyText();

    return dto;
}


int ReceptionPatientService::calcAge(const std::string& birthDate)
{
    if (birthDate.empty())
        return 0;

    // 解析出生日期 yyyy-MM-dd
    std::tm birthTm = {};
    std::istringstream ss(birthDate);
    ss >> std::get_time(&birthTm, "%Y-%m-%d");
    if (ss.fail())
        return 0;

    // 当前系统时间
    std::time_t nowT = std::time(nullptr);
    std::tm nowTm = *std::localtime(&nowT);

    int age = nowTm.tm_year - birthTm.tm_year;
    // 判断生日有没有过
    if (nowTm.tm_mon < birthTm.tm_mon ||
        (nowTm.tm_mon == birthTm.tm_mon && nowTm.tm_mday < birthTm.tm_mday))
    {
        age--;
    }
    return age > 0 ? age : 0;
}