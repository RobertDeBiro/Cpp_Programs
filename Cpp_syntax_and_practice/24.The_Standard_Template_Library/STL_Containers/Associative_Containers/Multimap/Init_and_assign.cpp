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

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initialization **********
    // Uniform initialization
    //  - multiple equal keys allowed
    //  - multiple equal key-value pairs allowed
    std::multimap<char, int> varMultimap { {'a', 5}, {'b', 7}, {'a', 12}, {'b', 9}, {'a', 12} };
    std::cout << "Multimap with uniform initialization: ";
    printMultimap(varMultimap);

    std::cout << "*****************************************************\n";
    return 0;
}
