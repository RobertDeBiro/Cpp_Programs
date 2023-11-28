/*
 * C++ Primer
 * Exercise Section 3.2.2
 *  - Exercise 3.5
 */

#include <iostream>
#include <string>
#include <sstream> // stringstream

int main()
{
    std::cout << "*****************************************************\n";

    std::string str_conc{};
    std::string str{};
    while(std::cin >> str)
        str_conc += str + ' ';
    
    std::cout << "-----------------------------\n";

    std::cout << "Concatenated string:\n";
    std::cout << str_conc << '\n';

    std::cout << "-----------------------------\n";
    std::cout << "Seperated string:\n";

    for(const auto& ch : str_conc)
    {
        if(ch == ' ')
        {
            std::cout << '\n';
            continue;
        }
        std::cout << ch;
    }

    std::cout << "*****************************************************\n";
    return 0;
}