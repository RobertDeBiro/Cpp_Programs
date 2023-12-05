/*
 * fill(const T& value) -> void
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/array/fill
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

    std::array<int, 5> varArr { 1, 2, 3, 4, 5 };
    std::cout << "Initial array: ";
    printArray(varArr);

    varArr.fill(5);
    std::cout << "Fill already filled array: ";
    printArray(varArr);

    std::array<int, 5> varArr2;
    varArr2.fill(3);
    std::cout << "Fill empty array(): ";
    printArray(varArr2);

    std::cout << "*****************************************************\n";
    return 0;
}
