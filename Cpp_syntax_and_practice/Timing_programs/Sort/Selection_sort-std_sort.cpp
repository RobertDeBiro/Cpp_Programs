#include <algorithm> // for std::sort
#include <array>
#include <cstddef> // for std::size_t
#include <iostream>
#include <numeric> // for std::iota
#include <chrono> // for std::chrono functions
#include "../Timer/Timer.hpp"

const int g_arrayElements { 10000 };

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, g_arrayElements> array;
    std::iota(array.rbegin(), array.rend(), 1); // fill the array with values 10000 to 1

    Timer t;

    std::sort(array.begin(), array.end());

    /*
     * Time measurements:
     *  1) 0.0004804 s
     *  2) 0.0004598 s
     *  3) 0.0005865 s
     *  - average = 0.0005089 s
     * 
     * Selection sort: manually vs. 'std::sort' algorithm
     *  - 0.219653 / 0.0005089 = 431.6231
     *
     *  -> 'std::sort' is 431 times faster!!
     */
    std::cout << "Time taken: " << t.elapsed() << " seconds\n";

    std::cout << "*****************************************************\n";
    return 0;
}