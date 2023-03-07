/*
 * C++ Primer
 * Exercise Section 3.2.2
 *  - Exercise 3.2
 */

#include <iostream>
#include <string>
#include <limits> // std::numeric_limits

int main()
{
    std::cout << "*****************************************************\n";

    std::cout << "Enter line by line:\n";
    std::string line;
    
    // In order to go out from the loop we must enter::
    //  1. Ctrl + Z
    //  2. Enter
    while (std::getline(std::cin >> std::ws, line))
        std::cout << "\tEntered: " << line << '\n';
    
    std::cout << "------------------------------------\n";

    std::cout << "Enter word by word:\n";
    std::string word;

    // Always needs to be executed after running "Ctrl + z"
    std::cin.clear();
    while (std::cin >> word)
    {
        std::cout << "\tEntered: " << word << '\n';
        // Additional words will be discarded
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "*****************************************************\n";
    return 0;
}