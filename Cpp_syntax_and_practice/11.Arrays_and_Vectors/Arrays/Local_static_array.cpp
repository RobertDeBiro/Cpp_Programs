#include <iostream>

// In order to return n local array from function, we need to initialize it as a
// static variable, so that array is not deleted at the end of the function
//  - static array variable for initialization requires compile time constant as its length
int* generateArray(/*int length*/)
{
    static int arr[5];
    //static int arr[length];
    std::cout << "Fulfill array: ";
    for(int i = 0; i < 5; i++)
        std::cin >> arr[i];
    return arr;
}

int main()
{
    std::cout << "*****************************************************\n";

    int length{ 5 };
    int* arr{ generateArray() };

    std::cout << "Array in main(): ";
    for(int i = 0; i < length; i++)
        std::cout << *(arr + i) << ' ';
    std::cout << '\n';
    
    std::cout << "*****************************************************\n";
    return 0;
}