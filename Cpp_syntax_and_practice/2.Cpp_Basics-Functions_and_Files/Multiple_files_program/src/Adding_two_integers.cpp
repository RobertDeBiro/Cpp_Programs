// LearnCpp
// C++ Basics - Functions and Files
// Summary and quiz

#include <iostream>
#include "../inc/io.hpp"

int main()
{
    std::cout << "*****************************************************\n";

    int x{ getInteger() };
    int y{ getInteger() };
    int sum{ add(x, y) };
    std::cout << x << " + " << y << " = " << sum << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
