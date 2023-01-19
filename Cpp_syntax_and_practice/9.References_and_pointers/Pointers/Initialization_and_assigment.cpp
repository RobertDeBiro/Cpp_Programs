#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    // It is valid to create a pointer without initializing it
    //   - but then the pointer will contain the garbage
    //   - dereferencing that pointer will cause Segmentation fault Exception
    int *ptr1;
    std::cout << "Uninitialized pointer, ptr1 = " << ptr1 << std::endl;
    //std::cout << "Dereferencing uninitialized pointer, *ptr1 = " << *ptr1 << std::endl;

    // Dereferencing nullptr, even initialized, causes Segmentation fault Exception
    int* ptr2{ nullptr };
    std::cout << "Pointer initialized with nullptr, ptr2 = " << ptr2 << std::endl;
    std::cout << "Dereferencing null pointer, *ptr2 = " << *ptr2 << std::endl;

    std::cout << "*****************************************************\n";
    return 0;
}