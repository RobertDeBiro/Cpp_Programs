/*
 * std::stoi:
    - converts string to int
    - cppreference: https://en.cppreference.com/w/cpp/string/basic_string/stol
    
 * std::to_string:
    - converts int to string
    - cppreference: https://en.cppreference.com/w/cpp/string/basic_string/to_string
*/

#include <iostream>
#include <string> // stoi, to_string

int main()
{
    std::cout << "*****************************************************\n";

    std::string s{ "45" };
    int i{ 54 };
    
    // ERROR: We cannot implicitly convert string into integer
    //!int i_s2{ s };

    //********** Convert string to integer **********
    int i_s{ std::stoi(s) };
    std::cout << "i_s = " << i_s << '\n';


    //********** Convert integer to string **********
    std::string s_i{ std::to_string(i) };
    std::cout << "s_i = " << s_i << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}