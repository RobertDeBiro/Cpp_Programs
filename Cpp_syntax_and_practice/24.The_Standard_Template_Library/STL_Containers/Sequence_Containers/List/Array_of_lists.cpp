/*
 * Array of 'std::list<int>' syntax:
 *  - std::list<int> varList[3]
 * 
 * List of 'std::list<int>' syntax:
 *  - std::list<std::list<int>> varList
 */

#include <iostream>
#include <list>

void printList(const std::list<int>& varList)
{
    for(int elem : varList)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::list<int> varList[3];
    for (int i = 0; i < 3; i++)
    {
        varList[i] = {1 + i, 2 + i, 3 + i};
    }
    for (int i = 0; i < 3; i++)
    {
        std::cout << i + 1 << ". list in array: ";
        printList(varList[i]);
    }

    std::cout << "*****************************************************\n";
    return 0;
}
