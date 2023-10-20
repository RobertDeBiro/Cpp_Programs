#include <iostream>

int main()
{
    int x = 5; // binary: 0101
    int y = 10; // binary 1010
    int z{ x | y}; // result: 1111

    std::cout << "z = " << z << '\n';

    return 0;
}