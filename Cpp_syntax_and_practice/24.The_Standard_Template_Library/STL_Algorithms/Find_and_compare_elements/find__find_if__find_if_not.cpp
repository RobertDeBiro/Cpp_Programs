/*
 * std::find(InputIt first, InputIt last, const T& value) -> InputIt
 * 
 * std::find_if(InputIt first, InputIt last, callable object) -> InputIt
 *  - callable object can be both function pointer or lambda function
 * 
 * std::find_if_not(InputIt first, InputIt last, callable object) -> iterator
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/find
 */

#include <iostream>
#include <array>
#include <algorithm>

bool containsBer(const std::string& str)
{
    // When 'str.find()' doesn't find the substring, it returns 'npos'
    return (str.find("ber") != std::string::npos);
}

int main()
{
    std::cout << "*****************************************************\n";

    const std::array<std::string, 12> months{
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    // ******************************* std::find *******************************
    // using 'const_iterator' rather that 'const auto'
    using arrConstIt = std::array<std::string, 12>::const_iterator;
    arrConstIt itFind { std::find(months.begin(), months.end(), "August") }; 
    std::cout << "When object is found it will print: " << *itFind << '\n';

    itFind = std::find(months.begin(), months.end(), "Kolovoz");
    std::cout << "When object is not found it will print: " << *itFind << '\n';

    std::cout << "-------------------------------------\n";

    // ******************************* std::find_if *******************************
    //  - find month that contains 'ber' in his name
    const auto itFindIf{ std::find_if(months.begin(), months.end(), containsBer) };
    if (itFindIf == months.end())
        std::cout << "No ber\n";
    else
        std::cout << "First element with ber: " << *itFindIf << '\n';
    
    const auto itFindIf2{ std::find_if(months.begin(), months.end(),
                                       [](const std::string& str) { 
                                           return (str.find("uar") != std::string::npos); }
                                        )};
    if (itFindIf2 == months.end())
        std::cout << "No uar\n";
    else
        std::cout << "First element with uar: " << *itFindIf2 << '\n';

    // ******************************* std::find_if_not *******************************
    auto itFindIfNot{ std::find_if_not(months.begin(), months.end(), containsBer) };
    if (itFindIfNot == months.end())
        std::cout << "Only elements with ber\n";
    else
        std::cout << "First element without ber: " << *itFindIfNot << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
