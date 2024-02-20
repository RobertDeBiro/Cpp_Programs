#include <iostream>
#include <vector>
#include <thread> // std::thread
#include <atomic> // std::atomic
#include <chrono>
#include "../Timer/Timer.hpp"

int main()
{
    std::cout << "*****************************************************\n";

    Timer t;

    unsigned int sum = 0;
    for (unsigned int i = 0; i <= 9'000'000; ++i)
    {
        sum += i;
    }

    std::cout << "Sum = " << sum << '\n';
    std::cout << "Time taken: " << t.elapsed() << " seconds\n";
    // Time elapsed in average: 0.0196451 s
    //  - for some reason this is much quicker then using program with three threads!!!

    std::cout << "*****************************************************\n";
    return 0;
}