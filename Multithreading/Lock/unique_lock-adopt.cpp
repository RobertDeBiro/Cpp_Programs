#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;
int buffer{ 0 };

void task(const char* threadNumber, int loopFor)
{
    m1.lock();
    unique_lock<mutex> lock(m1, adopt_lock);

    for(int i = 0; i < loopFor; ++i)
    {
        buffer++;
        cout << threadNumber << buffer << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // When using 'adopt_lock' we don't need to explicitly unlock the mutex, even though it is locked with 'mutex.lock()'
    //  - that will be done by 'unique_lock' destructor
    // m1.unlock();
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
