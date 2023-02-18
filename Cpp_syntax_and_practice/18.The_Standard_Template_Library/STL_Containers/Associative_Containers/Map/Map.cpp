/*
 * std::map
 *  - SYNTAX:
 *      template<
 *          class Key,
 *          class T,
 *          class Compare = std::less<Key>,
 *          class Allocator = std::allocator<std::pair<const Key, T>
 *      > class map;
 * 
 *  - std::map is an associative container that contains a sorted list of key-value pairs with unique keys
 *  - sorting is done using the key comparison function Compare
 *  - search, removal, and insertion operations have logarithmic complexity
 *  - std::map is generally used in Dictionary type problems
 *  - usually implemented as red-black trees
 *
 *  Element access          Capacity            Modifiers           Lookup          Observers
 *  + at                    - empty             - clear             - count         - key_comp
 *  + operator[]            + size              + insert            - find          - value_comp
 *                          - max_size          - insert_or_assign  - contains
 *                                              - emplace           - equal_range
 *                                              - emplace_hint      - lower_bound
 *                                              - erase             - upper_bound
 *                                              - swap
 *                                              - extract
 *                                              - merge
 */

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

// std::map functions
void initialization_and_assignment();
// Element access
void at_and_operator();
// Capacity
void size();
// Modifiers
void insert();
void erase();

int main()
{
    std::cout << "*****************************************************\n";

    initialization_and_assignment();

    // Element access
    at_and_operator();

    // Capacity
    size();

    // Modifiers
    insert();
    erase();

    std::cout << "*****************************************************\n";
    return 0;
}

void initialization_and_assignment()
{
    // Uniform initialization
    std::map<std::string, int> varMap1 { {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
    std::cout << "Map with uniform initialization: ";
    printMap(varMap1);

    // Initialization list
    std::map<std::string, int> varMap2 = { {"Marta", 29}, {"Toma", 2}, {"Luka", 4} };
    std::cout << "Map with initialization list: ";
    printMap(varMap2);

    // Assignment
    std::map<std::string, int> varMap3;
    varMap3 = { {"Real", 80}, {"Barca", 65}, {"Atletico", 60} };
    std::cout << "Map with assignment: ";
    printMap(varMap3);

    // If having several same keys only one will be assigned
    std::map<std::string, int> varMap4;
    varMap4 = { {"Real", 80}, {"Barca", 65}, {"Real", 60} };
    std::cout << "Map with duplicated keys: ";
    printMap(varMap4);

    std::map<std::string, int, std::greater<std::string>> varMap5 { {"CPU", 10}, {"GPU", 15}, {"RAM", 20} };
    std::cout << "Map initialized with std::greater: ";
    printMap(varMap5);

    std::cout << "------------------------------\n";
}

void at_and_operator()
{
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
    std::cout << "Sevilla score: " << varMap["Sevilla"] << "; Levante score: " << varMap.at("Levante") << '\n';

    /*
     * at(const Key& key) -> T&
     *  - returns a reference to the mapped value of the element with key equivalent to key
     *  - if no such element exists, an exception of type std::out_of_range is thrown
     */
    try
    {
        varMap.at("Getafe") = 10;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "Exception \"out_of_range\" is thrown!: ";
        std::cerr << e.what() << '\n';
    }

    std::cout << "------------------------------\n";
}

void size()
{
    std::map<std::string, int> varMap { {"Real", 80}, {"Barca", 65}, {"Atletico", 60}, };
    std::cout << "Initial map: ";
    printMap(varMap);
    std::cout << "Map size after initialization: " << varMap.size() << '\n';

    varMap = { {"Mallorca", 38} };
    std::cout << "Map after reassignment: ";
    printMap(varMap);
    std::cout << "Map size after reassignment: " << varMap.size() << '\n';

    std::cout << "------------------------------\n";
}

void insert()
{
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

    std::cout << "------------------------------\n";
}

void erase()
{
    std::map<std::string, int> varMap { {"Real", 80}, {"Barca", 65}, {"Atletico", 60}, };
    std::cout << "Initial map: ";
    printMap(varMap);

    varMap.erase("Barca");
    std::cout << "Map after erase: ";
    printMap(varMap);

    std::cout << "------------------------------\n";
}