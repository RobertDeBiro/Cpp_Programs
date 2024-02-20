#include <iostream>
#include <vector>
#include <thread> // std::thread
#include <atomic> // std::atomic

// long multiThreadedSum = 0;
std::atomic<long> multiThreadedSum( 0 );

void SumNumbers(const std::vector<int>& toBeSummed, int idxStart, int idxEnd)
{
    for (int i = idxStart; i <= idxEnd; ++i)
    {
        // atomic variable actually encompasses mutex variable and normal variable
        multiThreadedSum += toBeSummed[i];
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> toBeSummed;
    for (int i = 0; i < 30000; ++i)
    {
        toBeSummed.push_back( rand() );
    }

    long sum = 0;
    for (int i = 0; i < static_cast<int>(toBeSummed.size()); ++i)
    {
        sum += toBeSummed[i];
    }

    std::cout << "Sum = " << sum << '\n';

    /////////////////////////////////////////////////////////////

    std::thread t1( SumNumbers, toBeSummed, 0, 9999 );
    std::thread t2( SumNumbers, toBeSummed, 10000, 19999 );
    std::thread t3( SumNumbers, toBeSummed, 20000, 29999);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Multithread sum = " << multiThreadedSum.load() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}