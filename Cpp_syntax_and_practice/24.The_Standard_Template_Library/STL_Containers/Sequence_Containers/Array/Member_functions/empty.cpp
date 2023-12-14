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

    //* Non-initialized array of length 5
    std::array<int, 5> varArr1;
    std::cout << "Non-initialized array: ";
    printArray(varArr1);
    std::cout << "Non-initialized array is empty: " << varArr1.empty() << '\n';

    //* Non-initialized array of length 0
    std::array<int, 0> varArr2;
    // It is not possible to print print array with length 0
    //! printArray(varArr2);
    std::cout << "Array with length 0 is empty: " << varArr2.empty() << '\n';

    std::cout << std::noboolalpha;
    std::cout << "*****************************************************\n";
    return 0;
}
