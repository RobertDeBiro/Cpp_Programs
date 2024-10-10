#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "Series.h"
#include "Study.h"
#include "Database.h"

using namespace rtkplanning;

std::vector<std::shared_ptr<Series>> Series::getAll()
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all series from database.");

    std::vector<std::shared_ptr<Series>> series;
    std::string query = 
        "SELECT "
            "SeriesInstanceUID, "
            "SeriesNumber, "
            "SeriesDate, "
            "SeriesTime, "
            "SeriesDescription, "
            "Modality, "
            "BodyPartExamined, "
            "StudyInstanceUID "
        "FROM Series";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        while(statement->step())
        {
            auto s = std::make_shared<Series>();
            
            s->SeriesInstanceUID   = statement->getText(0).value();
            s->SeriesNumber        = statement->getText(1);
            s->SeriesDate          = statement->getText(2);
            s->SeriesTime          = statement->getText(3);
            s->SeriesDescription   = statement->getText(4);
            s->Modality            = statement->getText(5);
            s->BodyPartExamined    = statement->getText(6);
            s->StudyInstanceUID    = statement->getText(7).value();
            

            series.push_back(s);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting series: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting series: {}!", e.what());
    }

    return series;
}

std::vector<std::shared_ptr<Series>> Series::getAllWhere(const std::string& StudyInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all series from database where StudyInstanceUID is {}.", StudyInstanceUID);

    std::vector<std::shared_ptr<Series>> series;
    std::string query = 
        "SELECT "
            "SeriesInstanceUID, "
            "SeriesNumber, "
            "SeriesDate, "
            "SeriesTime, "
            "SeriesDescription, "
            "Modality, "
            "BodyPartExamined, "
            "StudyInstanceUID "
        "FROM Series "
        "WHERE StudyInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, StudyInstanceUID);

        while(statement->step())
        {
            auto s = std::make_shared<Series>();
            
            s->SeriesInstanceUID   = statement->getText(0).value();
            s->SeriesNumber        = statement->getText(1);
            s->SeriesDate          = statement->getText(2);
            s->SeriesTime          = statement->getText(3);
            s->SeriesDescription   = statement->getText(4);
            s->Modality            = statement->getText(5);
            s->BodyPartExamined    = statement->getText(6);
            s->StudyInstanceUID    = statement->getText(7).value();
            

            series.push_back(s);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting series: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting series: {}!", e.what());
    }

    return series;
}

std::shared_ptr<Series> Series::get(const std::string& SeriesInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get series from database where SeriesInstanceUID is {}.", SeriesInstanceUID);

    std::string query = 
        "SELECT "
            "SeriesInstanceUID, "
            "SeriesNumber, "
            "SeriesDate, "
            "SeriesTime, "
            "SeriesDescription, "
            "Modality, "
            "BodyPartExamined, "
            "StudyInstanceUID "
        "FROM Series "
        "WHERE SeriesInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, SeriesInstanceUID);

        if(statement->step())
        {
            auto s = std::make_shared<Series>();

            s->SeriesInstanceUID   = statement->getText(0).value();
            s->SeriesNumber        = statement->getText(1);
            s->SeriesDate          = statement->getText(2);
            s->SeriesTime          = statement->getText(3);
            s->SeriesDescription   = statement->getText(4);
            s->Modality            = statement->getText(5);
            s->BodyPartExamined    = statement->getText(6);
            s->StudyInstanceUID    = statement->getText(7).value();

            return s;
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting series: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting series: {}!", e.what());
    }
    
    return nullptr;
}

bool Series::insert(const Series& series)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Insert series with SeriesInstanceUID {} to database.", series.SeriesInstanceUID);

    std::string query = 
        "INSERT INTO Series ("
            "SeriesInstanceUID, "
            "SeriesNumber, "
            "SeriesDate, "
            "SeriesTime, "
            "SeriesDescription, "
            "Modality, "
            "BodyPartExamined, "
            "StudyInstanceUID) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        statement->bind(0, series.SeriesInstanceUID);
        statement->bind(1, series.SeriesNumber);
        statement->bind(2, series.SeriesDate);
        statement->bind(3, series.SeriesTime);
        statement->bind(4, series.SeriesDescription);
        statement->bind(5, series.Modality);
        statement->bind(6, series.BodyPartExamined);
        statement->bind(7, series.StudyInstanceUID);

        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while inserting series: {}!", e.what());
        return false;
    }
}

bool Series::remove(const std::string& SeriesInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Remove series by SeriesInstanceUID {} from database.", SeriesInstanceUID);

    try
    {
        auto series = Series::get(SeriesInstanceUID);

        auto q1 = "DELETE FROM Series WHERE SeriesInstanceUID = ?";
        auto s1 = Database::getInstance().createStatement(q1);
        
        s1->prepare();
        s1->bind(0, SeriesInstanceUID);
        s1->step();

        auto q2 = "SELECT * FROM Series WHERE SeriesInstanceUID != ? AND StudyInstanceUID = ?";
        auto s2 = Database::getInstance().createStatement(q2);

        s2->prepare();
        s2->bind(0, series->SeriesInstanceUID);
        s2->bind(1, series->StudyInstanceUID);

        // If study contains no more series
        if(!s2->step())
        {
            Study::remove(series->StudyInstanceUID);
        }

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while removing series: {}!", e.what());
        return false;
    }
}
