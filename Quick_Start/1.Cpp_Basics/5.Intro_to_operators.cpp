#include <iostream>

int main()
{
    //* Operators
    /**
     *  - mathematical operation: 3 + 7
     *      - operands: 3, 7
     *      - operator: +
     *  - operator's arity
     *      – the number of operands that an operator takes as input
     *  - three different arities:
     *      1. Unary operators
     *          - act on 1 operand
     *      2. Binary operators
     *          - act on 2 operands
     *      3. Ternary operator
     *          - act on 3 operands
     **/

    //* Unary operators
    int i = 5;
    std::cout << "-i = " << -i << std::endl;     // operator -
    std::cout << "++i = " << ++i << std::endl;   // operator ++
    std::cout << "--i = " << --i << std::endl;   // operator --

    //* Binary operator
    int j = 10;
    int k1 = i + j;                          // operator +
    int k2 = i - j;                          // operator -
    int k3 = i * j;                          // operator -
    int k4 = j / i;                          // operator -
    std::cout << "k1 = " << k1 << std::endl;  // operator <<
    std::cout << "k2 = " << k2 << std::endl;  // operator <<
    std::cout << "k3 = " << k3 << std::endl;  // operator <<
    std::cout << "k4 = " << k4 << std::endl;  // operator <<

    /**
     * * Ternary operator
     *  - there is only one ternary operator and it is called contitional operator ?:
     *?   condition ? expression1 : expression2
     **/
    int a;
    a = (i > j) ? i : j; // If i is bigger then "a = i", else "a = j"
    std::cout << "a = " << a << std::endl;

    return 0;
}