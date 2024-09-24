#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rm;
int shared_data = 0;

void increment() {
    rm.lock();
    ++shared_data;

    // Simulate a recursive function call that also needs to lock the mutex
    if (shared_data < 5) {
        increment();
    }

    rm.unlock();
}

int main()
{
    std::thread t1(increment);
    std::thread t2(increment);

    t1.join();
    t2.join();

    std::cout << "Final value: " << shared_data << std::endl;
    return 0;
}
