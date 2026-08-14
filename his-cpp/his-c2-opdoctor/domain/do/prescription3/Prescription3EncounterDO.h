#pragma once

#ifndef _PRESCRIPTION3_ENCOUNTER_DO_H_
#define _PRESCRIPTION3_ENCOUNTER_DO_H_

#include <string>

/**
 * Minimal encounter projection used for order-list optimistic locking.
 */
struct Prescription3EncounterDO
{
    bool found = false;
    std::string id;
    std::string tenantId;
    std::string patientId;
    std::string status;
    int version = 0;
    std::string updatedAt;
};

#endif
