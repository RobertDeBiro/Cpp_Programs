#pragma once

#include <filesystem>
#include <vector>
#include <map>

#include "libusb.h"

namespace fs = std::filesystem;

class MediaManager
{
public:
    static const fs::path mediaPath;
    static std::mutex mtx;

    static MediaManager& GetInstance();

    /**
     * @brief Initialize libusb context and register callbacks for USB device events.
     *
     * @details This function initializes the libusb context and sets up the necessary components
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
     * @brief Enumerates already attached USB devices and starts a thread
     * that continuously listens to USB ports.
     */
    void startListening();

    /**
     * @brief Get number of directories in /media (number of attached USB devices).
     */
    static int countMediaDirs();

    ~MediaManager();

private:
    static libusb_device_handle *_handle;
    static std::map<std::string, std::vector<fs::path>> _usbMap;
    static std::thread _workerStoreDicoms;

    MediaManager() = default;
    MediaManager(const MediaManager& other);
    MediaManager& operator=(const MediaManager& other);

    /**
     * @brief Callback called when an USB device is attached to the PC.
     *
     * @details This callback waits for the USB device to be mounted and then iterates through each and every
     * file present in the USB storage and saves DICOM files.
     *
     * @throw fs::filesystem_error If the USB device is detached during reading its storage, an exception is thrown.
     */
    static int LIBUSB_CALL mediaAttached(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);
    
    /**
     * @brief Callback called when an USB device is detached from the PC.
     */
    static int LIBUSB_CALL mediaDetached(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);

    /**
     * @brief Store DICOM files from USB devices into '_usbMap'
     */
    static void storeDicomFiles(std::string usbPath);

    /**
     * @brief Wait for the USB device to be mounted, with timeout of 20s defined.
     */
    static bool checkDeviceMount();

    /**
     * @brief Closes device handle, should be called on all open handles before application exits.
     */
    static void closeDeviceHandle();
};

inline const fs::path MediaManager::mediaPath{fs::path("/media") / getenv("USERNAME")};
inline std::mutex MediaManager::mtx;
inline libusb_device_handle* MediaManager::_handle{ NULL };
inline std::map<std::string, std::vector<fs::path>> MediaManager::_usbMap;
inline std::thread MediaManager::_workerStoreDicoms;
