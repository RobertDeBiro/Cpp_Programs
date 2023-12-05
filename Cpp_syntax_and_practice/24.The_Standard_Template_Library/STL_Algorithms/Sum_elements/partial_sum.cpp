/*
 * partial_sum( InputIt first, InputIt last, OutputIt d_first ) -> OutputIt
 * 
 *  - included in <numeric>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/partial_sum
 */

#include <iostream>
#include <vector>
#include <array>
#include <numeric>

int main()
{
    std::cout << "*****************************************************\n";

    std::array<int, 5> arr1{ 1, 2, 3, 4, 5 };

    std::partial_sum(arr1.begin(), arr1.end(), arr1.begin());
    for(const auto elem : arr1)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::cout << "----------------------------------\n";

    std::vector<int> varVect{1, 2, 3, 4, 5};

    // Partially sum vector elements and each sum put in the new place at the end of the vector
    //  - in order to properly do that we needed to reserve place for the sum elements
    varVect.reserve(10);
    std::cout << "Size = " << varVect.size() << "; Capacity = " << varVect.capacity() << '\n';
    std::partial_sum(varVect.begin(), varVect.end(), std::back_inserter(varVect));
    for(const auto elem : varVect)
        std::cout << elem << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}