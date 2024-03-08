/*
 * Showing that, immediately after thread is started, 'main()' function doesn't wait for the return value,
 * as it would usually do when using normal functions, but rather it continues with the execution.
 */

#include <iostream>
#include <thread>

using namespace std;

void run(int count, std::string thread_ID)
{
    // Sleep for 1 second to wait parts from 'main()' to be finished
    this_thread::sleep_for(chrono::seconds(1));
    
    while(count-- > 0)
    {
        if(thread_ID == "1")
            cout << thread_ID << ": CppNuts" << endl;
        else
            cout << " \t \t \t " << thread_ID << ": CppNuts" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // Sleep for 2 seconds to show that 'main()' function - when encounters 't.join()' -
    // will wait for thread to be finished
    this_thread::sleep_for(chrono::seconds(2));
}

int main()
{
    cout << "*****************************************************\n";

    thread t1(run, 10, "1");
    thread t2(run, 15, "2");

    cout << "main()" << endl;
    cout << "---------------------------------------" << endl;

    t1.join();
    t2.join();

    cout << "---------------------------------------" << endl;
    cout << "main() after!" << endl;

    std::cout << "*****************************************************\n";
    return 0;
}
