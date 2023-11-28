/*
 * LearnCpp
 * Arrays, Strings, and Dynamic Allocation
 * Sorting an array using selection sort
 */
// Bubble sort works by comparing adjacent pairs of elements, and swapping
// them if the criteria is met, so that elements "bubble" to the end of the array
// - every iteration the biggest element should be at the end of array

#include <iostream>
#include <utility> // std::swap

int main()
{
    std::cout << "*****************************************************\n";

    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    int arrayLength{ static_cast<int>(std::size(array)) };

    // Print unsorted array
    std::cout << "Array before sorting:\n";
    for(int counter = 0; counter < arrayLength; counter++)
    {
        std::cout << array[counter] << " ";
    }
    std::cout << '\n' << '\n';

    // Object 'needSort' will be used in order to reduce number of sorting loops i.e.
    // to avoid unnecessary loops
    bool needSort{};
    int numberOfIterations{};
    do
    {
        needSort = false;
        for(int counter = 1; counter < (arrayLength - numberOfIterations); counter++)
        {
            // If we go through all array and we don't find some element to sort,
            // means everything is already sorted and we can finish with looping
            if(array[counter] < array[counter - 1])
            {
                std::swap(array[counter], array[counter - 1]);
                needSort = true;
            }
        }
        // Print steps of array sorting
        if (needSort)
        {
            for(int counter = 0; counter < arrayLength; counter++)
            {
                std::cout << array[counter] << " ";
            }
            std::cout << '\n';
        }
        // 'numberOfIterations' indicates how many times we went through array
        // until we realized there is no more need for sorting
        numberOfIterations++;
    } while(needSort);

    std::cout << "Early termination on iteration " << numberOfIterations << '\n' << '\n';

    // Print sorted array
    std::cout << "Sorted array:\n";
    for(int counter = 0; counter < arrayLength; counter++)
    {
        std::cout << array[counter] << " ";
    }
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
