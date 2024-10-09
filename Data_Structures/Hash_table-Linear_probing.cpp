/*
 * Hash table:
 *  - a data structure that allows for a very fast retrieval of data, no matter how much data there is
 *  - it is implemented as a "key=>value" table
 *     - key and value can be any type of data structure
 *  - when constructing hash table collision can occur, and we can solve that in 2 ways:
 *     1) Open addressing - linear probing
 *     2) Closed addressing - chaining method using linked list
 */

#include <iostream>
#include <list>
#include <cstring>
#include <algorithm>

using namespace std;

/**
 * @brief Phonebook with "number-name" key-value pairs.
 * @details Example of hash table element that will be implemented: 905, Jimmy.
 *          For resolving collision we are using "linked list" approach.
 */
class HashTable
{
    /// @brief Number of lists that will be used within array (number of elements of array of lists)
    /// @details Using 'static' in order to use it for array length (array length must be compile-time constant)
    static const int hashGroups{ 10 };

    /// @brief Vector contianing key-value pairs
    vector<pair<int, string>> table;

    /// @brief Vector of booleans that keeps track of which slots are occupied
    vector<bool> isOccupied;
    
public:
    /// @brief Checks if 'HashTable' is empty i.e. there are no lists.
    /// @return true if there is at least one list fulfilled inside HashTable.
    /// @return false if all lists are empty.
    bool isEmpty() const;

    /// @brief Randomly returns index of array of lists
    /// @param key 'number'
    /// @return Index of array of lists
    int hashFunction(int key);
    
    /// @brief Inserts item (key-value pair) into the HashTable
    /// @param key Key of the item
    /// @param value Value of the item
    void insertItem(int key, string value);

    /// @brief Removes item from the HashTable
    /// @param key key of item required to remove
    void removeItem(int key);

    /// @brief Search item with corresponding key
    /// @param key Key of the searched item
    /// @return Value of the item with corresponding key
    string searchTable(int key);

    /// @brief Prints HashTable
    void printTable();
};

bool HashTable::isEmpty() const
{
    // Checking the size of every list in the hash table (in the array of lists)
    for (int i{}; i < hashGroups; i++)
        if (table[i].size() > 0) return false; // If at least one list is not empty, return false
    return true;
}

int HashTable::hashFunction(int key)
{
    // Our hash function must return number less then number of list that we are using
    //  - e.g. if key is 905 function returns 5
    return key % hashGroups;
}

void HashTable::insertItem(int key, string value)
{
    int hashValue = hashFunction(key); // retrieve hash value by hashing the key
    auto& cell = table[hashValue]; // return back the list in which we will put our value
    bool keyExists = false; // will use it as a flag to see if the key already exist or not
    
    for (auto beginIt = begin(cell); beginIt != end(cell); beginIt++)
    {
        if(beginIt->first == key)
        {
            keyExists = true;
            cout << "[WARNING] Key " << beginIt->first << " exists. Value " << beginIt->second << " replaced." << endl;
            beginIt->second = value; // if key exists, replace the value corresponding to that key
            break;
            // each key inside list is unique, so when we find first that is equal, break from the loop
        }
    }

    // Since in this program we are not using close addressing, it is the same if we use
    // 'emplace_back' or 'emplace_front'
    if (!keyExists)
        cell.emplace_back(key, value);

    return;
}

void HashTable::removeItem(int key)
{
    int hashValue = hashFunction(key); // Retrieve hash value by hashing the key
    auto& cell = table[hashValue]; // return back the list in which we will put our value
    bool keyExists = false; // will use it as a flag to see if the key already exist or not
    
    for (auto beginIt = begin(cell); beginIt != end(cell); beginIt++)
    {
        if(beginIt->first == key)
        {
            keyExists = true;
            // .erase() returns back iterator to the next position
            //   - if we don't save that iterator, we could ultimately
            //     have dangling iterator and segmetation fault
            beginIt = cell.erase(beginIt);
            cout << "[INFO] Item removed." << endl;
            break;
        }
    }

    if (!keyExists)
        cout << "[WARNING] Key not found. Pair not removed." << endl;

    return;
}

string HashTable::searchTable(int key)
{
    for (int i{}; i < hashGroups; i++)
    {
        if(table[i].size() == 0) continue;

        for (const auto& pair : table[i])
        {
            if (key == pair.first)
                return pair.second;
        }
    }
    return string("");
}

void HashTable::printTable()
{
    for (int i{}; i < hashGroups; i++)
    {
        if(table[i].size() == 0) continue;

        cout << "[ " << i << " ] ";

        for (auto beginIt = table[i].begin(); beginIt != table[i].end(); beginIt++)
        {
            cout << "Key: " << beginIt->first << " Value: " << beginIt->second << ";\t";
        }
        cout << endl;
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    HashTable HT;

    if (HT.isEmpty())
        cout << ".....Hash table empty.....\n";
    else
        cout << ".....ERROR: Hash table not empty.....\n" << endl;
    
    std::cout << "---------------------------------------------------\n";
    
    std::cout << "Inserting items...\n";
    HT.insertItem(905, "Jim");
    HT.insertItem(201, "Tom");
    HT.insertItem(332, "Bob");
    HT.insertItem(124, "Sally");
    HT.insertItem(107, "Sandy");
    HT.insertItem(929, "Barb");
    HT.insertItem(928, "Rob");
    HT.insertItem(928, "Rick");
    HT.insertItem(500, "Ivo");
    HT.insertItem(623, "Doc");
    HT.insertItem(12, "Alen");
    HT.insertItem(999, "Jo");
    
    std::cout << "---------------------------------------------------\n";

    std::cout << "Hash table: \n";
    HT.printTable();

    std::cout << "---------------------------------------------------\n";

    std::cout << "Removing items...\n";
    HT.removeItem(332);
    HT.removeItem(100);

    std::cout << "---------------------------------------------------\n";

    auto search_key = 12;
    auto found_string = HT.searchTable(search_key);
    if (!found_string.empty())
        cout << found_string << " found\n";
    else
        cout << "String with key " << search_key << " not found!\n";

    search_key = 13;
    found_string = HT.searchTable(search_key);
    if (!found_string.empty())
        cout << found_string << " found\n";
    else
        cout << "String with key " << search_key << " not found!\n";

    if (HT.isEmpty())
    {
        cout << ".....ERROR: Hash table empty.....\n";
    } else {
        cout << ".....Hash table not empty.....\n";
    }

    std::cout << "*****************************************************\n";
    return 0;
}
