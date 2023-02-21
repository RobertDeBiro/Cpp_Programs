/*
 * erase( iterator pos ) -> iterator
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/map/erase
 */

#include <iostream>
#include <string>
#include <map>

void printMap(const std::map<std::string, int>& varMap)
{
    for (const auto& [key, value] : varMap) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::map<std::string, int> varMap { {"Real", 80}, {"Barca", 65}, {"Atletico", 60}, };
    std::cout << "Initial map: ";
    printMap(varMap);

    varMap.erase("Barca");
    std::cout << "Map after erase: ";
    printMap(varMap);

    std::cout << "*****************************************************\n";
    return 0;
}
