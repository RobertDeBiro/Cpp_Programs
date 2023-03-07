/*
 * C++ Primer
 * Exercises section 3.2.3
 *  - Exercise 3.10
 */

#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::cout << "*****************************************************\n";

    std::string s{ "Hello, how are you today \"user\" ?? - I am fine (pretty fine)!" };
    std::cout << "Initial string:\n" << s << '\n';

    std::cout << "-----------------------------------------------------------------\n";

    std::cout << "String without punctation:\n";
    for(const auto& c : s)
    {
        if(ispunct(c))
            continue;
        std::cout << c;
    }
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}