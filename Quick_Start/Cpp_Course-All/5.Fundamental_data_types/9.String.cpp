/**
 * * String
 *      - collection of sequential characters
 *      - included as part of string library
 *      - sytax:
 *?         #include <string>
 *?         std::string some_string;
 **/
/**
 * * String input
 *      - for input the best is to use std::getline, with the help of std::ws
 *      - syntax:
 *?          std::getline(std::cin >> std::ws, string_variable)
 *      - std::ws - input manipulator tells std::cin to ignore any leading whitespaces
 **/

#include <iostream>
#include <string>

int main()
{
    std::string str1 = "Hello World!";
    std::cout << str1 << std::endl;

    str1 = "Bye bye World!";
    std::cout << str1 << std::endl;

    /////////////////////////////////////////////////////////////////////////

    /*
     * String input
     */
    std::cout << "Insert some character: ";
    char c;
    // std::cin memorizes everything after whitespace (including whitespace) in its private buffer
    std::cin >> c;

    std::cout << "Enter your full name: ";
    std::string fullName;
    
    // std::cin breaks on whitespace
    // std::cin >> fullName;
    // std::getline(std::cin, fullName);
    std::getline(std::cin >> std::ws, fullName);
    std::cout << fullName << std::endl;

    /////////////////////////////////////////////////////////////////////////

    // length() is string class member function
    std::cout << "String " << fullName << " has length of " << fullName.length() << " characters!\n";

    return 0;
}
