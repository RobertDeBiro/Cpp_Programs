#include <iostream>
#include "libusb.h"
#include <thread>
#include <chrono>
#include <functional>

// Callback function to handle USB device detection
void handleUSB(libusb_device* dev) {
    std::cout << "USB device detected" << std::endl;
    // Add your handling code here
}

// Callback function to handle USB device detachment
void handleUSBRemoved(libusb_device* dev) {
    std::cout << "USB device removed" << std::endl;
    // Add your handling code here
}

// Function to enumerate existing USB devices
void enumerateUSBDevices(libusb_context* ctx, std::function<void(libusb_device*)> callback) {
    // Get a list of USB devices
    libusb_device** list;
    ssize_t count = libusb_get_device_list(ctx, &list);
    if (count < 0) {
        std::cerr << "Failed to get device list" << std::endl;
        return;
    }

    // Iterate over the list of devices and call the callback function for each device
    for (ssize_t i = 0; i < count; ++i) {
        // libusb_device* dev = list[i];
        callback(list[i]);
    }

    // Free the device list
    libusb_free_device_list(list, 1);
}

// Function to monitor USB devices
void monitorUSB(std::function<void(libusb_device*)> attachCallback, std::function<void(libusb_device*)> detachCallback) {
    // Initialize libusb and create a context
    libusb_context* ctx;
    int ret = libusb_init_context(&ctx, NULL, 0);
    if (ret < 0) {
        std::cerr << "Failed to initialize libusb" << std::endl;
        return;
    }

    // Enumerate existing USB devices and call the attach callback for each
    enumerateUSBDevices(ctx, attachCallback);

    // Monitor loop to continuously check for USB events
    while (true) {
        // Open a device handle with vendor ID 0 and product ID 0
        libusb_device_handle* handle = libusb_open_device_with_vid_pid(ctx, 0, 0);
        if (handle) {
            // Call the attach callback with the device
            attachCallback(libusb_get_device(handle));
            // Close the device handle
            libusb_close(handle);
        } else {
            // Call the detach callback with a null device pointer
            detachCallback(nullptr);
        }
        // Wait for some time before checking again
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Cleanup: Free the libusb context
    libusb_exit(ctx);
}

int main() {
    // Start monitoring USB devices with the handleUSB and handleUSBRemoved callbacks
    monitorUSB(handleUSB, handleUSBRemoved);

    std::cout << "Doing something!\n";

    return 0;
}
