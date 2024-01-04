/*
 * template< class BidirIt >
 * reverse( BidirIt first, BidirIt last ) -> void
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/reverse
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::vector<int> v{1, 2, 3};
    std::cout << "Initial v: ";
    for (auto e : v)
        std::cout << e << ' ';
    std::cout << '\n';

    std::reverse(v.begin(), v.end());
    std::cout << "Reversed v: ";
    for (auto e : v)
        std::cout << e << ' ';
    std::cout << '\n';

    std::cout << "------------------------------------------------------------\n";
 
    int a[] = {4, 5, 6, 7};
    std::cout << "Initial a: "; 
    for (auto e : a)
        std::cout << e << ' ';
    std::cout << '\n';

    std::reverse(std::begin(a), std::end(a));
    std::cout << "Reversed a: "; 
    for (auto e : a)
        std::cout << e << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}