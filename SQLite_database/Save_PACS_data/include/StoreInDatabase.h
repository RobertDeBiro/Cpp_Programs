#pragma once

#include <filesystem>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <gtk/gtk.h>
#include <vtkDICOMImageReader.h>
#include <gdcmReader.h>

namespace rtkplanning
{

class StoreInDatabase
{
public:
    using dict_type = const itk::MetaDataDictionary&;

    long long StorePatientInDb(dict_type dictionary) const;
    void StoreStudyInDb(dict_type dictionary, long long patient_UID) const;
    void StoreSeriesInDb(dict_type dictionary, std::string series_inst_UID_value) const;
    void StoreImageInDb(dict_type dictionary, const std::filesystem::path& file_path) const;

    StoreInDatabase();

private:
    std::shared_ptr<spdlog::logger> logger_planning = nullptr;
};

}
