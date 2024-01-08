/*
 * fmtflags setf( fmtflags flags )
 *  - set the flag
 * 
 * fmtflags setf( fmtflags flags, fmtflags mask )
 *  - mask = format group
 * 
 * void unsetf( fmtflags flags )
 *  - unset the flag
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/io/ios_base/setf
 *  - https://en.cppreference.com/w/cpp/io/ios_base/unsetf
 */

#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    //* 'std::ios::showpos'
    //  - print a '+' sign in front of positive numbers
    std::cout.setf(std::ios::showpos); // turn on the 'std::ios::showpos' flag
    std::cout << 27 << '\n';

    std::cout.unsetf(std::ios::showpos); // turn off the std::ios::showpos flag
    std::cout << 27 << '\n';

    std::cout << "------------------------------------\n";

    //* 'std::ios::uppercase'
    //  - print scientific notation symbol 'e' in upper case
    std::cout << 1234567.89f << '\n';
    std::cout.setf(std::ios::uppercase);
    std::cout << 1234567.89f << '\n';

    std::cout << "------------------------------------\n";

    //* 'std::ios::hex'
    //  - print number in hexadecimal format
    //  - belongs to 'std::ios::basefield' format group
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 27 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}