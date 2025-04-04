#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <mutex>

namespace rtkplanning {

// Forward declaration
class FileScanner;

/**
 * @brief Represents a single USB storage device
 * 
 * Contains information about a USB device including its unique ID,
 * mount path, and status. Also manages file scanning operations.
 */
class UsbDevice {
public:
    /**
     * @brief Status of the USB device
     */
    enum class Status {
        UNKNOWN,
        PLUGGED,
        UNPLUGGED
    };
    
    /**
     * @brief Construct a new USB device
     * @param device_id Unique identifier for the device
     */
    explicit UsbDevice(const std::string& device_id);
    
    /**
     * @brief Get the unique identifier of the device
     * @return Device ID string
     */
    std::string GetDeviceId() const;
    
    /**
     * @brief Set the device status
     * @param status New status value
     */
    void SetStatus(Status status);
    
    /**
     * @brief Get the current device status
     * @return Current status
     */
    Status GetStatus() const;
    
    /**
     * @brief Set the filesystem path where the device is mounted
     * @param path Mount path string
     */
    void SetMountPath(const std::string& path);
    
    /**
     * @brief Get the filesystem path where the device is mounted
     * @return Mount path string
     */
    std::string GetMountPath() const;
    
    /**
     * @brief Scan the device for DICOMDIR and JSON files
     */
    void ScanForFiles();
    
    /**
     * @brief Get all found DICOMDIR file paths
     * @return Vector of DICOMDIR file paths
     */
    std::vector<std::filesystem::path> GetDicomDirPaths() const;
    
    /**
     * @brief Get all found JSON operation plan file paths
     * @return Vector of JSON file paths
     */
    std::vector<std::filesystem::path> GetOperationPlanPaths() const;

private:
    // Device unique identifier
    std::string _device_id;
    
    // Device status
    Status _status = Status::UNKNOWN;
    
    // Mount path
    std::string _mount_path;
    
    // File scanner used to find files
    std::shared_ptr<FileScanner> _file_scanner;
    
    // Found file paths
    std::vector<std::filesystem::path> _dicomdir_paths;
    std::vector<std::filesystem::path> _operation_plan_paths;
    
    // Mutex for thread-safe access
    mutable std::mutex _mutex;
};

} // namespace rtkplanning