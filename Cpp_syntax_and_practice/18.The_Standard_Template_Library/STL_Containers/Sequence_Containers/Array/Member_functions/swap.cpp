/*
 * swap( array& other ) -> void
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/array/swap
 */

#include <iostream>
#include <array>

void printArray(const std::array<int, 3>& varArr)
{
    for(int elem : varArr)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 3> varArr1 { 1, 2, 3 };
    std::array<int, 3> varArr2 { 4, 5, 6 };
    
    std::cout << "Arrays before swap: \n";

    printArray(varArr1);
    printArray(varArr2);

    std::cout << "Arrays after swap: \n";

    varArr1.swap(varArr2);

    printArray(varArr1);
    printArray(varArr2);

    std::cout << "*****************************************************\n";
    return 0;
}
