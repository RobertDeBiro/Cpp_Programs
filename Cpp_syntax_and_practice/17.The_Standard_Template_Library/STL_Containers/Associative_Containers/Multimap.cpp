/*
 * std::multimap
 *  - SYNTAX:
 *      template<
 *          class Key,
 *          class T,
 *          class Compare = std::less<Key>,
 *          class Allocator = std::allocator<std::pair<const Key, T>
 *      > class map;
 * 
 *  - std::multimap is an associative container that contains a sorted list of key-value pairs
 *  - sorting is done using the key comparison function Compare
 *  - search, removal, and insertion operations have logarithmic complexity
 *  - std::map is generally used in Dictionary type problems
 *  - usually implemented as red-black trees
 *
 *  Capacity            Modifiers           Lookup          Observers
 *  - empty             - clear             + count         - key_comp
 *  - size              - insert            + find          - value_comp
 *  - max_size          - emplace           - contains
 *                      - emplace_hint      + equal_range
 *                      - erase             - lower_bound
 *                      - swap              - upper_bound
 *                      - extract
 *                      - merge
 *  TODO - continue from 12:04
 */

#include <iostream>
#include <string>
#include <map>

void printMultimap(const std::multimap<char, int>& varMultimap)
{
    // Iterate using C++17 facilities
    for (const auto& [key, value] : varMultimap) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';
}

// std::multimap functions
void initialization_and_assignment();
// Lookup
void count();
void find();
void equal_range();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    // Lookup
    count();
    find();
    equal_range();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    // Uniform initialization
    //  - multiple equal key-value pairs are allowed
    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9}, {'a', 12} };
    std::cout << "Multimap with uniform initialization: ";
    printMultimap(varMultimap);

    std::cout << "------------------------------\n";
}

void count()
{
    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9} };
    std::cout << "Initial multimap: ";
    printMultimap(varMultimap);

    // Count number of paris that contain key 'a'
    std::cout << "Number of elements with key 'a': " << varMultimap.count('a') << '\n';

    std::cout << "------------------------------\n";
}

void find()
{
    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9} };
    std::cout << "Initial multimap: ";
    printMultimap(varMultimap);

    // Find pair that contains required key
    //  - I found on internet that it is not defined which pair will .find() return, but in this example
    //    it always return first pair that contains 'a'
    for(int i = 1; i<= 10; ++i)
    {
        auto pair{ varMultimap.find('a') };
        std::cout << "Found pair that contains 'a': " << '[' << pair->first << "] = " << pair->second << "\n";
    }
    
    std::cout << "------------------------------\n";
}

void equal_range()
{
    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9} };
    std::cout << "Initial multimap: ";
    printMultimap(varMultimap);

    /*
     * equal_range() returns 2 iterators as a pair:
     *   - 1. iterator points to the first element found in the range
     *   - 2. iterator points to the last element found in the range
     */
    std::pair<std::multimap<char, int>::iterator, std::multimap<char, int>::iterator> range = varMultimap.equal_range('a');
    std::cout << "Multimap with equal_range('a'): ";
    for(auto it = range.first; it != range.second; ++it)
        std::cout << '[' << it->first << "] = " << it->second << "; ";
    std::cout << '\n';

    std::cout << "------------------------------\n";
}