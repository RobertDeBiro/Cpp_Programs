/*
 * std::sort(RandomIt first, RandomIt last) -> void
 *  - by default sorts elements inside container in ascending order
 * 
 * std::sort(RandomIt first, RandomIt last, callable object) -> void
 *  - callable object must implement following behavior:
 *    - if two elements are already sorted, return 'true'
 *    - if two elements are not sorted, return 'false'
 *    - if we want to sort in ascending order we need to implement:
 *        'return (first element < second element)'
 *    - if we want to sort in descending order we need to implement:
 *        'return (first element > second element)'
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/sort
 */

#include <iostream>
#include <algorithm>
#include <array>

struct Season
{
    std::string name;
    double averageTemperature;
};

int main()
{
    std::cout << "*****************************************************\n";

    // 1)
    std::array arr{ 285.0, 296.0, 288.0, 263.0 };
    std::sort(arr.begin(), arr.end());
    std::cout << "Ascending order: ";
    for(const auto elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';

    // 2)
    auto descendingObj{
        [](const auto& a, const auto& b)
        {
          return (a > b);
        }
    };

    std::sort(arr.begin(), arr.end(), descendingObj);
    std::cout << "Descending order: ";
    for (const auto& elem : arr)
    {
        std::cout << elem << ' ';
    }

    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
