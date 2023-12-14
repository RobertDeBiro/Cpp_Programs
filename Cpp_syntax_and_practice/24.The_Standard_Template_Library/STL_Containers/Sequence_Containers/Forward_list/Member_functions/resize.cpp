#include <iostream>
#include <forward_list>

void printFwdList(const std::forward_list<int>& varFwdList)
{
    for(int elem : varFwdList)
        std::cout << elem << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "*****************************************************\n";

    std::forward_list<int> varFwdList1 { 2, 4, 6, 9, 10 };
    std::cout << "Initial forward list: ";
    printFwdList(varFwdList1);

    //* Resize to smaller amount of elements
    varFwdList1.resize(3);
    std::cout << "Forward list resized to smaller amount of elements: ";
    printFwdList(varFwdList1);

    //* Resize to bigger amount of elements
    varFwdList1.resize(7);
    std::cout << "Forward list resized to bigger amount of elements: ";
    printFwdList(varFwdList1);

    std::cout << "*****************************************************\n";
    return 0;
}