#include "UsbDevice.h"
#include "FileScanner.h"
#include <rtkdata/Utilities/Logger.h>

namespace rtkplanning {

UsbDevice::UsbDevice(const std::string& device_id)
    : _device_id(device_id)
    , _file_scanner(std::make_shared<FileScanner>())
{
}

std::string UsbDevice::GetDeviceId() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _device_id;
}

void UsbDevice::SetStatus(Status status)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _status = status;
}

UsbDevice::Status UsbDevice::GetStatus() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _status;
}

void UsbDevice::SetMountPath(const std::string& path)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _mount_path = path;
}

std::string UsbDevice::GetMountPath() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _mount_path;
}

void UsbDevice::ScanForFiles()
{
    auto logger_planning = rtkdata::Logger::GetInstance("rtkplanning");
    
    {
        std::lock_guard<std::mutex> lock(_mutex);
        
        if (_mount_path.empty())
        {
            LOG_WRITE_ERROR(logger_planning, "Cannot scan device with empty mount path: {}", _device_id);
            return;
        }
        
        LOG_WRITE_DEFAULT(logger_planning, "Scanning USB device for files: {} at {}", _device_id, _mount_path);
    }
    
    // Scan for DICOMDIR files
    auto dicomdir_paths = _file_scanner->FindDicomDirFiles(GetMountPath());
    
    // Scan for operation plan JSON files
    auto operation_plan_paths = _file_scanner->FindOperationPlanFiles(GetMountPath());
    
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _dicomdir_paths = dicomdir_paths;
        _operation_plan_paths = operation_plan_paths;
        
        LOG_WRITE_DEFAULT(logger_planning, "Found {} DICOMDIR files and {} operation plan files on device: {}", 
                        _dicomdir_paths.size(), _operation_plan_paths.size(), _device_id);
    }
}

std::vector<std::filesystem::path> UsbDevice::GetDicomDirPaths() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _dicomdir_paths;
}

std::vector<std::filesystem::path> UsbDevice::GetOperationPlanPaths() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _operation_plan_paths;
}

} // namespace rtkplanning