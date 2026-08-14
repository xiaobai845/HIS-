#pragma once

#ifndef _PRESCRIPTION3_SERVICE_H_
#define _PRESCRIPTION3_SERVICE_H_

#include "../../dao/prescription3/Prescription3DAO.h"
#include "../../domain/dto/prescription3/Prescription3BatchDeleteDTO.h"
#include "../../domain/dto/prescription3/Prescription3MergeGroupDTO.h"
#include "../../domain/dto/prescription3/Prescription3SplitGroupDTO.h"

#include <stdexcept>
#include <string>
#include <vector>

enum Prescription3ErrorCode
{
    PRESCRIPTION3_INVALID_REQUEST = 21001,
    PRESCRIPTION3_NOT_FOUND = 21002,
    PRESCRIPTION3_INVALID_STATUS = 21003,
    PRESCRIPTION3_INVALID_GROUP = 21004,
    PRESCRIPTION3_SCOPE_MISMATCH = 21005,
    PRESCRIPTION3_CONCURRENT_CHANGE = 21006,
    PRESCRIPTION3_DATABASE_ERROR = 21007
};

struct Prescription3OperationResult
{
    int affectedRows = 0;
    std::string groupId;
    std::vector<Prescription3OrderDO> affectedOrders;
    int version = 0;
    std::string updatedAt;
};

class Prescription3BusinessException : public std::runtime_error
{
public:
    Prescription3BusinessException(int code, const std::string& message)
        : std::runtime_error(message), code_(code)
    {
    }

    int code() const
    {
        return code_;
    }

private:
    int code_;
};

class Prescription3Service
{
public:
    Prescription3OperationResult batchDelete(
        const Prescription3BatchDeleteDTO::Wrapper& dto,
        const std::string& operatorId);

    Prescription3OperationResult mergeGroup(
        const Prescription3MergeGroupDTO::Wrapper& dto,
        const std::string& operatorId);

    Prescription3OperationResult splitGroup(
        const Prescription3SplitGroupDTO::Wrapper& dto,
        const std::string& operatorId);

private:
    static constexpr std::size_t MAX_BATCH_SIZE = 200;

    Prescription3DAO dao_;

    static std::vector<std::string> extractAdviceIds(
        const oatpp::List<oatpp::String>& adviceIds);
    static std::string extractEncounterId(
        const oatpp::String& encounterId);
    static int extractVersion(const oatpp::Int32& version);

    static void validateOperator(const std::string& operatorId);
    static void validateEncounterState(
        const Prescription3EncounterDO& encounter,
        int expectedVersion);
    static void validateRowsExist(
        const std::vector<Prescription3OrderDO>& rows,
        const std::vector<std::string>& requestedIds);
    static void validateEncounter(
        const std::vector<Prescription3OrderDO>& rows,
        const Prescription3EncounterDO& encounter);
    static void validateDraft(
        const std::vector<Prescription3OrderDO>& rows);
    static void validateSameScope(
        const std::vector<Prescription3OrderDO>& rows);
    static void validateGroupScopes(
        const std::vector<Prescription3OrderDO>& rows);
    static std::vector<Prescription3OrderDO> expandGroups(
        Prescription3DAO& dao,
        const std::vector<Prescription3OrderDO>& selected);
    static std::string generateGroupId();
};

#endif
