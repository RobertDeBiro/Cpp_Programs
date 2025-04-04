#include "UsbDeviceRegistry.h"
#include "UsbDevice.h"
#include <rtkdata/Utilities/Logger.h>
#include <thread>
#include <chrono>

namespace rtkplanning {

UsbDeviceRegistry& UsbDeviceRegistry::GetInstance()
{
    static UsbDeviceRegistry instance;
    return instance;
}

void UsbDeviceRegistry::Initialize()
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    LOG_WRITE_DEFAULT(logger_planning, "Initializing UsbDeviceRegistry");
    
    // Check for devices that might have been connected before application start
    CheckForPreexistingDevices();
}

void UsbDeviceRegistry::CheckForPreexistingDevices()
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    int devices_count = CountMediaDirs();
    
    if (devices_count > 0)
    {
        LOG_WRITE_DEFAULT(logger_planning, "Found {} preexisting USB devices", devices_count);
        
        // Process each preexisting device
        for (const auto& path : GetConnectedUsbPaths())
        {
            std::string mock_device_id = "preexisting:" + path.filename().string();
            
            // Create a new device entry
            auto device = std::make_shared<UsbDevice>(mock_device_id);
            device->SetStatus(UsbDevice::Status::PLUGGED);
            device->SetMountPath(path.string());
            
            {
                std::lock_guard<std::mutex> lock(_devices_mutex);
                _devices[mock_device_id] = device;
            }
            
            // Start a thread to scan this device
            _ongoing_threads++;
            std::thread worker_thread([this, device, mock_device_id]() {
                device->ScanForFiles();
                _ongoing_threads--;
            });
            worker_thread.detach();
        }
    }
}

int UsbDeviceRegistry::CountMediaDirs() const
{
    int count = 0;
    
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(_media_path))
        {
            if (std::filesystem::is_directory(entry))
                ++count;
        }
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        LOG_WRITE_ERROR(logger_planning, "Error counting media directories: {}", ex.what())
    }
    
    return count;
}

std::vector<std::filesystem::path> UsbDeviceRegistry::GetConnectedUsbPaths() const
{
    std::vector<std::filesystem::path> paths;
    
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(_media_path))
        {
            // Save only non-hidden directories
            if (std::filesystem::is_directory(entry) && entry.path().filename().string().front() != '.')
                paths.push_back(entry.path());
        }
    }
    catch (const std::filesystem::filesystem_error& ex)
    {
        LOG_WRITE_ERROR(logger_planning, "Error getting USB paths: {}", ex.what())
    }
    
    return paths;
}

void UsbDeviceRegistry::DevicePlugged(const std::string& device_id)
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    
    {
        std::lock_guard<std::mutex> lock(_devices_mutex);
        
        if (_devices.count(device_id) > 0)
        {
            // Device already known, update its status
            _devices[device_id]->SetStatus(UsbDevice::Status::PLUGGED);
            LOG_WRITE_DEFAULT(logger_planning, "Updated status of existing device: {}", device_id);
        }
        else
        {
            // New device, create and add it
            auto device = std::make_shared<UsbDevice>(device_id);
            device->SetStatus(UsbDevice::Status::PLUGGED);
            _devices[device_id] = device;
            LOG_WRITE_DEFAULT(logger_planning, "Added new device to registry: {}", device_id);
        }
    }
    
    // Start a thread to process the device
    _ongoing_threads++;
    std::thread worker_thread([this, device_id]() {
        auto logger = rtkdata::Logger::GetInstance("rtkplanning");
        
        // Wait for the device to be mounted
        LOG_WRITE_DEFAULT(logger, "Waiting for device to be mounted: {}", device_id);
        
        auto start_time = std::chrono::steady_clock::now();
        auto max_mount_time = std::chrono::seconds(5);
        int initial_count = CountMediaDirs();
        
        while (CountMediaDirs() == initial_count)
        {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
            
            if (elapsed_time > max_mount_time)
            {
                LOG_WRITE_ERROR(logger, "Timeout waiting for device to be mounted: {}", device_id);
                _ongoing_threads--;
                return;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            // Check if device was unplugged during mounting
            bool device_still_connected = false;
            {
                std::lock_guard<std::mutex> lock(_devices_mutex);
                if (_devices.count(device_id) > 0 && 
                    _devices[device_id]->GetStatus() == UsbDevice::Status::PLUGGED)
                {
                    device_still_connected = true;
                }
            }
            
            if (!device_still_connected)
            {
                LOG_WRITE_DEFAULT(logger, "Device unplugged during mounting: {}", device_id);
                _ongoing_threads--;
                return;
            }
        }
        
        LOG_WRITE_DEFAULT(logger, "Device mounted, starting scanning: {}", device_id);
        
        // Find all mounting points
        auto connected_paths = GetConnectedUsbPaths();
        
        // Only process newly connected device
        for (const auto& path : connected_paths)
        {
            std::shared_ptr<UsbDevice> device;
            {
                std::lock_guard<std::mutex> lock(_devices_mutex);
                if (_devices.count(device_id) > 0)
                {
                    device = _devices[device_id];
                }
            }
            
            if (device)
            {
                device->SetMountPath(path.string());
                device->ScanForFiles();
            }
        }
        
        _ongoing_threads--;
    });
    worker_thread.detach();
}

void UsbDeviceRegistry::DeviceUnplugged(const std::string& device_id)
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    
    {
        std::lock_guard<std::mutex> lock(_devices_mutex);
        
        if (_devices.count(device_id) > 0)
        {
            _devices[device_id]->SetStatus(UsbDevice::Status::UNPLUGGED);
            LOG_WRITE_DEFAULT(logger_planning, "Updated status of device to unplugged: {}", device_id);
        }
        else
        {
            // Device was likely connected before application started
            auto device = std::make_shared<UsbDevice>(device_id);
            device->SetStatus(UsbDevice::Status::UNPLUGGED);
            _devices[device_id] = device;
            LOG_WRITE_DEFAULT(logger_planning, "Added previously unknown device as unplugged: {}", device_id);
        }
    }
    
    // Give the system time to properly unmount the device
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int UsbDeviceRegistry::GetOngoingThreadCount() const
{
    return _ongoing_threads.load();
}

} // namespace rtkplanning