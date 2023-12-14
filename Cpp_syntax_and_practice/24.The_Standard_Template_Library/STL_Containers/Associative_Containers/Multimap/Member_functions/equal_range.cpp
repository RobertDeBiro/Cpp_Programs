/*
 * - returns 2 iterators as a pair:
 *   - 1. iterator points to the first element found in the range
 *   - 2. iterator points to the last element found in the range
 * - because multimap is always sorted, this function actually returns every appearance of required
 *   key
 *   - on the other side, function 'find()' returns only first appearance of required key
 */

#include <iostream>
#include <string>
#include <map>

void printMultimap(const std::multimap<char, int>& varMultimap)
{
    for (const auto& [key, value] : varMultimap) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9} , {'a', 12}};
    std::cout << "Initial multimap: ";
    printMultimap(varMultimap);

    using mapIt = std::multimap<char, int>::iterator;
    std::pair<mapIt, mapIt> range = varMultimap.equal_range('a');
    std::cout << "Multimap with equal_range('a'): ";
    for(auto it = range.first; it != range.second; ++it)
        std::cout << '[' << it->first << "] = " << it->second << "; ";
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
