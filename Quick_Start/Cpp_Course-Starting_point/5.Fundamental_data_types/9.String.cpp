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

int main()
{
    std::cout << "Hello World!" << std::endl;

    return 0;
}