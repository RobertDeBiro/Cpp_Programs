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

void printMap(const std::map<std::string, int, std::greater<std::string>>& varMap)
{
    for (const auto& n : varMap) {
        std::cout << '[' << n.first << "] = " << n.second << "; ";
    }
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::map<std::string, int> varMap { {"Real", 80}, {"Barca", 65}, {"Atletico", 60}, };
    std::cout << "Initial map: ";
    printMap(varMap);
    std::cout << "Map size after initialization: " << varMap.size() << '\n';

    varMap = { {"Mallorca", 38} };
    std::cout << "Map after reassignment: ";
    printMap(varMap);
    std::cout << "Map size after reassignment: " << varMap.size() << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
