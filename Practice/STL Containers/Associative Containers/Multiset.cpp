/*
 * std::multiset
 *  - SYNTAX:
 *      template<
 *          class Key,
 *          class Compare = std::less<Key>,
 *          class Allocator = std::allocator<Key>
 *      > class multiset;
 * 
 *  - std::multiset is an associative container that contains a sorted set of objects of type Key
 *  - std::multiset is the same as std::set, except multiple keys with equivalent values are allowed
 *  - sorting is done using the key comparison function Compare
 *  - search, removal, and insertion operations have logarithmic complexity
 *  - usually implemented as red-black trees
 *
 *  Capacity           Modifiers           Lookup          Observers
 *  - empty            - clear             - count         - key_comp
 *  - size             - insert            - find          - value_comp
 *  - max_size         - emplace           - contains
 *                     - emplace_hint      - equal_range
 *                     - erase             - lower_bound
 *                     - swap              - upper_bound
 *                     - extract
 *                     - merge
 */

#include <iostream>
#include <set>

template <typename T>
void printMultiset(T varSet)
{
    for(auto elem : varSet)
        std::cout << elem << ' ';
    std::cout << '\n';
}

// std::multiset functions
void initialization_and_assignment();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    std::cout << "*****************************************************\n";
    return 0;
}


void initialization_and_assignment()
{
    std::multiset<int> varMultiset1{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "Initial set container: \n";
    printMultiset(varMultiset1);

    std::multiset<int, std::less<>> varMultiset2{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::less set container: \n";
    printMultiset(varMultiset2);

    std::multiset<int, std::greater<>> varMultiset3{ 1, 8, 2, 8, 1, 9, 9};
    std::cout << "std::greater set container: \n";
    printMultiset(varMultiset3);

    std::cout << "------------------------------\n";
}