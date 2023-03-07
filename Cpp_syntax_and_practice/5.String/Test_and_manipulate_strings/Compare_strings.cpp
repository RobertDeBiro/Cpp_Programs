/*
 * C++ Primer
 * Exercise Section 3.2.2
 *  - Exercise 3.4
 */
#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::string s1, s2;

    std::getline(std::cin >> std::ws, s1);
    std::getline(std::cin >> std::ws, s2);

    std::cout << "---------------------------------\n";

    if(s1 == s2)
        std::cout << "Strings are equal!\n";
    else if(s1 > s2)
        std::cout << s1 << " is larger!\n";
    else
        std::cout << s2 << " is larger!\n";
    
    std::cout << "---------------------------------\n";

    if(s1.length() == s2.length())
        std::cout << "Strings have the same length!\n";
    else if(s1 > s2)
        std::cout << s1 << " is longer!\n";
    else
        std::cout << s2 << " is longer!\n";

    std::cout << "*****************************************************\n";
    return 0;
}