#pragma once

#include <memory>
#include <string>
#include <vector>

namespace rtkplanning
{

/**
 * @brief Class representing an image in the database model.
 */
class Image
{
public:
    std::string SOPInstanceUID; // primary key
    std::string Filename;
    std::string SeriesInstanceUID;
    
    /**
     * @brief Get all images from the database.
     * 
     * @return std::vector<std::shared_ptr<Image>> 
     */
    static std::vector<std::shared_ptr<Image>> getAll();

    /**
     * @brief Get an image with the given SOP instance UID.
     * 
     * @param SOPInstanceUID unique identifier of an image (in general unique identifier of every DICOM file)
     * @return std::shared_ptr<Image> 
     */
    static std::shared_ptr<Image> get(const std::string& SOPInstanceUID);

    /**
     * @brief Get an image with the given Series instance UID.
     * There are multiple images within same series, but for this functionality
     * one is enough.
     * 
     * @param SeriesInstanceUID Instance UID of series to which image belongs to
     * @return std::shared_ptr<Image> 
     */
    static std::shared_ptr<Image> getBySeriesUID(const std::string& SeriesInstanceUID);

    /**
     * @brief Insert a given image in the database.
     * 
     * @param image 
     * @return true if image added successfully
     * @return false if image was failed to be added
     */
    static bool insert(const Image& image);

    /**
     * @brief Remove an image with a given SOP instance UID. 
     * If parent series is left empty after deleting an image, series gets deleted as well.
     * 
     * @param SOPInstanceUID unique identifier of an image (in general unique identifier of every DICOM file)
     * @return true if image removed successfully
     * @return false if image was failed to be removed
     */
    static bool remove(const std::string& SOPInstanceUID);
};

}
