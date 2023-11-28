/*
 * append
    - append characters to string
    - cppreference: https://en.cppreference.com/w/cpp/string/basic_string/append
 */

#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    // Concatenate using append function
    std::string concat{"Hello "};
    concat.append("Zagreb!");
    std::cout << "Concatenated string: " << concat << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
