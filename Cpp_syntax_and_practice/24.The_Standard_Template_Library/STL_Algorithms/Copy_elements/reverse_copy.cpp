/*
 * template< class BidirIt, class OutputIt >
 * reverse_copy( BidirIt first, BidirIt last, OutputIt d_first ) -> OutputIt
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/reverse_copy
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v{1, 2, 3};
    std::cout << "v: ";
    for (auto e : v)
        std::cout << e << ' ';
    std::cout << '\n';

    // We need to reserve to destination vector the same amount of elements we want to copy
    std::vector<int> destination(3);
    std::reverse_copy(v.begin(), v.end(), destination.begin());

    // We couldn't do following since reverse_copy() requires that the size of destination vector
    // is the same as initial vector, whereas here the capacity would be the same
    //  - the same is also required by copy() function
    // destination.reserve(3);

    std::cout << "destination: ";
    for (auto e : destination)
        std::cout << e << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}