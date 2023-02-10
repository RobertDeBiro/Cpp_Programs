/*
 * abs( int n ) -> int
 *
 *  - included in <cmath>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/numeric/math/abs
 */

#include <iostream>
#include <cmath>

int main()
{
    std::cout << "*****************************************************\n";

    int a = 5;
    int b = -6;

    std::cout << "|a + b| = " << std::abs(a + b) << '\n';
    std::cout << "|a - b| = " << std::abs(a - b) << '\n';
    std::cout << "|b - a| = " << std::abs(b - a) << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}