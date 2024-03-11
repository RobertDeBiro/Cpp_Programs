#pragma once

#include <filesystem>
#include <vector>
#include <map>
// #include <boost/container/flat_map.hpp>

#include "libusb.h"

namespace fs = std::filesystem;

class MediaManager
{
    MediaManager() = default;
    MediaManager(const MediaManager& other);
    MediaManager& operator=(const MediaManager& other);

    static libusb_device_handle *handle;
    static std::map<std::string, std::vector<fs::path>> usbMap;
    static const fs::path mediaPath;
    static std::thread workerStoreDicoms;

    /**
     * @brief Callback called when an USB device is attached to the PC.
     *
     * This callback waits for the USB device to be mounted and then iterates through each and every
     * file present in the USB storage and saves DICOM files.
     *
     * @throw fs::filesystem_error If the USB device is detached during reading its storage, an exception is thrown.
     */
    static int LIBUSB_CALL mediaAttached(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);
    
    /**
     * @brief Callback called when an USB device is detached from the PC.
     */
    static int LIBUSB_CALL mediaDetached(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);

    // static void checkMediaExisting();

    /**
     * @brief Wait for the USB device to be mounted, with timeout of 20s defined.
     */
    static bool checkDeviceMount();

    static void cleanup();

    static void storeDicomFiles(std::string usbPath);

public:
    // bool listenFlag{ true };

    ~MediaManager();

    /**
     * @brief Initialize libusb context and register callbacks for USB device events.
     *
     * This function initializes the libusb context and sets up the necessary components
     * to monitor USB device attachment and detachment events.
     *
     * Initialization Steps:
     * - Initialize the libusb context.
     * - Check if the system supports USB hotplug capability.
     * - Register callbacks to handle USB device attachment and detachment events.
     *
     * @return true if initialization is successful.
     * @return false if any libusb function fails during initialization.
     */
    bool init();

    /**
     * @brief Start a thread that continuously listens to USB ports.
     * 
     * The thread will be automatically destroyed when the MediaManager instance is destructed.
     */
    void startListening();

    /**
     * @brief Get the singleton instance of the MediaManager.
     */
    static MediaManager& GetInstance();

    static std::map<std::string, std::vector<fs::path>>& getUsbMap() { return usbMap; }
    static int countDirs();

    static std::mutex mtx;
};

inline const fs::path MediaManager::mediaPath{fs::path("/media") / getenv("USERNAME")};
inline libusb_device_handle* MediaManager::handle{ NULL };
inline std::map<std::string, std::vector<fs::path>> MediaManager::usbMap;
inline std::thread MediaManager::workerStoreDicoms;
inline std::mutex MediaManager::mtx;
