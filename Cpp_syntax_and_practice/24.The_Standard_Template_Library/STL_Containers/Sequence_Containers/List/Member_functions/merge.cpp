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

    std::list<int> varList1 { 1, 2, 3, 4, 5 };
    std::cout << "List1: ";
    printList(varList1);

    std::list<int> varList2 { 6, 7, 8, 9, 10 };
    std::cout << "List2: ";
    printList(varList2);

    varList1.merge(varList2);
    std::cout << "List2 merged to List1: ";
    printList(varList1);

    std::cout << "*****************************************************\n";
    return 0;
}
