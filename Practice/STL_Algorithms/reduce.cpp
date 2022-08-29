#include <iostream>
#include <array>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    std::array arr{ 1, 2, 3, 4, 5 };

    /*
     * std::reduce(InputIt first, InputIt last) -> T
     *  - returns the sum of every container element
     *  - comparison to std::accumulate
     *     - std::accumulate - sums elements starting from the initial value
     *     - std::reduce - sums the elements
     */
    int sum{ std::reduce(arr.begin(), arr.end()) };
    std::cout << "Accumulated numbers from array = " << sum << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
