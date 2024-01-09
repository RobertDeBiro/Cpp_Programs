//* Arithmetic operators
/**
 *  1. Unary operators
 *  2. Binary operators
 *  3. Arithmetic assignment operators 
 **/

#include <iostream>
#include <cmath>

int main()
{
    int x = 5;
    std::cout << "x = " << x << '\n';

    //* Unary operators
    x = +x;
    std::cout << "+x = " << x << '\n';

    x = -x;
    std::cout << "-x = " << x << '\n';

    std::cout << "------------------------------------------\n";

    //////////////////////////////////////////////////////////

    //* Binary operators
    int d1 = 9;
    int d2 = 3;
    int d3 = 4;

    // Integer division
    std::cout << "9 / 3 = " << d1 / d2 << '\n';
    std::cout << "9 / 4 = " << d1 / d3 << '\n';

    // Modulus (Remainder)
    std::cout << "9 % 4 = " << d1 % d3 << '\n';

    // Floating and integer division
    float f1 = 5.5f;
    std::cout << "5.5 / 4 = " << f1 / d3 << '\n';

    // Exponentiation
    std::cout << "9 ^ 3 = " << std::pow(9, 3) << '\n';

    std::cout << "------------------------------------------\n";

    //////////////////////////////////////////////////////////

    //* Arithmetic assignment operators
    int a = 5;
    std::cout << "a = " << a << '\n';

    a = a + 5;
    std::cout << "a = " << a << '\n';
    
    a += 5;
    std::cout << "a = " << a << '\n';

    return 0;
}