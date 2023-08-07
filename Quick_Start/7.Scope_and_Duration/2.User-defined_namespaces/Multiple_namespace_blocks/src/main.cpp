#include <iostream>
#include "../inc/Int_division.hpp"

int main()
{
    int x = 8;
    int y = 3;
    std::cout << "Int division: " << x << " / " << y << " = " << int_div::divide(x, y) << '\n';

    return 0;
}