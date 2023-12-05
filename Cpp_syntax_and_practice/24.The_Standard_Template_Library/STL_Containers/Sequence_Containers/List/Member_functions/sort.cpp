/*
 * sort() -> void
 *
 * References:
 *  - https://en.cppreference.com/w/cpp/container/list/sort
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

    std::list<int> varList { 3, 1, 5, 4, 2 };
    std::cout << "Initial list: ";
    printList(varList);

    varList.sort();
    std::cout << "Sorted list: ";
    printList(varList);

    std::cout << "*****************************************************\n";
    return 0;
}
