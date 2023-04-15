// What’s wrong with this program fragment?

#include <iostream>

// 1)
// void divide(int x, int y)
// {
//     return x / y;
// }

// int main()
// {
//     std::cout << divide(8, 2) << std::endl;
//     return 0;
// }

//////////////////////////////////////////////////////////////////////
// What two things are wrong with this program fragment?

// 2)
int multiply(int x, int y)
{
    int product{ x * y };
}

int main()
{
    std::cout << multiply(4) << std::endl;
    return 0;
}