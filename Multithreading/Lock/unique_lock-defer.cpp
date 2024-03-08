#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;
int buffer{ 0 };

void task(const char* threadNumber, int loopFor)
{
    unique_lock<mutex> lock(m1, defer_lock);

    // When using 'defer_lock' we need to explicitly lock it later on with 'lock()' function
    lock.lock();
    for(int i = 0; i < loopFor; ++i)
    {
        buffer++;
        cout << threadNumber << buffer << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main()
{
    cout << "*****************************************************\n";

    thread t1(task, "T0 ", 10);
    thread t2(task, "T1 ", 10);
    t1.join();
    t2.join();

    cout << "*****************************************************\n";
    return 0;
}
