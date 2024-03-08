#include <iostream>
#include <thread>

using namespace std;

void run(int count)
{
    while(count-- > 0)
        cout << "CppNuts" << endl;
}

int main()
{
    cout << "*****************************************************\n";

    thread t(run, 10);

    t.join();

    cout << "---------------------------------------" << endl;

    //* Join the same thread, twice
    try
    {
        t.join();
    }
    catch(const std::system_error& e)
    {
        // The same thread cannot be joined twice - 'std::system_error' exception is thrown
        cout << "EXCEPTION: " << e.what() << endl;
        cout << "The same thread cannot be joined twice" << endl;
    }

    cout << "---------------------------------------" << endl;

    //* Check thread with 'joinable()'
    if(t.joinable())
    {
        t.join();
    }
    else
    {
        cout << "Thread is not joinable!" << endl;
    }

    std::cout << "*****************************************************\n";
    return 0;
}
