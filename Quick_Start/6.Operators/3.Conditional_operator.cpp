//* Conditional operator
/**
 *  - only ternary operator in C++ programmin language
 *      - it takes 3 operands
 *  - syntax:
 *?     condition ? variable_1 : variable_2
 *  - example:
 *?     z = (x > y) ? x : y 
 *  - variables data types must match, or second variable data type must be convertible to the data
 *    type of the first varaible 
 **/

#include <iostream>

int main()
{
    int x, y;
    std::cout << "Insert x: ";
    std::cin >> x;
    std::cout << "Insert y: ";
    std::cin >> y;

    int z = (x > y) ? x : y;
    std::cout << "z = " << z << '\n';

    // z will be always equal to bigger of x and y variables
    z = (x == y) ? x : ++x;
    std::cout << "z = " << z << '\n';

    return 0;
}