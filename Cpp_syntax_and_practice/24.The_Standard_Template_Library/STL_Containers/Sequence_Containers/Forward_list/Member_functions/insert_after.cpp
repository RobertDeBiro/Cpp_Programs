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

    std::forward_list<int> varFwdList1 { 2, 4, 6 };
    std::cout << "Initial forward list: ";
    printFwdList(varFwdList1);

    //* Insert element at the index '1' of the forward_list object
    //  - it is not possible to put on the beginning of the forward_list because we can insert
    //    elements only after existing elements (hence name 'insert_after()')
    varFwdList1.insert_after(varFwdList1.begin(), 3);
    printFwdList(varFwdList1);

    //* Insert element at the end of the forward_list object
    varFwdList1.insert_after(std::next(varFwdList1.begin(), 3), 7);
    printFwdList(varFwdList1);

    std::cout << "*****************************************************\n";
    return 0;
}