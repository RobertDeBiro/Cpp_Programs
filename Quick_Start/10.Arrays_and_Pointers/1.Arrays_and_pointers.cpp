#include <iostream>

void funct(int* arr2, int length2)
{
    // Print first array element
    std::cout << "*arr2 = " << *arr2 << '\n';

    // Value added to pointer represents number of addresses
    //  - in other words, addition of number one means to go to one address after
    //  - we can also decrease address
    std::cout << "*(arr2 + 1) = " << *(arr2 + 1) << '\n';
    std::cout << "*(arr2 + 2) = " << *(arr2 + 2) << '\n';

}

int main()
{
    int length1 = 3;
    int arr1[length1] = {1, 2, 3};

    std::cout << "length1 address = " << &length1 << '\n';
    std::cout << "arr1 address = " << &arr1[0] << '\n';
    
    // When sending array to function, address of the first array element is sent
    //  - array decays - it is implicitly converted to pointer of type int* that points to the first element of the array
    funct(arr1, length1);

    return 0;
}