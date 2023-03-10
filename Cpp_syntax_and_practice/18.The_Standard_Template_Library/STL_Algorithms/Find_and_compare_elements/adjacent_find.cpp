/*
 * 1) std::adjacent_find(ForwardIt first, ForwardIt last) -> OutputIt
 * 
 * 2) std::adjacent_find(ForwardIt first, ForwardIt last, callable object) -> OutputIt
 * 
 * - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/adjacent_find
 */

#include <iostream>
#include <array>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    constexpr std::array<const char*, 12> months{
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    const auto itSameLetter{ std::adjacent_find(months.begin(), months.end(),
                                                [](const auto& a, const auto& b) {
                                                   return (a[0] == b[0]);
                                                }) };

    if (itSameLetter != months.end())
        std::cout << *itSameLetter << " and " << *std::next(itSameLetter)
                  << " start with the same letter.\n";

    std::cout << "*****************************************************\n";
    return 0;
}
