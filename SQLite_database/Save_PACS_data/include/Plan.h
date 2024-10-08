#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rtkplanning
{

/**
 * @brief Class representing an operation plan in the database model.
 * 
 */
class Plan
{
public:
    long long UID = 0;
    std::optional<std::string> PlanJson;
    std::string SeriesInstanceUID;
    std::string PlanName;

    /**
     * @brief Get all plans from the database.
     * 
     * @return std::vector<std::shared_ptr<Plan> > 
     */
    static std::vector<std::shared_ptr<Plan>> getAll();

    /**
     * @brief Get all plans from the database that belong to a given patient.
     * 
     * @param PatientUID 
     * @return std::vector<std::shared_ptr<Plan> > 
     */
    static std::vector<std::shared_ptr<Plan>> getAllWhere(const std::string& SeriesInstanceUID);

    /**
     * @brief Get a Plan with the given study instance UID.
     * 
     * @param UID 
     * @return std::shared_ptr<Plan> 
     */
    static std::shared_ptr<Plan> get(const std::string& UID);

    /**
     * @brief Insert a given plan in the database.
     * 
     * @param plan 
     * @return true if plan added successfully
     * @return false if plan was failed to be added
     */
    static bool insert(const Plan& plan);

    /**
     * @brief Remove a plan with the given plan instance UID from the database.
     * 
     * @param UID 
     * @return true if plan removed successfully
     * @return false if plan was failed to be removed
     */
    static bool remove(const std::string& UID);

    /**
     * @brief Get the UID of a last inserted plan in the database.
     * 
     * @return long long 
     */
    static long long getLastInsertedUID();


    /** @brief Check if given plan already exists in the database.
     * 
     * @return true if plan exists database
     * @return false if plan is does not exist in the database
     */
    static bool exists(const std::string& json_string);

    static bool updateName(const std::string& UID, const std::string& new_name);
    static bool updatePlanJson(const std::string& UID, std::string new_json);

private:
    inline static long long lastInsertedUID;
};

}