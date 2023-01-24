#include <iostream>

int arrLength()
{
    std::cout << "Enter fixed-array length: ";
    int length{};
    std::cin >> length;
    return length;
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
    for(int i = 0; i < arr1_size; i++)
        std::cout << arr1[i] << ' ';
    std::cout << '\n';
    

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
     *  - LearnCpp says that following examples should trigger compiler error because
     *    array length must be known at compile time
     */
    std::cout << "Enter fixed-array length: ";
    int length{};
    std::cin >> length;
    int arr4[length]{};
    arr4[0] = 1;
    std::cout << arr4[0] << '\n';

    int arr5[arrLength()];
    arr5[0] = 2;
    std::cout << arr5[0] << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}