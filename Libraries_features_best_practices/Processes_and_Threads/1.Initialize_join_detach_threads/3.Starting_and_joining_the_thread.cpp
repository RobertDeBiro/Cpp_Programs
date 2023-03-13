/*
 * Showing that, immediately after thread is started, main function doesn't wait for the return value,
 * as it would usually do when using normal functions, but rather it continues with the execution.
 */

#include <iostream>
#include <thread>

using namespace std;

void run(int count)
{
    // Sleep for one second to wait parts from main() to be finished
    this_thread::sleep_for(chrono::seconds(1));
    
    while(count-- > 0)
        cout << "CppNuts" << endl;

    // Sleep for two seconds to show that main() function - when encounters t.join() - will wait for
    // thread to be finished
    this_thread::sleep_for(chrono::seconds(2));
}

int main()
{
    cout << "*****************************************************\n";

    thread t(run, 10);

    cout << "main()" << endl;
    cout << "---------------------------------------" << endl;

    t.join();

    cout << "---------------------------------------" << endl;
    cout << "main() after!" << endl;

    std::cout << "*****************************************************\n";
    return 0;
}
