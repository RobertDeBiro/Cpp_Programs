#include <iostream>
#include <libusb.h>

int main() {
    // Initialize libusb
    libusb_init(nullptr);

    // Get the list of USB devices
    libusb_device** list;
    ssize_t count = libusb_get_device_list(nullptr, &list);
    if (count < 0) {
        std::cerr << "Failed to get device list" << std::endl;
        libusb_exit(nullptr);
        return 1;
    }

    // Iterate over the list of devices
    for (ssize_t i = 0; i < count; ++i) {
        libusb_device* dev = list[i];
        libusb_device_descriptor desc;
        int ret = libusb_get_device_descriptor(dev, &desc);
        if (ret != 0) {
            std::cerr << "Failed to get device descriptor" << std::endl;
            continue;
        }

        std::cout << "Device ID: " << desc.idVendor << ":" << desc.idProduct << std::endl;

        // Open the USB device
        libusb_device_handle* handle;
        ret = libusb_open(dev, &handle);
        if (ret != LIBUSB_SUCCESS) {
            std::cerr << "Failed to open device" << std::endl;
            continue;
        } else {
            std::cout << "*****SUCCESS*****" << std::endl;
        }

        // Get the active configuration descriptor
        libusb_config_descriptor* config;
        ret = libusb_get_active_config_descriptor(dev, &config);
        if (ret != LIBUSB_SUCCESS) {
            std::cerr << "Failed to get configuration descriptor" << std::endl;
            libusb_close(handle);
            continue;
        }

        // Iterate over the interfaces
        for (int j = 0; j < config->bNumInterfaces; ++j) {
            const libusb_interface_descriptor* interface = &config->interface[j].altsetting[0];
            std::cout << "Interface class: " << static_cast<int>(interface->bInterfaceClass) << std::endl;
            std::cout << "Interface subclass: " << static_cast<int>(interface->bInterfaceSubClass) << std::endl;
            std::cout << "Interface protocol: " << static_cast<int>(interface->bInterfaceProtocol) << std::endl;
            // Add more fields as needed

            // Handle each interface based on its class
            switch (interface->bInterfaceClass) {
                case LIBUSB_CLASS_MASS_STORAGE:
                    std::cout << "Interface is Mass Storage" << std::endl;
                    break;
                case LIBUSB_CLASS_HID:
                    std::cout << "Interface is HID (Human Interface Device)" << std::endl;
                    break;
                // Add cases for other interface classes as needed
                default:
                    std::cout << "Unknown interface class" << std::endl;
                    break;
            }
        }

        // Free configuration descriptor
        libusb_free_config_descriptor(config);

        // Close the device handle
        libusb_close(handle);
    }

    // Free the device list
    libusb_free_device_list(list, 1);

    // Deinitialize libusb
    libusb_exit(nullptr);

    return 0;
}
