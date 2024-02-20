#include <iostream>
#include <thread>

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

    // 'std::thread' constructor called:
    // template< class Function, class... Args >
    // explicit thread( Function&& f, Args&&... args );
    //  - 'start' and 'end' are arguments for thread functions
    std::thread t1(findEven, start, end);
    std::thread t2(findOdd, start, end);

    t1.join();
    t2.join();

    std::cout << "OddSum: " << oddSum << std::endl;
    std::cout << "EvenSum: " << evenSum << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}