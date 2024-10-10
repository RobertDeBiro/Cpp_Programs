#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rtkplanning
{

/**
 * @brief Class representing an operation report in the database model.
 * 
 */
class Report
{
public:
    long long UID = 0;
    std::optional<std::string> ReportJson;
    std::string SeriesInstanceUID;
    std::string ReportName;

    /**
     * @brief Get all reports from the database.
     * 
     * @return std::vector<std::shared_ptr<Report> > 
     */
    static std::vector<std::shared_ptr<Report> > getAll();

    /**
     * @brief Get all reports from the database that belong to a given patient.
     * 
     * @param PatientUID 
     * @return std::vector<std::shared_ptr<Plan> > 
     */
    static std::vector<std::shared_ptr<Report> > getAllWhere(const std::string&  SeriesInstanceUID);

    /**
     * @brief Get a Report with the given study instance UID.
     * 
     * @param UID 
     * @return std::shared_ptr<Report> 
     */
    static std::shared_ptr<Report> get(const std::string& UID);

    /**
     * @brief Insert a given report in the database.
     * 
     * @param report 
     * @return true if report added successfully
     * @return false if report was failed to be added
     */
    static bool insert(const Report& report);

    /**
     * @brief Remove a report with the given report instance UID from the database.
     * 
     * @param UID 
     * @return true if report removed successfully
     * @return false if report was failed to be removed
     */
    static bool remove(const std::string& UID);

    /**
     * @brief Get the UID of a last inserted report in the database.
     * 
     * @return long long 
     */
    static long long getLastInsertedUID();


    /** @brief Check if given report already exists in the database.
     * 
     * @return true if report exists database
     * @return false if report is does not exist in the database
     */
    static bool exists(const std::string& json_string);

    static bool updateReportJson(const std::string& UID, std::string new_json);

private:
    inline static long long lastInsertedUID;
};

}