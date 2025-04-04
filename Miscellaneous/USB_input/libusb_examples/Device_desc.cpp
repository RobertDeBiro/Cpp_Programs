#include <iostream>
#include "libusb.h"
#include <thread>

// Function to determine the type of USB device based on its descriptors
void determineDeviceType(libusb_device* dev) {
    libusb_device_descriptor desc;
    int ret = libusb_get_device_descriptor(dev, &desc);
    if (ret != 0) {
        std::cerr << "Failed to get device descriptor" << std::endl;
        return;
    }

    // Examine descriptor fields to determine device type
    std::cout << "Device idVendor: " << desc.idVendor << std::endl;
    std::cout << "Device idVendor: 0x" << std::hex << desc.idVendor << std::endl;
    std::cout << "Device idProduct: 0x" << std::hex << desc.idProduct << std::endl;
    std::cout << "Device bLength: " << std::dec << (int)desc.bLength << std::endl;
    std::cout << "Device bDescriptorType: " << std::dec << (int)desc.bDescriptorType << std::endl;
    std::cout << "Device bcdUSB: " << std::hex << (int)desc.bcdUSB << std::endl;
    std::cout << "Device bDeviceClass: " << std::dec << (int)desc.bDeviceClass << std::endl;
    std::cout << "Device bDeviceSubClass: " << std::dec << (int)desc.bDeviceSubClass << std::endl;
    std::cout << "Device bDeviceProtocol: " << std::dec << (int)desc.bDeviceProtocol << std::endl;
    std::cout << "Device bMaxPacketSize0: " << std::dec << (int)desc.bMaxPacketSize0 << std::endl;
    std::cout << "Device iManufacturer: " << std::dec << (int)desc.iManufacturer << std::endl;
    std::cout << "Device iProduct: " << std::dec << (int)desc.iProduct << std::endl;
    std::cout << "Device iSerialNumber: " << std::dec << (int)desc.iSerialNumber << std::endl;
    std::cout << "Device bNumConfigurations: " << std::dec << (int)desc.bNumConfigurations << std::endl;

    std::cout << "---------------------------------------------------------" << std::endl;

    // Add your logic to determine device type based on descriptor fields
    // For example, you could check the device class, subclass, and protocol
    // to identify the type of device (e.g., mass storage, audio, HID, etc.)
}

// Function to monitor USB devices
void monitorUSB() {
    libusb_context* ctx;
    int ret = libusb_init(&ctx);
    if (ret < 0) {
        std::cerr << "Failed to initialize libusb" << std::endl;
        return;
    }

    // Monitor loop to continuously check for USB events
    while (true) {
        // Get a list of USB devices
        libusb_device** list;
        ssize_t count = libusb_get_device_list(ctx, &list);
        if (count < 0) {
            std::cerr << "Failed to get device list" << std::endl;
            libusb_exit(ctx);
            return;
        }

        // Iterate over the list of devices
        for (ssize_t i = 0; i < count; ++i) {
            libusb_device* dev = list[i];
            // Determine the type of device
            determineDeviceType(dev);
        }

        // Free the device list
        libusb_free_device_list(list, 1);
        
        // Wait for some time before checking again
        std::this_thread::sleep_for(std::chrono::seconds(30));
        std::cout << "**************************************\n";
    }

    // Cleanup: Free the libusb context
    libusb_exit(ctx);
}

int main() {
    // Start monitoring USB devices
    monitorUSB();
    return 0;
}
