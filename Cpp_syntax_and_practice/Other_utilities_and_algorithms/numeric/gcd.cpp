/*
 * References:
 *  - https://en.cppreference.com/w/cpp/numeric/gcd
 */

#include <iostream>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    int nominator{ 12 };
    int denominator{ 8 };

    // '12' and '8' has two common divisors: '4' and '2'
    //  - hence, the greatest common divisor (gcd) should be '4'
    std::cout << "Greatest common divisor of " 
              << nominator << " and " << denominator << " is " << std::gcd(nominator, denominator) << '\n';
    
    std::cout << "*****************************************************\n";
    return 0;
}