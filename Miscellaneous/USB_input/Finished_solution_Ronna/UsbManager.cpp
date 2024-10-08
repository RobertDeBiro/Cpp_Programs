#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <exception>
#include <cctype>

#include <itkGDCMImageIO.h>

#include "UsbManager.h"
#include "rtkcommon/utils/DCMReader.h"
#include "DatabaseState.h"

using namespace rtkplanning;

bool UsbManager::Init()
{
	int rc;
	logger_planning = spdlog::get("rtkplanning");

	// Initialze libusb context
	// rc = libusb_init_context(nullptr, nullptr, 0); -> Use in libusb 1.0.27
	rc = libusb_init(nullptr);
	if (LIBUSB_SUCCESS != rc)
	{
    	SPDLOG_LOGGER_ERROR(logger_planning, "Failed to initialise libusb: {}!", libusb_strerror((enum libusb_error)rc));
		return false;
	}

    SPDLOG_LOGGER_DEBUG(logger_planning, "libusb context initialized");

	// Check if loaded libusb library has hotplug capability
	// - needs to be performed after libusb_init_context() function
	if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG))
	{
    	SPDLOG_LOGGER_ERROR(logger_planning, "Hotplug capabilities are not supported on this platform!");
		libusb_exit(nullptr);
		return false;
	}

    SPDLOG_LOGGER_DEBUG(logger_planning, "Usb device has hotplug capability");

	// Register callback which will be called every time USB device is plugged
	rc = libusb_hotplug_register_callback(
			nullptr, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, 0, LIBUSB_HOTPLUG_MATCH_ANY,
		    LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, UsbPlugged, nullptr, nullptr
		 );

	if (LIBUSB_SUCCESS != rc)
	{
    	SPDLOG_LOGGER_ERROR(logger_planning, "Error registering callback for media attach!");
		libusb_exit(nullptr);
		return false;
	}

	// Register callback which will be called every time USB device is unplugged
	rc = libusb_hotplug_register_callback(
			nullptr, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, LIBUSB_HOTPLUG_MATCH_ANY,
			LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, UsbUnplugged, nullptr, nullptr
		 );

	if (LIBUSB_SUCCESS != rc)
	{
    	SPDLOG_LOGGER_ERROR(logger_planning, "Error registering callback for media detach!");
		libusb_exit(nullptr);
		return false;
	}

    SPDLOG_LOGGER_INFO(logger_planning, "USB device successfully initialized.");
	return true;
}

[[noreturn]] void UsbManager::StartListening()
{
    SPDLOG_LOGGER_INFO(logger_planning, "StartListening");

	std::thread worker_store_dicoms;

	// Cases wheb USB device was plugged before application even started need to be
	// handled a bit differently, because in those cases hotplug callback won't be called
	int usbs_not_processed = CountMediaDirs();
	while (usbs_not_processed > 0) // start thread for every USB attached
	{
    	SPDLOG_LOGGER_INFO(logger_planning, "USB device mounted. Start processing.");
		// Sending empty string because we don't need USB unique ID in this case
		worker_store_dicoms = std::thread(&UsbManager::StoreDicomDirs, std::string());
		worker_store_dicoms.detach();
		usbs_not_processed--;
	}

	// Continuously handle USB plug and unplug events
	int rc;
	while(true)
	{
		rc = libusb_handle_events_completed(nullptr, nullptr);
		if (LIBUSB_SUCCESS != rc)
		{
    		SPDLOG_LOGGER_ERROR(logger_planning, "libusb_handle_events() failed: {}!", libusb_strerror((enum libusb_error)rc));
			// TODO Popup window and define circumstances
		}
	}
}

int LIBUSB_CALL UsbManager::UsbPlugged(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
	std::thread worker_store_dicoms;

	int rc;
	struct libusb_device_descriptor desc;
	rc = libusb_get_device_descriptor(dev, &desc);

	if (LIBUSB_SUCCESS == rc)
	{
		std::ostringstream device_unique_id;
		device_unique_id << desc.idVendor << ":" << desc.idProduct << ":" << desc.bcdDevice << ":" << static_cast<int>(desc.iSerialNumber);
		const std::string device_unique_id_str = device_unique_id.str();

		{
			std::lock_guard<std::mutex> lock(_mtx_usbs_status);

			if (_libusb_status_map.contains(device_unique_id_str))
				_libusb_status_map[device_unique_id_str] = UsbStatus::PLUGGED;
			else
				_libusb_status_map.insert(std::make_pair(device_unique_id_str, UsbStatus::PLUGGED));
		}

		worker_store_dicoms = std::thread(&UsbManager::StoreDicomDirs, device_unique_id_str);
		worker_store_dicoms.detach();
	}
	else
	{
    	SPDLOG_LOGGER_ERROR(logger_planning, "Error: Problems during device attachment! Failed to get device descriptor: {}.",
							libusb_strerror((enum libusb_error)rc));
	}

	return 0;
}

int LIBUSB_CALL UsbManager::UsbUnplugged(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
	struct libusb_device_descriptor desc;
	int rc;

	rc = libusb_get_device_descriptor(dev, &desc);
	if (LIBUSB_SUCCESS == rc)
	{
		std::ostringstream device_unique_id;
		device_unique_id << desc.idVendor << ":" << desc.idProduct << ":" << desc.bcdDevice << ":" << static_cast<int>(desc.iSerialNumber);
		const std::string device_unique_id_str = device_unique_id.str();
    	SPDLOG_LOGGER_INFO(logger_planning, "USB device unplugged.");

		{
			std::lock_guard<std::mutex> lock(_mtx_usbs_status);

			if (_libusb_status_map.contains(device_unique_id_str))
			{
				_libusb_status_map[device_unique_id_str] = UsbStatus::UNPLUGGED;
			}
			else
			{
				// This block will be executed in cases when USB was plugged before application even started running
				_libusb_status_map.insert(std::make_pair(device_unique_id_str, UsbStatus::UNPLUGGED));
			}
		}
	}
	else
	{
		SPDLOG_LOGGER_ERROR(logger_planning, "Error: Problems during device detachment! Failed to get device descriptor: {}.",
							libusb_strerror((enum libusb_error)rc));
	}

	// Wait for USB to be unmounted
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	for (auto& [device, dcm_file] : _usb_dicomdirs_map)
	{
		bool found = false;
		for (auto it = std::filesystem::directory_iterator(media_path); it != std::filesystem::directory_iterator(); it++)
		{
			if (it->path().string() == device)
				found = true;
		}
		if (!found)
		{
			std::lock_guard<std::mutex> lock(_mtx_usb_dicomdirs_map);
			_usb_dicomdirs_map.erase(device);
			break;
		}
	}

	return 0;
}

void UsbManager::StoreDicomDirs(std::string device_unique_id_str)
{
	_count_ongoing_threads++;

	// Waiting for USB to be mounted only in cases when USB device is plugged during application execution
	//	- in those cases device_unique_id_str won't be empty
	if (!device_unique_id_str.empty())
	{
		// Get the current time
		auto start_time = std::chrono::steady_clock::now();

		// 5 seconds will be maximum wait time for USB device to mount
		std::chrono::seconds max_mount_time(5);

		int current_mounted_usbs_count = CountMediaDirs();

		while(current_mounted_usbs_count == CountMediaDirs())
		{
			// Check if 5 seconds have passed
			auto current_time = std::chrono::steady_clock::now();
			auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
			if (elapsed_time > max_mount_time)
			{
				// USB device not mountable
				_count_ongoing_threads--;
				return;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			if (_libusb_status_map[device_unique_id_str] == UsbStatus::UNPLUGGED)
			{
				SPDLOG_LOGGER_INFO(logger_planning, "USB device is unplugged during mount process.");
				_count_ongoing_threads--;
				return;
			}
		}
		SPDLOG_LOGGER_INFO(logger_planning, "USB device mounted. Start processing.");
	}

	for (auto it = std::filesystem::directory_iterator(media_path); it != std::filesystem::directory_iterator(); it++)
	{
		auto usb_dir_path = it->path().string();
		_mtx_usb_dicomdirs_map.lock();
		if (!_usb_dicomdirs_map.contains(usb_dir_path))
		{
			_usb_dicomdirs_map.insert({usb_dir_path, {}});
			_mtx_usb_dicomdirs_map.unlock();
			SaveDicomDirsPaths(usb_dir_path);
		}
		else
		{
			_mtx_usb_dicomdirs_map.unlock();
		}
	}
	_count_ongoing_threads--;
}

void UsbManager::SaveDicomDirsPaths(const std::string& usb_path)
{
	using r_dir_it = std::filesystem::recursive_directory_iterator;
	std::vector<std::filesystem::path> dicomdir_files;
	try
	{
		for (auto it = r_dir_it(usb_path); it != r_dir_it(); ++it)
		{
			auto it_path_local = it->path();
			if (std::filesystem::is_regular_file(it_path_local))
			{
				auto path_str = it_path_local.string();
				for (auto& c : path_str)
					c = std::toupper(c);

				if (path_str.find("DICOMDIR") == std::string::npos)
					continue;

				if (!IsHidden(it_path_local))
				{
					dicomdir_files.push_back(it_path_local);
					SPDLOG_LOGGER_DEBUG(logger_planning, "Save DICOMDIR file {} to data structure.", it_path_local.string());
				}
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex)
	{
		SPDLOG_LOGGER_WARN(logger_planning, "Exception due to unplugging USB while reading DICOM files: {}!", ex.what());
	}

	std::lock_guard<std::mutex> lock(_mtx_usb_dicomdirs_map);
	_usb_dicomdirs_map[usb_path] = dicomdir_files;
}

int UsbManager::CountMediaDirs()
{
    int count = 0;
    for (const auto& entry : std::filesystem::directory_iterator(media_path))
	{
        if (std::filesystem::is_directory(entry))
            ++count;
    }
    return count;
}

void UsbManager::DeinitializeUsbDevices()
{
	if (_handle)
	{
		libusb_close(_handle);
		_handle = nullptr;
	}
	libusb_exit(nullptr);
	SPDLOG_LOGGER_INFO(logger_planning, "USB devices deinitialized.");
}

std::map<std::string, std::vector<std::filesystem::path>>& UsbManager::GetUsbDicomDirsMap()
{
	return _usb_dicomdirs_map;
}

int UsbManager::GetCountOngoingThreads()
{
	return _count_ongoing_threads;
}

bool UsbManager::IsHidden(const std::filesystem::path& file_path)
{
	for (const auto& component : file_path)
	{
		if (!component.empty() && component.string().front() == '.')
			return true;
	}
	return false;
}
