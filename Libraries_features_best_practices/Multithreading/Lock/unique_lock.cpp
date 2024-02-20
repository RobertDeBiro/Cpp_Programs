/*
 * 'unique_lock'
    
    syntax: std::unique_lock<mutex> lockVar(mutexVar)

    1. The class 'unique_lock' is a mutex ownership wrapper
    2. It allows:
        a. can have different locking strategies
        b. time-constrained attempts at locking ('try_lock_for', 'try_lock_until')
        c. recursive locking
        d. transfer of lock ownership (move not copy)
        e. condition variables

    Locking Strategies
    TYPE                EFFECTS(S)
    1. 'defer_lock'     Do not acquire ownership of the mutex
    2. 'try_to_lock'    Try to acquire ownership of the mutex without blocking
    3. 'adopt_lock'     Assume the calling thread already has ownership of the mutex

    - very similar to 'lock_guard()' but more flexible and feature-rich
    - it provides exclusive ownership of a mutex, but it allows more control over locking and unlocking operations
    - preferred when we need more advanced locking mechanisms or when we need to conditionally acquire or release the lock
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;
int buffer{ 0 };

void task(const char* threadNumber, int loopFor)
{
    unique_lock<mutex> lock(m1);
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
