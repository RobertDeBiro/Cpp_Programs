/*
 * template< class InputIt >
 * distance( InputIt first, InputIt last ) -> typename std::iterator_traits<InputIt>::difference_type
 * 
 *  - with this function we can get index of container for the particular iterator position
 * 
 *  - included in <iterator>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/iterator/distance
 */

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() 
{
    std::cout << "*****************************************************\n";

    std::vector<int> v{ 1, 2, 3, 4, 5 };
    std::cout << "distance(first, last) = " << std::distance(v.begin(), v.end()) << '\n';
    
    int elem{ 4 };
    auto it_find{ std::find(v.begin(), v.end(), elem) };
    auto index{ std::distance(v.begin(), it_find) };
    std::cout << "Index of found element = " << index << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}