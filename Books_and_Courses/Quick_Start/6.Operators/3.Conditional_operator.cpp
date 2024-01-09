//* Conditional operator
/**
 *  - only ternary operator in C++ programming language
 *      - it takes 3 operands
 *  - syntax:
 *?     condition ? variable_1 : variable_2
 **/

#include <iostream>

int main()
{
    int x, y;
    std::cout << "Insert x: ";
    std::cin >> x;
    std::cout << "Insert y: "2;
    std::cin >> y;

    // z will be always equal to bigger of x and y variables, or it will be equal to them
    int z = (x > y) ? x : y;
    std::cout << "z = " << z << '\n';

    return 0;
}