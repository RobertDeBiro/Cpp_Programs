// State whether program will fail to compile, fail to link, fail both, or compile and link successfully

#include <iostream>

// 1)
// int add(int x, int y);

// int main()
// {
//     std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
//     return 0;
// }

// int add(int x, int y)
// {
//     return x + y;
// }

/////////////////////////////////////////////////////////////////////////////

// 2)
// int add(int x, int y);

// int main()
// {
//     std::cout << "3 + 4 = " << add(3, 4) << '\n';
//     return 0;
// }

// int add(int x, int y, int z)
// {
//     return x + y + z;
// }

/////////////////////////////////////////////////////////////////////////////

// 3)
// int add(int x, int y, int z);

// int main()
// {
//     std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
//     return 0;
// }

// int add(int x, int y, int z)
// {
//     return x + y + z;
// }

/////////////////////////////////////////////////////////////////////////////

// 4)
int add(int x, int y, int z);

int main()
{
    std::cout << "3 + 4 + 5 = " << add(3, 4, 5) << '\n';
    return 0;
}

int add(int x, int y, char z)
{
    return x + y + z;
}