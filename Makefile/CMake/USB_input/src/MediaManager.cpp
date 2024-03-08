#include <iostream>
#include <thread>
#include <chrono>
#include <exception>

#include "MediaManager.h"
//! #include "DCMReader.h"


MediaManager::~MediaManager()
{
	if (handle) {
		libusb_close(handle);
	}

	// listenFlag = false;
	libusb_exit(NULL);
}

MediaManager& MediaManager::GetInstance()
{
    static MediaManager instance;
    return instance;
}

bool MediaManager::init()
{
	int rc;

	rc = libusb_init_context(NULL, NULL, 0);
	if (LIBUSB_SUCCESS != rc)
	{
		std::cerr << "Failed to initialise libusb: "
		          << libusb_strerror((enum libusb_error)rc) << '\n';
		return false;
	}

	if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG))
	{
		std::cout << "Hotplug capabilities are not supported on this platform\n";
		libusb_exit(NULL);
		return false;
	}

	rc = libusb_hotplug_register_callback(
			NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED, 0, LIBUSB_HOTPLUG_MATCH_ANY,
		    LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, mediaAttached, NULL, NULL
		 );

	if (LIBUSB_SUCCESS != rc)
	{
		std::cerr << "Error registering callback for media attach\n";
		libusb_exit(NULL);
		return false;
	}

	rc = libusb_hotplug_register_callback(
			NULL, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT, 0, LIBUSB_HOTPLUG_MATCH_ANY,
			LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY, mediaDetached, NULL, NULL
		 );

	if (LIBUSB_SUCCESS != rc)
	{
		std::cerr << "Error registering callback for media detach\n";
		libusb_exit(NULL);
		return false;
	}

	return true;
}

void MediaManager::startListening()
{
	int rc;

	checkMediaExisting();

	while(true)
	{
		rc = libusb_handle_events_completed (NULL, NULL);
		if (LIBUSB_SUCCESS != rc)
		{
			std::cerr << "libusb_handle_events() failed: "
			          << libusb_strerror((enum libusb_error)rc) << '\n';
		}
	}
}

void MediaManager::cleanup()
{
	if (handle)
	{
		libusb_close(handle);
		handle = NULL;
	}
}

bool MediaManager::checkDeviceMount()
{
	std::cout << "Waiting for the media device to be mounted...\n";

	// Get the current time
    auto startTime = std::chrono::steady_clock::now();

	// 10 seconds will be maximum wait time for media device to mount
    std::chrono::seconds maxMountTime(10);

	while(countDir >= countDirs())
	{
		// Check if 10 seconds have passed
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);
        if (elapsedTime > maxMountTime)
			return false;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	countDir++;
	return true;
}

// Function to enumerate existing USB devices
void MediaManager::checkMediaExisting()
{
	for(auto it = fs::directory_iterator(mediaPath); it != fs::directory_iterator(); it++)
	{
		auto usbDirPath = it->path().string();
		std::cout << usbDirPath << std::endl;
		std::cout << "Insert " << it->path().string() << " to usbMap!\n";
		std::cout << "Start thread to read dicom files frob USB device!\n";
		usbMap.insert({usbDirPath, {}});
		workerStoreDicoms = std::thread(&MediaManager::storeDicomFiles, usbDirPath);
		workerStoreDicoms.detach();
		countDir++;
	}
}

int LIBUSB_CALL MediaManager::mediaAttached(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
	//! Initialize mutex
	struct libusb_device_descriptor desc;
	int rc;

	rc = libusb_get_device_descriptor(dev, &desc);
	if (LIBUSB_SUCCESS == rc) {
		std::cout << "Device attached: " << desc.idVendor << ":" << desc.idProduct << '\n';
		if(!MediaManager::checkDeviceMount())
		{
			std::cerr << "Media device mounting TIMEOUT!" << std::endl;
		}
		else
		{
			for(auto it = fs::directory_iterator(mediaPath); it != fs::directory_iterator(); it++)
			{
				auto usbDirPath = it->path().string();
				std::cout << usbDirPath << std::endl;
				if(!usbMap.contains(usbDirPath))
				{
					std::cout << "Insert " << it->path().string() << " to usbMap!\n";
					std::cout << "Start thread to read dicom files frob USB device!\n";
					usbMap.insert({usbDirPath, {}});
					workerStoreDicoms = std::thread(&MediaManager::storeDicomFiles, usbDirPath);
					workerStoreDicoms.detach();
				}
			}
		}
	} else {
		std::cout << "Device attached\n";
		std::cerr << "Error getting device descriptor: "
		          << libusb_strerror((enum libusb_error)rc) << '\n';
	}

	std::cout << "****************** Cleanup ***************\n";
	MediaManager::cleanup();
	//! Send condition signal

	return 0;
}

int LIBUSB_CALL MediaManager::mediaDetached(libusb_context *ctx, libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
	//! Initialize mutex
	struct libusb_device_descriptor desc;
	int rc;

	rc = libusb_get_device_descriptor(dev, &desc);
	if (LIBUSB_SUCCESS == rc)
	{
		std::cout << "Device detached: " << desc.idVendor << ":" << desc.idProduct << '\n';
	}
	else
	{
		std::cout << "Device detached\n";
		std::cerr << "Error getting device descriptor: "
				  << libusb_strerror((enum libusb_error)rc) << '\n';
	}

	MediaManager::cleanup();
	countDir--;

	for(auto it = fs::directory_iterator(mediaPath); it != fs::directory_iterator(); it++)
	{
		auto usbDirPath = it->path().string();
		std::cout << usbDirPath << std::endl;
		if(!usbMap.contains(usbDirPath))
		{
	}
	//! Send condition signal

	return 0;
}

void MediaManager::storeDicomFiles(std::string usbPath)
{
	std::vector<fs::path> usbFilesTemp;
	try
	{
		for (auto it = fs::recursive_directory_iterator(usbPath); it != fs::recursive_directory_iterator(); ++it)
		{
			//! if (fs::is_regular_file(it->path()) && dcmImageIO->CanReadFile(dicomFile.string().c_str()))
			if (fs::is_regular_file(it->path()))
			{
				usbFilesTemp.push_back(it->path());
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				std::cout << "File: " << it->path().string() << '\n';
			}
		}
	} catch (const fs::filesystem_error& ex) {
		std::cerr << "Caught filesystem_error: " << ex.what() << std::endl;
		MediaManager::cleanup();
	} catch (const std::exception& ex) {
		std::cerr << "Caught exception: " << ex.what() << std::endl;
		MediaManager::cleanup();
	}
	mtx.lock();
	usbMap[usbPath] = usbFilesTemp;
	mtx.unlock();
}

int MediaManager::countDirs()
{
    int count = 0;
    for (const auto& entry : fs::directory_iterator(MediaManager::mediaPath)) {
        if (entry.is_directory()) {
            ++count;
        }
    }
    return count;
}
