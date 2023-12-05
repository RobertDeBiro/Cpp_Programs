/*
 * insert( const value_type& value ) -> std::pair<iterator, bool>
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/map/insert
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

    // Using std::pair<type1, type2>(data1, data2)
    varMap.insert(std::pair<std::string, int>("Bilbao", 42));
    std::cout << "Map after inserting a pair: ";
    printMap(varMap);

    // Using std::make_pair(elem1, elem2)
    varMap.insert(std::make_pair("Valencia", 48));
    std::cout << "Map after inserting a pair using make_par: ";
    printMap(varMap);

    std::cout << "*****************************************************\n";
    return 0;
}
