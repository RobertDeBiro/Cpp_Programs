#include <iostream>
#include <vector>

using namespace std;

class HashTable
{
    static const int hashGroups = 10; // Fixed number of buckets
    vector<pair<int, string>> table;
    vector<bool> isOccupied; // Keep track of which slots are occupied

public:
    HashTable() : table(hashGroups, {-1, ""}), isOccupied(hashGroups, false) {}

    bool isEmpty() const;
    int hashFunction(int key) const;
    void insertItem(int key, string value);
    void removeItem(int key);
    string searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const
{
    for (const auto& pair : isOccupied)
        if (pair) return false;
    return true;
}

int HashTable::hashFunction(int key) const
{
    return key % hashGroups; // Simple modulo hashing function
}

void HashTable::insertItem(int key, string value)
{
    int hashValue = hashFunction(key);
    int probeCount = 0;

    while (probeCount < hashGroups && isOccupied[hashValue])
    {
        if (table[hashValue].first == key)
        {
            // Key already exists, update value
            cout << "[WARNING] Key " << key << " exists. Value " << table[hashValue].second << " replaced.\n";
            table[hashValue].second = value;
            return;
        }

        // Linear probing: check the next slot
        hashValue = (hashValue + 1) % hashGroups;
        probeCount++;
    }

    if (probeCount >= hashGroups)
    {
        cout << "[ERROR] Hash table is full, cannot insert " << key << ".\n";
        return;
    }

    // Insert new key-value pair
    table[hashValue] = {key, value};
    isOccupied[hashValue] = true;
}

void HashTable::removeItem(int key)
{
    int hashValue = hashFunction(key);
    int probeCount = 0;

    while (probeCount < hashGroups && isOccupied[hashValue])
    {
        if (table[hashValue].first == key)
        {
            // Mark the slot as unoccupied
            isOccupied[hashValue] = false;
            table[hashValue] = {-1, ""}; // Clear the value
            cout << "[INFO] Item with key " << key << " removed.\n";
            return;
        }

        // Linear probing: check the next slot
        hashValue = (hashValue + 1) % hashGroups;
        probeCount++;
    }

    cout << "[WARNING] Key " << key << " not found, cannot remove.\n";
}

string HashTable::searchTable(int key)
{
    int hashValue = hashFunction(key);
    int probeCount = 0;

    while (probeCount < hashGroups && isOccupied[hashValue])
    {
        if (table[hashValue].first == key)
            return table[hashValue].second;

        // Linear probing: check the next slot
        hashValue = (hashValue + 1) % hashGroups;
        probeCount++;
    }

    return string(""); // Not found
}

void HashTable::printTable()
{
    for (int i = 0; i < hashGroups; i++)
    {
        if (isOccupied[i])
            cout << "[ " << i << " ] Key: " << table[i].first << " Value: " << table[i].second << "\n";
        else
            cout << "[ " << i << " ] Empty\n";
    }
}

int main()
{
    HashTable HT;

    if (HT.isEmpty())
        cout << "Hash table is empty\n";
    
    cout << "Inserting items...\n";
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

    cout << "Hash table:\n";
    HT.printTable();

    cout << "Removing item with key 332...\n";
    HT.removeItem(332);

    auto search_key = 12;
    auto found_string = HT.searchTable(search_key);
    if (!found_string.empty())
        cout << "Found: " << found_string << "\n";
    else
        cout << "String with key " << search_key << " not found!\n";

    return 0;
}
