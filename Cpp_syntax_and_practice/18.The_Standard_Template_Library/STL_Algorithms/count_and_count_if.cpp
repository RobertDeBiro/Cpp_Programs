/*
 * std::count(InputIt first, InputIt last, const T& value) -> Int
 * 
 * std::count_if(InputIt first, InputIt last, callable object) -> Int
 * 
 * - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/count
 */

#include <iostream>
#include <array>
#include <algorithm>
#include <cstring> // strlen

int main()
{
    std::cout << "*****************************************************\n";

    constexpr std::array<const char*, 6> names{
        "Luka", "Ivan", "Marko",
        "Ivan", "Luka", "Matej",
    };

    // ******************************* std::count *******************************
    const auto amountIvan{ std::count(names.begin(), names.end(), "Ivan") };
    std::cout << "There are " << amountIvan << " of Ivan's\n";


    // ******************************* std::count_if *******************************
    const auto fiveLetterNames{ std::count_if(names.begin(), names.end(),
                                              [](const auto& name) {
                                                 return (strlen(name) == 5);
                                              }) };
    std::cout << "There are " << fiveLetterNames << " names with 5 letters\n";

    std::cout << "*****************************************************\n";
    return 0;
}
