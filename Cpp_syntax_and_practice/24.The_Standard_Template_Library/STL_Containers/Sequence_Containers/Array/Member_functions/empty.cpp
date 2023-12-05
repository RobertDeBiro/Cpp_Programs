/*
 * empty() -> bool
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/array/empty
 */

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
    std::cout << std::boolalpha;

    std::array<int, 5> varArr1;
    std::cout << "Non-initialized array: ";
    printArray(varArr1);
    std::cout << "Non-initialized array is empty: " << varArr1.empty() << '\n';

    std::array<int, 0> varArr2;
    // printArray(varArr2); // ERROR: cannot print array with length 0
    std::cout << "Array with length 0 is empty: " << varArr2.empty() << '\n';

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}
