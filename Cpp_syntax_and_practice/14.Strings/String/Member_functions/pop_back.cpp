/*
 * pop_back
    - removes the last character
    - cppreference: https://en.cppreference.com/w/cpp/string/basic_string
 */

#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::string str{"Hello!"};
    str.pop_back();
    std::cout << "Result: " << str << '\n';

    //! It is not possible to 'pop_back' empty string
    //!std::string empty_str{};
    //!empty_str.pop_back;

    std::cout << "*****************************************************\n";
    return 0;
}
