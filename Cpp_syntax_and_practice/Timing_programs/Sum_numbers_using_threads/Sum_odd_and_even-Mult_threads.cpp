#include <iostream>
#include <thread>
#include <chrono>
#include "../Timer/Timer.hpp"

typedef unsigned long long ull;

ull oddSum = 0;
ull evenSum = 0;

void findEven(ull start, ull end)
{
    for(ull i = start; i <= end; ++i)
    {
        // If first digit is not equal to 1, the number is even
        if((i & 1) == 0)
        {
            evenSum += i;
        }
    }
}

void findOdd(ull start, ull end)
{
    for(ull i = start; i <= end; ++i)
    {
        // If first digit is equal to 1, the number is odd
        if((i & 1) == 1)
        {
            oddSum += i;
        }
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    ull start = 0, end = 1'900'000'000;
    Timer t;

    std::thread t1(findEven, start, end);
    std::thread t2(findOdd, start, end);

    t1.join();
    t2.join();

    std::cout << "OddSum: " << oddSum << std::endl;
    std::cout << "EvenSum: " << evenSum << std::endl;

    std::cout << "Time taken: " << t.elapsed() << " seconds\n";
    // Time elapsed in average: 4.741 s

    std::cout << "*****************************************************\n";
    return 0;
}