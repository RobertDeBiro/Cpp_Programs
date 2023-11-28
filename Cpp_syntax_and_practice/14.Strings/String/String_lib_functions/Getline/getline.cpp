/*
 * std::getline
    - input string from keyboard into variable
    - cppreference: https://en.cppreference.com/w/cpp/string/basic_string/getline
 */

#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Enter your full name: ";
    std::string fullName;
    
    // the std::ws input manipulator tells std::cin to ignore any leading whitespace
    // that may be left from previous std::cin inputs
    std::getline(std::cin >> std::ws, fullName);

    std::cout << "Fullname = " << fullName << '\n';

    std::cout << "*****************************************************\n";
    
    return 0;
}