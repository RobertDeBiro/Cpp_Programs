#include <iostream>

template <typename T>
void f(T& i)
{
    std::cout << 1 << std::endl;
}

template <>
void f(const int& i)
{
    std::cout << 2 << std::endl;
}

int main()
{
    int i = 8;
    const int j = 8;
    
    f(i); // Prints 1 because we didn't send variable of "const int" type
    f(j); // Prints 2 because we sent variable of "const int" type

    return 0;
}
