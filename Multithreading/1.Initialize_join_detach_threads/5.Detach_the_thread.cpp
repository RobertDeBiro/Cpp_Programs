#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void run(int count)
{
    while(count-- > 0)
        cout << count << " CppNuts" << endl;
    cout << "Thread finished!" << endl;
}

int main()
{
    cout << "*****************************************************\n";

    thread t(run, 10);
    cout << "main()" << endl;

    t.detach();

    if(t.joinable())
    {
        std::cout << "Detach thread\n";
        t.join();
    }

    cout << "main() after" << endl;

    this_thread::sleep_for(chrono::seconds(3));

    cout << "*****************************************************\n";
    return 0;
}