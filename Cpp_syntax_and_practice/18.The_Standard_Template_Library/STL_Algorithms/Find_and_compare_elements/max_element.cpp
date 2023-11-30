/*
 * 1) std::max_element(ForwardIt first, ForwardIt last) -> ForwardIt
 * 
 * 2) std::max_element(ForwardIt first, ForwardIt last, callable object) -> ForwardIt
 *      - when we want maximum value of some user-defined type, we need to provide callable object
 *        in which we define attributes that will be compared
 *      - callable object must return 'true' when second element is bigger then first,
 *        because callable object goes from the beginning of the container and transfers the maximum
 *        element to the end of container
 *      - if it returns 'true', means that it doesn't have to swap elements
 *      - similar to sorting algorithm
 *
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/max_element
 */

#include <iostream>
#include <array>
#include <algorithm>

struct Student
{
    std::string name{};
    int points{};
};

int main()
{
    std::cout << "*****************************************************\n";

    std::array arr{ 3, 5, 8, 1 };

    // 1)
    const auto itMaxVal{ std::max_element(arr.begin(), arr.end()) };
    std::cout << "Maximum value of the array arr is: " << *itMaxVal << '\n';

    // 2)
    std::array<Student, 4> stArr{
        { { "Albert", 3 },
          { "Ben", 5 },
          { "Dan", 8 },
          { "Francis", 1 } }
    };

    auto lambdaMax{
        [](const auto& a, const auto& b)
        {
          return (a.points < b.points);
        }
    };

    const auto itBestSt{ std::max_element(stArr.begin(), stArr.end(), lambdaMax) };
    std::cout << itBestSt->name << " is the best student and has " << itBestSt->points << " points.\n";

    std::cout << "*****************************************************\n";
    return 0;
}
