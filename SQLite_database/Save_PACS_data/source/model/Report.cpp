#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "Study.h"
#include "Patient.h"
#include "Database.h"
#include "Report.h"

using namespace rtkplanning;

std::vector<std::shared_ptr<Report>> Report::getAll()
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all operation reports from database.");

    std::vector<std::shared_ptr<Report>> reports;
    std::string query = 
        "SELECT "
            "UID, "
            "ReportJson, "
            "SeriesInstanceUID, "
            "ReportName "
        "FROM OperationReports";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        while(statement->step())
        {
            auto s = std::make_shared<Report>();
            
            s->UID                      = statement->getInt64(0);
            s->ReportJson               = statement->getText(1);
            s->SeriesInstanceUID        = statement->getText(2).value_or("N/A");
            s->ReportName               = statement->getText(3).value_or("N/A");

            reports.push_back(s);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation reports: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation reports: {}!", e.what());
    }

    return reports;
}

std::vector<std::shared_ptr<Report> > Report::getAllWhere(const std::string& SeriesInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all operation reports from database where SeriesInstanceUID is {}.", SeriesInstanceUID);

    std::vector<std::shared_ptr<Report> > reports;
    std::string query = 
        "SELECT "
            "UID, "
            "ReportJson, "
            "SeriesInstanceUID, "
            "ReportName "
        "FROM OperationReports "
        "WHERE SeriesInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, SeriesInstanceUID);

        while(statement->step())
        {
            auto s = std::make_shared<Report>();
            
            s->UID                      = statement->getInt64(0);
            s->ReportJson               = statement->getText(1);
            s->SeriesInstanceUID        = statement->getText(2).value_or("N/A");
            s->ReportName               = statement->getText(3).value_or("N/A");

            reports.push_back(s);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation reports: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation reports: {}!", e.what());
    }

    return reports;
}

std::shared_ptr<Report> Report::get(const std::string& UID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get operation report by UID {} from database.", UID);

    std::string query = 
        "SELECT "
            "UID, "
            "ReportJson, "
            "SeriesInstanceUID, "
            "ReportName "
        "FROM OperationReports "
        "WHERE UID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, UID);

        if(statement->step())
        {
            auto s = std::make_shared<Report>();

            s->UID                      = statement->getInt64(0);
            s->ReportJson               = statement->getText(1);
            s->SeriesInstanceUID        = statement->getText(2).value_or("N/A");
            s->ReportName               = statement->getText(3).value_or("N/A");

            return s;
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation report: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation report: {}!", e.what());
    }
    
    return nullptr;
}

bool Report::insert(const Report& report)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Insert operation report {} to database.", report.ReportName);

    std::string query = 
        "INSERT INTO OperationReports ("
            "ReportJson, "
            "SeriesInstanceUID, "
            "ReportName) "
        "VALUES (?, ?, ?)";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        statement->bind(0, report.ReportJson.value_or("N/A"));
        statement->bind(1, report.SeriesInstanceUID);
        statement->bind(2, report.ReportName);

        statement->step();

        lastInsertedUID = Database::getInstance().getLastInsertedRowID();
        // lastInsertedUID = Report::getLastInsertedUID();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation report: {}!", e.what());
        return false;
    }
}

bool Report::remove(const std::string& UID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Remove operation report from database by UID {}.", UID);

    try
    {
        auto report = Report::get(UID);

        if (report == nullptr)
            return false;

        std::string query = "DELETE FROM OperationReports WHERE UID = ?";
        std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);
        
        statement->prepare();
        statement->bind(0, report->UID);
        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting operation report: {}!", e.what());
        return false;
    }
}

long long Report::getLastInsertedUID()
{
    return Report::lastInsertedUID;
}

bool Report::exists(const std::string& json_string)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Check if operation report exists in database.");

    std::string query = "SELECT FROM OperationReports WHERE ReportJson = ?";
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
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while checking existance of operation report: {}!", e.what());
        return false;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while checking existance of operation report: {}!", e.what());
        return false;
    }
}

bool Report::updateReportJson(const std::string &UID, std::string new_json)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Update operation report JSON file in database.");

    std::string query = 
        "UPDATE OperationReports SET ReportJson = ? WHERE UID = ?";
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
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while updating operation report: {}!", e.what());
        return false;
    }
}
