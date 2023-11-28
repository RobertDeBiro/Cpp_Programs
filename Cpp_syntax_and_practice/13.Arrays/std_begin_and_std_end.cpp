/*
 * LearnCpp
 * Arrays, Strings, and Dynamic Allocation
 * Pointer arithmetic and array indexing
 */

// This program implements 'find' function which finds element in array,
// but there is already implemented 'find' function inside algorithm library 
// which finds element and returns iterator to that element.

#include <iostream>
#include <iterator> // std::begin, std::end

int* find(int *array, int *arrayEnd, int value)
{
    for( ; array != arrayEnd; array++)
    {
        if(*array == value)
            return array;
    }

    return arrayEnd;
}

int main()
{
    std::cout << "*****************************************************\n";

    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };

    // Search for the first element with value 20.
    int* found{ find(std::begin(arr), std::end(arr), 20) };

    // If an element with value 20 was found, print it.
    if (found != std::end(arr))
    {
        std::cout << "Element found: " << *found << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
