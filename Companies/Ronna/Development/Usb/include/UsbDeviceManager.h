#pragma once

#include <libusb-1.0/libusb.h>
#include <functional>
#include <atomic>
#include <memory>
#include <string>

namespace rtkplanning {

// Forward declarations
class UsbDeviceRegistry;

/**
 * @brief Manages USB device detection using libusb
 * 
 * Responsible for initializing libusb, registering hotplug callbacks,
 * and handling USB device events.
 */
class UsbDeviceManager {
public:
    // Callback type for USB events
    using UsbEventCallback = std::function<void(const std::string&)>;
    
    /**
     * @brief Initialize libusb and register hotplug callbacks
     * @return true if initialization was successful, false otherwise
     */
    static bool Init();
    
    /**
     * @brief Start listening for USB events in an infinite loop
     * This function never returns and should be called in a separate thread
     */
    [[noreturn]] static void StartListening();
    
    /**
     * @brief Clean up libusb resources
     */
    static void Deinitialize();
    
    /**
     * @brief Register a callback to be invoked when a USB device is plugged in
     * @param callback The function to call when a device is plugged in
     */
    static void RegisterPluggedCallback(UsbEventCallback callback);
    
    /**
     * @brief Register a callback to be invoked when a USB device is unplugged
     * @param callback The function to call when a device is unplugged
     */
    static void RegisterUnpluggedCallback(UsbEventCallback callback);
    
private:
    // libusb callback for device arrival events
    static int LIBUSB_CALL UsbPlugged(libusb_context *ctx, libusb_device *dev, 
                                     libusb_hotplug_event event, void *user_data);
    
    // libusb callback for device removal events
    static int LIBUSB_CALL UsbUnplugged(libusb_context *ctx, libusb_device *dev, 
                                       libusb_hotplug_event event, void *user_data);
    
    // Generate a unique device ID string from device descriptor
    static std::string GetDeviceUniqueId(const libusb_device_descriptor& desc);
    
    // USB device handle
    static libusb_device_handle* _handle;
    
    // Callbacks for USB events
    static UsbEventCallback _plugged_callback;
    static UsbEventCallback _unplugged_callback;
};

} // namespace rtkplanning