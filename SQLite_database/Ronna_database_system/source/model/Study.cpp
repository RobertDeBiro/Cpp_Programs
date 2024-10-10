#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "Study.h"
#include "Patient.h"
#include "Database.h"

using namespace rtkplanning;

std::vector<std::shared_ptr<Study>> Study::getAll()
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all studies from database.");

    std::vector<std::shared_ptr<Study>> studies;
    std::string query =
        "SELECT "
            "StudyInstanceUID, "
            "StudyID, "
            "StudyDate, "
            "StudyTime, "
            "StudyDescription, "
            "AccessionNumber, "
            "PatientUID "
        "FROM Studies";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        while (statement->step())
        {
            auto s = std::make_shared<Study>();

            s->StudyInstanceUID = statement->getText(0).value();
            s->StudyID = statement->getText(1);
            s->StudyDate = statement->getText(2);
            s->StudyTime = statement->getText(3);
            s->StudyDescription = statement->getText(4);
            s->AccessionNumber = statement->getText(5);
            s->PatientUID = statement->getInt64(6);

            studies.push_back(s);
        }
    }
    catch (const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting studies: {}!", e.what());
    }
    catch (const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting studies: {}!", e.what());
    }

    return studies;
}

std::vector<std::shared_ptr<Study>> Study::getAllWhere(long long PatientUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get studies from database where PatientUID is {}.", PatientUID);

    std::vector<std::shared_ptr<Study>> studies;
    std::string query =
        "SELECT "
            "StudyInstanceUID, "
            "StudyID, "
            "StudyDate, "
            "StudyTime, "
            "StudyDescription, "
            "AccessionNumber, "
            "PatientUID "
        "FROM Studies "
        "WHERE PatientUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, PatientUID);

        while (statement->step())
        {
            auto s = std::make_shared<Study>();

            s->StudyInstanceUID = statement->getText(0).value();
            s->StudyID = statement->getText(1);
            s->StudyDate = statement->getText(2);
            s->StudyTime = statement->getText(3);
            s->StudyDescription = statement->getText(4);
            s->AccessionNumber = statement->getText(5);
            s->PatientUID = statement->getInt64(6);

            studies.push_back(s);
        }
    }
    catch (const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting studies: {}!", e.what());
    }
    catch (const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting studies: {}!", e.what());
    }

    return studies;
}

std::shared_ptr<Study> Study::get(const std::string& StudyInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get studies from database where StudyInstanceUID is {}.", StudyInstanceUID);

    std::string query =
        "SELECT "
            "StudyInstanceUID, "
            "StudyID, "
            "StudyDate, "
            "StudyTime, "
            "StudyDescription, "
            "AccessionNumber, "
            "PatientUID "
        "FROM Studies "
        "WHERE StudyInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, StudyInstanceUID);

        if (statement->step())
        {
            auto s = std::make_shared<Study>();

            s->StudyInstanceUID = statement->getText(0).value();
            s->StudyID = statement->getText(1);
            s->StudyDate = statement->getText(2);
            s->StudyTime = statement->getText(3);
            s->StudyDescription = statement->getText(4);
            s->AccessionNumber = statement->getText(5);
            s->PatientUID = statement->getInt64(6);

            return s;
        }
    }
    catch (const std::bad_optional_access &e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting study: {}!", e.what());
    }
    catch (const SQLException &e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting study: {}!", e.what());
    }

    return nullptr;
}

std::shared_ptr<Study> Study::getByStudyId(const std::string& StudyID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get study from database where StudyID is {}.", StudyID);

    std::string query =
        "SELECT "
            "StudyInstanceUID, "
            "StudyID, "
            "StudyDate, "
            "StudyTime, "
            "StudyDescription, "
            "AccessionNumber, "
            "PatientUID "
        "FROM Studies "
        "WHERE StudyID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);
    try
    {
        statement->prepare();
        statement->bind(0, StudyID);
        if (statement->step())
        {
            auto s = std::make_shared<Study>();
            s->StudyInstanceUID = statement->getText(0).value();
            s->StudyID = statement->getText(1);
            s->StudyDate = statement->getText(2);
            s->StudyTime = statement->getText(3);
            s->StudyDescription = statement->getText(4);
            s->AccessionNumber = statement->getText(5);
            s->PatientUID = statement->getInt64(6);
            return s;
        }
    }
    catch (const std::bad_optional_access &e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting study: {}!", e.what());
    }
    catch (const SQLException &e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting study: {}!", e.what());
    }

    return nullptr;
}

bool Study::insert(const Study& study)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Insert study with StudyInstanceUID {} and StudyID {} to database.",
                       study.StudyInstanceUID, study.StudyID.value());

    std::string query =
        "INSERT INTO Studies ("
            "StudyInstanceUID, "
            "StudyID, "
            "StudyDate, "
            "StudyTime, "
            "StudyDescription, "
            "AccessionNumber, "
            "PatientUID) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        statement->bind(0, study.StudyInstanceUID);
        statement->bind(1, study.StudyID);
        statement->bind(2, study.StudyDate);
        statement->bind(3, study.StudyTime);
        statement->bind(4, study.StudyDescription);
        statement->bind(5, study.AccessionNumber);
        statement->bind(6, study.PatientUID);

        statement->step();

        return true;
    }
    catch (const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while inserting studies: {}!", e.what());
        return false;
    }
}

bool Study::remove(const std::string& StudyInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Remove study from database where StudyInstanceUID is {}.", StudyInstanceUID);

    try
    {
        auto study = Study::get(StudyInstanceUID);

        auto q1 = "DELETE FROM Studies WHERE StudyInstanceUID = ?";
        auto s1 = Database::getInstance().createStatement(q1);

        s1->prepare();
        s1->bind(0, study->StudyInstanceUID);
        s1->step();

        auto q2 = "SELECT * FROM Studies WHERE StudyInstanceUID != ? AND PatientUID = ?";
        auto s2 = Database::getInstance().createStatement(q2);

        s2->prepare();
        s2->bind(0, study->StudyInstanceUID);
        s2->bind(1, study->PatientUID);

        // If patient contains no more studies
        if (!s2->step())
        {
            Patient::remove(study->PatientUID);
        }

        return true;
    }
    catch (const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while removing study: {}!", e.what());
        return false;
    }
}
