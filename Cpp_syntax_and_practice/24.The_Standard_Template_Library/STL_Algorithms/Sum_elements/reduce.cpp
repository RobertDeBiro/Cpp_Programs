/*
 * std::reduce(InputIt first, InputIt last) -> T
 *  - comparison to std::accumulate
 *     - std::accumulate - sums elements in addition with initial value
 *     - std::reduce - sums elements
 * 
 *  - included in <numeric>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/reduce
 */

#include <iostream>
#include <array>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    std::array arr{ 1, 2, 3, 4, 5 };

    int sum{ std::reduce(arr.begin(), arr.end()) };
    std::cout << "Sum = " << sum << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
