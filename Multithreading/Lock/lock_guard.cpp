/*
 * 'lock_guard'
    
    syntax: std::lock_guard<mutex> lockVar(mutexVar)

    0. It is very light weight wrapper for owning 'mutex' on scoped basis
    1. It acquires mutex lock the moment you create the object of 'lock_guard'
    2. It automatically removes the lock while goes out of scope (removed by 'std::lock_guard' destructor)
    3. You can not explicitly unlock the 'lock_guard'
    4. You can not copy 'lock_guard'

    - used when we want to give explicit message that we want our mutex locked until the end of the block
    - alternative is to use 'mutexVar.lock()' and at the end of the block 'mutexVar.unlock()'
    - does not provide any additional functionalities beyond acquiring and releasing the lock
    - it is preferred when we need a simple and straightforward way to lock and unlock a mutex within a limited scope
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m1;
int buffer{ 0 };

void task(const char* threadNumber, int loopFor)
{
    // m1.lock();
    lock_guard<mutex> lock(m1);
    for(int i = 0; i < loopFor; ++i)
    {
        buffer++;
        cout << threadNumber << buffer << endl;
    }
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
