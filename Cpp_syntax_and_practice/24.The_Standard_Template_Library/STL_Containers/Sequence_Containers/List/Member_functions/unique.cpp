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

    std::list<int> varList { 1, 2, 3, 2, 4, 4, 5, 5, 1 };
    std::cout << "Initial list: ";
    printList(varList);

    // Remove '4' and '5'
    varList.unique();
    std::cout << "List after removing adjacent duplicates: ";
    printList(varList);

    std::cout << "*****************************************************\n";
    return 0;
}
