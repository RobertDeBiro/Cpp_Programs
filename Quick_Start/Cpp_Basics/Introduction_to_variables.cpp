#include <iostream>

int main()
{
    std::cout << 2 + 3 << std::endl;
    std::cout << 5 /*multiply with some object*/ << std::endl;

    // You all had mathematics in school and there very often when solving some tasks
    // you needed to use some variables, which were frequently named as x or y.
    // So, let's do it that way and name our variables x and y.
    // x = 2;
    // y = 3;

    // TODO - explain declaration, definition, instantiation and data types
    // TODO - variable initialization and assignment

    int x = 1;
    int y( 2 );
    int z1{ 3 };
    int z2{ }; // zero initialization

    int a, b;
    int c = 3, d{ 4 };

    x = 4;

    // Uninitialized variable - undefined value
    std::cout << a << std::endl;

    return 0;
}