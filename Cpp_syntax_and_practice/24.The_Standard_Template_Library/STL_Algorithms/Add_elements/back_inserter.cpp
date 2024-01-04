/*
 * std::back_inserter(Container& c) -> std::back_insert_iterator<Container>
 *  - returns a 'std::back_insert_iterator' which can be used to add elements
 *    to the end of the container 'c'
 *  - mostly used as an input parameter to other algorithms, such as:
 *      - std::fill_n
 *      - std::generate_n
 *  - note that it cannot be used with:
 *      - std::fill
 *      - std::generate
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/iterator/back_inserter
 */

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    // Declaring empty vector
    std::vector<int> v;
    
    // Add number '-1', '3' times, at the back of the vector
    //  - with 'std::back_inserter' we can fill empty vector area
    //  - we can do that only with 'std::fill_n', not with 'std::fill'
    std::fill_n(std::back_inserter(v), 3, -1);
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}