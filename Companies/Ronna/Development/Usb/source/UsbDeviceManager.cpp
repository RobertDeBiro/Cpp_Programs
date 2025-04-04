#include "UsbDeviceManager.h"
#include "UsbDeviceRegistry.h"
#include <rtkdata/Utilities/Logger.h>
#include <thread>
#include <chrono>
#include <sstream>

namespace rtkplanning {

// Static member initialization
libusb_device_handle* UsbDeviceManager::_handle = nullptr;
UsbDeviceManager::UsbEventCallback UsbDeviceManager::_plugged_callback = nullptr;
UsbDeviceManager::UsbEventCallback UsbDeviceManager::_unplugged_callback = nullptr;

bool UsbDeviceManager::Init()
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    int rc;
    
    // Initialize libusb with retry mechanism
    int retry_count = 5;
    int attempt = 0;
    
    while (attempt < retry_count)
    {
        rc = libusb_init(nullptr);
        if (LIBUSB_SUCCESS == rc)
        {
            LOG_WRITE_DEFAULT(logger_planning, "libusb context initialized");
            break;
        }
        
        LOG_WRITE_ERROR(logger_planning, "Failed to initialize libusb on attempt {}: {}!", 
                      attempt + 1, libusb_strerror((enum libusb_error)rc));
        attempt++;
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    if (attempt == retry_count)
    {
        LOG_WRITE_ERROR(logger_planning, "libusb failed to initialize after {} attempts!", retry_count);
        return false;
    }
    
    // Verify hotplug capability
    if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG))
    {
        LOG_WRITE_ERROR(logger_planning, "Hotplug capabilities are not supported on this platform!");
        libusb_exit(nullptr);
        return false;
    }
    
    LOG_WRITE_DEFAULT(logger_planning, "USB device has hotplug capability");
    
    // Register device arrival callback
    rc = libusb_hotplug_register_callback(
        nullptr, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, 0, LIBUSB_HOTPLUG_MATCH_ANY,
        LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, UsbPlugged, nullptr, nullptr
    );
    
    if (LIBUSB_SUCCESS != rc)
    {
        LOG_WRITE_ERROR(logger_planning, "Error registering callback for media attach!");
        libusb_exit(nullptr);
        return false;
    }
    
    // Register device removal callback
    rc = libusb_hotplug_register_callback(
        nullptr, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, LIBUSB_HOTPLUG_MATCH_ANY,
        LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, UsbUnplugged, nullptr, nullptr
    );
    
    if (LIBUSB_SUCCESS != rc)
    {
        LOG_WRITE_ERROR(logger_planning, "Error registering callback for media detach!");
        libusb_exit(nullptr);
        return false;
    }
    
    LOG_WRITE_DEFAULT(logger_planning, "UsbDeviceManager successfully initialized.");
    return true;
}

[[noreturn]] void UsbDeviceManager::StartListening()
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    LOG_WRITE_DEFAULT(logger_planning, "StartListening");
    
    // Continuously handle USB events
    while (true)
    {
        int rc = libusb_handle_events_completed(nullptr, nullptr);
        if (LIBUSB_SUCCESS != rc)
        {
            LOG_WRITE_ERROR(logger_planning, "libusb_handle_events() failed: {}!", 
                          libusb_strerror((enum libusb_error)rc));
        }
    }
}

int LIBUSB_CALL UsbDeviceManager::UsbPlugged(libusb_context *ctx, libusb_device *dev, 
                                           libusb_hotplug_event event, void *user_data)
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    int rc;
    struct libusb_device_descriptor desc;
    
    rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS == rc)
    {
        std::string device_id = GetDeviceUniqueId(desc);
        LOG_WRITE_DEFAULT(logger_planning, "USB device plugged: {}", device_id);
        
        // Notify listeners via callback
        if (_plugged_callback)
        {
            _plugged_callback(device_id);
        }
    }
    else
    {
        LOG_WRITE_ERROR(logger_planning, "Error: Problems during device attachment! Failed to get device descriptor: {}.",
                      libusb_strerror((enum libusb_error)rc));
    }
    
    return 0;
}

int LIBUSB_CALL UsbDeviceManager::UsbUnplugged(libusb_context *ctx, libusb_device *dev, 
                                             libusb_hotplug_event event, void *user_data)
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    int rc;
    struct libusb_device_descriptor desc;
    
    rc = libusb_get_device_descriptor(dev, &desc);
    if (LIBUSB_SUCCESS == rc)
    {
        std::string device_id = GetDeviceUniqueId(desc);
        LOG_WRITE_DEFAULT(logger_planning, "USB device unplugged: {}", device_id);
        
        // Notify listeners via callback
        if (_unplugged_callback)
        {
            _unplugged_callback(device_id);
        }
    }
    else
    {
        LOG_WRITE_ERROR(logger_planning, "Error: Problems during device detachment! Failed to get device descriptor: {}.",
                      libusb_strerror((enum libusb_error)rc));
    }
    
    return 0;
}

std::string UsbDeviceManager::GetDeviceUniqueId(const libusb_device_descriptor& desc)
{
    std::ostringstream device_unique_id;
    device_unique_id << desc.idVendor << ":" << desc.idProduct << ":" 
                     << desc.bcdDevice << ":" << static_cast<int>(desc.iSerialNumber);
    return device_unique_id.str();
}

void UsbDeviceManager::Deinitialize()
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    
    if (_handle)
    {
        libusb_close(_handle);
        _handle = nullptr;
    }
    libusb_exit(nullptr);
    LOG_WRITE_DEFAULT(logger_planning, "USB devices deinitialized.");
}

void UsbDeviceManager::RegisterPluggedCallback(UsbEventCallback callback)
{
    _plugged_callback = callback;
}

void UsbDeviceManager::RegisterUnpluggedCallback(UsbEventCallback callback)
{
    _unplugged_callback = callback;
}

} // namespace rtkplanning