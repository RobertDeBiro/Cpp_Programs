#pragma once

#include <string>
#include <map>
#include <vector>
#include <filesystem>
#include <mutex>
#include <atomic>

namespace rtkplanning {

// Forward declaration
class UsbDevice;

/**
 * @brief Registry for managing all connected USB devices
 * 
 * This class maintains a collection of all USB devices and their states.
 * It handles USB device addition and removal events.
 */
class UsbDeviceRegistry {
public:
    /**
     * @brief Get the singleton instance of the registry
     * @return Reference to the singleton instance
     */
    static UsbDeviceRegistry& GetInstance();
    
    /**
     * @brief Initialize the registry
     */
    void Initialize();
    
    /**
     * @brief Handle a USB device being plugged in
     * @param device_id Unique identifier of the device
     */
    void DevicePlugged(const std::string& device_id);
    
    /**
     * @brief Handle a USB device being unplugged
     * @param device_id Unique identifier of the device
     */
    void DeviceUnplugged(const std::string& device_id);
    
    /**
     * @brief Check for devices that were connected before the application started
     */
    void CheckForPreexistingDevices();
    
    /**
     * @brief Get all connected USB device paths
     * @return Vector of filesystem paths to connected USB devices
     */
    std::vector<std::filesystem::path> GetConnectedUsbPaths() const;
    
    /**
     * @brief Get the number of ongoing scanning threads
     * @return Current count of active scanning threads
     */
    int GetOngoingThreadCount() const;

private:
    UsbDeviceRegistry() = default;
    ~UsbDeviceRegistry() = default;
    
    // Disable copy and move operations
    UsbDeviceRegistry(const UsbDeviceRegistry&) = delete;
    UsbDeviceRegistry& operator=(const UsbDeviceRegistry&) = delete;
    UsbDeviceRegistry(UsbDeviceRegistry&&) = delete;
    UsbDeviceRegistry& operator=(UsbDeviceRegistry&&) = delete;
    
    // Count mounted media directories
    int CountMediaDirs() const;
    
    // Map of device IDs to device objects
    std::map<std::string, std::shared_ptr<UsbDevice>> _devices;
    mutable std::mutex _devices_mutex;
    
    // Counter for ongoing scanning threads
    std::atomic<int> _ongoing_threads{0};
    
    // Path to media directory
    std::filesystem::path _media_path{"/media"};
};

} // namespace rtkplanning