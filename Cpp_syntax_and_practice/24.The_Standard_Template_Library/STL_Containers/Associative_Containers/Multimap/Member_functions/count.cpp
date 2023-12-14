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

    // Count number of pairs that contain key 'a'
    std::cout << "Number of elements with key 'a': " << varMultimap.count('a') << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
