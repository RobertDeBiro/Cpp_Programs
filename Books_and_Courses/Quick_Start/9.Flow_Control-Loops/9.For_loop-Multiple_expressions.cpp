#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x <= y; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}