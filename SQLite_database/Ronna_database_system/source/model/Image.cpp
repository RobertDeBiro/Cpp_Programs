#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "Image.h"
#include "Series.h"
#include "Database.h"

using namespace rtkplanning;

std::vector<std::shared_ptr<Image>> Image::getAll()
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get all images from database.");

    std::vector<std::shared_ptr<Image>> images;
    std::string query =
        "SELECT "
            "SOPInstanceUID, "
            "Filename, "
            "SeriesInstanceUID "
        "FROM Images";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();

        while(statement->step())
        {
            auto img = std::make_shared<Image>();
            img->SOPInstanceUID      = statement->getText(0).value();
            img->Filename            = statement->getText(1).value();
            img->SeriesInstanceUID   = statement->getText(2).value();

            images.push_back(img);
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting images: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting images: {}!", e.what());
    }
    
    return images;
}

std::shared_ptr<Image> Image::get(const std::string& SOPInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get images from database where SOPInstanceUID is {}.", SOPInstanceUID);

    std::string query =
        "SELECT "
            "SOPInstanceUID, "
            "Filename, "
            "SeriesInstanceUID "
        "FROM Images "
        "WHERE SOPInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, SOPInstanceUID);

        if(statement->step())
        {
            auto img = std::make_shared<Image>();
            img->SOPInstanceUID      = statement->getText(0).value();
            img->Filename            = statement->getText(1).value();
            img->SeriesInstanceUID   = statement->getText(2).value();

            return img;
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting images: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting images: {}!", e.what());
    }
    
    return nullptr;
}

std::shared_ptr<Image> Image::getBySeriesUID(const std::string& SeriesInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Get images from database where SeriesInstanceUID is {}.", SeriesInstanceUID);

    std::string query =
        "SELECT "
            "SOPInstanceUID, "
            "Filename, "
            "SeriesInstanceUID "
        "FROM Images "
        "WHERE SeriesInstanceUID = ?";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
        statement->bind(0, SeriesInstanceUID);

        if(statement->step())
        {
            auto img = std::make_shared<Image>();
            img->SOPInstanceUID      = statement->getText(0).value();
            img->Filename            = statement->getText(1).value();
            img->SeriesInstanceUID   = statement->getText(2).value();

            return img;
        }
    }
    catch(const std::bad_optional_access& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting images: {}!", e.what());
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while getting images: {}!", e.what());
    }
    
    return nullptr;
}

bool Image::insert(const Image& image)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Insert image {} to database.", image.Filename);

    std::string query =
        "INSERT INTO Images ("
            "SOPInstanceUID, "
            "Filename, "
            "SeriesInstanceUID) "
        "VALUES (?, ?, ?)";
    std::shared_ptr<Statement> statement = Database::getInstance().createStatement(query);

    try
    {
        statement->prepare();
    
        // If we never want an empty string in DB (but a NULL), check if empty in bind function ?
        if(!image.SOPInstanceUID.empty())       statement->bind(0, image.SOPInstanceUID);
        if(!image.Filename.empty())             statement->bind(1, image.Filename);
        if(!image.SeriesInstanceUID.empty())    statement->bind(2, image.SeriesInstanceUID);
        
        statement->step();

        return true;
    }
    catch(const SQLException& e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while inserting images: {}!", e.what());
        return false;
    }
}

bool Image::remove(const std::string& SOPInstanceUID)
{
    SPDLOG_LOGGER_INFO(spdlog::get("rtkplanning_db"), "Remove image from database where SOPInstanceUID is {}.", SOPInstanceUID);

    try
    {
        auto img = Image::get(SOPInstanceUID);    

        auto q1 = "DELETE FROM Images WHERE SOPInstanceUID = ?";
        auto s1 = Database::getInstance().createStatement(q1);

        s1->prepare();
        s1->bind(0, SOPInstanceUID);
        s1->step();

        auto q2 = "SELECT * FROM Images WHERE SeriesInstanceUID == ?";
        auto s2 = Database::getInstance().createStatement(q2);
        
        s2->prepare();
        s2->bind(0, img->SeriesInstanceUID);
        
        // If series contains no more image, remove series row from database
        if(!s2->step())
        {
            Series::remove(img->SeriesInstanceUID);
        }

        return true;
    }
    catch (const SQLException &e)
    {
        SPDLOG_LOGGER_ERROR(spdlog::get("rtkplanning_db"), "Exception while removing image: {}!", e.what());
        return false;
    }
}
