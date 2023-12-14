#include <iostream>
#include <string>
#include <map>

void printMap(const std::map<std::string, int>& varMap)
{
    // Iterate using C++17 facilities
    for (const auto& [key, value] : varMap) {
        std::cout << '[' << key << "] = " << value << "; ";
    }

    // C++11 alternative:
    // for (const auto& n : varMap) {
    //     std::cout << '[' << n.first << "] = " << n.second << "; ";
    // }
    // C++98 alternative
    //  for (std::map<std::string, int>::const_iterator it = varMap.begin(); it != varMap.end(); it++) {
    //      std::cout << it->first << " = " << it->second << "; ";
    //  }
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

    //********** Initialization **********
    // Uniform initialization
    std::map<std::string, int> varMap1 { {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
    std::cout << "Map with uniform initialization: ";
    printMap(varMap1);

    // Initialization list
    std::map<std::string, int> varMap2 = { {"Marta", 29}, {"Toma", 2}, {"Luka", 4} };
    std::cout << "Map with initialization list: ";
    printMap(varMap2);

    //********** Assignment **********
    std::map<std::string, int> varMap3;
    varMap3 = { {"Real", 80}, {"Barca", 65}, {"Atletico", 60} };
    std::cout << "Map with assignment: ";
    printMap(varMap3);

    // If having several equal keys only one will be assigned
    std::map<std::string, int> varMap4;
    varMap4 = { {"Real", 80}, {"Barca", 65}, {"Real", 60} };
    std::cout << "Map with duplicated keys: ";
    printMap(varMap4);

    //********** Sort elements by decreasing values **********
    std::map<std::string, int, std::greater<std::string>> varMap5 { {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
    std::cout << "Map initialized with std::greater: ";
    printMap(varMap5);

    std::cout << "*****************************************************\n";
    return 0;
}
