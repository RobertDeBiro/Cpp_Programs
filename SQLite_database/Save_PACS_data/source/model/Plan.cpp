#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "Study.h"
#include "Patient.h"
#include "Database.h"
#include "Plan.h"

using namespace rtkplanning;

std::vector<std::shared_ptr<Plan>> Plan::getAll()
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all operation plans from database.");

    std::vector<std::shared_ptr<Plan>> plans;
    std::string query = 
        "SELECT "
            "UID, "
            "PlanJson, "
            "SeriesInstanceUID, "
            "PlanName "
        "FROM OperationPlans";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        while(statement->step())
        {
            auto s = std::make_shared<Plan>();
            
            s->UID                      = statement->getInt64(0);
            s->PlanJson                 = statement->getText(1);
            s->SeriesInstanceUID        = statement->getText(2).value_or("N/A");
            s->PlanName                 = statement->getText(3).value_or("N/A");

            plans.push_back(s);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation plans: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation plans: {}!", e.what());
    }

    return plans;
}

std::vector<std::shared_ptr<Plan>> Plan::getAllWhere(const std::string& SeriesInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all operation plans from database where SeriesInstanceUID is {}.", SeriesInstanceUID);

    std::vector<std::shared_ptr<Plan>> plans;
    std::string query = 
        "SELECT "
            "UID, "
            "PlanJson, "
            "SeriesInstanceUID, "
            "PlanName "
        "FROM OperationPlans "
        "WHERE SeriesInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, SeriesInstanceUID);

        while(statement->step())
        {
            auto s = std::make_shared<Plan>();
            
            s->UID                      = statement->getInt64(0);
            s->PlanJson                 = statement->getText(1);
            s->SeriesInstanceUID        = statement->getText(2).value_or("N/A");
            s->PlanName                 = statement->getText(3).value_or("N/A");

            plans.push_back(s);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation plans: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation plans: {}!", e.what());
    }

    return plans;
}

std::shared_ptr<Plan> Plan::get(const std::string& UID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get operation plan by UID {} from database.", UID);

    std::string query = 
        "SELECT "
            "UID, "
            "PlanJson, "
            "SeriesInstanceUID, "
            "PlanName "
        "FROM OperationPlans "
        "WHERE UID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, UID);

        if(statement->step())
        {
            auto s = std::make_shared<Plan>();

            s->UID                      = statement->getInt64(0);
            s->PlanJson                 = statement->getText(1);
            s->SeriesInstanceUID        = statement->getText(2).value_or("N/A");
            s->PlanName                 = statement->getText(3).value_or("N/A");

            return s;
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation plan: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation plan: {}!", e.what());
    }
    
    return nullptr;
}

bool Plan::insert(const Plan& plan)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Insert operation plan {} into database.", plan.PlanName);

    std::string query = 
        "INSERT INTO OperationPlans ("
            "PlanJson, "
            "SeriesInstanceUID, "
            "PlanName) "
        "VALUES (?, ?, ?)";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        statement->bind(0, plan.PlanJson.value_or("N/A"));
        statement->bind(1, plan.SeriesInstanceUID);
        statement->bind(2, plan.PlanName);

        statement->step();

        lastInsertedUID = Database::getInstance().getLastInsertedRowID();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while inserting operation plan: {}!", e.what());
        return false;
    }
}

bool Plan::remove(const std::string& UID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Remove operation plan by UID {} from database.", UID);

    try
    {
        auto plan = Plan::get(UID);

        if (plan == nullptr)
            return false;

        std::string query = "DELETE FROM OperationPlans WHERE UID = ?";
        std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);
        
        statement->prepare();
        statement->bind(0, plan->UID);
        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while removing operation plan: {}!", e.what());
        return false;
    }
}

long long Plan::getLastInsertedUID()
{
    return Plan::lastInsertedUID;
}

bool Plan::exists(const std::string& json_string)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Check if operation plan exists in database.");

    std::string query = "SELECT FROM OperationPlans WHERE PlanJson = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(1, json_string);

        if(statement->step())
        {
            if (json_string.compare(statement->getText(1).value()) == 0)
                return true;
        }
        return false;
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while checking existance of an operation plan: {}!", e.what());
        return false;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while checking existance of an operation plan: {}!", e.what());
        return false;
    }
}

bool Plan::updateName(const std::string& UID, const std::string& new_name)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Update operation plan name (UID={}) to: {}.", UID, new_name);

    std::string query =
        "UPDATE OperationPlans SET PlanName = ? WHERE UID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, new_name);
        statement->bind(1, UID);
        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while updating operation plan name: {}!", e.what());
        return false;
    }
}

bool Plan::updatePlanJson(const std::string& UID, std::string new_json)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Update operation plan JSON file in database.");

    std::string query = 
        "UPDATE OperationPlans SET PlanJson = ? WHERE UID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, new_json);
        statement->bind(1, UID);
        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while updating operation plan JSON: {}!", e.what());
        return false;
    }
}
