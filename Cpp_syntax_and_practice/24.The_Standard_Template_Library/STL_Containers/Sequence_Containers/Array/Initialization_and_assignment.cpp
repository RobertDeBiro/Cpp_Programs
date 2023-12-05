#include <iostream>
#include <array>

void printArray(const std::array<int, 5>& varArr)
{
    for(int elem : varArr)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    /*
     * Initialization
     */
    std::array<int, 5> varArr1 { 1, 2, 3, 4, 5 }; // 1) Uniform initialization
    std::cout << "Uniform initialization: ";
    printArray(varArr1);

    std::array<int, 5> varArr2 = { 1, 2, 3, 4, 5 }; // 2) Initializer list
    std::cout << "Initializer list: ";
    printArray(varArr2);

    // As of C++17 we are able to initialize std::array without defining type and lenght
    std::array varArr4 = { 1, 2, 3, 4, 5 };
    std::cout << "Initialization ithout data type and length: ";
    printArray(varArr4);
    
    /*
     * Assignment
     *  - it is possible to assign values to array using initializer list
     *    (which is not the case in fixed-width array!)
     *  - after empty declaration array contains garbage
     */
    std::array<int, 5> varArr3;
    std::cout << "Array after empty declaration: ";
    printArray(varArr3);

    varArr3 = {1, 2, 3, 4, 5 };
    std::cout << "Assignment after declaration: ";
    printArray(varArr3);

    std::cout << "*****************************************************\n";
    return 0;
}
