/*
 * Mutex

    RACE CONDITION:
        0. Race condition is a situation where two or more threads/process happens to change a common data at the same time.
        1. If there is a race condition then we have to protect it and the protected section is called critical section/region.

    MUTEX:
        0. Mutex is used to avoid race condition.
        1. We use 'lock()', 'unlock()' on mutex to avoid race condition.
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;
int buffer{ 0 };

void task(const char* threadNumber, int loopFor)
{
    m1.lock();
    for(int i = 0; i < loopFor; ++i)
    {
        buffer++;
        cout << threadNumber << buffer << endl;
    }
    m1.unlock();
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
