#include <iostream>
#include <vector>
#include <thread> // std::thread
#include <atomic> // std::atomic
#include <chrono>
#include "../Timer/Timer.hpp"

std::atomic<unsigned int> multiThreadedSum( 0 );

void SumNumbers(unsigned int idxStart, unsigned int idxEnd)
{
    for (unsigned int i = idxStart; i <= idxEnd; ++i)
    {
        multiThreadedSum += i;
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    Timer t;

    std::thread t1( SumNumbers, 0, 3'000'000 );
    std::thread t2( SumNumbers, 3'000'001, 6'000'000 );
    std::thread t3( SumNumbers, 6'000'001, 9'000'000);
    t1.join();
    t2.join();
    t3.join();

    std::cout << "Multithread sum = " << multiThreadedSum.load() << '\n';

    std::cout << "Time taken: " << t.elapsed() << " seconds\n";
    // Time elapsed in average: 0.121243 s

    std::cout << "*****************************************************\n";
    return 0;
}