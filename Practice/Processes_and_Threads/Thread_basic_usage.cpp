/*
 * std::thread
 *  - programs shows just basic usage of std::thread
 *  - more info: https://www.youtube.com/watch?v=wXBcwHwIt_I
 */

#include <iostream>
#include <thread>

// Flag for quiting the thread execution
static bool s_Finished = false;

// Thread function
void DoWork()
{
    using namespace std::literals::chrono_literals; // std::this_thread::sleep_for

    // DoWork thread id
    std::cout << "Started DoWork thread: id = " << std::this_thread::get_id() << std::endl;

    while (!s_Finished)
    {
        std::cout << "Working...\n";
        std::this_thread::sleep_for(1s);
    }
}

// Starting main thread
int main()
{
    // Main thread id
    std::cout << "Started main thread: id = " << std::this_thread::get_id() << std::endl;

    // Starting DoWork thread
    std::thread worker(DoWork);

    // std::cin.get() extracts a single character from the stream, until it reaches a newline
    //  - when we hit the enter in terminal, std::cin.get() execution will be finished
    std::cin.get();
    
    s_Finished = true;

    worker.join();
    std::cout << "Finished." << std::endl;

    return 0;
}