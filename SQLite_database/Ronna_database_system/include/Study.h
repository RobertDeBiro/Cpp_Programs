#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rtkplanning
{

/**
 * @brief Class representing a study in the database model.
 */
class Study
{
public:
    std::string StudyInstanceUID; // primary key
    std::optional<std::string> StudyID;
    std::optional<std::string> StudyDate;
    std::optional<std::string> StudyTime;
    std::optional<std::string> StudyDescription;
    std::optional<std::string> AccessionNumber;
    long long PatientUID;

    /**
     * @brief Get all studies from the database.
     * 
     * @return std::vector<std::shared_ptr<Study>> 
     */
    static std::vector<std::shared_ptr<Study>> getAll();

    /**
     * @brief Get all studies from the database that belong to a given patient.
     * 
     * @param PatientUID 
     * @return std::vector<std::shared_ptr<Study>> 
     */
    static std::vector<std::shared_ptr<Study>> getAllWhere(long long PatientUID);

    /**
     * @brief Get a study with the given study instance UID.
     * 
     * @param StudyInstanceUID 
     * @return std::shared_ptr<Study> 
     */
    static std::shared_ptr<Study> get(const std::string& StudyInstanceUID);

    /**
     * @brief Insert a given study in the database.
     * 
     * @param study 
     * @return true if study added successfully
     * @return false if study was failed to be added
     */
    static bool insert(const Study& study);

    /**
     * @brief Remove a study with the given study instance UID from the database.
     * If parent patient is left empty after deleting a study, patient gets deleted as well.
     * 
     * @param StudyInstanceUID 
     * @return true if study removed successfully
     * @return false if study was failed to be removed
     */
    static bool remove(const std::string& StudyInstanceUID);

    static std::shared_ptr<Study> getByStudyId(const std::string &StudyID);

};

}