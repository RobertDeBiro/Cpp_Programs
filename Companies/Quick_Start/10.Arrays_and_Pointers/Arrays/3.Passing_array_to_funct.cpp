#include <iostream>

// When receiving array in function, full declaration must be set (so, together with data type and length)
void funct(int arr2[3], int length2)
{
    // When a normal variable is passed by value, C++ copies the value
    // of the argument into the function parameter
    std::cout << "length2 address = " << &length2 << '\n';

    // Because copying large arrays can be very expensive, C++ does not copy an array when an
    // array is passed into a function, instead the actual array is passed
    //  - in other words, address of the first array element is passed and in that way
    //    we can actually approach any of existing elements, since we know address of the first
    std::cout << "arr2[0] = " << arr2[0] << '\n';
    std::cout << "arr2[1] = " << arr2[1] << '\n';
    std::cout << "arr2[2] = " << arr2[2] << '\n';
    std::cout << "arr2 address = " << &arr2[0] << '\n';
}

int main()
{
    int length1 = 3;
    int arr1[length1] = {1, 2, 3};

    std::cout << "length1 address = " << &length1 << '\n';
    std::cout << "arr1 address = " << &arr1[0] << '\n';
    
    funct(arr1, length1);

    return 0;
}