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

    //* Take fixed array from 'std::array' container
    int* arr{ varArr.data() };

    // Print array
    for(int i = 0; i < static_cast<int>(varArr.size()); i++)
        std::cout << *(arr + i) << ' ';

    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
