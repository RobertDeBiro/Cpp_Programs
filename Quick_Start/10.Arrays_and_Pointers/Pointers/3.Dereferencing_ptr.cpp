#include <iostream>

int main()
{
    //* Dereferencing a pointer
    int a = 5;
    int* p = &a;

    std::cout << "a = " << a << '\n';
    std::cout << "*P = " << *p << '\n';

    // Pointer and object has approavh to the same memory, i.e. to the same data
    a = 10;
    std::cout << "*P = " << *p << '\n';
    *p = 20;
    std::cout << "a = " << a << '\n';

    return 0;
}