/*
 * count( const Key& key ) const -> size_type
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/multimap/count
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

    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9} };
    std::cout << "Initial multimap: ";
    printMultimap(varMultimap);

    // Count number of paris that contain key 'a'
    std::cout << "Number of elements with key 'a': " << varMultimap.count('a') << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
