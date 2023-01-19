#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Array can be declared, without initialization
     */
    int ar[10];
    ar[0] = 50;
    int ar_size = static_cast<int>(std::size(ar));

    // First element is 50, the rest is some garbage
    std::cout << "Printing first element and garbage: \n";
    for(int i = 0; i < ar_size; i++)
        std::cout << ar[i] << ' ';
    std::cout << '\n';
    

    /*
     * Compiler error: we cannot assign values using initializer list on object that is 
     * already declared or initialized
     */
    int numbers[] = { 1, 2, 3 };
    // numbers[] = { 5, 6, 7 };
    // int numbers_2[3];
    // numbers_2[] = { 4, 5, 6 };

    /*
     * LearnCpp says that this should be compiler error because
       array length must be known at compile time, but here I don't obtain an error
     */
    std::cout << "Enter fixed-array length: ";
    int length{};
    std::cin >> length;
    int numbers_3[length]{};
    numbers_3[0] = 1;
    std::cout << numbers_3[0] << '\n';

    /*
     * Array values can be changed, but not the width
     */
    std::cout << "Printing array: \n";
    for(auto elem : numbers)
        std::cout << elem << " ";
    std::cout << '\n';

    numbers[0] = 3;
    numbers[2] = 1;
    
    std::cout << "Printing updated array: \n";
    for(auto elem : numbers)
        std::cout << elem << " ";
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}