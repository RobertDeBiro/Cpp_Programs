#include <iostream>

int arrLength()
{
    std::cout << "Enter fixed-array length: ";
    int length{};
    std::cin >> length;
    return length;
}

void printArray(int* arr, int arr_size)
{
    for(int i = 0; i < arr_size; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

int main()
{
    //********** Array length not known at compile time **********
    //  - according to C++ standard array length must be known at compile time,
    //    but some compilers (like my) can support non-standard feature that enables
    //    unknown array length at compile time

    // 1) Adding length via std::cin
    std::cout << "Enter fixed-array length: ";
    int length1{};
    std::cin >> length1;
    int arr1[length1]{};
    arr1[0] = 1;
    printArray(arr1, length1);

    // 2) Adding length from function return value
    int length2 = arrLength();
    int arr2[length2];
    arr2[1] = 2;
    printArray(arr2, length2);

    // 3) Adding length as runtime constant
    int temp{ 5 };
    // the value of 'length3' isn't known until runtime, so this is a runtime constant,
    // not a compile-time constant!
    const int length3{ temp };
    int arr3[length3]{};
    std::cout << "Runtime constant length:\n";
    printArray(arr3, length3);

    std::cout << "*****************************************************\n";
    return 0;
}