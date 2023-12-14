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

    std::cout << "First element of the array using front = " << varArr.front() << '\n';
    std::cout << "Last element of the array using back = " << varArr.back() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
