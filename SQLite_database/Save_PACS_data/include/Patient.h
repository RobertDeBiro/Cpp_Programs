#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rtkplanning
{

/**
 * @brief Class representing a patient in the database model
 */
class Patient
{
public:
    long long UID = 0; // primary key
    std::optional<std::string> PatientName;
    std::optional<std::string> PatientID;
    std::optional<std::string> PatientBirthDate;
    std::optional<std::string> PatientBirthTime;
    std::optional<std::string> PatientSex;
    std::optional<std::string> PatientAge;

    /**
     * @brief Get all patients from the database.
     * 
     * @return std::vector<std::shared_ptr<Patient>> 
     */
    static std::vector<std::shared_ptr<Patient>> getAll();

    /**
     * @brief Get the patient with the given UID from the database.
     * 
     * @param UID 
     * @return std::shared_ptr<Patient> 
     */
    static std::shared_ptr<Patient> get(int UID);

    /**
     * @brief Get the patient with the given patient ID from the database. Patient ID is allowed to be null.
     * 
     * @param PatientID 
     * @return std::shared_ptr<Patient> 
     */
    static std::shared_ptr<Patient> get(const std::optional<std::string>& PatientID);
    
    /**
     * @brief Insert a given patient in the database.
     * 
     * @param patient 
     * @return true if patient added successfully
     * @return false if patient was failed to be added
     */
    static bool insert(const Patient& patient);

    /**
     * @brief Remove a patient with given UID.
     * 
     * @param UID 
     * @return true if patient removed successfully
     * @return false if patient was failed to be removed
     */
    static bool remove(int UID);

    /**
     * @brief Get the UID of a last inserted patient in the database.
     * 
     * @return long long 
     */
    static long long getLastInsertedUID();

private:
    inline static long long lastInsertedUID;
};

}
