/*
 * std::accumulate(InputIt first, InputIt last, T init) -> T
 *  - comparison to std::reduce
 *     - std::accumulate - sums elements in addition with initial value
 *     - std::reduce - sums elements
 * 
 *  - included in <numeric>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/accumulate
 */

#include <iostream>
#include <array>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    std::array arr{ 1, 2, 3, 4, 5 };

    int sum1{ std::accumulate(arr.begin(), arr.end(), 0) };
    std::cout << "Sum = " << sum1 << '\n';

    int sum2{ std::accumulate(arr.begin(), arr.end(), 10) };
    std::cout << "Sum + init integer = " << sum2 << '\n';

    double sum3{ std::accumulate(arr.begin(), arr.end(), 20.5) };
    std::cout << "Sum + init double = " << sum3 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
