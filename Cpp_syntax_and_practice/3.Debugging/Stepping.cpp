/*
 * LearnCpp
 * Debugging C++ Programs
 * Using an integrated debugger: Stepping
 */

#include <iostream>

void printValue(int value)
{
    std::cout << value << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    int x(5);
    printValue(5);
    printValue(6);
    printValue(7);
    std::cout << "x is " << x << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}
