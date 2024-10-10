#include "rtkcommunication/Common/ThreadPool.h"

using namespace rtkcommunication;


ThreadPool::ThreadPool(const int num_of_workers)
{
	workers_vec.reserve(num_of_workers);
	should_stop = false;

	try
	{
		for (int i = 0; i < num_of_workers; i++)
			workers_vec.emplace_back(&ThreadPool::WorkerFunction, this);
	}
	catch (...)
	{
		{
			std::lock_guard<std::mutex> lock(queue_mutex);
			should_stop = true;
		}

		cond_variable.notify_all();

		for (std::thread& worker : workers_vec)
		{
			if (worker.joinable() == true)
				worker.join();
		}

		throw;
	}
}


ThreadPool::~ThreadPool()
{
	{
		std::lock_guard<std::mutex> lock(queue_mutex);
		should_stop = true;
	}

	cond_variable.notify_all();

	for (std::thread& worker : workers_vec)
	{
		if (worker.joinable() == true)
			worker.join();
	}
}


void ThreadPool::WorkerFunction() {
	while (true)
	{
		std::function<void()> task;

		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			while (tasks_queue.empty() == true)
			{
				if (should_stop == true)
					return;

				cond_variable.wait(lock);
			}

			task = std::move(tasks_queue.front());
			tasks_queue.pop();
		}

		task();
	}
}


int ThreadPool::GetNumberOfHardwareThreads()
{
	int detected_num_of_threads = std::thread::hardware_concurrency();

	if (detected_num_of_threads > 0)
		return detected_num_of_threads;
	else
		return 1;
}