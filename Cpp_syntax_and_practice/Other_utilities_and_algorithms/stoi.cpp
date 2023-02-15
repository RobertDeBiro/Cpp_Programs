/*
 *  stoi( const std::string& str, std::size_t* pos = nullptr, int base = 10 ); -> int
 *
 *  - included in <string>
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/string/basic_string/stol
 */

#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    std::string s{ "45" };
    
    // ERROR: We cannot implicitly convert string into integer
    //int i{ s };

    int i{ std::stoi(s) };
    std::cout << "i = " << i << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}