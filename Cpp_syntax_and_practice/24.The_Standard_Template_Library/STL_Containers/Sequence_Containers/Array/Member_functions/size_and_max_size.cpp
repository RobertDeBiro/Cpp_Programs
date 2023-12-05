/*
 * size() ->  size_type
 * 
 * max_size() -> size_type
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/container/array/size
 *  - https://en.cppreference.com/w/cpp/container/array/max_size
 */

#include <iostream>
#include <array>

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 5> varArr;

    std::cout << "varArr size: " << varArr.size() << '\n';
    std::cout << "varArr max_size: " << varArr.max_size() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
