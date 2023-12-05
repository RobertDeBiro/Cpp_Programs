/*
 * std::iota(InputIt first, InputIt last, T value) -> void
 *  - comparison with std::fill and std::generate:
 *     - std::fill - puts elements with the same specified value into container
 *     - std::generate - puts elements with generated values into container
 *     - std::iota - puts elements with contiguous values - starting from specified value - into container
 * 
 * - inlcuded in <numeric>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/iota
 */

#include <iostream>
#include <array>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 5> arr{};
    for(const auto elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::iota(arr.begin(), arr.end(), 10);
    for(const auto elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
