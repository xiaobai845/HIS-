#include "stdafx.h"
#include "Prescription3DAO.h"

#include <array>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace
{
struct TableSpec
{
    Prescription3OrderType type;
    const char* table;
    const char* groupColumn;
};

const std::array<TableSpec, 3> TABLES = {{
    {Prescription3OrderType::Medication,
        "med_medication_request", "group_id"},
    {Prescription3OrderType::Service,
        "wkf_service_request", "group_id"},
    {Prescription3OrderType::Device,
        "wkf_device_request", "group_no"}
}};

const TableSpec& tableFor(Prescription3OrderType type)
{
    for (const auto& spec : TABLES)
    {
        if (spec.type == type)
        {
            return spec;
        }
    }
    throw std::invalid_argument("Unsupported order type");
}

std::string makePlaceholders(std::size_t count)
{
    if (count == 0)
    {
        throw std::invalid_argument("SQL IN list must not be empty");
    }

    std::ostringstream stream;
    for (std::size_t index = 0; index < count; ++index)
    {
        if (index > 0)
        {
            stream << ',';
        }
        stream << '?';
    }
    return stream.str();
}

int bindStrings(
    sql::PreparedStatement& statement,
    int start,
    const std::vector<std::string>& values)
{
    int position = start;
    for (const auto& value : values)
    {
        statement.setString(position++, value);
    }
    return position;
}

std::string nullableString(
    sql::ResultSet& result,
    const std::string& column)
{
    const auto value = result.getString(column);
    return result.wasNull() ? std::string() : value.asStdString();
}

Prescription3OrderDO mapOrder(
    sql::ResultSet& result,
    Prescription3OrderType type)
{
    Prescription3OrderDO order;
    order.type = type;
    order.id = nullableString(result, "id");
    order.tenantId = nullableString(result, "tenant_id");
    order.groupId = nullableString(result, "group_value");
    order.status = nullableString(result, "status_enum");
    order.patientId = nullableString(result, "patient_id");
    order.encounterId = nullableString(result, "encounter_id");
    order.requesterId = nullableString(result, "requester_id");
    order.orgId = nullableString(result, "org_id");
    order.locationId = nullableString(result, "location_id");
    order.isDeleted = result.getInt("is_deleted");
    return order;
}

Prescription3EncounterDO mapEncounter(sql::ResultSet& result)
{
    Prescription3EncounterDO encounter;
    encounter.found = true;
    encounter.id = nullableString(result, "id");
    encounter.tenantId = nullableString(result, "tenant_id");
    encounter.patientId = nullableString(result, "patient_id");
    encounter.status = nullableString(result, "status_enum");
    encounter.version = result.getInt("version");
    encounter.updatedAt = nullableString(result, "updated_at_text");
    return encounter;
}

sql::Connection& requireConnection(Prescription3DAO& dao)
{
    auto* session = dao.getSqlSession();
    if (session == nullptr || session->getConnection() == nullptr)
    {
        throw std::runtime_error("Database connection is unavailable");
    }
    return *session->getConnection();
}

std::map<Prescription3OrderType, std::vector<std::string>> groupIdsByType(
    const std::vector<Prescription3OrderDO>& orders)
{
    std::map<Prescription3OrderType, std::vector<std::string>> grouped;
    for (const auto& order : orders)
    {
        grouped[order.type].push_back(order.id);
    }
    return grouped;
}

int executeUpdateByType(
    sql::Connection& connection,
    const std::vector<Prescription3OrderDO>& orders,
    const std::string& assignment,
    const std::vector<std::string>& leadingParameters,
    const std::string& operatorId)
{
    int affected = 0;
    const auto grouped = groupIdsByType(orders);

    for (const auto& entry : grouped)
    {
        const auto& spec = tableFor(entry.first);
        const auto& ids = entry.second;
        if (ids.empty())
        {
            continue;
        }

        const std::string sqlText =
            std::string("UPDATE ") + spec.table + " SET " + assignment +
            ", updated_at = NOW(6), updated_by = ?, "
            "version = version + 1 "
            "WHERE id IN (" + makePlaceholders(ids.size()) + ") "
            "AND status_enum = 'DRAFT' AND is_deleted = 0";

        std::unique_ptr<sql::PreparedStatement> statement(
            connection.prepareStatement(sqlText));
        int position = bindStrings(*statement, 1, leadingParameters);
        statement->setString(position++, operatorId);
        bindStrings(*statement, position, ids);
        affected += statement->executeUpdate();
    }
    return affected;
}
}

Prescription3EncounterDO Prescription3DAO::selectEncounterForUpdate(
    const std::string& encounterId)
{
    auto& connection = requireConnection(*this);
    const std::string sqlText =
        "SELECT id, tenant_id, patient_id, status_enum, version, "
        "DATE_FORMAT(updated_at, '%Y-%m-%d %H:%i:%s.%f') "
        "AS updated_at_text FROM adm_encounter "
        "WHERE id = ? AND is_deleted = 0 FOR UPDATE";

    std::unique_ptr<sql::PreparedStatement> statement(
        connection.prepareStatement(sqlText));
    statement->setString(1, encounterId);
    std::unique_ptr<sql::ResultSet> rows(statement->executeQuery());
    return rows->next() ? mapEncounter(*rows) : Prescription3EncounterDO{};
}

Prescription3EncounterDO Prescription3DAO::incrementEncounterVersion(
    const std::string& encounterId,
    int expectedVersion,
    const std::string& operatorId)
{
    auto& connection = requireConnection(*this);
    const std::string updateText =
        "UPDATE adm_encounter SET version = version + 1, "
        "updated_at = NOW(6), updated_by = ? "
        "WHERE id = ? AND version = ? AND is_deleted = 0";

    std::unique_ptr<sql::PreparedStatement> updateStatement(
        connection.prepareStatement(updateText));
    updateStatement->setString(1, operatorId);
    updateStatement->setString(2, encounterId);
    updateStatement->setInt(3, expectedVersion);
    if (updateStatement->executeUpdate() != 1)
    {
        return {};
    }

    const std::string selectText =
        "SELECT id, tenant_id, patient_id, status_enum, version, "
        "DATE_FORMAT(updated_at, '%Y-%m-%d %H:%i:%s.%f') "
        "AS updated_at_text FROM adm_encounter WHERE id = ?";
    std::unique_ptr<sql::PreparedStatement> selectStatement(
        connection.prepareStatement(selectText));
    selectStatement->setString(1, encounterId);
    std::unique_ptr<sql::ResultSet> rows(selectStatement->executeQuery());
    return rows->next() ? mapEncounter(*rows) : Prescription3EncounterDO{};
}

std::vector<Prescription3OrderDO>
Prescription3DAO::selectByAdviceIdsForUpdate(
    const std::vector<std::string>& adviceIds)
{
    std::vector<Prescription3OrderDO> result;
    if (adviceIds.empty())
    {
        return result;
    }

    auto& connection = requireConnection(*this);
    for (const auto& spec : TABLES)
    {
        const std::string sqlText =
            std::string("SELECT id, tenant_id, ") + spec.groupColumn +
            " AS group_value, status_enum, patient_id, encounter_id, "
            "requester_id, org_id, location_id, is_deleted FROM " +
            spec.table +
            " WHERE id IN (" + makePlaceholders(adviceIds.size()) +
            ") FOR UPDATE";

        std::unique_ptr<sql::PreparedStatement> statement(
            connection.prepareStatement(sqlText));
        bindStrings(*statement, 1, adviceIds);
        std::unique_ptr<sql::ResultSet> rows(statement->executeQuery());
        while (rows->next())
        {
            result.push_back(mapOrder(*rows, spec.type));
        }
    }
    return result;
}

std::vector<Prescription3OrderDO>
Prescription3DAO::selectByGroupIdsForUpdate(
    const std::vector<std::string>& groupIds)
{
    std::vector<Prescription3OrderDO> result;
    if (groupIds.empty())
    {
        return result;
    }

    auto& connection = requireConnection(*this);
    for (const auto& spec : TABLES)
    {
        const std::string sqlText =
            std::string("SELECT id, tenant_id, ") + spec.groupColumn +
            " AS group_value, status_enum, patient_id, encounter_id, "
            "requester_id, org_id, location_id, is_deleted FROM " +
            spec.table +
            " WHERE " + spec.groupColumn + " IN (" +
            makePlaceholders(groupIds.size()) +
            ") AND is_deleted = 0 FOR UPDATE";

        std::unique_ptr<sql::PreparedStatement> statement(
            connection.prepareStatement(sqlText));
        bindStrings(*statement, 1, groupIds);
        std::unique_ptr<sql::ResultSet> rows(statement->executeQuery());
        while (rows->next())
        {
            result.push_back(mapOrder(*rows, spec.type));
        }
    }
    return result;
}

int Prescription3DAO::softDelete(
    const std::vector<Prescription3OrderDO>& orders,
    const std::string& operatorId)
{
    return executeUpdateByType(
        requireConnection(*this),
        orders,
        "is_deleted = 1, deleted_at = NOW(6), deleted_by = ?",
        {operatorId},
        operatorId);
}

int Prescription3DAO::assignGroup(
    const std::vector<Prescription3OrderDO>& orders,
    const std::string& groupId,
    const std::string& operatorId)
{
    int affected = 0;
    const auto grouped = groupIdsByType(orders);
    auto& connection = requireConnection(*this);

    for (const auto& entry : grouped)
    {
        const auto& ids = entry.second;
        if (ids.empty())
        {
            continue;
        }

        const auto& spec = tableFor(entry.first);
        const std::string sqlText =
            std::string("UPDATE ") + spec.table + " SET " +
            spec.groupColumn +
            " = ?, updated_at = NOW(6), updated_by = ?, "
            "version = version + 1 WHERE id IN (" +
            makePlaceholders(ids.size()) +
            ") AND status_enum = 'DRAFT' AND is_deleted = 0";

        std::unique_ptr<sql::PreparedStatement> statement(
            connection.prepareStatement(sqlText));
        statement->setString(1, groupId);
        statement->setString(2, operatorId);
        bindStrings(*statement, 3, ids);
        affected += statement->executeUpdate();
    }
    return affected;
}

int Prescription3DAO::clearGroups(
    const std::vector<Prescription3OrderDO>& orders,
    const std::string& operatorId)
{
    int affected = 0;
    const auto grouped = groupIdsByType(orders);
    auto& connection = requireConnection(*this);

    for (const auto& entry : grouped)
    {
        const auto& ids = entry.second;
        if (ids.empty())
        {
            continue;
        }

        const auto& spec = tableFor(entry.first);
        const std::string sqlText =
            std::string("UPDATE ") + spec.table + " SET " +
            spec.groupColumn +
            " = NULL, updated_at = NOW(6), updated_by = ?, "
            "version = version + 1 WHERE id IN (" +
            makePlaceholders(ids.size()) +
            ") AND status_enum = 'DRAFT' AND is_deleted = 0";

        std::unique_ptr<sql::PreparedStatement> statement(
            connection.prepareStatement(sqlText));
        statement->setString(1, operatorId);
        bindStrings(*statement, 2, ids);
        affected += statement->executeUpdate();
    }
    return affected;
}
