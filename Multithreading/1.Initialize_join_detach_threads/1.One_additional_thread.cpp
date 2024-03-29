#include <iostream>
#include <thread>

// Flag for quiting the thread execution
static bool s_Finished = false;

// Thread function
void DoWork()
{
    using namespace std::literals::chrono_literals; // std::this_thread::sleep_for

    // 'DoWork' thread id
    std::cout << "Started DoWork thread: id = " << std::this_thread::get_id() << std::endl;

    while (!s_Finished)
    {
        std::cout << "Working...\n";
        // Without 'using namespace std::literals::chrono_literals' we would need to write
        // 'std::this_thread::sleep_for(std::chrono::seconds(1))'
        std::this_thread::sleep_for(1s);
    }
}

// Starting main thread
int main()
{
    std::cout << "*****************************************************\n";

    // 'main()' thread id
    //  - 'get_id()' is 'std::thread' member function
    std::cout << "Started main thread: id = " << std::this_thread::get_id() << std::endl;

    // Starting 'DoWork' thread
    std::thread worker(DoWork);

    // 'std::cin.get()' extracts a single character from the stream, until it reaches a newline
    //  - when we hit the enter in terminal, 'std::cin.get()' execution will be finished
    std::cin.get();
    
    s_Finished = true;

    // 'join' is 'std::thread' member function
    worker.join();
    std::cout << "Finished." << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}