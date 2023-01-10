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

    /*
     * std::adjacent_find(ForwardIt first, ForwardIt last, callable object) -> OutputIt
     *  - returns iterator of the first element of the pair of adjacent elements for which callable object returned true
     *  - example:
     *     - find adjacent elements that have the same first letter
     */
    const auto itSameLetter{ std::adjacent_find(months.begin(), months.end(),
                                                [](const auto& a, const auto& b) {
                                                   return (a[0] == b[0]);
                                                }) };

    if (itSameLetter != months.end())
        std::cout << *itSameLetter << " and " << *std::next(itSameLetter) << " start with the same letter.\n";

    std::cout << "*****************************************************\n";
    return 0;
}
