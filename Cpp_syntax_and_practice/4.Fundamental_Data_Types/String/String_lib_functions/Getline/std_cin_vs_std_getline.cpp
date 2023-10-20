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

    //********** Print strings via std::getline in infinite loop **********
    std::cout << "Enter line by line:\n";
    std::string line;

    while (std::getline(std::cin >> std::ws, line))
    {
        if(line == "exit") break;
        std::cout << "\tEntered: " << line << '\n';
    }
    
    std::cout << "------------------------------------\n";

    //********** Print strings via std::getline in infinite loop **********
    std::cout << "Enter word by word:\n";
    std::string word;

    // Clear newline from buffer (placed there with "enter")
    std::cin.clear();
    while (std::cin >> word)
    {
        std::cout << "\tEntered: " << word << '\n';
        if(line == "exit") break;
        
        // If we want to remove words from buffer we can use:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "*****************************************************\n";
    return 0;
}