#pragma once

#include <functional>
#include <future>
#include <queue>


namespace rtkcommunication

{
	/**
	 * @brief Class for using the thread pooling, whose implementation is based on https://codereview.stackexchange.com/questions/275834/tiny-thread-pool-implementation.
	 */
	class ThreadPool
	{

	public:
		explicit ThreadPool(const int num_of_threads = ThreadPool::GetNumberOfHardwareThreads());
		~ThreadPool();


		template<typename FunctionType, typename... ArgumentType>
		inline std::future<std::result_of_t<FunctionType(ArgumentType...)>> Enqueue(FunctionType&& function, ArgumentType&&... arguments)
		{
			typedef std::result_of_t<FunctionType(ArgumentType...)> ResultType;

			std::shared_ptr<std::packaged_task<ResultType()>> task = std::make_shared<std::packaged_task<ResultType()>>(std::bind(std::forward<FunctionType>(function),
				std::forward<ArgumentType>(arguments)...));

			std::future<ResultType> result = task->get_future();

			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				tasks_queue.emplace([task]() { (*task)(); });
			}

			cond_variable.notify_one();

			return result;
		}


	private:
		ThreadPool(const ThreadPool&) = delete;
		ThreadPool(ThreadPool&&) = delete;

		ThreadPool& operator=(const ThreadPool&) = delete;
		ThreadPool& operator=(ThreadPool&&) = delete;

		void WorkerFunction();

		static int GetNumberOfHardwareThreads();


		std::vector<std::thread> workers_vec;
		bool should_stop;

		std::mutex queue_mutex;
		std::condition_variable cond_variable;

		std::queue<std::function<void()>> tasks_queue;
	};
}