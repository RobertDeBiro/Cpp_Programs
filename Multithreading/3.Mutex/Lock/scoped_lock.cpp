#include <mutex>
#include <thread>
#include <iostream>

std::mutex mutex1;
std::mutex mutex2;

void thread_function()
{
    // Locks both mutex1 and mutex2
    std::scoped_lock lock(mutex1, mutex2);

    // Critical section, where both mutexes are locked
    std::cout << "Thread has locked both mutex1 and mutex2." << std::endl;
}

int main()
{
    std::thread t1(thread_function);
    std::thread t2(thread_function);

    t1.join();
    t2.join();
    
    return 0;
}
