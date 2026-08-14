#pragma once

#ifndef _PRESCRIPTION3_ORDER_DO_H_
#define _PRESCRIPTION3_ORDER_DO_H_

#include <string>

enum class Prescription3OrderType
{
    Medication,
    Service,
    Device
};

/**
 * Minimal persistence projection shared by the three outpatient order tables.
 */
struct Prescription3OrderDO
{
    Prescription3OrderType type = Prescription3OrderType::Medication;
    std::string id;
    std::string tenantId;
    std::string groupId;
    std::string status;
    std::string patientId;
    std::string encounterId;
    std::string requesterId;
    std::string orgId;
    std::string locationId;
    int isDeleted = 0;

    std::string key() const
    {
        return std::to_string(static_cast<int>(type)) + ":" + id;
    }
};

#endif
