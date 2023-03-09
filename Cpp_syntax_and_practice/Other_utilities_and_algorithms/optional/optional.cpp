/*
 * class optional
 * 
 *  - included in <optional>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/utility/optional
 */

#include <iostream>
#include <string>
#include <optional>

std::optional<std::string> checkText(bool b)
{
    if(b)
        return "Valid";
    return {};
}


int main()
{
    std::cout << "*****************************************************\n";

    // If checkText function doesn't return anything, we will printout default text "Invalid"
    std::cout << "Function checkText is " << checkText(true).value_or("Invalid") << '\n';
    std::cout << "Function checkText is " << checkText(false).value_or("Invalid") << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}