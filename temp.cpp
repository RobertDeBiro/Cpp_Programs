#include <list>

class HashTable
{
    static constexpr int hashGroups{ 10 };

    std::list<std::pair<int, std::string>> table[hashGroups];

public:
    bool isEmpty() const;

    int hashFunction(int key);

    void insertItem(int key, std::string value);

    void removeItem(int key);

    bool searchItem(int key);

    void printTable();
};