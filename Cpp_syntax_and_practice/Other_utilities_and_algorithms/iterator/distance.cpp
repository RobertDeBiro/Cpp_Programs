/*
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

    //* Obtain container size
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    std::cout << "distance(first, last) = " << std::distance(v.begin(), v.end()) << '\n';
    
    //* Obtain container index for the particular iterator position
    int elem{ 4 };
    auto it_find{ std::find(v.begin(), v.end(), elem) };
    auto index{ std::distance(v.begin(), it_find) };
    std::cout << "Index of found element = " << index << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}