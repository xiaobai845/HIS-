#pragma once
#ifndef _ENUMDICTUTIL_H_
#define _ENUMDICTUTIL_H_
#include <string>
#include <unordered_map>
#include "MongoClient.h"

class EnumDictUtil
{
public:
    
    static std::unordered_map<std::string, std::string> loadEnumDict(MongoClient& mongoCli,
        const std::string& tenantId, const std::string& enumTypeKey);

    static std::string getText(const std::unordered_map<std::string, std::string>& dict,
        const std::string& enumKey, const std::string& defaultText = "δ֪");
};

#endif // _ENUMDICTUTIL_H_