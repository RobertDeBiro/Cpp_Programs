#include <iostream>

void printArray(int* arr, int arr_size)
{
    for(int i = 0; i < arr_size; i++)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    //********** Array assignment **********
    // Declare array without initialization and later on assign values to it
    int arr1[10];
    arr1[0] = 50;
    int arr1_size = static_cast<int>(std::size(arr1));

    // First element is 50, the rest is some garbage
    std::cout << "Printing first element and garbage: \n";
    printArray(arr1, arr1_size);

    ///////////////////////////////////////////////////////////////////////////

    // We cannot assign values using initializer list
    int arr2[] = { 1, 2, 3 };
    //! arr2[] = { 5, 6, 7 };

    int arr3[3];
    //! arr3[] = { 4, 5, 6 };

    ///////////////////////////////////////////////////////////////////////////

    // Array values can be changed, but not the width
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

    // Assigning values to array when using array as a pointer
    //  - array can be always used as pointer (not only when received inside a funciton),
    //    since it always decays to pointer
    int arr7[3]{ 1, 2, 3 };
    int arr7_size = static_cast<int>(std::size(arr7));
    *(arr7) = 2;
    *(arr7 + 2) = 2;
    printArray(arr7, arr7_size);

    std::cout << "*****************************************************\n";
    return 0;
}