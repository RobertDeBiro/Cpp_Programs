#include <array>
#include <chrono> // std::chrono
#include <cstddef> // std::size_t
#include <iostream>
#include <numeric> // std::iota
#include "../Timer/Timer.hpp"

const int g_arrayElements { 10000 };

void sortArray(std::array<int, g_arrayElements>& array)
{
    // Step through each element of the array
    // (except the last one, which will already be sorted by the time we get there)
    for (std::size_t startIndex{ 0 }; startIndex < (g_arrayElements - 1); ++startIndex)
    {
        // smallestIndex is the index of the smallest element we’ve encountered this iteration
        // Start by assuming the smallest element is the first element of this iteration
        std::size_t smallestIndex{ startIndex };

        // Then look for a smaller element in the rest of the array
        for (std::size_t currentIndex{ startIndex + 1 }; currentIndex < g_arrayElements; ++currentIndex)
        {
            // If we've found an element that is smaller than our previously found smallest
            if (array[currentIndex] < array[smallestIndex])
            {
                // then keep track of it
                smallestIndex = currentIndex;
            }
        }

        // smallestIndex is now the smallest element in the remaining array
        // swap our start element with our smallest element (this sorts it into the correct place)
        std::swap(array[startIndex], array[smallestIndex]);
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, g_arrayElements> array;
    std::iota(array.rbegin(), array.rend(), 1); // fill the array with values 10000 to 1

    Timer t;

    sortArray(array);

    /*
     * Time measurements:
     *  1) 0.226205 s
     *  2) 0.212281 s
     *  3) 0.220473 s
     *  - average = 0.219653 s
     *
     * Selection sort: manually vs. std::sort algorithm
     *  - 0.219653 / 0.0005089 = 431.6231
     *
     *  -> std::sort is 431 times faster!!
     */
    std::cout << "Time taken: " << t.elapsed() << " seconds\n";

    std::cout << "*****************************************************\n";
    return 0;
}