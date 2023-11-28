#include <iostream>

//********** Return local static array from function **********
// In order to return local array from function, we need to initialize it as a
// static variable, so that array is not deleted at the end of the function
int* generateArray_subIdent(/* const int length */)
{
    // static array variable for initialization requires compile time constant as its length
    //  - compile time constant can be variable or literal constant
    //! static int arr[length];
    const int length{ 3 };
    static int arr[length]; // length value used for static array must be 'const'
    std::cout << "Fulfill array with " << length << " number of elements: ";
    for(int i = 0; i < length; i++)
        std::cin >> arr[i];
    return arr;
}

int* generateArray_subLiteral()
{
    // Literal '3' is also a constant
    static int arr[3];
    std::cout << "Fulfill array with 3 elements: ";
    for(int i = 0; i < 3; i++)
        std::cin >> arr[i];
    return arr;
}

int main()
{
    std::cout << "*****************************************************\n";

    const int length{ 3 };
    int* arr1{ generateArray_subIdent(/* length */) };

    std::cout << "1. Array in main(): ";
    for(int i = 0; i < length; i++)
        std::cout << *(arr1 + i) << ' ';
    std::cout << '\n';

    ////////////////////////////////////////////////////////////////////

    int* arr2{ generateArray_subLiteral() };

    std::cout << "2. Array in main(): ";
    for(int i = 0; i < 3; i++)
        std::cout << *(arr2 + i) << ' ';
    std::cout << '\n';
    
    std::cout << "*****************************************************\n";
    return 0;
}