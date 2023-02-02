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
    std::cout << "*****************************************************\n";

    /*
     * Array can be declared, without initialization
     */
    int arr1[10];
    arr1[0] = 50;
    int arr1_size = static_cast<int>(std::size(arr1));

    // First element is 50, the rest is some garbage
    std::cout << "Printing first element and garbage: \n";
    printArray(arr1, arr1_size);
    

    /*
     * Compiler error: we cannot assign values using initializer list on object that is 
     * already declared or initialized
     */
    int arr2[] = { 1, 2, 3 };
    // arr2[] = { 5, 6, 7 };

    // int arr3[3];
    // arr3[] = { 4, 5, 6 };


    /*
     * Array values can be changed, but not the width
     */
    std::cout << "Printing array: \n";
    for(auto elem : arr2)
        std::cout << elem << " ";
    std::cout << '\n';

    arr2[0] = 3;
    arr2[2] = 1;
    
    std::cout << "Printing updated array: \n";
    for(auto elem : arr2)
        std::cout << elem << " ";
    std::cout << '\n';


    /*
     * Array length not known at compile time:
     *  - according to C++ standard array length must be known at compile time,
     *    but some compilers (like my) can support non-standard feature that enables
     *    unknown array length at compile time
     */
    // 1) Adding length via std::cin
    std::cout << "Enter fixed-array length: ";
    int length1{};
    std::cin >> length1;
    int arr4[length1]{};
    arr4[0] = 1;
    printArray(arr4, length1);

    // 2) Adding length from function return value
    int length2 = arrLength();
    int arr5[length2];
    arr5[1] = 2;
    printArray(arr5, length2);

    // 3) Adding length as runtime constant
    int temp{ 5 };
    // the value of length2 isn't known until runtime, so this is a runtime constant, not a compile-time constant!
    const int length3{ temp };
    int arr6[length3]{};
    std::cout << "Runtime constant length:\n";
    printArray(arr6, length3);

    std::cout << "*****************************************************\n";
    return 0;
}