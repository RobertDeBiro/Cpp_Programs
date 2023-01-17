#include <iostream>

int main()
{
    std::cout << "Checking if it is valid to create pointer to const without initializing it:\n";
    const int *ptr;
    std::cout << "OK, but ptr is garbage = " << ptr << std::endl;

    int var1 = 5;
    ptr = &var1;
    std::cout << "Assigned ptr = " << ptr << std::endl;

    int var2 = 10;
    ptr = &var2;
    std::cout << "Updated ptr = " << ptr << std::endl;

    return 0;
}