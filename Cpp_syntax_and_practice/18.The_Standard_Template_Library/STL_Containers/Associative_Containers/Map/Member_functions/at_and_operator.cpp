/*
 * at(const Key& key) -> T&
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/map/at
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

    // Adding new values using operator[]
    varMap["Sevilla"] = 50;
    varMap["Levante"] = 30;
    std::cout << "Map after adding element with operator[]: ";
    printMap(varMap);

    // Changing existing value using operator[]
    // - note that only value can be changed inside a map, key cannot be changed!
    varMap["Real"] = 90;
    std::cout << "Changing the value of Real using operator[]: ";
    printMap(varMap);

    // Fetching elements using operator[] and .at()
    std::cout << "Fetching elements with operator[] and with .at(): ";
    std::cout << "Sevilla score: " << varMap["Sevilla"]
              << "; Levante score: " << varMap.at("Levante") << '\n';

    try
    {
        varMap.at("Getafe") = 10;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Exception \"out_of_range\" is thrown!: ";
        std::cerr << e.what() << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
