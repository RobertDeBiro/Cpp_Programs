#pragma once

#include <filesystem>
#include <vector>
#include <map>
#include <atomic>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <libusb-1.0/libusb.h>

namespace rtkplanning
{

enum class UsbStatus
{
	PLUGGED,
	UNPLUGGED
};

/**
 * @brief Pure static class that manages attachment, detachment and read of USB devices
 */
class UsbManager
{
public:
	/**
	 * @brief Path to /media dir where USB devices are mounted
     */
    static const std::filesystem::path media_path;

    static std::shared_ptr<spdlog::logger> logger_planning;

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
    static bool Init();

    /**
     * @brief Enumerates already plugged USB devices and starts a thread
     * that continuously listens to USB ports.
     */
    [[noreturn]] static void StartListening();

    /**
     * @brief Get number of directories in /media (number of plugged Mass Storage USB devices).
     */
    static int CountMediaDirs();

	/**
     * @brief Deinitialize all USB devices plugged to the PC
	 * 
	 * @details Function closes all USB device handlers and afterwards deinitializes them.
	 * Should be called before application terminates.
     */
	static void DeinitializeUsbDevices();

    static std::map<std::string, std::vector<std::filesystem::path>>& GetUsbDicomDirsMap();

    static int GetCountOngoingThreads();

    static bool IsHidden(const std::filesystem::path& file_path);

private:
    static libusb_device_handle *_handle;

	/**
	 * @brief Map that saves USB attachment status
	 * 
     * @details Map saves pairs that contain:
	 *  - USB unique identifier combined from libusb_device_descriptor struct members
	 *  - status noting if device is currently plugged or unplugged
     */
    static std::map<std::string, UsbStatus> _libusb_status_map;

    /**
     * @brief Map that saves paths to DICOMDIR files present in USB devices
	 * 
	 * @details Map saves pairs that contain:
	 *  - USB "/media" path from PC file explorer
	 *  - path to DICOMDIR files
     */
    static std::map<std::string, std::vector<std::filesystem::path>> _usb_dicomdirs_map;

    /**
	 * @brief Atomic object used for synchronization with "search" instruction
	 * 
	 * @details "Search" instruction is executed during SearchState.
	 * If one or multiple threads are currently ongoing, variable 'count_ongoing_threads'
	 * will be bigger than zero and "Search" instruction will wait
     */
	static std::atomic<int> _count_ongoing_threads;

	/**
	 * @brief Mutex that locks counter that counts plugged USB devices
     */
	static std::mutex _mtx_usbs_status;

	/**
	 * @brief Mutex that locks '_usb_dicomdirs_map'
     */
	static std::mutex _mtx_usb_dicomdirs_map;

    /**
     * @brief Callback called when an USB device is plugged.
     *
     * @details This callback waits for the USB device to be mounted and then iterates
     * through each and every file present in the USB storage and saves DICOM files.
     *
     * @throw std::filesystem_error If the USB device is unplugged during reading its storage, an exception is thrown.
     */
    static int LIBUSB_CALL UsbPlugged(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);

    /**
     * @brief Callback called when an USB device is unplugged.
     */
    static int LIBUSB_CALL UsbUnplugged(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data);

    /**
     * @brief Store DICOMDIR files paths from USB devices into '_usb_dicomdirs_map'
     */
    static void SaveDicomDirsPaths(const std::string& usb_path);

    /**
     * @brief Wait for the USB device to be mounted, with timeout of 5s defined and start saving DICOMDIR files.
     */
    static void StoreDicomDirs(std::string device_unique_id_str);
};

inline const std::filesystem::path UsbManager::media_path{
    std::filesystem::path("/media")
    / getenv("USERNAME") // This line should be commented for app that runs on K2 machine
};

inline libusb_device_handle* UsbManager::_handle{ nullptr };
inline std::map<std::string, UsbStatus> UsbManager::_libusb_status_map;
inline std::map<std::string, std::vector<std::filesystem::path>> UsbManager::_usb_dicomdirs_map;
inline std::mutex UsbManager::_mtx_usb_dicomdirs_map;
inline std::mutex UsbManager::_mtx_usbs_status;
inline std::atomic<int> UsbManager::_count_ongoing_threads{ 0 };
inline std::shared_ptr<spdlog::logger> UsbManager::logger_planning{ nullptr };

}
