for (auto it = std::filesystem::recursive_directory_iterator(usb_path); it != std::filesystem::recursive_directory_iterator(); ++it)
	{
		std::cout << "0\n";
		if (std::filesystem::is_regular_file(it->path()))
		{
			std::cout << "0.1\n";
			std::shared_ptr<std::timed_mutex> mt{ new std::timed_mutex() };
			// std::timed_mutex mutex;
			// std::unique_lock<std::mutex> lock(*mt, std::defer_lock);
			std::unique_lock<std::timed_mutex> lock(*mt, std::defer_lock);
			std::shared_ptr<std::condition_variable> cv{ new std::condition_variable() };

			// Thread wrapper for managing CanReadFile() function
            // std::unique_ptr<std::thread> t{ new std::thread([it, mt, cv, &lock, gdcmImageIO, &dicom_files]()
			// {
			// 	std::cout << "1\n";
			// 	// lock.lock();
			// 	std::cout << "2\n";
			// 	if(gdcmImageIO->CanReadFile(it->path().c_str()))
			// 	{
			// 		dicom_files.push_back(it->path());
			// 		// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			// 		std::cout << "DICOM file: " << it->path().string() << '\n';
			// 	}
			// 	// lock.unlock();
			// 	std::cout << "3\n";
				// cv->notify_all();
			// 	std::cout << "4\n";
			// })};
			using namespace std::literals;
            std::future<void> task = std::async([it, mt, cv, &lock, gdcmImageIO, &dicom_files]()
			{
				std::cout << "**************************\n";
				if(gdcmImageIO->CanReadFile(it->path().c_str()))
				{
					dicom_files.push_back(it->path());
					// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					std::cout << "DICOM file: " << it->path().string() << '\n';
				}
				// std::atomic<bool> all_tasks_completed = true;
			});
			auto status = task.wait_for(500ms);

			if (status == std::future_status::timeout)
			{
				// Cancel the task if it hasn't completed within the timeout period
				task = std::future<void>{}; // Replace the future with a new, empty future
				std::cout << "Timeout!\n";
			}
			else
				std::cout << "No timeout!\n";

			// all_tasks_completed.wait(false);

			// if(lock.try_lock_for(std::chrono::milliseconds(500)))
			// {
			// 	std::cout << "Thread joined!\n";
			// 	t->join();
			// }
			// else
			// {
			// 	std::cout << "Thread detached!\n";
			// 	t->detach();
			// }
			// if(cv->wait_for(lock, std::chrono::milliseconds(500)) != std::cv_status::timeout)
			// {
			// 	t->join();
			// 	std::cout << "Thread joined!\n";
			// }
			// else
			// {
			// 	t->detach();
			// 	std::cout << "Thread detached!\n";
			// }
		}
	}