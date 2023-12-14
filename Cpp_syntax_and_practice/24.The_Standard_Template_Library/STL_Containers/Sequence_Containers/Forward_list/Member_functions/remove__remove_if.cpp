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

    std::forward_list<int> varFwdList1 = {1, 100, 2, 3, 10, 1, 11, -1, 12};

    //* Remove elements and save amount of removed elements into 'count' variables
    auto count1 = varFwdList1.remove(1);
    std::cout << count1 << " elements equal to 1 were removed: ";
    printFwdList(varFwdList1);
 
    auto count2 = varFwdList1.remove_if([](int n){ return n > 10; });
    std::cout << count2 << " elements greater than 10 were removed: ";
    printFwdList(varFwdList1);

    std::cout << "*****************************************************\n";
    return 0;
}