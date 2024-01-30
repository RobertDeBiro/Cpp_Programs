#include <iostream>

int main()
{
    //* Prefix increment operator
    int x = 1;
    int y = ++x;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    std::cout << "-------------------------------\n";

    //* Postfix  increment operator
    int z = 1;
    int k = z++;
    std::cout << "z = " << z << std::endl;
    std::cout << "k = " << k << std::endl;

    return 0;
}