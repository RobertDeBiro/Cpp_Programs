/*
 * at(size_type pos) -> reference
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/array/at
 *  - https://en.cppreference.com/w/cpp/container/array/operator_at
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

    /*
     * We can fetch element in 2 ways:
     *  1) [index]
     *  2) .at(index)
     */
    std::cout << "Fetching element using []: " << varArr[1]
              << " and .at(): " << varArr.at(3) << '\n';

    try
    {
        varArr.at(8) = 10;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Exception \"out_of_range\" is thrown!: ";
        std::cerr << e.what() << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
