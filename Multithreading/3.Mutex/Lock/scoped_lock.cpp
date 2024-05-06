#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void threadFunction() {
    // Attempt to lock both mutexes using std::lock_guard
    std::lock_guard<std::mutex> lock1(mutex1); // Locks mutex1
    std::lock_guard<std::mutex> lock2(mutex2);
    std::cout << "Thread locked both mutexes" << std::endl;
}

int main() {
    std::thread t(threadFunction);
    t.join();
    return 0;
}
