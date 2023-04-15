#include <iostream>

int main()
{
    // Prefix increment operator
    int x = 1;
    int y = ++x;
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    // Postfix  increment operator
    int z = 5;
    int k = z++;
    std::cout << z << std::endl;
    std::cout << k << std::endl;

    return 0;
}