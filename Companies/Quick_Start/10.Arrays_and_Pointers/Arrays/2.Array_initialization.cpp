#include <iostream>

int main()
{
    //* Initialize array with initializer list
    int prime[5] { 2, 3, 5, 7, 11 };
    std::cout << "prime[0]:\t value = " << prime[0] << '\n';
    std::cout << "prime[1]:\t value = " << prime[1] << '\n';
    std::cout << "prime[2]:\t value = " << prime[2] << '\n';
    std::cout << "prime[3]:\t value = " << prime[3] << '\n';
    std::cout << "prime[4]:\t value = " << prime[4] << '\n';

    // Non-initialized elements will be initialized to zero
    int arr1[3] = { 1, 2 };
    std::cout << "arr1[0]:\t value = " << arr1[0] << '\n';
    std::cout << "arr1[1]:\t value = " << arr1[1] << '\n';
    std::cout << "arr1[2]:\t value = " << arr1[2] << '\n';

    // More elements in initializer list than array can hold results with error
    //int arr2[3] = { 1, 2, 3, 4, 5 };

    // We cannot assign values by using initializer list
    int arr[3];
    // arr[3] = {1, 2, 3};

    // When using initializer list length can be ommited
    int arr2[] { 1, 2, 3, 4 };

    return 0;
}