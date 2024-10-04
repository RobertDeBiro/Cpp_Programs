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

    // Transfer elements from 'varList2' to the position of the 'varList1.begin()'
    // i.e. to the beginning of the 'varList1'
    //  - after transfering there are no elements inside list from which elements are transfered
    varList1.splice(varList1.begin(), varList2);
    std::cout << "List2 spliced to the beginning of the List1: ";
    printList(varList1);
    std::cout << "List2 after splicing is empty: ";
    printList(varList2);

    std::cout << "--------------------------------------------------------\n";

    std::list<int> varList3 { 100, 200, 300, 400 };
    std::cout << "List3: ";
    printList(varList3);

    std::list<int> varList4 { 220, 280 };
    std::cout << "List4: ";
    printList(varList4);
    
    // 'std::list' iterator cannot traverse by using '+' operator, due to how it is internally implemented
    //! varList3.splice(varList3.begin() + 2, varList4);
    varList3.splice(std::next(varList3.begin(), 2), varList4);
    std::cout << "List4 spliced to the middle of the List3: ";
    printList(varList3);

    std::cout << "*****************************************************\n";
    return 0;
}
