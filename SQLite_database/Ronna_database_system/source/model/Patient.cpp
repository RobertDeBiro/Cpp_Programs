#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "Patient.h"
#include "Database.h"

using namespace rtkplanning;

std::vector<std::shared_ptr<Patient>> Patient::getAll()
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all patients from database.");

    std::vector<std::shared_ptr<Patient>> patients;
    std::string query = 
        "SELECT "
            "UID, "
            "PatientName, "
            "PatientID, "
            "PatientBirthDate, "
            "PatientBirthTime, "
            "PatientSex, "
            "PatientAge "
        "FROM Patients";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        while(statement->step())
        {
            auto p = std::make_shared<Patient>();
            
            p->UID                  = statement->getInt64(0);
            p->PatientName          = statement->getText(1);
            p->PatientID            = statement->getText(2);
            p->PatientBirthDate     = statement->getText(3);
            p->PatientBirthTime     = statement->getText(4);
            p->PatientSex           = statement->getText(5);
            p->PatientAge           = statement->getText(6);

            patients.push_back(p);
        }
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting patients: {}!", e.what());
    }

    return patients;
}

std::shared_ptr<Patient> Patient::get(int UID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get patient by UID {} from database.", UID);

    std::string query = 
        "SELECT "
            "UID, "
            "PatientName, "
            "PatientID, "
            "PatientBirthDate, "
            "PatientBirthTime, "
            "PatientSex, "
            "PatientAge "
        "FROM Patients "
        "WHERE UID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, UID);

        if(statement->step())
        {
            auto p = std::make_shared<Patient>();

            p->UID                  = statement->getInt64(0);
            p->PatientName          = statement->getText(1);
            p->PatientID            = statement->getText(2);
            p->PatientBirthDate     = statement->getText(3);
            p->PatientBirthTime     = statement->getText(4);
            p->PatientSex           = statement->getText(5);
            p->PatientAge           = statement->getText(6);

            return p;
        }
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting patient: {}!", e.what());
    }

    return nullptr;
}

std::shared_ptr<Patient> Patient::get(const std::optional<std::string>& PatientID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get patient with PatientID {} from database.", PatientID.value());

    if(!PatientID)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Error: Invalid Patient ID!");
        return nullptr;
    }
    
    std::string query = 
        "SELECT "
            "UID, "
            "PatientName, "
            "PatientID, "
            "PatientBirthDate, "
            "PatientBirthTime, "
            "PatientSex, "
            "PatientAge "
        "FROM Patients "
        "WHERE PatientID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, PatientID);

        if(statement->step())
        {
            auto p = std::make_shared<Patient>();

            p->UID                  = statement->getInt64(0);
            p->PatientName          = statement->getText(1);
            p->PatientID            = statement->getText(2);
            p->PatientBirthDate     = statement->getText(3);
            p->PatientBirthTime     = statement->getText(4);
            p->PatientSex           = statement->getText(5);
            p->PatientAge           = statement->getText(6);

            return p;
        }
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting patient: {}!", e.what());
    }

    return nullptr;
}

bool Patient::insert(const Patient& patient)
{
    //* Check if the patient already exists
    std::string checkQuery = "SELECT COUNT(*) FROM Patients WHERE PatientID = ?";
    std::shared_ptr<Statement> checkStatement = Database::getInstance().createStatement(checkQuery);

    try
    {
        checkStatement->prepare();
        checkStatement->bind(0, patient.PatientID);
        checkStatement->step();

        // Get the count of patients with the same PatientID
        const int column = 0;
        long long count = checkStatement->getInt64(column);
        
        if (count > 0)
        {
            SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Patient with PatientID {} already exists in database. Skipping insertion.",
                               patient.PatientID.value());
            return false; // Patient already exists, skip insertion
        }
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while checking for existing patient: {}!", e.what());
        return false;
    }

    //* Insert Patient to database
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Insert patient {} with PatientID {} to database.",
                       patient.PatientName.value(), patient.PatientID.value());

    std::string query = 
        "INSERT INTO Patients ("
            "PatientID, "
            "PatientName, "
            "PatientBirthDate, "
            "PatientBirthTime, "
            "PatientSex, "
            "PatientAge) "
        "VALUES (?, ?, ?, ?, ?, ?)";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        statement->bind(0, patient.PatientID);
        statement->bind(1, patient.PatientName);
        statement->bind(2, patient.PatientBirthDate);
        statement->bind(3, patient.PatientBirthTime);
        statement->bind(4, patient.PatientSex);
        statement->bind(5, patient.PatientAge);

        statement->step();

        lastInsertedUID = Database::getInstance().getLastInsertedRowID();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while inserting patients: {}!", e.what());
    }

    return false;
}

bool Patient::remove(int UID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Remove patient by UID {} from database.", UID);

    try
    {
        auto query = "DELETE FROM Patients WHERE UID = ?";
        auto statement = Database::getInstance().createStatement(query);
        
        statement->prepare();
        statement->bind(0, UID);
        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while deleting patients: {}!", e.what());
    }

    return false;
}

long long Patient::getLastInsertedUID()
{
    return lastInsertedUID;
}
