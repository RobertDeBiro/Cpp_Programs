#include <iostream>
#include "Adder/adder.h"

int main()
{
    std::cout << "Hello CMake!" << std::endl;
    std::cout << "Adder result = " << add(17.3, 16.5) << std::endl;

    return 0;
}