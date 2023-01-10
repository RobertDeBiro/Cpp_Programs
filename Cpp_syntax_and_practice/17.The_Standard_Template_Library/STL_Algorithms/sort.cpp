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

    /*
     * std::sort(RandomIt first, RandomIt last) -> void
     *  - sorts elements inside container in ascending order
     */
    std::array arr{ 285.0, 296.0, 288.0, 263.0 };
    std::sort(arr.begin(), arr.end());
    for(const auto elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';

    /*
     * std::sort(RandomIt first, RandomIt last, callable object) -> void
     *  - when we want to sort elements of used-defined object, or we want to choose our way to sort,
     *    we need to use callable object
     *  - callable object must implement following behavior:
     *     - if two elements are already sorted, return true
     *     - if two elements are not sorted, return false
     *  - if we want to sort in ascending order we need to implement:
     *     return (first element < second element)
     *  - if we want to sort in descending order we need to implement:
     *     return (first element > second element)
     */
    std::array<Season, 4> seasons{
        { { "Spring", 285.0 },
          { "Summer", 296.0 },
          { "Fall", 288.0 },
          { "Winter", 263.0 } }
    };

    auto ascendingObj{
        [](const Season& a, const Season& b)
        {
          return (a.averageTemperature < b.averageTemperature);
        }
    };

    std::sort(seasons.begin(), seasons.end(), ascendingObj);
    for (const auto& season : seasons)
    {
        std::cout << season.name << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
