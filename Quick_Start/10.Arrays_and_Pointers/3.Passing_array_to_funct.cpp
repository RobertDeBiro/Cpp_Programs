#include <iostream>

// When receiving array in function, full declaration must be set (so, together with data type and length)
void funct(int arr2[3], int length2)
{
    // When a normal variable is passed by value, C++ copies the value
    // of the argument into the function parameter
    std::cout << "length2 address = " << &length2 << '\n';

    // Because copying large arrays can be very expensive, C++ does not copy an array when an
    // array is passed into a function, instead the actual array is passed
    std::cout << "arr2 address = " << &arr2[0] << '\n';
}

int main()
{
    int length1 = 3;
    int arr1[length1] = {1, 2, 3};

    std::cout << "length1 address = " << &length1 << '\n';
    std::cout << "arr1 address = " << &arr1[0] << '\n';
    
    // When sending array to function, only array name is sent
    funct(arr1, length1);

    return 0;
}