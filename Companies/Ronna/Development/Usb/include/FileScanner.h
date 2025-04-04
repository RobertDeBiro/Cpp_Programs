#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace rtkplanning {

/**
 * @brief Scans filesystem for specific file types
 * 
 * Responsible for recursively scanning a directory for specific files
 * like DICOMDIR and operation plan JSON files.
 */
class FileScanner {
public:
    /**
     * @brief Find all DICOMDIR files in a directory tree
     * @param root_path Path to start the search from
     * @return Vector of found DICOMDIR file paths
     */
    std::vector<std::filesystem::path> FindDicomDirFiles(const std::string& root_path);
    
    /**
     * @brief Find all operation plan JSON files in a directory tree
     * @param root_path Path to start the search from
     * @return Vector of found JSON file paths
     */
    std::vector<std::filesystem::path> FindOperationPlanFiles(const std::string& root_path);
    
private:
    /**
     * @brief Check if a path is a hidden file or directory
     * @param path Path to check
     * @return true if the path is hidden, false otherwise
     */
    bool IsHidden(const std::filesystem::path& path);
};

} // namespace rtkplanning