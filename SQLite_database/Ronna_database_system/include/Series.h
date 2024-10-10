#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rtkplanning
{

/**
 * @brief Class representing a series in the database model.
 */
class Series
{
public:
    std::string SeriesInstanceUID; // primary key
    std::optional<std::string> SeriesNumber;
    std::optional<std::string> SeriesDate;
    std::optional<std::string> SeriesTime;
    std::optional<std::string> SeriesDescription;
    std::optional<std::string> Modality;
    std::optional<std::string> BodyPartExamined;
    std::string StudyInstanceUID;

    /**
     * @brief Get all series from the database.
     * 
     * @return std::vector<std::shared_ptr<Series>> 
     */
    static std::vector<std::shared_ptr<Series>> getAll();

    /**
     * @brief Get all series from the database that belong to a given study.
     * 
     * @param StudyInstanceUID 
     * @return std::vector<std::shared_ptr<Series>> 
     */
    static std::vector<std::shared_ptr<Series>> getAllWhere(const std::string& StudyInstanceUID);
    
    /**
     * @brief Get a series with the given series instance UID.
     * 
     * @param SeriesInstanceUID 
     * @return std::shared_ptr<Series> 
     */
    static std::shared_ptr<Series> get(const std::string& SeriesInstanceUID);
    
    /**
     * @brief Insert a given series in the database.
     * 
     * @param series 
     * @return true if series added successfully
     * @return false if series was failed to be added
     */
    static bool insert(const Series& series);

    /**
     * @brief Remove a series with the given series instance UID from the database.
     * If parent study is left empty after deleting a series, study gets deleted as well.
     * 
     * @param SeriesInstanceUID 
     * @return true if series removed successfully
     * @return false if series was failed to be removed
     */
    static bool remove(const std::string& SeriesInstanceUID);
};

}