/*
 * LearnCpp
 * Arrays, Strings, and Dynamic Allocation
 * An introduction to std::array
 */

#include <array>
#include <cstddef>
#include <iostream>

// printArray is a template function that uses both:
//  - type parameter (size)
//  - non-type parameter (T)
template <typename T, std::size_t size>
void printArray(const std::array<T, size>& myArray)
{
    for (auto element : myArray)
        std::cout << element << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 5> myArray5{ 9, 7, 5, 3, 1 };
    printArray(myArray5);

    std::array<double, 7> myArray7{ 9.0, 7.2, 5.4, 3.6, 1.8, 1.2, 0.7 };
    printArray(myArray7);

    std::cout << "*****************************************************\n";
    return 0;
}