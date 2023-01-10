#include <iostream>
#include <array>
#include <algorithm>

bool containsBer(const std::string& str)
{
    return (str.find("ber") != std::string::npos); // When str.find() doesn't find the substring, it returns npos
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
    /*
     * std::find(InputIt first, InputIt last, const T& value) -> InputIt
     *  - returns the iterator of the first element found in input container
     *    that is equal to specified value
     *  - if element is not found, returns iterator with the address of last element + 1
     */
    using arrConstIt = std::array<std::string, 12>::const_iterator; // using const_iterator rather that const auto
    arrConstIt itFind { std::find(months.begin(), months.end(), "August") }; 
    std::cout << "When object is found it will print: " << *itFind << '\n';

    itFind = std::find(months.begin(), months.end(), "Kolovoz");
    std::cout << "When object is not found it will print: " << *itFind << '\n';

    std::cout << '\n';


    // ******************************* std::find_if *******************************
    /*
     * std::find_if(InputIt first, InputIt last, callable object) -> InputIt
     *  - returns the iterator of the first element found in input container,
     *    for which callable object returns true
     *  - callable object can be both function pointer or lambda function
     *    (even though in cppreference.com says that callable object must be function)
     */
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
    /*
     * std::find_if_not(InputIt first, InputIt last, callable object) -> iterator
     *  - returns the iterator of the first element found in input container,
     *    for which callable object returns false
     */
    auto itFindIfNot{ std::find_if_not(months.begin(), months.end(), containsBer) };
    if (itFindIfNot == months.end())
        std::cout << "Only elements with ber\n";
    else
        std::cout << "First element without ber: " << *itFindIfNot << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
