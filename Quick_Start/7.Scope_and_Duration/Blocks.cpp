/**
 * * Compound statements (blocks)
 *      - group of zero or more statements that is treated by the compiler as if it were a single statement
 *      - begins with a { symbol and ends with a } symbol
 *      - blocks can be nested
 **/

#include <iostream>

int add(int x, int y)
{ // block
    return x + y;
} // end block

int main()
{ // outer block

    // multiple statements
    int value {};

    { // inner/nested block
        add(5, 6);
    } // end inner/nested block

    return 0;

} // end outer block