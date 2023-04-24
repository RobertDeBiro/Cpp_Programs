#include <iostream>

//! SYNTAX ERROR - there is no add function()

// int add(int x, int y);

// It is not necessary to put parameter names, only data types
int add(int, int);

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // compile error
    return 0;
}