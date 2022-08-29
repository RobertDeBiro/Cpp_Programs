// Program finds first two months that starts with the same letter

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

    /*
     * std::next(InputIt it, int n = 1) -> InputIt
     *  - returns the iterator which is following the input_iterator after "n" elements
     *  - default value of "n" is 1
     */

    if (itSameLetter != months.end())
    {
        std::cout << *itSameLetter << " and " << *std::next(itSameLetter)
                  << " start with the same letter.\n";
    }

    if (itSameLetter != months.end())
    {
        std::cout << *(itSameLetter - 1) << " and " << *std::next(itSameLetter)
                  << " doesn't start with the same letter.\n";
    }

    if (itSameLetter != months.end())
    {
        std::cout << *itSameLetter << " and " << *std::next(itSameLetter + 1)
                  << " maybe start with the same letter?!\n";
    }

    std::cout << "*****************************************************\n";
    return 0;
}
