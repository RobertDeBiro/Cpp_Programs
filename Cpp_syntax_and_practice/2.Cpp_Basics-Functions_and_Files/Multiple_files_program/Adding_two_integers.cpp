// LearnCpp
// 2. C++ Basics - Functions and Files
// Summary and quiz

#include <iostream>
#include "io.hpp"

int main()
{
    int x{ getInteger() };
    int y{ getInteger() };
    int sum{ add(x, y) };
    std::cout << x << " + " << y << " = " << sum << '\n';
    return 0;
}
