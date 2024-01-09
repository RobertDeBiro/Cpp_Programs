/*
 * References:
 *  - https://en.cppreference.com/w/cpp/string/byte/toupper
 *  - https://en.cppreference.com/w/cpp/string/byte/tolower
 */

#include <iostream>
#include <cctype>

int main()
{
    std::cout << "*****************************************************\n";

    std::string word{ "Hello World!" };

    for(auto& c : word)
    {
        c = std::toupper(c);
    }
    std::cout << word << '\n';

    for(auto& c : word)
    {
        c = std::tolower(c);
    }
    std::cout << word << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}