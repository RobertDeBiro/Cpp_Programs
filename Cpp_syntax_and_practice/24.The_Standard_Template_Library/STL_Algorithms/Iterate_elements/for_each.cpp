/*
 * std::for_each(InputIt first, InputIt last, callable object) -> callable object
 *  - callable object that is returned is actually the same one that is sent to 'for_each()' function
 *  
 * - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/for_each
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector nums{ 1, 2, 3, 4 };

    // For each 'nums' element, print its value
    auto callObj = std::for_each(std::begin(nums), std::end(nums),
                                 [](int element) { 
                                     std::cout << "Number: " << element << '\n'; });
    std::cout << "Callable object after returning: ";
    callObj(5);

    std::cout << "*****************************************************\n";
    return 0;
}
