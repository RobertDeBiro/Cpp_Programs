/*
 * Hash table:
 *  - a data structure that allows for a very fast retrieval of data, no matter how much data there is
 *  - it is implemented as a key=>value table
 *     - key and value can be any type of data structure
 *  - when constructing hash table collision can occur, and we can solve that in 2 ways:
 *     1) Open addressing - linear probing
 *     2) Closed addressing - chaining method using linked list
 *
 *  - more info:
 *     - https://www.youtube.com/watch?v=2_3fR-k-LzI&t=519s
 */

#include <iostream>
#include <list>
#include <cstring>

using namespace std;

// Example of hash table element that will be implemented: 905, Jimmy
//  - presents phonebook with key-value pair
//  - for resolving collision we are using linked list
class HashTable
{
    static const int hashGroups{ 10 }; // number of list that will be used
    list<pair<int, string>> table[hashGroups]; // array of list
    
public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const
{
    // Checking the size of every list in the hast table (in the array of lists)
    for (int i{}; i < hashGroups; i++)
        if (table[i].size() > 0) return false;
    return true;
}

// Our hash function must return number less then number of list that we are using
int HashTable::hashFunction(int key)
{
    return key % hashGroups; // If key is 905 function returns 5
}

void HashTable::insertItem(int key, string value)
{
    int hashValue = hashFunction(key); // Retrieve hash value by hashing the key
    auto& cell = table[hashValue]; // return back the list in which we will put our value
    bool keyExists = false; // will use it as a flag to see if the key already exist or not
    
    for (auto beginIt = begin(cell); beginIt != end(cell); beginIt++)
    {
        if(beginIt->first == key)
        {
            keyExists = true;
            beginIt->second = value; // if key exists, replace the value corresponding to that key
            cout << "[WARNING] Key exists. Value replaced." << endl;
            break;
            // each key inside list is unique, so when we find first that is equal, break from the loop
        }
    }

    // Since in this program we are not using close adressing, it is the same if we use emplace_back
    // or emplace_front
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
            //   - if we don't save that iterator to some variable, we could ultimately have
            //     a segmetation fault
            beginIt = cell.erase(beginIt);
            cout << "[INFO] Item removed." << endl;
            break;
        }
    }

    if (!keyExists)
        cout << "[WARNING] Key not found. Pair not removed." << endl;

    return;
}

void HashTable::printTable()
{
    for (int i{}; i < hashGroups; i++)
    {
        if(table[i].size() == 0) continue;

        for (auto beginIt = table[i].begin(); beginIt != table[i].end(); beginIt++)
        {
            cout << "[INFO] Key: " << beginIt->first << " Value: " << beginIt->second << endl;
        }
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
    
    std::cout << "---------------------------------------------------\n";

    std::cout << "Hash table: \n";
    HT.printTable();

    std::cout << "---------------------------------------------------\n";

    std::cout << "Removing items...\n";
    HT.removeItem(332);
    HT.removeItem(100);

    std::cout << "---------------------------------------------------\n";

    if (HT.isEmpty())
    {
        cout << ".....ERROR: Hash table empty.....\n";
    } else {
        cout << ".....Hash table not empty.....\n";
    }

    std::cout << "*****************************************************\n";
    return 0;
}