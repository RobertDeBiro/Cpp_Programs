/**
 * * Void
 *      - means "no type"
 *      - three different contexts in which is used:
 *          1. For functions that do not return a value
 *          2. For functions that do not take parameters
 *          3. Void pointers
 **/

#include <iostream>

void printHello(void)
{
    std::cout << "Hello" << std::endl;
}

int main()
{
    printHello();

    return 0;
}