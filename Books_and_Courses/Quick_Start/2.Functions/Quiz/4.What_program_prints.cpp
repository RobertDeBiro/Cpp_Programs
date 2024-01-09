// What value does the following program print?

#include <iostream>

// 1)
// int add(int x, int y, int z)
// {
//     return x + y + z;
// }

// int multiply(int x, int y)
// {
//     return x * y;
// }

// int main()
// {
//     std::cout << multiply(add(5, 10, 15), 2) << std::endl;
//     return 0;
// }

///////////////////////////////////////////////////////////////////

// 2)
void doIt(int x)
{
    int y{ 4 };
    std::cout << "doIt: x = " << x << " y = " << y << '\n';

    x = 3;
    std::cout << "doIt: x = " << x << " y = " << y << '\n';
}

int main()
{
    int x{ 1 };
    int y{ 2 };

    std::cout << "main: x = " << x << " y = " << y << '\n';

    doIt(x);

    std::cout << "main: x = " << x << " y = " << y << '\n';

    return 0;
}