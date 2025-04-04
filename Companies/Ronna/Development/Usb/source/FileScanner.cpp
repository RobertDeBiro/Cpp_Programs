#include "FileScanner.h"
#include <rtkdata/Utilities/Logger.h>
#include <cctype>
#include <algorithm>

namespace rtkplanning {

std::vector<std::filesystem::path> FileScanner::FindDicomDirFiles(const std::string& root_path)
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    std::vector<std::filesystem::path> dicomdir_files;
    
    try
    {
        LOG_WRITE_DEFAULT(logger_planning, "Scanning for DICOMDIR files in {}", root_path);
        
        for (auto it = std::filesystem::recursive_directory_iterator(root_path); 
             it != std::filesystem::recursive_directory_iterator(); ++it)
        {
            try
            {
                if (std::filesystem::is_regular_file(it->path()))
                {
                    auto path_str = it->path().string();
                    
                    // Convert path to uppercase for case-insensitive comparison
                    std::string uppercase_path = path_str;
                    std::transform(uppercase_path.begin(), uppercase_path.end(), uppercase_path.begin(),
                                  [](unsigned char c) { return std::toupper(c); });
                    
                    if (uppercase_path.find("DICOMDIR") != std::string::npos && !IsHidden(it->path()))
                    {
                        dicomdir_files.push_back(it->path());
                        LOG_WRITE_DEFAULT(logger_planning, "Found DICOMDIR file: {}", it->path().string());
                    }
                }
            }
            catch (const std::filesystem::filesystem_error& ex)
            {
                // Skip this file and continue with the next one
                LOG_WRITE_WARN(logger_planning, "Error accessing file during scan: {}", ex.what());
                continue;
            }
        }
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        LOG_WRITE_WARN(logger_planning, "Exception during file scanning: {}", ex.what());
    }
    
    LOG_WRITE_DEFAULT(logger_planning, "Found {} DICOMDIR files in {}", dicomdir);
}