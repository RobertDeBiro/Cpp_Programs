#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;
int buffer{ 0 };

void task(const char* threadNumber, int loopFor)
{
    m1.lock();

    // The benefit of 'adopt_lock' is that we don't need to explicitly unlock the mutex 'm1',
    // with 'm1.unlock()', even though it is locked with 'm1.lock()'
    //  - that will be done by 'unique_lock' destructor
    unique_lock<mutex> lock(m1, adopt_lock);

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
