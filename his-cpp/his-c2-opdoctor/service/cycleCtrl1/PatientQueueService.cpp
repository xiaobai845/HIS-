#include "PatientQueueService.h"
#include "dao/cycleCtrl1/PatientQueueDAO.h"
#include <ctime>
#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <sstream>

oatpp::Vector<PatientQueueDTO::Wrapper> PatientQueueService::getPatientQueueList(
    const PatientQueueQuery::Wrapper& query,
    const std::string& tenantId,
    const std::string& practitionerId)
{
    std::unordered_map<std::string, std::string> statusDict;
    if (m_mongoClient)
    {
        statusDict = EnumDictUtil::loadEnumDict(*m_mongoClient, tenantId, "visit_status");
    }

    std::list<PtrPatientQueueCombineDO> dataList = m_patientQueueDAO.queryPatientQueue(query, tenantId, practitionerId);
    auto resultVec = oatpp::Vector<PatientQueueDTO::Wrapper>::createShared();

    static const std::unordered_map<std::string, std::string> statusMapping = {
        {"arrived", "待诊"},
        {"in-progress", "在诊"},
        {"on-hold", "暂离"},
        {"finished", "完诊"}
    };

    for (auto& combineDO : dataList)
    {
        auto item = PatientQueueDTO::createShared();

        auto encDO = combineDO->getEncounterDO();
        auto patDO = combineDO->getPatientDO();
        auto servDO = combineDO->getServiceDO();
        auto accDO = combineDO->getAccountDO();

        item->patientName = patDO->getName();

        if (patDO->getGenderEnum() == "MALE")
            item->gender = u8"男性";
        else if (patDO->getGenderEnum() == "FEMALE")
            item->gender = u8"女性";
        else
            item->gender = u8"未知";

        item->age = calcAge(patDO->getBirthDate());
        item->registerType = servDO->getName();

        int64_t ts = encDO->getReceptionTime();
        if (ts > 0)
        {
            time_t t = static_cast<time_t>(ts);
            tm* lt = localtime(&t);
            char buf[64] = { 0 };
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", lt);
            item->visitTime = buf;
        }
        else
        {
            item->visitTime = "";
        }

        item->encounterId = encDO->getBusNo();
        item->payType = accDO->getTypeCode();

        std::string statusCode = encDO->getStatusEnum();
        std::string visitStatusText = "未知";

        // 直接用mysql取出的statusCode匹配Mongo enumKey
        auto itDict = statusDict.find(statusCode);
        if (itDict != statusDict.end())
        {
            visitStatusText = itDict->second;
        }
        else
        {
            // 降级本地映射
            auto itMap = statusMapping.find(statusCode);
            if (itMap != statusMapping.end())
            {
                visitStatusText = itMap->second;
            }
        }
        item->visitStatus = visitStatusText;

        resultVec->push_back(item);
    }

    return resultVec;
}

int PatientQueueService::calcAge(const std::string& birthDate)
{
    if (birthDate.empty())
        return 0;

    std::tm birthTm = {};
    std::istringstream ss(birthDate);
    ss >> std::get_time(&birthTm, "%Y-%m-%d");
    if (ss.fail())
        return 0;

    std::time_t nowT = std::time(nullptr);
    std::tm nowTm = *std::localtime(&nowT);

    int age = nowTm.tm_year - birthTm.tm_year;
    if (nowTm.tm_mon < birthTm.tm_mon ||
        (nowTm.tm_mon == birthTm.tm_mon && nowTm.tm_mday < birthTm.tm_mday))
    {
        age--;
    }
    return age > 0 ? age : 0;
}