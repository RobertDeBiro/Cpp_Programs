// What does the following program print?

#include <iostream>

void funct2()
{
    std::cout << "In funct2()" << std::endl;
}

void funct1()
{
    std::cout << "In funct1()" << std::endl;
    funct2();
}

int main()
{
    std::cout << "Starting main()" << std::endl;

    funct1();
    funct2();

    std::cout << "Ending main()" << std::endl;

    return 0;
}