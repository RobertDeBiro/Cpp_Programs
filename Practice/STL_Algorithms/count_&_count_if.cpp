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
    /*
     * std::count(InputIt first, InputIt last, const T& value) -> Int
     *  - returns the amount of specified elements found inside input container
     */
    const auto amountIvan{ std::count(names.begin(), names.end(), "Ivan") };
    std::cout << "There are " << amountIvan << " of Ivan's\n";


    // ******************************* std::count_if *******************************
    /*
     * std::count_if(InputIt first, InputIt last, callable object) -> Int
     *  - returns the amount of elements found inside input container,
     *    for which callable object returns true
     */
    const auto fiveLetterNames{ std::count_if(names.begin(), names.end(),
                                              [](const auto& name) {
                                                 return (strlen(name) == 5);
                                              }) };
    std::cout << "There are " << fiveLetterNames << " names with 5 letters\n";

    std::cout << "*****************************************************\n";
    return 0;
}
